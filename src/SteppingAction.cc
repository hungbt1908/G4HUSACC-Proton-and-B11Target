#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "G4ParticleDefinition.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "g4root.hh"

SteppingAction::SteppingAction(const DetectorConstruction* detConstruction, EventAction* eventAction)
  : fDetConstruction(detConstruction), fEventAction(eventAction)
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{   
    //
    auto analysisManager = G4AnalysisManager::Instance();

    // scoring step in detector
    if(step->GetPreStepPoint()->GetPhysicalVolume()->GetName()=="physDetector")
    {
        auto touchable = (step->GetPreStepPoint()->GetTouchable());
        G4int detID = touchable->GetReplicaNumber(0);
        G4double edep = step->GetTotalEnergyDeposit();

        G4Track* track = dynamic_cast<G4Track*>(step->GetTrack());
        G4ParticleDefinition* particleDef = track->GetDefinition();
        G4String projname = particleDef->GetParticleName();

        // total edep
        fEventAction->AddEdepTotal(edep, detID);

        // 
        if(projname == "proton") fEventAction->AddEdepProton(edep, detID);
        else if(projname == "alpha") fEventAction->AddEdepAlpha(edep, detID);
        else if(projname == "Be8") fEventAction->AddEdepBe8(edep, detID);
        else if(projname == "B11") fEventAction->AddEdepB11(edep, detID);
        else if(projname == "B10") fEventAction->AddEdepB10(edep, detID);
        else if(projname == "gamma") fEventAction->AddEdepGamma(edep, detID);
        else if(projname == "neutron") fEventAction->AddEdepNeutron(edep, detID);
        else fEventAction->AddEdepOther(edep, detID);
    }
}