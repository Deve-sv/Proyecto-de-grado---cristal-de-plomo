#include "pmt.hh"

pmt_sens::pmt_sens(const G4String& name) : G4VSensitiveDetector(name){

    constexpr auto PMT_COLLECTION_NAME = "PMTCollection";
    collectionName.insert(PMT_COLLECTION_NAME);

	qeff = new G4PhysicsOrderedFreeVector();
	std::ifstream datafile;
	datafile.open("PMTeff.dat");

	while(1)
    {
		G4double wlen, pmtEff;

		datafile >> wlen >> pmtEff;
		if(datafile.eof())
			break;
		G4cout << wlen << " " << pmtEff << G4endl;
		qeff->InsertValues(wlen, pmtEff/100.);
        //G4cout << "QE(" << wlen << " nm) = " << qeff->Value(wlen) << G4endl;
	}

	datafile.close();
}

//----------------------------------------------------------------------
pmt_sens::~pmt_sens(){
}

//-------------------------------------------------------------------------
void pmt_sens::Initialize(G4HCofThisEvent*){

    pmtCollection = new pmtHitsCollection(SensitiveDetectorName, collectionName[0]);
}

//----------------------------------------------------------------------------
void pmt_sens::EndOfEvent(G4HCofThisEvent *collection){

    static G4int collectionIdentifier = -1;
    if (collectionIdentifier < 0){
        collectionIdentifier = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);    
    }
    collection->AddHitsCollection(collectionIdentifier, pmtCollection);
}

//-----------------------------------------------------------------------------
G4bool pmt_sens::ProcessHits(G4Step *aStep, G4TouchableHistory *){
    
    G4Track *track = aStep->GetTrack();

    G4ParticleDefinition *particle = aStep->GetTrack()->GetDefinition();
    if(particle != G4OpticalPhoton::OpticalPhotonDefinition()) return false;

    if (particle == G4OpticalPhoton::OpticalPhotonDefinition()){

        G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
        G4ThreeVector posPhoton = preStepPoint->GetPosition();
        G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
        G4double time = preStepPoint->GetGlobalTime();
        G4double nrg = preStepPoint->GetTotalEnergy();
        G4ThreeVector momPhoton = preStepPoint->GetMomentum();
        G4double wlen = (1.239841939*eV/momPhoton.mag())*1E+03;

        const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
        G4int copyNo = touchable->GetCopyNumber();

        if(G4UniformRand() < qeff->Value(wlen)){
   
            auto pmtHit = new pmt_hit();
            pmtHit->SetEventId(evt);
            pmtHit->SetPos(posPhoton);
            pmtHit->SetNrg(nrg);
            pmtHit->SetTime(time);
            pmtHit->SetCopyN(copyNo);
            pmtCollection->insert(pmtHit); 
        }
    }
    track->SetTrackStatus(fStopAndKill);
    return true;
}

void pmt_sens::clear(){
}

void pmt_sens::DrawAll(){
}

void pmt_sens::PrintAll(){
}

