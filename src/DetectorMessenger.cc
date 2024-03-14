#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"


DetectorMessenger::DetectorMessenger(DetectorConstruction* pDetConstruction)
    : G4UImessenger(), fDetConstruction(pDetConstruction)
{
    GeoDIR = new G4UIdirectory("/HUS/Geometry/");
    GeoDIR->SetGuidance("............................");

    //
    targetXYDimCmd = new G4UIcmdWithADoubleAndUnit("/HUS/Geometry/Target/SetTargetXYDim", this);
    targetXYDimCmd->SetGuidance("Set Target Size along X and Y axis.");
    targetXYDimCmd->SetParameterName("TargetXYDim", false);
    targetXYDimCmd->SetUnitCategory("Length");
    targetXYDimCmd->SetRange("TargetXYDim>0.0");
    targetXYDimCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    //
    targetZThickCmd = new G4UIcmdWithADoubleAndUnit("/HUS/Geometry/Target/SetTargetZThick", this);
    targetZThickCmd->SetGuidance("Set Target Size along Z axis.");
    targetZThickCmd->SetParameterName("TargetZThick", false);
    targetZThickCmd->SetUnitCategory("Length");
    targetZThickCmd->SetRange("TargetZThick>0.0");
    targetZThickCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    //
    baseXYDimCmd = new G4UIcmdWithADoubleAndUnit("/HUS/Geometry/Target/SetBaseXYDim", this);
    baseXYDimCmd->SetGuidance("Set Base Size along X and Y axis.");
    baseXYDimCmd->SetParameterName("BaseXYDim", false);
    baseXYDimCmd->SetUnitCategory("Length");
    baseXYDimCmd->SetRange("BaseXYDim>0.0");
    baseXYDimCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    //
    baseZThickCmd = new G4UIcmdWithADoubleAndUnit("/HUS/Geometry/Target/SetBaseZThick", this);
    baseZThickCmd->SetGuidance("Set Base Size along Z axis.");
    baseZThickCmd->SetParameterName("BaseZThick", false);
    baseZThickCmd->SetUnitCategory("Length");
    baseZThickCmd->SetRange("BaseZThick>0.0");
    baseZThickCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    //
    targetRotationAngleCmd = new G4UIcmdWithADoubleAndUnit("/HUS/Geometry/Target/SetTargetAngle", this);
    targetRotationAngleCmd->SetGuidance("Set Target Rotation Angle");
    targetRotationAngleCmd->SetParameterName("TargetAngle", false);
    targetRotationAngleCmd->SetUnitCategory("Angle");
    //targetRotationAngleCmd->SetRange("TargetAngle>0.0");
    targetRotationAngleCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    //
    det0AngleCmd = new G4UIcmdWithADoubleAndUnit("/HUS/Geometry/Detector/SetDet0Angle", this);
    det0AngleCmd->SetGuidance("Set DET 0 Rotation Angle");
    det0AngleCmd->SetParameterName("Det0Angle", false);
    det0AngleCmd->SetUnitCategory("Angle");
    //det0AngleCmd->SetRange("Det0Angle>0.0");
    det0AngleCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    //
    det1AngleCmd = new G4UIcmdWithADoubleAndUnit("/HUS/Geometry/Detector/SetDet1Angle", this);
    det1AngleCmd->SetGuidance("Set DET 1 Rotation Angle");
    det1AngleCmd->SetParameterName("Det1Angle", false);
    det1AngleCmd->SetUnitCategory("Angle");
    //det1AngleCmd->SetRange("Det1Angle>0.0");
    det1AngleCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    //
    det2AngleCmd = new G4UIcmdWithADoubleAndUnit("/HUS/Geometry/Detector/SetDet2Angle", this);
    det2AngleCmd->SetGuidance("Set DET 2 Rotation Angle");
    det2AngleCmd->SetParameterName("Det2Angle", false);
    det2AngleCmd->SetUnitCategory("Angle");
    //det2AngleCmd->SetRange("Det2Angle>0.0");
    det2AngleCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    //
    det3AngleCmd = new G4UIcmdWithADoubleAndUnit("/HUS/Geometry/Detector/SetDet3Angle", this);
    det3AngleCmd->SetGuidance("Set DET 3 Rotation Angle");
    det3AngleCmd->SetParameterName("Det3Angle", false);
    det3AngleCmd->SetUnitCategory("Angle");
    //det3AngleCmd->SetRange("Det3Angle>0.0");
    det3AngleCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    //
    det4AngleCmd = new G4UIcmdWithADoubleAndUnit("/HUS/Geometry/Detector/SetDet4Angle", this);
    det4AngleCmd->SetGuidance("Set DET 4 Rotation Angle");
    det4AngleCmd->SetParameterName("Det4Angle", false);
    det4AngleCmd->SetUnitCategory("Angle");
    //det4AngleCmd->SetRange("Det4Angle>0.0");
    det4AngleCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    //
    det5AngleCmd = new G4UIcmdWithADoubleAndUnit("/HUS/Geometry/Detector/SetDet5Angle", this);
    det5AngleCmd->SetGuidance("Set DET 5 Rotation Angle");
    det5AngleCmd->SetParameterName("Det5Angle", false);
    det5AngleCmd->SetUnitCategory("Angle");
    //det5AngleCmd->SetRange("Det5Angle>0.0");
    det5AngleCmd->AvailableForStates(G4State_PreInit, G4State_Idle); 
}

DetectorMessenger::~DetectorMessenger()
{   
    delete GeoDIR;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
    if(command == targetXYDimCmd)
    fDetConstruction->SetTargetXYDim(targetXYDimCmd->GetNewDoubleValue(newValue));

    if(command == targetZThickCmd)
    fDetConstruction->SetTargetThickness(targetZThickCmd->GetNewDoubleValue(newValue));

    if(command == baseXYDimCmd)
    fDetConstruction->SetBaseXYDim(baseXYDimCmd->GetNewDoubleValue(newValue));

    if(command == baseZThickCmd)
    fDetConstruction->SetBaseThickness(baseZThickCmd->GetNewDoubleValue(newValue));

    if(command == targetRotationAngleCmd)
    fDetConstruction->SetTargetAngle(targetRotationAngleCmd->GetNewDoubleValue(newValue));

    if(command == det0AngleCmd)
    fDetConstruction->SetDetAngle(0, det0AngleCmd->GetNewDoubleValue(newValue));

    if(command == det1AngleCmd)
    fDetConstruction->SetDetAngle(1, det1AngleCmd->GetNewDoubleValue(newValue));

    if(command == det2AngleCmd)
    fDetConstruction->SetDetAngle(2, det2AngleCmd->GetNewDoubleValue(newValue));
    
    if(command == det3AngleCmd)
    fDetConstruction->SetDetAngle(3, det3AngleCmd->GetNewDoubleValue(newValue));
    
    if(command == det4AngleCmd)
    fDetConstruction->SetDetAngle(4, det4AngleCmd->GetNewDoubleValue(newValue));
    
    if(command == det5AngleCmd)
    fDetConstruction->SetDetAngle(5, det5AngleCmd->GetNewDoubleValue(newValue));
}