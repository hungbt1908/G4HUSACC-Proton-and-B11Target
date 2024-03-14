#include "PhysicsList.hh"
#include "PhysicsListMessenger.hh"

#include "G4PhysicsListHelper.hh"
#include "G4ProcessManager.hh"

#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

#include "G4Gamma.hh"
#include "G4Proton.hh"
#include "G4Alpha.hh"
#include "G4He3.hh"
#include "G4Neutron.hh"

// gamma
#include "G4RayleighScattering.hh" //
#include "G4PenelopeRayleighModel.hh"
#include "G4LivermoreRayleighModel.hh"
#include "G4PhotoElectricEffect.hh" //
#include "G4PenelopePhotoElectricModel.hh"
#include "G4LivermorePhotoElectricModel.hh"
#include "G4ComptonScattering.hh" //
#include "G4PenelopeComptonModel.hh"
#include "G4LivermoreComptonModel.hh"
#include "G4KleinNishinaModel.hh"
#include "G4GammaConversion.hh" //
#include "G4PenelopeGammaConversionModel.hh"
#include "G4LivermoreGammaConversionModel.hh"
#include "G4BetheHeitler5DModel.hh"
#include "G4BetheHeitlerModel.hh" 
#include "G4PairProductionRelModel.hh"
#include "G4HadronInelasticProcess.hh" //
#include "G4PhotoNuclearProcess.hh"
//#include "G4LowEGammaNuclearModel.hh"
#include "G4CascadeInterface.hh"

// e-
#include "G4CoulombScattering.hh" //
#include "G4eSingleCoulombScatteringModel.hh"
#include "G4eMultipleScattering.hh" //
#include "G4UrbanMscModel.hh"
#include "G4GoudsmitSaundersonMscModel.hh"
#include "G4WentzelVIModel.hh"
#include "G4eIonisation.hh" //
#include "G4MollerBhabhaModel.hh"
#include "G4PenelopeIonisationModel.hh"
#include "G4LivermoreIonisationModel.hh"
#include "G4eBremsstrahlung.hh" //
#include "G4SeltzerBergerModel.hh"
#include "G4LivermoreBremsstrahlungModel.hh"
#include "G4eplusAnnihilation.hh" //

// proton
#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"
#include "G4CoulombScattering.hh"
#include "G4ProtonInelasticProcess.hh"
#include "G4HadronInelasticProcess.hh" //
#include "G4BGGNucleonInelasticXS.hh"
#include "G4ParticleInelasticXS.hh"
#include "G4CascadeInterface.hh"
#include "G4BinaryCascade.hh"
#include "G4QGSModel.hh"
#include "G4FTFModel.hh"
#include "G4HadronElasticProcess.hh" //
#include "G4BGGNucleonElasticXS.hh"
#include "G4ChipsElasticModel.hh"

#include "ProtonInelasticXS.hh"
#include "ProtonElasticXS.hh"
#include "G4ProtonInelasticCrossSection.hh"
#include "G4ChipsElasticModel.hh"

// alpha
#include "G4hMultipleScattering.hh" //
#include "G4ionIonisation.hh" //
#include "G4NuclearStopping.hh" //
#include "G4BinaryLightIonReaction.hh"
#include "G4CrossSectionInelastic.hh"
#include "G4CrossSectionElastic.hh"
#include "G4ComponentGGNuclNuclXsc.hh"
#include "G4HadronElastic.hh"

// He3
#include "G4HadronInelasticProcess.hh" //
#include "G4CrossSectionInelastic.hh"
#include "G4BinaryLightIonReaction.hh"
#include "G4HadronElasticProcess.hh" //
#include "G4CrossSectionElastic.hh"
#include "G4HadronElastic.hh"


// neutron
#include "G4HadronInelasticProcess.hh" //
#include "G4NeutronInelasticXS.hh"
#include "G4BinaryLightIonReaction.hh"
#include "G4HadronElasticProcess.hh" //
#include "G4NeutronElasticXS.hh"
#include "G4HadronElastic.hh"
//#include "G4NeutronCaptureProcess.hh" //
#include "G4NeutronCaptureXS.hh"
#include "G4NeutronRadCapture.hh"

// ions
#include "G4ionIonisation.hh"
#include "G4IonParametrisedLossModel.hh"

#include "G4HadronicParameters.hh"
#include "G4Decay.hh"



PhysicsList::PhysicsList()
  : G4VUserPhysicsList()
{
    fPhysicsListMessenger = new PhysicsListMessenger(this);
}

PhysicsList::~PhysicsList()
{
    delete fPhysicsListMessenger;
}

void PhysicsList::ConstructParticle()
{
    G4BosonConstructor bosonConst;
    bosonConst.ConstructParticle();

    G4LeptonConstructor leptonConst;
    leptonConst.ConstructParticle();

    G4MesonConstructor mesonConst;
    mesonConst.ConstructParticle();

    G4BaryonConstructor baryonConst;
    baryonConst.ConstructParticle();

    G4IonConstructor ionConst;
    ionConst.ConstructParticle();

    G4ShortLivedConstructor shortLivedConst;
    shortLivedConst.ConstructParticle();
}

void PhysicsList::ConstructProcess()
{
    G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
    ph->AddTransportation();
    auto particleIterator = GetParticleIterator();
    particleIterator->reset();

    while((*particleIterator)())
    {   
        // get the current particle definition
        G4ParticleDefinition* particle = particleIterator->value();
        G4String particleName = particle->GetParticleName();

        G4Decay* aDecay = new G4Decay();
        if (aDecay->IsApplicable(*particle)) ph->RegisterProcess(aDecay, particle);

        if (particleName == "gamma") 
        {
            // rayleigh
            G4RayleighScattering* raylProcess = new G4RayleighScattering();
            raylProcess->SetEmModel(new G4LivermoreRayleighModel());
            ph->RegisterProcess(raylProcess, particle);

            // photoelectric
            G4PhotoElectricEffect* photProcess = new G4PhotoElectricEffect();
            photProcess->SetEmModel(new G4LivermorePhotoElectricModel());
            ph->RegisterProcess(photProcess, particle);

            // compton
            G4ComptonScattering* comptProcess = new G4ComptonScattering();
            comptProcess->SetEmModel(new G4KleinNishinaModel());
            ph->RegisterProcess(comptProcess, particle);

            // conversion
            G4GammaConversion* convProcess = new G4GammaConversion();
            convProcess->SetEmModel(new G4BetheHeitlerModel());
            ph->RegisterProcess(convProcess, particle);

            // photo-nuclear
            G4PhotoNuclearProcess* photoNuclProcess = new G4PhotoNuclearProcess();
            G4CascadeInterface* theCascadeModel = new G4CascadeInterface();
            theCascadeModel->SetMaxEnergy(10*GeV);
            photoNuclProcess->RegisterMe(theCascadeModel);
            G4ProcessManager* gammaProcessManager = G4Gamma::Gamma()->GetProcessManager();
            gammaProcessManager->AddDiscreteProcess(photoNuclProcess);
        } 
        else if (particleName == "e-") 
        {
            // coulomb scattering
            G4CoulombScattering* eCoulombScatProcess = new G4CoulombScattering();
            eCoulombScatProcess->SetEmModel(new G4eSingleCoulombScatteringModel());
            ph->RegisterProcess(eCoulombScatProcess, particle);

            // msc
            G4eMultipleScattering* mscProcess = new G4eMultipleScattering();
            mscProcess->SetEmModel(new G4GoudsmitSaundersonMscModel());
            ph->RegisterProcess(mscProcess, particle);

            // ionisation
            G4eIonisation* eIoniProcess = new G4eIonisation();
            eIoniProcess->SetEmModel(new G4MollerBhabhaModel());
            ph->RegisterProcess(eIoniProcess,  particle);

            // bremsstrahlung
            G4eBremsstrahlung* eBremProcess = new G4eBremsstrahlung();
            eBremProcess->SetEmModel(new G4SeltzerBergerModel());
            ph->RegisterProcess(eBremProcess, particle);   
        } 
        else if (particleName == "e+") 
        {
            // coulomb scattering
            G4CoulombScattering* eCoulombScatProcess = new G4CoulombScattering();
            eCoulombScatProcess->SetEmModel(new G4eSingleCoulombScatteringModel());
            ph->RegisterProcess(eCoulombScatProcess, particle);

            // msc
            G4eMultipleScattering* eMscProcess = new G4eMultipleScattering();
            eMscProcess->SetEmModel(new G4UrbanMscModel());
            ph->RegisterProcess(eMscProcess, particle);

            // ionisation
            G4eIonisation* eIoniProcess = new G4eIonisation();
            eIoniProcess->SetEmModel(new G4MollerBhabhaModel());
            ph->RegisterProcess(eIoniProcess,  particle);

            // bremsstrahlung
            G4eBremsstrahlung* eBremProcess = new G4eBremsstrahlung();
            eBremProcess->SetEmModel(new G4SeltzerBergerModel());
            ph->RegisterProcess(eBremProcess, particle); 

            // annihilation
            G4eplusAnnihilation* eAnnihilProcess = new G4eplusAnnihilation();
            ph->RegisterProcess(eAnnihilProcess, particle);      
        }
        else if (particleName == "proton")
        {
            // EM
            ph->RegisterProcess(new G4hMultipleScattering, particle); 
            ph->RegisterProcess(new G4hIonisation, particle);
            ph->RegisterProcess(new G4hBremsstrahlung, particle);
            ph->RegisterProcess(new G4hPairProduction, particle);
            ph->RegisterProcess(new G4CoulombScattering, particle);

            // inelastic
            //G4HadronInelasticProcess* theProtonInelasticProcess = new G4HadronInelasticProcess("protonInelastic", G4Proton::Definition());
            G4ProtonInelasticProcess* theProtonInelasticProcess = new G4ProtonInelasticProcess("protonInelastic");
            // theProtonInelasticProcess->AddDataSet(new G4ProtonInelasticCrossSection());
            theProtonInelasticProcess->AddDataSet(new ProtonInelasticXS()); // G4ProtonInelasticCrossSection
            // Bertini Intranuclear Cascade Model
            // G4CascadeInterface* theBertiniCascadeModel = new G4CascadeInterface();
            // theBertiniCascadeModel->SetMinEnergy(0.*GeV);
            // theBertiniCascadeModel->SetMaxEnergy(6.*GeV);
            G4BinaryLightIonReaction* theBinaryLightModel = new G4BinaryLightIonReaction();
            theBinaryLightModel->SetMinEnergy(0.*GeV);
            theProtonInelasticProcess->RegisterMe(theBinaryLightModel);
            RegisterProcess(theProtonInelasticProcess, particle);

            // elastic
            G4HadronElasticProcess * theProtonElasticProcess = new G4HadronElasticProcess("hadElastic");
            //theProtonElasticProcess->AddDataSet(new G4BGGNucleonElasticXS(G4Proton::Definition()));
            theProtonElasticProcess->AddDataSet(new ProtonElasticXS()); //G4ChipsProtonElasticXS
            //theProtonElasticProcess->AddDataSet(new G4ChipsProtonElasticXS());
            theProtonElasticProcess->RegisterMe(new G4ChipsElasticModel());
            
            //
            G4ProcessManager* protonProcessManager = G4Proton::Proton()->GetProcessManager();
            protonProcessManager->AddDiscreteProcess(theProtonElasticProcess);
            protonProcessManager->AddDiscreteProcess(theProtonInelasticProcess);

        }
        else if (particleName == "alpha")
        {
            ph->RegisterProcess(new G4hMultipleScattering, particle);
            ph->RegisterProcess(new G4ionIonisation, particle);
            ph->RegisterProcess(new G4NuclearStopping, particle);

            // inelastic
            G4HadronInelasticProcess* theAlphaInelasticProcess = new G4HadronInelasticProcess("AlphaInelastic", G4Alpha::Alpha());
            G4CrossSectionInelastic* theAlphaInelasticCrossSection = new G4CrossSectionInelastic(new G4ComponentGGNuclNuclXsc());
            theAlphaInelasticCrossSection->SetMinKinEnergy(0.*eV);
            theAlphaInelasticCrossSection->SetMaxKinEnergy(25.6*PeV);
            theAlphaInelasticProcess->AddDataSet(theAlphaInelasticCrossSection);
            G4BinaryLightIonReaction* theAlphaInelasticModel = new G4BinaryLightIonReaction();
            theAlphaInelasticModel->SetMinEnergy(0.*eV);
            theAlphaInelasticModel->SetMaxEnergy(6.*GeV);
            theAlphaInelasticProcess->RegisterMe(theAlphaInelasticModel);
            
            // elastic
            G4HadronElasticProcess* theAlphaElasticProcess = new G4HadronElasticProcess("hadElastic");
            G4CrossSectionElastic* theAlphaElasticCrossSection = new G4CrossSectionElastic(new G4ComponentGGNuclNuclXsc());
            theAlphaElasticCrossSection->SetMinKinEnergy(0.*eV);
            theAlphaElasticCrossSection->SetMaxKinEnergy(25.6*PeV);
            theAlphaElasticProcess->AddDataSet(theAlphaElasticCrossSection);
            G4HadronElastic* theAlphaElasticModel = new G4HadronElastic("hElasticLHEP");
            theAlphaElasticModel->SetMinEnergy(0.*eV);
            theAlphaElasticModel->SetMaxEnergy(6.*GeV);
            theAlphaElasticProcess->RegisterMe(theAlphaElasticModel);

            //
            G4ProcessManager* alphaProcessManager = G4Alpha::Alpha()->GetProcessManager();
            alphaProcessManager->AddDiscreteProcess(theAlphaElasticProcess);
            alphaProcessManager->AddDiscreteProcess(theAlphaInelasticProcess);
        }
        else if (particleName == "He3")
        {
            // inelastic
            G4HadronInelasticProcess* theHe3InelasticProcess = new G4HadronInelasticProcess("He3Inelastic", G4He3::He3());
            G4CrossSectionInelastic* theHe3InelasticCrossSection = new G4CrossSectionInelastic(new G4ComponentGGNuclNuclXsc());
            theHe3InelasticCrossSection->SetMinKinEnergy(0.*eV);
            theHe3InelasticCrossSection->SetMaxKinEnergy(25.6*PeV);
            theHe3InelasticProcess->AddDataSet(theHe3InelasticCrossSection); // like FTFP-BERT, QGSP-BERT
            G4BinaryLightIonReaction* theHe3InelasticModel = new G4BinaryLightIonReaction();
            theHe3InelasticModel->SetMinEnergy(0.*eV);
            theHe3InelasticModel->SetMaxEnergy(6.*GeV);
            theHe3InelasticProcess->RegisterMe(theHe3InelasticModel);

            // elastic
            G4HadronElasticProcess* theHe3ElasticProcess = new G4HadronElasticProcess("hadElastic");
            G4CrossSectionElastic* theHe3ElasticCrossSection = new G4CrossSectionElastic(new G4ComponentGGNuclNuclXsc());
            theHe3ElasticCrossSection->SetMinKinEnergy(0.*eV);
            theHe3ElasticCrossSection->SetMaxKinEnergy(25.6*PeV);
            theHe3ElasticProcess->AddDataSet(theHe3ElasticCrossSection);
            G4HadronElastic* theHe3ElasticModel = new G4HadronElastic("hElasticLHEP");
            theHe3ElasticModel->SetMinEnergy(0.*eV);
            theHe3ElasticModel->SetMaxEnergy(100.*TeV);
            theHe3ElasticProcess->RegisterMe(theHe3ElasticModel);

            //
            G4ProcessManager* He3ProcessManager = G4He3::He3()->GetProcessManager();
            He3ProcessManager->AddDiscreteProcess(theHe3ElasticProcess);
            He3ProcessManager->AddDiscreteProcess(theHe3InelasticProcess);
        }
        else if (particleName == "neutron")
        {
            // inelastic
            G4HadronInelasticProcess* theNeutronInelasticProcess = new G4HadronInelasticProcess("neutronInelastic", G4Neutron::Neutron());
            G4NeutronInelasticXS* theNeutronInelasticCrossSection = new G4NeutronInelasticXS();
            theNeutronInelasticCrossSection->SetMinKinEnergy(0.*eV);
            theNeutronInelasticCrossSection->SetMaxKinEnergy(100.*TeV);
            theNeutronInelasticProcess->AddDataSet(theNeutronInelasticCrossSection);
            G4CascadeInterface* theNeutronInelasticModel = new G4CascadeInterface(); // Bertini Cascade model
            theNeutronInelasticModel->SetMinEnergy(1.*GeV);
            theNeutronInelasticModel->SetMaxEnergy(6.*GeV);
            theNeutronInelasticProcess->RegisterMe(theNeutronInelasticModel);
            G4BinaryCascade* theNeutronInelasticModel2 = new G4BinaryCascade(); // Binary Cascade model
            theNeutronInelasticModel2->SetMinEnergy(0.*eV);
            theNeutronInelasticModel2->SetMaxEnergy(1.5*GeV);
            theNeutronInelasticProcess->RegisterMe(theNeutronInelasticModel2);

            // elastic
            G4HadronElasticProcess* theNeutronElasticProcess = new G4HadronElasticProcess("hadElastic");
            G4NeutronElasticXS* theNeutronElasticCrossSection = new G4NeutronElasticXS();
            theNeutronElasticProcess->AddDataSet(theNeutronElasticCrossSection);
            theNeutronElasticCrossSection->SetMinKinEnergy(0.*eV);
            theNeutronElasticCrossSection->SetMaxKinEnergy(100.*TeV);
            G4HadronElastic* theNeutronElasticModel = new G4HadronElastic("hElasticCHIPS");
            theNeutronElasticModel->SetMinEnergy(0.*eV);
            theNeutronElasticModel->SetMaxEnergy(100.*TeV);
            theNeutronElasticProcess->RegisterMe(theNeutronElasticModel);

            //
            G4ProcessManager* theNeutronProcessManager = G4Neutron::Neutron()->GetProcessManager();
            theNeutronProcessManager->AddDiscreteProcess(theNeutronElasticProcess);
            theNeutronProcessManager->AddDiscreteProcess(theNeutronInelasticProcess);
        }
        else if (particleName == "GenericIon")
        {
            ph->RegisterProcess(new G4hMultipleScattering, particle);
            G4ionIonisation* ionIoni = new G4ionIonisation;
            ionIoni->SetEmModel(new G4IonParametrisedLossModel());
            ph->RegisterProcess(ionIoni, particle);
            ph->RegisterProcess(new G4NuclearStopping(), particle);
        }
        else if((!particle->IsShortLived()) &&
               (particle->GetPDGCharge() != 0.0) && 
               (particle->GetParticleName() != "chargedgeantino"))
        {
            // all others charged particles except geantino
            ph->RegisterProcess(new G4hMultipleScattering(), particle);
            ph->RegisterProcess(new G4hIonisation(), particle);
            ph->RegisterProcess(new G4NuclearStopping(), particle);
        }
    }
}