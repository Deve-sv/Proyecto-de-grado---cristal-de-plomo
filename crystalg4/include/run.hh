#ifndef RUN_HH 
#define RUN_HH

#include "G4UserRunAction.hh"
#include "globals.hh"

#include "G4Run.hh"
#include "G4Threading.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"

#include <cstdlib>
#include "analysis.hh"

class G4Run;

class run_act : public G4UserRunAction{

    public:
        explicit run_act();
        ~run_act() override;

        void BeginOfRunAction(const G4Run *run) override;
        void EndOfRunAction(const G4Run *run) override;
        auto GetOutputFile()->std::ofstream*;

    private:
        std::ofstream *outFile{nullptr};
        G4String fileName{"NULL"};
        G4int fRunID{-1};
        void OpenFile();
};
#endif
