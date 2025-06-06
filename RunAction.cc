#include "RunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include <string>

RunAction::RunAction()
 : G4UserRunAction()
{}

RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(const G4Run*)
{
    auto* analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile("spect_simulation.root");

    // Create ntuple with 48 columns: edep[0..15], xpos[0..15], ypos[0..15]
    analysisManager->CreateNtuple("datatree", "Crystal Energies + Pinhole Positions");

    for (G4int i = 0; i < 16; ++i) {
        analysisManager->CreateNtupleDColumn("edep" + std::to_string(i));
    }
    for (G4int i = 0; i < 16; ++i) {
        analysisManager->CreateNtupleDColumn("xpos" + std::to_string(i));
    }
    for (G4int i = 0; i < 16; ++i) {
        analysisManager->CreateNtupleDColumn("ypos" + std::to_string(i));
    }

    analysisManager->FinishNtuple();
}

void RunAction::EndOfRunAction(const G4Run*)
{
    auto* analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}