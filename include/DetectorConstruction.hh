#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4RotationMatrix.hh"

class G4NistManager;
class G4Isotope;
class G4Element;
class G4Material;
class G4VisAttributes;
class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class DetectorMessenger;

class DetectorConstruction : public G4VUserDetectorConstruction 
{
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();
    virtual G4VPhysicalVolume* Construct();
    void DefineMaterial();
    void DefineAttribute();
    G4VPhysicalVolume* ConstructVolume();
    void ConstructTarget();
    void ConstructDetector();
    void PrintInformation();
    inline const G4VPhysicalVolume* GetPhysDetector() const {return physDetector;};

public:
    void SetTargetAngle(G4double val);
    G4double GetTargetAngle();
    void SetTargetXYDim(G4double val);
    G4double GetTargetXYDim();
    void SetTargetThickness(G4double val);
    G4double GetTargetThickness();
    void SetBaseXYDim(G4double val);
    G4double GetBaseXYDim();
    void SetBaseThickness(G4double val);
    G4double GetBaseThickness();
    void SetDetAngle(int detID, G4double angle);
    
private:
    G4bool checkOverlap = true;
    G4double targetXYDim, targetZThick, baseXYDim, baseZThick, targetAngle;
    G4Box* solidTargetFrame, * solidTarget, * solidBackLayer;
    G4VPhysicalVolume* physTargetFrame, * physTarget, * physBackLayer;
    G4RotationMatrix* fTargetAngleRotationMatrix = nullptr;
    DetectorMessenger* fDetMessenger;

public:
    G4Material* Air, * Vacuum, * Si, * B11, * C3H6O2;
    G4LogicalVolume* logicWorld;
    G4VPhysicalVolume* physWorld, * physDetector;
    //G4double targetAngle;
    G4double frameXYDim, frameZThick;
    G4double thetaMat[6] = {0.*deg, 0.*deg, 0.*deg, 0.*deg, 0.*deg, 0.*deg};
};
#endif
