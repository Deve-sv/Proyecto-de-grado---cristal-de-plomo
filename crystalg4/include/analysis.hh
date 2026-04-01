#ifndef ANALYSIS_HH
#define ANALYSIS_HH

#include "globals.hh"
#include <vector>
#include "G4ThreeVector.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include <fstream>
#include <iomanip>

class pmt_analysis{

    public: 
        ~pmt_analysis();
        void BeginOfRun();
        void EndOfRun();
        void EndOfEvent(G4int flag);
        void Init();
        void Finish();
    
        void InsertPositionXY(G4double x, G4double y);
        void InsertNumber(G4int num);
        void InsertNrgDep(G4double dep);

        void setNtuple(G4int evt, G4double nrg, G4double time, G4int num);
        void setNtuple_lg(G4int evt, G4double z, G4double nrg, G4int type, G4int firstStep);

        static auto getInstance() -> pmt_analysis*;

    private:
        pmt_analysis();

        void Plot();
        static pmt_analysis *instance;
        G4String histogramFileName;
    
};
#endif
