#ifndef PMT_HH
#define PMT_HH

#include "G4VSensitiveDetector.hh"
#include "globals.hh"

#include "pmtHit.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalPhoton.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4PhysicsOrderedFreeVector.hh"
#include "G4ios.hh"

class G4HCofThisEvent;
class G4Step;

class pmt_sens : public G4VSensitiveDetector{

    public:
        explicit pmt_sens(const G4String& name);
        ~pmt_sens() override;

        G4bool ProcessHits(G4Step *step, G4TouchableHistory *history) override;
        void Initialize(G4HCofThisEvent *event) override;
        void EndOfEvent(G4HCofThisEvent *collection) override;

        void clear() override;
        void DrawAll() override;
        void PrintAll() override;

    private:
   
        pmtHitsCollection *pmtCollection;
        G4PhysicsOrderedFreeVector *qeff;

};
#endif
