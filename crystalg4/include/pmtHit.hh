#ifndef pmtHit_HH
#define pmtHit_HH

#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4Threading.hh"
#include "G4ThreeVector.hh"
#include "G4VHit.hh"

class pmt_hit : public G4VHit{

    public:
        explicit pmt_hit();
        ~pmt_hit() override;
        pmt_hit(const pmt_hit &right);

        //operators
        auto operator = (const pmt_hit &right)->const pmt_hit&;
        G4bool operator == (const pmt_hit &right) const;

        inline void* operator new(size_t);
        inline void operator delete(void *hit);

        //methods
        void Draw() override;
        void Print() override;

        //Set methods
        void SetEventId(G4int evt) { fevtId = evt;};
        void SetPos(G4ThreeVector xyz) {fPos = xyz;};
        void SetNrg(G4double nrg) {fNrg = nrg;};
        void SetTime(G4double time) {fTime = time;};
        void SetCopyN(G4int num) {fCopyN = num;};

        //Get methods
        G4int GetEventId() const{return fevtId; };
        G4ThreeVector GetPos() const {return fPos; };
        G4double GetNrg() const {return fNrg; };
        G4double GetTime() const {return fTime; };
        G4int GetCopyN() const {return fCopyN; }; 

    private:
        G4int fevtId = -1;
        G4ThreeVector fPos{G4ThreeVector(0.,0.,0.)};
        G4double fNrg=0;
        G4double fTime=0;
        G4int fCopyN=0;
        
};

using pmtHitsCollection = G4THitsCollection<pmt_hit>;
extern G4ThreadLocal G4Allocator<pmt_hit> *pmtHitAllocator;

//-----------------------------------------------------------------------
inline void* pmt_hit::operator new(size_t){
    if (pmtHitAllocator == nullptr){
        pmtHitAllocator = new G4Allocator<pmt_hit>;
    }
    return (void*) pmtHitAllocator->MallocSingle();
}


inline void pmt_hit::operator delete(void* hit){
  pmtHitAllocator->FreeSingle((pmt_hit*) hit);
}

#endif
