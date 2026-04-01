#include "event.hh"

event_act::event_act(run_act *runAct) : theRunAct(runAct){

    fMuonDecay=false;
}

event_act::~event_act(){
}


void event_act::BeginOfEventAction(const G4Event *event){

    fMuonDecay=false;

    G4int eventIdentifier = event->GetEventID();
    auto *sensDetMan = G4SDManager::GetSDMpointer();

    if(pmtCollectionId == -1){
        pmtCollectionId = sensDetMan->GetCollectionID("PMTCollection");    
    }
    if(lgCollectionId == -1){
        lgCollectionId = sensDetMan->GetCollectionID("LGCollection");    
    }
}

void event_act::EndOfEventAction(const G4Event *event){

    G4int eventIdentifier = event->GetEventID();

    if(theRunAct == nullptr){
        G4Exception("event_act::BeginOfEventAction()", "PMT0001", FatalException, "Null pointer to Run Action: this should not be");    
    }

    if(fMuonDecay){

        auto *collection = event->GetHCofThisEvent();
        pmtHitsCollection *pmtCollection{nullptr};
        lgHitsCollection *lgCollection{nullptr};

        pmt_analysis *analysis = pmt_analysis::getInstance();

        if (collection != nullptr){
            pmtCollection = (pmtHitsCollection*) (collection->GetHC(pmtCollectionId));
            lgCollection = (lgHitsCollection*) (collection->GetHC(lgCollectionId));

            if(pmtCollection != nullptr){
                G4int NoOfHits = pmtCollection->entries();
                //G4cout<<"Number of PMT hits in this event "<<NoOfHits<<G4endl;

                G4int evt;
                G4ThreeVector pos;
                G4double nrg;     
                G4double wlen;
                G4double time;
                G4int num;

                //cycle over all hits in this event
                for(auto i=0; i<NoOfHits; i++){
                    evt = (*pmtCollection)[i]->GetEventId();
                    pos = (*pmtCollection)[i]->GetPos();
                    nrg = (*pmtCollection)[i]->GetNrg();
                    time = (*pmtCollection)[i]->GetTime();
                    num = (*pmtCollection)[i]->GetCopyN();
                    //Fill Histograms of the Analysis Manager
                    analysis->InsertPositionXY((*pmtCollection)[i]->GetPos().x()/mm,(*pmtCollection)[i]->GetPos().y()/mm);
                    analysis->setNtuple(evt, nrg/keV, time/ns, num);
                }
                analysis->InsertNumber(NoOfHits);
                analysis->EndOfEvent(NoOfHits);  
            }  
            if (lgCollection){
                G4int NoOfHits_lg = lgCollection->entries();
                G4int evt_lg;
                G4ThreeVector pos_lg;
                G4double nrg_lg;     
                G4double nrg_dep_lg=0;
                G4int type;
                G4int firstStep;

                for(auto i=0; i<NoOfHits_lg; i++){
                    evt_lg = (*lgCollection)[i]->GetEventId();
                    pos_lg = (*lgCollection)[i]->GetPos();
                    nrg_lg = (*lgCollection)[i]->GetNrg();
                    nrg_dep_lg += (*lgCollection)[i]->GetNrgDep();
                    type = (*lgCollection)[i]->GetType();
                    firstStep = (*lgCollection)[i]->GetFirstStep();
                    //Fill tuples
                    analysis->setNtuple_lg(evt_lg,pos_lg.z()/mm,nrg_lg/MeV, type,firstStep);
                }
                analysis->InsertNrgDep(nrg_dep_lg);
            }
        }
    }
}
