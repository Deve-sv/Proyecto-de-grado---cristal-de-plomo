#include "run.hh"

run_act::run_act(){

    auto *manager = G4AnalysisManager::Instance();
    manager->SetDefaultFileType("root");
    manager->SetFirstHistoId(1);

    manager->SetNtupleMerging(true);

    manager->CreateH2("1", "Hits XY", 100, -300, 300, 100, -300, 300);

    manager->CreateH1("Number", "Number Phot", 100, 0, 1000);
    manager->CreateH1("NrgDep", "NrgDep", 100, 0, 200);
 
    manager->CreateNtuple("PMT", "PMT");
    manager->CreateNtupleIColumn("event");
    manager->CreateNtupleDColumn("energy");
    manager->CreateNtupleDColumn("time");
    manager->CreateNtupleIColumn("pmtNo");
    manager->FinishNtuple(0);

    manager->CreateNtuple("LG", "LG");
    manager->CreateNtupleIColumn("fEvent");
    manager->CreateNtupleDColumn("fZ");
    manager->CreateNtupleDColumn("fNrg");
    manager->CreateNtupleIColumn("fType");
    manager->CreateNtupleIColumn("fFirstStep");
    manager->FinishNtuple(1);
}

run_act::~run_act(){
}



void run_act::BeginOfRunAction(const G4Run *run){

    fRunID = run->GetRunID();

    //Master mode or sequential
    if (IsMaster()){
        G4cout << "### Run "<<run->GetRunID() << " starts (master)."<<G4endl;
    }
    else{
        G4cout << "### Run "<<run->GetRunID() << " starts (worker)." <<G4endl;
    }

    auto *analysis = pmt_analysis::getInstance();
    analysis->BeginOfRun();

}

void run_act::EndOfRunAction(const G4Run *run){

    G4cout << "End of Run "<<run->GetRunID()<<G4endl;
    auto *analysis = pmt_analysis::getInstance();
    analysis->EndOfRun();
}

