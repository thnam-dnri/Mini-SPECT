#ifndef SIM_MESSENGER_H
#define SIM_MESSENGER_H

#include "G4UImessenger.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4ThreeVector.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
class DetectorConstruction;
class PrimaryGeneratorAction;

class SimMessenger : public G4UImessenger {
public:
  SimMessenger(DetectorConstruction* det, PrimaryGeneratorAction* gen);
  ~SimMessenger() override;

  void SetNewValue(G4UIcommand* command, G4String newValue) override;

private:
  DetectorConstruction*        fDetector;
  PrimaryGeneratorAction*      fGenerator;
  G4UIcmdWith3Vector*          fOffsetCmd;
  G4UIcmdWith3VectorAndUnit*          fRotateCmd;
};

#endif // SIM_MESSENGER_H
