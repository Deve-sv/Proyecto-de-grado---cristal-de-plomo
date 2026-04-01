#ifndef STEPPING_HH
#define STEPPING_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "G4PhysicsOrderedFreeVector.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4OpticalPhoton.hh"
#include "G4MuonMinus.hh"
#include "G4MuonPlus.hh"
#include "G4ProcessManager.hh"
#include "G4ThreeVector.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"

#include "construction.hh"
#include "event.hh"

class step_act : public G4UserSteppingAction{

    public:
        step_act(event_act* eventAction);
        ~step_act();
  
        virtual void UserSteppingAction(const G4Step*);
  
  
    private:
        event_act *fEventAction;
  
};


#endif
