#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
#include "G4UImanager.hh"
#include "QBBC.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "Randomize.hh"


int main(int argc,char** argv)
{
    // Detect interactive mode (if no arguments) and define UI session
    //
    G4UIExecutive* ui = 0;
    if (argc == 1) 
    {
        ui = new G4UIExecutive(argc, argv);
    }

    // Choose the Random engine
    G4int seed =  time(NULL);
	G4Random::setTheSeed(seed);

    // Construct the default run manager
    //
    #ifdef G4MULTITHREADED
        G4MTRunManager* runManager = new G4MTRunManager;
    #else
        G4RunManager* runManager = new G4RunManager;
    #endif

    // Set mandatory initialization classes
    auto detConstruction = new DetectorConstruction();
	runManager->SetUserInitialization(detConstruction);
	auto physicsList = new PhysicsList();
	runManager->SetUserInitialization(physicsList);
	auto actionInitialization = new ActionInitialization(detConstruction);
	runManager->SetUserInitialization(actionInitialization);
	// runManager->Initialize();
    
    // Initialize visualization
    //
    G4VisManager* visManager = new G4VisExecutive;
    // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
    // G4VisManager* visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();

    // Get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    // Process macro or start UI session
    //
    if ( ! ui )
    { 
        // batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }
    else 
    { 
        // interactive mode
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }

    // Job termination
    // Free the store: user actions, physics_list and detector_description are
    // owned and deleted by the run manager, so they should not be deleted 
    // in the main() program !
  
  delete visManager;
  delete runManager;
}