#include "EventAction.hh"
#include "g4root.hh"

EventAction::EventAction()
	: G4UserEventAction()
{
	eDep = new eDepStruct[6];
}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction( const G4Event*)
{ 
	for(int i=0; i<6; i++)
	{
		eDep[i].TotalEDep = 0.;
		eDep[i].ProtonEDep = 0.;
		eDep[i].AlphaEDep = 0.;
		eDep[i].Be8EDep = 0.;
		eDep[i].B11EDep = 0.;
		eDep[i].B10EDep = 0.;
		eDep[i].NeutronEDep = 0.;
		eDep[i].GammaEDep = 0.;
		eDep[i].OtherEDep = 0.;
	}
}

void EventAction::EndOfEventAction(const G4Event*)
{
    auto analysisManager = G4AnalysisManager::Instance();

	// fill NTuple 0-5
	for(G4int i=0; i<6; i++)
	{	
		if(eDep[i].TotalEDep > 0.)
		{
			analysisManager->FillNtupleDColumn(i, 0, eDep[i].TotalEDep);
			analysisManager->FillNtupleDColumn(i, 1, eDep[i].ProtonEDep);
			analysisManager->FillNtupleDColumn(i, 2, eDep[i].AlphaEDep);
			analysisManager->FillNtupleDColumn(i, 3, eDep[i].Be8EDep);
			analysisManager->FillNtupleDColumn(i, 4, eDep[i].B11EDep);
			analysisManager->FillNtupleDColumn(i, 5, eDep[i].B10EDep);
			analysisManager->FillNtupleDColumn(i, 6, eDep[i].NeutronEDep);
			analysisManager->FillNtupleDColumn(i, 7, eDep[i].GammaEDep);
			analysisManager->FillNtupleDColumn(i, 8, eDep[i].OtherEDep);
			analysisManager->AddNtupleRow(i);
		}
	}
}