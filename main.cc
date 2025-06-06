#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "SimMessenger.hh"

int main(int argc, char** argv)
{
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    // Core run manager
    auto* runManager = new G4RunManager;

    // Set user initialization classes
    auto* detector = new DetectorConstruction();
    runManager->SetUserInitialization(detector);

    auto* physicsList = new PhysicsList();
    runManager->SetUserInitialization(physicsList);

    auto* generator = new PrimaryGeneratorAction();
    runManager->SetUserAction(generator);

    auto* runAction = new RunAction();
    runManager->SetUserAction(runAction);

    auto* eventAction = new EventAction(runAction, detector);
    runManager->SetUserAction(eventAction);

    runManager->SetUserAction(new SteppingAction(eventAction));

    // Create simulation messenger (handles UI commands)
    auto* simMessenger = new SimMessenger(detector, generator);

    // Initialize the run
    runManager->Initialize();

    // Visualization setup
    auto* visManager = new G4VisExecutive;
    visManager->Initialize();

    // UI manager
    auto* UImanager = G4UImanager::GetUIpointer();
    if (!ui) {
        // Batch mode
        G4String command = "/control/execute ";
        G4String macroFile = argv[1];
        UImanager->ApplyCommand(command + macroFile);
    } else {
        // Interactive mode
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }

    // Clean up
    delete visManager;
    delete runManager;
    return 0;
}