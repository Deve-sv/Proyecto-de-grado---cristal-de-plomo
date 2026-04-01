#ifndef EVENT_hh
#define EVENT_hh

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "run.hh"

#include "pmtHit.hh"
#include "lg_hit.hh"
#include "analysis.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UImanager.hh"
#include "G4UnitsTable.hh"
#include "G4VHitsCollection.hh"
#include "Randomize.hh"

class event_act : public G4UserEventAction{

    public:
        explicit event_act(run_act *runAct = nullptr);
        ~event_act() override;

        void BeginOfEventAction(const G4Event *event) override;
        void EndOfEventAction(const G4Event *event) override;

        void SetDrawFlag(G4String value){
            drawFlag=value;        
        };

        void SetMuonDecay(G4bool value){fMuonDecay = value;}

    private:
        G4int pmtCollectionId{-1};
        G4int lgCollectionId{-1};
        G4String drawFlag{"all"};
        run_act *theRunAct;
        
        G4bool fMuonDecay;

};
#endif
