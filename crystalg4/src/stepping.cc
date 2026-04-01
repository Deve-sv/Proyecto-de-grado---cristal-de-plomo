#include "stepping.hh"

step_act::step_act(event_act *eventAction){
    fEventAction = eventAction;
}
  
step_act::~step_act(){
}

void step_act::UserSteppingAction(const G4Step *step){
    G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  
    const crystal_construct *detectorConstruction = static_cast<const crystal_construct*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  
    G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();

    if(volume != fScoringVolume)
        return;

    G4ParticleDefinition *particle = step->GetTrack()->GetDefinition();

    if (particle == G4MuonMinus::MuonMinusDefinition()){
    
        if(step->GetPostStepPoint()){
            const G4VProcess *process = step->GetPostStepPoint()->GetProcessDefinedStep();

            if(process && process->GetProcessName() == "Decay"){
                fEventAction = (event_act*)(G4RunManager::GetRunManager()->GetUserEventAction());
                if(fEventAction){
                    fEventAction->SetMuonDecay(true);
                    //G4cout<<"Decay"<<G4endl;
                }
            }
        }
    }

    
}
