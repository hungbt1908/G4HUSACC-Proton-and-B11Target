#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

class G4NistManager;
class G4Isotope;
class G4Element;
class G4Material;
class G4VisAttributes;
class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;

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
    G4bool checkOverlap = false;
    G4Material* Air, * Vacuum, * Si, * B11, * C3H6O2;
    G4LogicalVolume* logicWorld;
    G4VPhysicalVolume* physWorld, * physDetector;
    G4double targetXYDim, targetZThick, baseXYDim, baseZThick;
    G4double targetAngle;
    G4double frameXYDim, frameZThick;
    G4double thetaMat[6] = {40.*deg, 70.*deg, 150.*deg, 233.*deg, 270.*deg, 330.*deg};
};
#endif
