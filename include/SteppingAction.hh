#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class DetectorConstruction;
class EventAction;

class SteppingAction : public G4UserSteppingAction
{
public:
    SteppingAction(const DetectorConstruction* detConstruction, EventAction* eventAction);
    ~SteppingAction() override = default;
    void UserSteppingAction(const G4Step* step) override;

private:
    const DetectorConstruction* fDetConstruction = nullptr;
    EventAction* fEventAction = nullptr;
};
#endif