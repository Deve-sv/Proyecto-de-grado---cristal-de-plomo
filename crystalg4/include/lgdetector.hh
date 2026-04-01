#ifndef LGDETECTOR_HH
#define LGDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4MuonMinus.hh"
#include "G4MuonPlus.hh"
#include "G4OpticalPhoton.hh"
#include "lg_hit.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4Step.hh"


class G4HCofThisEvent;
class G4Step;

class crystal_sens : public G4VSensitiveDetector{

    public:

        explicit crystal_sens(G4String name);
        ~crystal_sens() override ;

        G4bool ProcessHits(G4Step *step, G4TouchableHistory *history) override;
        void Initialize(G4HCofThisEvent *event) override;
        void EndOfEvent(G4HCofThisEvent *collection) override;

        void clear() override;
        void DrawAll() override;
        void PrintAll() override;
    
    private:

        lgHitsCollection *lgCollection;
    

};

#endif
