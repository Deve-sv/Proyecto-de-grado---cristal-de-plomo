#include "lg_hit.hh"

G4ThreadLocal G4Allocator<lg_hit> *lgHitAllocator{nullptr};

lg_hit::lg_hit(){
}

lg_hit::~lg_hit(){
}

lg_hit::lg_hit(const lg_hit &right){

    fevtId = right.fevtId;
    fPos = right.fPos;
    fNrg= right.fNrg;
    fNrgDep= right.fNrgDep;
    fType = right.fType;
    fFirstStep = right.fFirstStep;
}

auto lg_hit::operator=(const lg_hit &right)-> const lg_hit&{

    fevtId = right.fevtId;
    fPos = right.fPos;
    fNrg= right.fNrg;
    fNrgDep= right.fNrgDep;
    fType = right.fType;
    fFirstStep = right.fFirstStep;

    return *this;
}

G4bool lg_hit::operator==(const lg_hit &right) const{
    return (this==&right) ? true : false;
}

void lg_hit::Draw(){
}

void lg_hit::Print(){
    //G4cout<<fevtId<<fTime<<G4endl;
}
