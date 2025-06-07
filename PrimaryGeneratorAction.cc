#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4Gamma.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4ThreeVector.hh"
#include "G4RandomDirection.hh"
#include <cmath>

// ── Geometry definitions (matching phantom construction) ──
static const G4double kThyX = 0.4 * cm, kThyY = 0.4 * cm, kThyZ = 0.2 * cm;
static const G4double kBodyX = 3.5 * cm, kBodyY = 1.5 * cm, kBodyZ = 1.5 * cm;

static const G4ThreeVector kThyCenter(0, 0, 20.0 * cm);
static const G4ThreeVector kBodyCenter(0, 0, 20.0 * cm);

PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(new G4ParticleGun(1)),
   fSourceOffset(0, 0, 20 * cm)
{
    fParticleGun->SetParticleDefinition(G4Gamma::Definition());
    fParticleGun->SetParticleEnergy(364.0 * keV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    G4ThreeVector pos;
    G4double r = G4UniformRand();

    if (r < 0.5) {
        // 70% chance: generate within thyroid ellipsoid
        do {
            G4double x = (2.0 * G4UniformRand() - 1.0) * kThyX;
            G4double y = (2.0 * G4UniformRand() - 1.0) * kThyY;
            G4double z = (2.0 * G4UniformRand() - 1.0) * kThyZ;

            if ((x * x) / (kThyX * kThyX) +
                (y * y) / (kThyY * kThyY) +
                (z * z) / (kThyZ * kThyZ) <= 1.0) {
                pos = fSourceOffset + G4ThreeVector(x, y, z);
                break;
            }
        } while (true);
    } else {
        // 30% chance: generate in body excluding thyroid
        do {
            G4double x = (2.0 * G4UniformRand() - 1.0) * kBodyX;
            G4double y = (2.0 * G4UniformRand() - 1.0) * kBodyY;
            G4double z = (2.0 * G4UniformRand() - 1.0) * kBodyZ;

            if ((x * x) / (kBodyX * kBodyX) +
                (y * y) / (kBodyY * kBodyY) +
                (z * z) / (kBodyZ * kBodyZ) <= 1.0 &&
                (x * x) / (kThyX * kThyX) +
                (y * y) / (kThyY * kThyY) +
                (z * z) / (kThyZ * kThyZ) > 1.0) {
                pos = kBodyCenter + G4ThreeVector(x, y, z);
                break;
            }
        } while (true);
    }

    fParticleGun->SetParticlePosition(pos);
// Sample isotropic direction in the lower hemisphere (Z < 0)
G4ThreeVector dir;
do {
    dir = G4RandomDirection();  // uniformly on full sphere
} while (dir.z() > 0);          // reject if not in lower hemisphere

fParticleGun->SetParticleMomentumDirection(dir);
    fParticleGun->GeneratePrimaryVertex(anEvent);
}