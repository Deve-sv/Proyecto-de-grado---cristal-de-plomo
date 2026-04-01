#include "action.hh"

action_init::action_init() : G4VUserActionInitialization(){
}


void action_init::BuildForMaster() const{

    SetUserAction(new run_act());
}


void action_init::Build() const{

	SetUserAction(new generator);

	auto *theRunAct = new run_act();
	SetUserAction(theRunAct);

    auto *theEventAct = new event_act(theRunAct);
    SetUserAction(theEventAct);

    SetUserAction(new step_act(theEventAct));
}
