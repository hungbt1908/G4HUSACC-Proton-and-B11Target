#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

class G4VPhysicsConstructor;
class G4ProcessManager;
class PhysicsListMessenger;
class G4ParticleDefinition;
class G4Decay;
class G4RayleighScattering;
class G4LivermoreRayleighModel;
class G4PhotoElectricEffect;
class G4LivermorePhotoElectricModel;
class G4ComptonScattering;
class G4KleinNishinaModel;
class G4GammaConversion;
class G4BetheHeitlerModel;
class G4PhotoNuclearProcess;
class G4CascadeInterface;
class G4CoulombScattering;
class G4eSingleCoulombScatteringModel;
class G4eMultipleScattering;
class G4GoudsmitSaundersonMscModel;
class G4eIonisation;
class G4MollerBhabhaModel;
class G4eBremsstrahlung;
class G4SeltzerBergerModel;
class G4UrbanMscModel;
class G4eplusAnnihilation;
class G4hMultipleScattering;
class G4hIonisation;
class G4hBremsstrahlung;
class G4hPairProduction;
class G4HadronInelasticProcess;
class G4ParticleInelasticXS;
class G4HadronElasticProcess;
class G4BGGNucleonElasticXS;
class G4ChipsElasticModel;
class G4ionIonisation;
class G4NuclearStopping;
class G4CrossSectionInelastic;
class G4BinaryLightIonReaction;
class G4HadronElastic;
class G4CrossSectionElastic;
class G4NeutronInelasticXS;
class G4BinaryCascade;
class G4NeutronElasticXS;

class PhysicsList: public G4VUserPhysicsList
{
public:
    PhysicsList();
    virtual ~PhysicsList();
    virtual void ConstructParticle();
    virtual void ConstructProcess();

private:
    PhysicsListMessenger* fPhysicsListMessenger;

public:
    G4double elasticScaleFactor;
    G4double inelasticScaleFactor;

public:
    inline void SetElasticScaleFactor(G4double val) {elasticScaleFactor = val;}
    inline void SetInelasticScaleFactor(G4double val) {inelasticScaleFactor = val;}
};
#endif

