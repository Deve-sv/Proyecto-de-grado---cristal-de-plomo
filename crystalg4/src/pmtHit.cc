#include "pmtHit.hh"

G4ThreadLocal G4Allocator<pmt_hit> *pmtHitAllocator{nullptr};

pmt_hit::pmt_hit(){
}

pmt_hit::~pmt_hit(){
}

pmt_hit::pmt_hit(const pmt_hit &right){

    fevtId = right.fevtId;
    fPos = right.fPos;
    fNrg = right.fNrg;
    fTime = right.fTime;
    fCopyN = right.fCopyN;
}

auto pmt_hit::operator=(const pmt_hit &right)-> const pmt_hit&{

    fevtId = right.fevtId;
    fPos = right.fPos;
    fNrg = right.fNrg;
    fTime = right.fTime;
    fCopyN = right.fCopyN;

    return *this;
}


G4bool pmt_hit::operator==(const pmt_hit &right) const{
    return (this==&right) ? true : false;
}

void pmt_hit::Draw(){
}

void pmt_hit::Print(){
    //G4cout<<fevtId<<fTime<<G4endl;
}

