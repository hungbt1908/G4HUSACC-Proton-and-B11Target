#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4NistManager.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4RunManager.hh"

DetectorConstruction::DetectorConstruction()
    : G4VUserDetectorConstruction()
{
    fTargetAngleRotationMatrix = new G4RotationMatrix();
    fTargetAngleRotationMatrix->rotateY(targetAngle);

    fDetMessenger = new DetectorMessenger(this);
}

DetectorConstruction::~DetectorConstruction()
{
    delete fDetMessenger;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // clear old geometry
    G4GeometryManager::GetInstance()->OpenGeometry();
	G4PhysicalVolumeStore::GetInstance()->Clean();
	G4LogicalVolumeStore::GetInstance()->Clean();
	G4SolidStore::GetInstance()->Clean();

    DefineMaterial();
    return ConstructVolume();
}

void DetectorConstruction::DefineMaterial()
{
    G4NistManager* nistManager = G4NistManager::Instance();
    Air = nistManager->FindOrBuildMaterial("G4_AIR");
    Vacuum = nistManager-> FindOrBuildMaterial("G4_Galactic");
    B11 = new G4Material("B11", 5., 10.811*g/mole, 2.37*g/cm3);
    // C12
    G4Isotope* isoC12 = new G4Isotope("C12", 6, 12, 12.00*g/mole);
    G4Element* elC12 = new G4Element("C12","C12", 1);
    elC12->AddIsotope(isoC12, 100.*perCent);
    // H1
    G4Isotope* isoH1 = new G4Isotope("Hydro", 1, 1, 1.00*g/mole);
    G4Element* elH = new G4Element("Hyrdro" ,"H", 1);
    elH->AddIsotope(isoH1, 100.*perCent);
    // O16
    G4Isotope* isoO16 = new G4Isotope("O16", 8, 16, 16.00*g/mole);
    G4Element* elO16 = new G4Element("O16", "O16", 1);
    elO16->AddIsotope(isoO16, 100.*perCent);
    //
    C3H6O2 = new G4Material("Dioxolane", 0.932*g/cm3, 3);
    C3H6O2->AddElement(elC12, 3);
    C3H6O2->AddElement(elH, 6);
    C3H6O2->AddElement(elO16, 2);
    //
    Si = nistManager->FindOrBuildMaterial("G4_Si"); 
}

void DetectorConstruction::DefineAttribute()
{}

G4VPhysicalVolume* DetectorConstruction::ConstructVolume()
{
    // mother world volume
    G4Box* solidworld =  
        new G4Box("solidworld", 500.*cm, 500.*cm, 500.*cm);
    logicWorld = 
        new G4LogicalVolume(solidworld, Vacuum, "logicWorld");
    physWorld =  
        new G4PVPlacement(0, G4ThreeVector(), "physWorld", logicWorld, 0, false, checkOverlap);
    logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());

    // target volumes
    ConstructTarget();

    // detector volumes
    ConstructDetector();

    //
    DefineAttribute();
    PrintInformation();

    return physWorld;
}

void DetectorConstruction::ConstructTarget()
{
    frameZThick = targetZThick + baseZThick;
    frameXYDim = targetXYDim;
    // frame = target + base layer
    solidTargetFrame = 
        new G4Box("solidTargetFrame", 0.5*frameXYDim, 0.5*frameXYDim, 0.5*frameZThick);
    G4LogicalVolume* logicTargetFrame = 
        new G4LogicalVolume(solidTargetFrame, Vacuum, "logicTargetFrame");
    G4RotationMatrix rotm = G4RotationMatrix();
    rotm.rotateY(targetAngle);
    G4ThreeVector targetFramePos = G4ThreeVector(0,0,0);
    G4Transform3D targetFrameTrans = G4Transform3D(rotm, targetFramePos);
    physTargetFrame = 
        new G4PVPlacement(targetFrameTrans, logicTargetFrame, 
        "physTargetFrame", logicWorld, false, 0, checkOverlap);
    
    logicTargetFrame->SetVisAttributes(G4VisAttributes::GetInvisible());

    // target
    solidTarget =  
        new G4Box("Target", 0.5*targetXYDim, 0.5*targetXYDim, 0.5*targetZThick);
    G4LogicalVolume* logicTarget =
        new G4LogicalVolume(solidTarget, B11, "Target");
    G4double targetZPos = (-0.5*frameZThick + 0.5*targetZThick);
    physTarget =
        new G4PVPlacement(0, G4ThreeVector(0, 0, targetZPos), 
        logicTarget, "physTarget", logicTargetFrame, false, 0, checkOverlap);
    //
    G4VisAttributes* targetAtt = new G4VisAttributes(G4Colour(0. ,0. ,0.7));
    targetAtt->SetVisibility(true);
    targetAtt->SetForceSolid(true);
    logicTarget->SetVisAttributes(targetAtt);

    // base
    solidBackLayer = 
        new G4Box("solidBackLayer", 0.5*baseXYDim,  0.5*baseXYDim, 0.5*baseZThick);
    G4LogicalVolume* logicBackLayer =
        new G4LogicalVolume(solidBackLayer, C3H6O2, "logicBackLayer");
    G4double backLayerZPos = 0.5*frameZThick - 0.5*baseZThick;
    physBackLayer = 
        new G4PVPlacement(0, G4ThreeVector(0, 0, backLayerZPos), 
        logicBackLayer, "physBackLayer",  logicTargetFrame, false, 0, checkOverlap);
    //
    G4VisAttributes* baseAtt = new G4VisAttributes(G4Colour(0.5 ,0.5 ,0.5));
    baseAtt->SetVisibility(true);
    baseAtt->SetForceSolid(true);
    logicBackLayer->SetVisAttributes(baseAtt);
}

void DetectorConstruction::ConstructDetector()
{
    G4double detXDim = 10.*mm;
	G4double detYDim = 10.*mm;
	G4double detZThick = 0.30*mm;

    G4Box* solidDet = 
        new G4Box("solidDet", 0.5*detXDim, 0.5*detYDim, 0.5*detZThick);
    G4LogicalVolume* logicDet = 
        new G4LogicalVolume(solidDet, Si, "logicDet");
    for(int copyNo=0; copyNo<6; copyNo++)
    {
        G4double theta = 0.;
		G4double phi = 0.;
		G4ThreeVector uz;
        G4double detThick = 0.3*mm;
        G4double detTarDis = 6.2*cm;
        theta = thetaMat[copyNo];
        uz.setX(std::cos(phi)*std::sin(theta));
		uz.setY(std::sin(phi)*std::sin(theta));
		uz.setZ(std::cos(theta));
        G4ThreeVector detPos = (detTarDis + 0.5*detThick)*uz;
        G4RotationMatrix rotm = G4RotationMatrix();
        rotm.rotateY(theta);
        G4Transform3D trans = G4Transform3D(rotm, detPos);
        physDetector = 
            new G4PVPlacement(trans, logicDet, "physDetector", 
            logicWorld, false, copyNo, checkOverlap);
    } 
    G4VisAttributes* detAtt = new G4VisAttributes(G4Colour(1.0, 0., 0.));
    detAtt->SetVisibility(true);
    detAtt->SetForceSolid(true);
    logicDet->SetVisAttributes(detAtt); 
}

void DetectorConstruction::PrintInformation()
{}

void DetectorConstruction::SetTargetAngle(G4double val)
{
    targetAngle = val;
}

G4double DetectorConstruction::GetTargetAngle()
{
    return targetAngle;
}

void DetectorConstruction::SetTargetXYDim(G4double val)
{
    targetXYDim = val;
}

G4double DetectorConstruction::GetTargetXYDim()
{
    return targetXYDim;
}

void DetectorConstruction::SetTargetThickness(G4double val)
{
    targetZThick = val;
}

G4double DetectorConstruction::GetTargetThickness()
{
    return targetZThick;
}

void DetectorConstruction::SetBaseXYDim(G4double val)
{
    baseXYDim = val;
}

G4double DetectorConstruction::GetBaseXYDim()
{
    return baseXYDim;
}

void DetectorConstruction::SetBaseThickness(G4double val)
{
    baseZThick = val;
}

G4double DetectorConstruction::GetBaseThickness()
{
    return baseZThick;
}

void DetectorConstruction::SetDetAngle(int detID, G4double angle)
{
	thetaMat[detID] = angle;
}