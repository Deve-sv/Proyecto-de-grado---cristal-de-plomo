#include "physics.hh"

physics_list::physics_list(){

	RegisterPhysics (new G4EmStandardPhysics());
	RegisterPhysics (new G4OpticalPhysics());
	RegisterPhysics (new G4DecayPhysics());
}

physics_list::~physics_list(){
}
