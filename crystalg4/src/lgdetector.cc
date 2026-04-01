#include "lgdetector.hh"

crystal_sens::crystal_sens(G4String name) : G4VSensitiveDetector(name){
    
    constexpr auto DETEC_COLLECTION_NAME = "LGCollection";
    collectionName.insert(DETEC_COLLECTION_NAME);
}

crystal_sens::~crystal_sens(){
}

void crystal_sens::Initialize(G4HCofThisEvent *) {
    //Create Collection
    lgCollection = new lgHitsCollection(SensitiveDetectorName, collectionName[0]);
}


G4bool crystal_sens::ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist){

    G4ParticleDefinition *particle = aStep->GetTrack()->GetDefinition();

    if(particle == G4OpticalPhoton::OpticalPhotonDefinition()) {
        return false;
    }
    
    //Definition ------------------------------------
    G4int type=0;
    if (particle == G4MuonMinus::MuonMinusDefinition() || particle == G4MuonPlus::MuonPlusDefinition()){
        type = 1;
    }
    if (particle == G4Electron::ElectronDefinition() || particle == G4Positron::PositronDefinition()){
        type = 2;
    }

    //Step ---------------------------------------------
    G4bool isFirstStep = aStep->IsFirstStepInVolume();
    G4int firstStep = 0;
    //if(isFirstStep){firstStep=1;}

    const G4VProcess *proc = aStep->GetTrack()->GetCreatorProcess();
    const G4String& creator= proc ? proc->GetProcessName() : " ";
    //G4cout<<creator<<G4endl;
    if(creator=="Decay"){
        firstStep=1;
    }

    //Fill Data --------------------------------------------------
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4ThreeVector posPhoton = preStepPoint->GetPosition();
    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    G4double nrg = preStepPoint->GetTotalEnergy();
    G4double nrg_dep = aStep->GetTotalEnergyDeposit();

    auto lgHit = new lg_hit();
    lgHit->SetEventId(evt);
    lgHit->SetPos(posPhoton);
    lgHit->SetNrg(nrg);
    lgHit->SetNrgDep(nrg_dep);
    lgHit->SetType(type);
    lgHit->SetFirstStep(firstStep);
    lgCollection->insert(lgHit);

    return true;
}

void crystal_sens::EndOfEvent(G4HCofThisEvent *collection) {

   static G4int collectionIdentifier = -1;
    if (collectionIdentifier < 0){
        collectionIdentifier = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);    
    }
    collection->AddHitsCollection(collectionIdentifier, lgCollection);
}

void crystal_sens::clear(){
}

void crystal_sens::DrawAll(){
}

void crystal_sens::PrintAll(){
}
