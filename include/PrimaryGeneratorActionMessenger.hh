#ifndef PrimaryGeneratorActionMessenger_h
#define MPrimaryGeneratorActionMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class PrimaryGeneratorAction;
class G4UImessenger;
class G4UIdirectory;
class G4UIcmdWithAnInteger;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;

class PrimaryGeneratorActionMessenger : public G4UImessenger 
{
public:
	PrimaryGeneratorActionMessenger(PrimaryGeneratorAction* pPrimaryGeneratorAction);
	~PrimaryGeneratorActionMessenger(void);
	void SetNewValue(G4UIcommand* cmd, G4String newValue);

private:
	PrimaryGeneratorAction* fPrimaryGeneratorAction;
	G4UIdirectory* BeamDIR;
	G4UIcmdWithAnInteger* SetNOfParticleCmd;
	G4UIcmdWithADoubleAndUnit* SetBeamEnergyCmd;
	G4UIcmdWithADoubleAndUnit* SetBeamRadiusCmd;
	G4UIcmdWithADoubleAndUnit* SetBeamXPosCmd, * SetBeamYPosCmd, * SetBeamZPosCmd;
	G4UIcmdWithADoubleAndUnit* SetMinSolidAngleCmd, * SetMaxSolidAngleCmd;
	G4UIcmdWithADoubleAndUnit* SetPhiRotationAngleCmd, * SetThetaRotationAngleCmd;
};
#endif

