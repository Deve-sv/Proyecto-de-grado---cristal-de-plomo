#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"
#include "generator.hh"
#include "run.hh"
#include "event.hh"
#include "globals.hh"
#include "G4RunManager.hh"
#include "stepping.hh"

class action_init : public G4VUserActionInitialization{

    public:
    	explicit action_init();
	    ~action_init(){;};

        //virtual void Build() const override;
        //virtual void BuildForMaster() const override;
        void Build() const override;
        void BuildForMaster() const override;
};

#endif
