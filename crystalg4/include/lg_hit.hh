#ifndef LG_HIT_HH
#define LG_HIT_HH


#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4VHit.hh"

class lg_hit : public G4VHit{

    public:
        lg_hit();
        ~lg_hit() override;
        lg_hit(const lg_hit &right);

        auto operator = (const lg_hit &right)->const lg_hit&;
        G4bool operator == (const lg_hit &right) const;

        inline void* operator new(size_t);
        inline void operator delete(void *hit);

        //methods
        void Draw() override;
        void Print() override;

        //Add method
        inline void AddDepNrg(G4double value){
            fNrg += value;
        }

        //Set methods
        void SetEventId(G4int evt) { fevtId = evt;};
        void SetPos(G4ThreeVector xyz) {fPos = xyz;};
        void SetNrg(G4double nrg) {fNrg = nrg;};
        void SetNrgDep(G4double nrg_dep) {fNrgDep = nrg_dep;};
        void SetType(G4int type) {fType = type;};
        void SetFirstStep(G4int firstStep) {fFirstStep = firstStep;};

        //Get methods
        G4int GetEventId() const{return fevtId; };
        G4ThreeVector GetPos() const {return fPos; };
        G4double GetNrg() const {return fNrg; };
        G4double GetNrgDep() const {return fNrgDep; };
        G4int GetType() const {return fType;};
        G4int GetFirstStep() const {return fFirstStep;};

    private:
        G4int fevtId = -1;
        G4ThreeVector fPos{G4ThreeVector(0.,0.,0.)};
        G4double fNrg=0;
        G4double fNrgDep=0;
        G4int fType=0;
        G4int fFirstStep =0;

};

using lgHitsCollection = G4THitsCollection<lg_hit>;
extern G4ThreadLocal G4Allocator<lg_hit> *lgHitAllocator;

//-----------------------------------------------------------------------
inline void* lg_hit::operator new(size_t){
    if (lgHitAllocator == nullptr){
        lgHitAllocator = new G4Allocator<lg_hit>;
    }
    return (void*) lgHitAllocator->MallocSingle();
}


inline void lg_hit::operator delete(void* hit){
  lgHitAllocator->FreeSingle((lg_hit*) hit);
}


#endif
