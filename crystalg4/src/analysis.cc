#include "analysis.hh"

pmt_analysis *pmt_analysis::instance{nullptr};

pmt_analysis::pmt_analysis(){
} 

pmt_analysis::~pmt_analysis(){
    Finish();
}

void pmt_analysis::Init(){
}

void pmt_analysis::Finish(){
}

auto pmt_analysis::getInstance()-> pmt_analysis*{
    if (instance == nullptr){
        instance = new pmt_analysis();
    }
    return instance;
}


void pmt_analysis::InsertPositionXY(G4double x, G4double y){
    auto *manager = G4AnalysisManager::Instance();
    manager->FillH2(1, x, y);
}

void pmt_analysis::InsertNumber(G4int num){
    auto *manager = G4AnalysisManager::Instance();
    manager->FillH1(1, num);
}

void pmt_analysis::InsertNrgDep(G4double dep){
    auto *manager = G4AnalysisManager::Instance();
    manager->FillH1(2, dep);
}

void pmt_analysis::setNtuple(G4int evt, G4double nrg, G4double time, G4int num){
    auto *manager = G4AnalysisManager::Instance();
    manager->FillNtupleIColumn(0,0, evt);
    manager->FillNtupleDColumn(0,1, nrg);
    manager->FillNtupleDColumn(0,2, time);
    manager->FillNtupleIColumn(0,3, num);
    manager->AddNtupleRow(0);
}

void pmt_analysis::setNtuple_lg(G4int evt, G4double z, G4double nrg, G4int type, G4int firstStep){
    auto *manager = G4AnalysisManager::Instance();
    manager->FillNtupleIColumn(1,0, evt);
    manager->FillNtupleDColumn(1,1, z);
    manager->FillNtupleDColumn(1,2, nrg);
    manager->FillNtupleIColumn(1,3, type);
    manager->FillNtupleIColumn(1,4, firstStep);
    manager->AddNtupleRow(1);
}

void pmt_analysis::BeginOfRun(){

    G4RunManager *run = G4RunManager::GetRunManager();
    const G4Run *currentRun = run->GetCurrentRun();
    G4int runID = currentRun->GetRunID();
    std::stringstream strRunID;
    strRunID<<runID;
   
    histogramFileName = "../analysis/PMT_"+strRunID.str();

    auto *manager = G4AnalysisManager::Instance();
    manager->SetDefaultFileType("root");
    manager->OpenFile(histogramFileName);
}

void pmt_analysis::EndOfRun(){
    auto *manager = G4AnalysisManager::Instance();
    manager->Write();
    manager->CloseFile();
}

void pmt_analysis::EndOfEvent(G4int){
}











