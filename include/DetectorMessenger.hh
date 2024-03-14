#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class DetectorConstruction;

class DetectorMessenger: public G4UImessenger
{
public:
    DetectorMessenger(DetectorConstruction* );
    ~DetectorMessenger();
    void SetNewValue(G4UIcommand*, G4String);

private:
    G4UIdirectory* GeoDIR;
    G4UIcmdWithADoubleAndUnit* targetXYDimCmd;
    G4UIcmdWithADoubleAndUnit* targetZThickCmd;
    G4UIcmdWithADoubleAndUnit* baseXYDimCmd;
    G4UIcmdWithADoubleAndUnit* baseZThickCmd;
    G4UIcmdWithADoubleAndUnit* targetRotationAngleCmd;
    G4UIcmdWithADoubleAndUnit* det0AngleCmd;
    G4UIcmdWithADoubleAndUnit* det1AngleCmd;
    G4UIcmdWithADoubleAndUnit* det2AngleCmd;
    G4UIcmdWithADoubleAndUnit* det3AngleCmd;
    G4UIcmdWithADoubleAndUnit* det4AngleCmd;
    G4UIcmdWithADoubleAndUnit* det5AngleCmd;

    DetectorConstruction* fDetConstruction;
};
#endif