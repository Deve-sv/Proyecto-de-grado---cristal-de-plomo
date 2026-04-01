#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4MuonDecayChannelWithSpin.hh"
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"
#include "G4DecayTable.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "FTFP_BERT.hh"

class physics_list : public G4VModularPhysicsList{

public:		
	physics_list();
	~physics_list();
};

#endif
