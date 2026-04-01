#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4MTRunManager.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"


int main(int argc, char** argv){

#ifdef G4MULTITHREADED
    G4MTRunManager *runManager = new G4MTRunManager();
#else
	G4RunManager *runManager = new G4RunManager();
#endif

	runManager->SetUserInitialization(new crystal_construct());	
	runManager->SetUserInitialization(new physics_list());	
	runManager->SetUserInitialization(new action_init());
/*
	G4VModularPhysicsList *physics = new FTFP_BERT();
	physics->RegisterPhysics(new G4DecayPhysics());
	runManager->SetUserInitialization(physics);
*/
	//runManager->Initialize();

	G4UIExecutive *ui = 0;

	if(argc == 1){
		ui = new G4UIExecutive(argc, argv);
	}

	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();
	
	G4UImanager *UImanager = G4UImanager::GetUIpointer();

	if(ui){
		UImanager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();
	}
    else{
		G4String command = "/control/execute ";
		G4String filename = argv[1];
		UImanager->ApplyCommand(command+filename);
	}
    delete ui;
    delete visManager;
    delete runManager;

	return 0;
}
