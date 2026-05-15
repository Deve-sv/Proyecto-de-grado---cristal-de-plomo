#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4Cache.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4SDManager.hh"
#include "G4GenericMessenger.hh"
#include "G4SubtractionSolid.hh"

#include "pmt.hh"
#include "lgdetector.hh"

class pmt_sens;
class crystal_sens;

class crystal_construct : public G4VUserDetectorConstruction{

    public:
	    crystal_construct();
		~crystal_construct();

		virtual G4VPhysicalVolume *Construct();
        G4LogicalVolume *GetScoringVolume() const {return fScoringVolume;}
        
        void ConstructGlass();
	
	private:
        
        void DefineMaterials(); 
        virtual void ConstructSDandField();

        G4Material *leadGlass, *air, *Al, *pyrex;

        G4Box *solidWorld;
        G4Tubs *solidCover, *solidCrystal, *solidPMT, *solidLid, *solidBottom;

		G4LogicalVolume *logicWorld, *logicCrystal, *logicPMT, *logicCover, *logicLid, *logicBottom;
        G4LogicalVolume *fScoringVolume;

        G4VPhysicalVolume *physCover, *physWorld, *physCrystal, *physPMT, *physLid, *physBottom;

        G4GenericMessenger *fMessenger;
        G4bool pmt_top;

        G4Cache<pmt_sens*> pmtSD;
        G4Cache<crystal_sens*> lgSD;

};
#endif
