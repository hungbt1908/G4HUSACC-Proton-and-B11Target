#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"


ActionInitialization::ActionInitialization(DetectorConstruction* pDetConstruction)
    : fDetConstruction(pDetConstruction)
{}

void ActionInitialization::BuildForMaster() const
{
    SetUserAction(new RunAction());
}

void ActionInitialization::Build() const
{
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new RunAction());
    auto fEventAction = new EventAction();
    SetUserAction(fEventAction);
    auto fSteppingAction = new SteppingAction(fDetConstruction, fEventAction);
    SetUserAction(fSteppingAction);
}