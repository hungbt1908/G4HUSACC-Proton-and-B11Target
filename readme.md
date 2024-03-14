# ⭐ About this project:
- This project was implemented to simulate a proton-B11 experiment at HUS.
### 1. Geometry
- This simulation included 2 main geometrical components:
  - Target and base layer: The target layer and base layer are placed in a parent block (physFrame). The target is made of B11 and has three side dimensions of 1cm x 1cm x 324.786 nm. The base material is made from C3H6O2 with 3-dimensional dimensions of 1cm x 1 cm x 36.70 nm.
  - 6 detectors: The detectors have three-sided dimensions of 10x10x0.3 cm3 and are made of Si material placed around the target with rotation angles of 40; 70; 150; 233; 270; 330 degrees.

### 2. Physics
- In this application there are two main processes declared including EM and Hadron:
#### EM process:
1. **photon**:
    - Rayleigh Scattering: `G4RayleighScattering`, model: `G4LivermoreRayleighModel`
    - Photoelectric: `G4PhotoElectricEffect`, model: `G4LivermorePhotoElectricModel`
    - Compton Scattering: `G4ComptonScattering`, model: `G4KleinNishinaModel`
    - Gamma Conversion: `G4GammaConversion`, model: `G4BetheHeitlerModel`
    
2. **e-**:
   - Coulomb Scattering: `G4CoulombScattering`, model: `G4eSingleCoulombScatteringModel`
   - Multiple Scattering: `G4eMultipleScattering`, model:  `G4GoudsmitSaundersonMscModel`
   - Ionisation: `G4eIonisation`, model: `G4MollerBhabhaModel`
   - Bremsstrahlung: `G4eBremsstrahlung`, model: (default)
   
3. **e+**:
   - Coulomb Scattering: `G4CoulombScattering`, model: `G4eSingleCoulombScatteringModel`
   - Multiple Scattering: `G4eMultipleScattering`, model: `G4UrbanMscModel`
   - Ionisation: `G4eIonisation`, model: `G4MollerBhabhaModel`
   - Bremsstrahlung: `G4eBremsstrahlung`, model: (default)
   - Annihilation: `G4eplusAnnihilation`, model: (default)
   
4. **proton**:
   - Multiple Scattering: `G4hMultipleScattering`, model: (default)
   - Ionisation: `G4hIonisation`, model: (default)
   - Bremsstrahlung: `G4hBremsstrahlung`, model: (default)
   - Pair Production: `G4hPairProduction`, model: (default)
   - Coulomb Scattering: `G4CoulombScattering`, model: (default)

5. **alpha**:
   - Multiple Scattering: `G4hMultipleScattering`, model: (default)
   - Ionisation: `G4ionIonisation`, model: (default)
   - Nuclear Stopping: `G4NuclearStopping`, model: (default)

6. **He3**:
7. **Neutron**:
8. **GenericIon**:
   - Multiple Scattering: `G4hMultipleScattering`, model: (default)
   - Ionisation: `G4ionIonisation`, model: `G4IonParametrisedLossModel`
   - Nuclear stopping: `G4NuclearStopping`, model: (default)
#### Hadron:
1. **photon**:
- Photo-Nuclear:  
  - process: `G4PhotoNuclearProcess`
  - model: `G4CascadeInterface`
  - dataset: 
2. **proton**:
- Inelastic:
  - process: `G4ProtonInelasticProcess`
  - model: `G4BinaryLightIonReaction`
  - datasets: `ProtonInelasticXS` modified from `G4ProtonInelasticCrossSection`
- Elastic:
  - process: `G4HadronElasticProcess`
  - model: `G4ChipsElasticModel`
  - datasets: `ProtonElasticXS` modified from `G4ChipsProtonElasticXS`

3. **alpha**:
- Inelastic:
  - process: `G4HadronInelasticProcess("AlphaInelastic", G4Alpha::Alpha());`
  - model: `G4BinaryLightIonReaction`
  - datasets: `G4ComponentGGNuclNuclXsc`
- Elastic:
  - process: `G4HadronElasticProcess("hadElastic")`
  - model: `G4HadronElastic("hElasticLHEP")`
  - datasets: `G4ComponentGGNuclNuclXsc`

4. **He3**:
- Inelastic:
  - process: `G4HadronInelasticProcess("He3Inelastic", G4He3::He3())`
  - model: `G4BinaryLightIonReaction`
  - datasets: `G4ComponentGGNuclNuclXsc`
- Elastic:
  - process: `G4HadronElasticProcess("hadElastic")`
  - model: `G4HadronElastic("hElasticLHEP")`
  - datasets: `G4ComponentGGNuclNuclXsc`

5. **Neutron**:
- Inelastic:
  - process: `G4HadronInelasticProcess("neutronInelastic", G4Neutron::Neutron())`
  - model: `G4CascadeInterface` from 1 GeV to 6 GeV and `G4BinaryCascade` from 0 eV to 1.5 GeV
  - datasets: `G4NeutronInelasticXS`
- Elastic:
  - process: `G4HadronElasticProcess("hadElastic")`
  - model: `G4HadronElastic("hElasticCHIPS")`
  - datasets: `G4NeutronElasticXS`

#### Note: 
- To reduce simulation time, we increased the proton reaction cross section for elastic and inelastic processes simultaneously 1000 times in two classes `ProtonElasticXS` and `ProtonInelasticXS`.

### 3. Primary Generator
- The primary protons are initially constructed using the `G4ParticleGun` class. In one event, 100 protons are initialized. This value is set in the `particleGun->SetNumberOfParticles(100)` method. Users can change 100 to an arbitrary positive integer value.
- Other parameter settings of ParticleGun are built through the following commands:
  - Set the energy for the primary proton shooted to the target:
    ```c++
    /HUS/Beam/SetBeamEnergy 2.0 MeV
    ```
  - Set the size of the beam
    ```c++
    /HUS/Beam/SetBeamRadius 0.01 mm
    ```
  - Set the starting position of the beam:
    ```c++
    /HUS/Beam/SetBeamXPos  0. mm
    /HUS/Beam/SetBeamYPos  0. mm
    /HUS/Beam/SetBeamZPos -1. cm
    ```
  - Set up the proton emission angle distribution:
    ```c++
    /HUS/Beam/SetMinSolidAngle      0. deg
    /HUS/Beam/SetMaxSolidAngle      0.01 deg
    /HUS/Beam/SetThetaRotationAngle 0. deg
    /HUS/Beam/SetPhiRotationAngle   90. deg
    ```
### 4. Scoring
- The attribution method uses the UserAction class. The energy deposited for each step in the detector is recorded and accumulated for each event. This is then saved for each event to NTuple files.

### 5. Output and Analysis
- Results are saved in ROOT format. The energy deposition results in the 6 detectors are saved into 6 branches named **DetResults0;1** to **DetResults5;1**. Users can use the ROOT code named **plot.c** to plot the energy spectrum in the probe.
- In the **secondaries0;1** branch is information about secondary alpha particles produced by the reaction of interacting protons in target B11. To plot the kinetic energy spectrum information and spatial position distribution of alpha particles, users can run the file **alphaPlot.c** in ROOT.

# 🆕 Release notes:
- **03/14/2024: released version 1.0 (this version)**

---
# 🔧 Requirements:
* Geant4 version: 10.5.1
* Platform: Ubuntu 20.04
* Analsis tools: ROOT

---
# 🏃‍♂️ How to run:
* Run example in interactive mode
    ```c++
    ./sim
    ```
* Run example in batch mode
    ```c++
    ./sim
    ```
---
# 🚀 About Me:
**Bùi Tiến Hưng** - *hungbt1908@gmail.com*
1. Nuclear Engineering Lab, Hanoi University of Science and Technology (HUST).
2. Vietnam Atomic Energy Institute (VINATOM).

**Interestet Fields:**
* Medical physics, 
* Monte-Carlo simulation, 
* Machine learning.
---