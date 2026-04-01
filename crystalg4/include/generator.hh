#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4PhysicsOrderedFreeVector.hh"
#include "G4RunManager.hh"
#include "physics.hh"
#include "G4RandomDirection.hh"
#include "G4RandomTools.hh"
#include "G4GenericMessenger.hh"

class generator : public G4VUserPrimaryGeneratorAction{
    public:
        generator();
        ~generator();

        virtual void GeneratePrimaries(G4Event*);

    private:
        G4ParticleGun *fParticleGun;
        G4GenericMessenger *fMessenger;
        G4int deg;
};

#endif
