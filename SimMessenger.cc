#include "SimMessenger.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWith3Vector.hh"

SimMessenger::SimMessenger(DetectorConstruction* det,
                           PrimaryGeneratorAction* gen)
 : G4UImessenger(),
   fDetector(det),
   fGenerator(gen)
{
    // Create /simulation/ command directory
    auto* simDir = new G4UIdirectory("/simulation/");
    simDir->SetGuidance("Simulation control commands");

    // /simulation/offset command: set phantom & source global offset
    fOffsetCmd = new G4UIcmdWith3Vector("/simulation/offset", this);
    fOffsetCmd->SetGuidance("Set global offset for phantom & source");
    fOffsetCmd->SetParameterName("X", "Y", "Z", false);
    // Note: SetUnitCategory removed for compatibility
    fOffsetCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    // rotation command: takes 3 Euler angles (degrees)
    fRotateCmd = new G4UIcmdWith3VectorAndUnit("/simulation/rotate", this);
    fRotateCmd->SetGuidance("Set phantom rotation (deg) about X, Y, Z");
    fRotateCmd->SetParameterName("rotX","rotY","rotZ", false, false);
    fRotateCmd->SetUnitCandidates("deg rad mrad");
    fRotateCmd->SetDefaultUnit("deg");
    fRotateCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

SimMessenger::~SimMessenger()
{
    delete fOffsetCmd;
}

void SimMessenger::SetNewValue(G4UIcommand* cmd, G4String newValue)
{
    if (cmd == fOffsetCmd) {
        G4ThreeVector off = fOffsetCmd->GetNew3VectorValue(newValue);
        fDetector->SetPhantomOffset(off);
        fGenerator->SetSourceOffset(off);
    }
    else if ( cmd == fRotateCmd ) {
        G4ThreeVector rot = fRotateCmd->GetNew3VectorValue(newValue);
        fDetector->SetPhantomRotation(rot);
    }
}