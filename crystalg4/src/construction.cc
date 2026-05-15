#include "construction.hh"

crystal_construct::crystal_construct(){

    fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");
    fMessenger->DeclareProperty("pmt_top", pmt_top, "PMT position");

    pmt_top = false;

    DefineMaterials();
    pmtSD.Put(nullptr);
    lgSD.Put(nullptr);
}

crystal_construct::~crystal_construct(){
    delete fMessenger;
}


void crystal_construct::DefineMaterials(){

    G4NistManager *nist = G4NistManager::Instance();

    //Materials
    leadGlass = nist->FindOrBuildMaterial("G4_GLASS_LEAD");
	air = nist->FindOrBuildMaterial("G4_AIR");
	Al = nist->FindOrBuildMaterial("G4_Al");
	pyrex = nist->FindOrBuildMaterial("G4_Pyrex_Glass");

    //Properties
	const G4int nentries = 32;

	// photon energy matrix	
	G4double energy[nentries] = {
		1.77*eV, 1.84*eV, 1.90*eV, 1.97*eV, 2.03*eV, 2.10*eV, 2.16*eV, 2.23*eV,
		2.29*eV, 2.36*eV, 2.42*eV, 2.49*eV, 2.55*eV, 2.62*eV, 2.68*eV, 2.75*eV,
		2.81*eV, 2.88*eV, 2.94*eV, 3.01*eV, 3.07*eV, 3.14*eV, 3.20*eV, 3.27*eV,
		3.33*eV, 3.40*eV, 3.46*eV, 3.53*eV, 3.59*eV, 3.66*eV, 3.72*eV, 4.13*eV
	};

	// lead glass index refraction matrix 
	G4double rindexLG[nentries] = {
		1.75, 1.76, 1.77, 1.78, 1.79, 1.80, 1.81, 1.82, 1.83, 1.84,
		1.85, 1.86, 1.87, 1.88, 1.89, 1.90, 1.91, 1.92, 1.94, 1.96,
		1.98, 2.00, 2.02, 2.05, 2.07, 2.10, 2.12, 2.15, 2.18, 2.20,
		2.23, 2.26};

	// air index refraction matrix
	G4double rindexWorld[nentries] = {
		1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0
	};

	// pmt index refraction matrix
	G4double rindexPMT[nentries] = {
		1.46, 1.47, 1.47, 1.48, 1.48, 1.48, 1.49, 1.49, 1.50, 1.50,
		1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50,
		1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50,
		1.50, 1.50};

	// Absorption lengths (in mm) for PMT Borosilicate based 
	G4double absorptionLengthPMT[nentries] = {
		10*mm, 9*mm, 8*mm, 7*mm, 6*mm, 5*mm, 4.5*mm, 4*mm, 3.5*mm, 3*mm,
		2.8*mm, 2.6*mm, 2.4*mm, 2.2*mm, 2*mm, 1.8*mm, 1.6*mm, 1.5*mm, 1.4*mm, 1.3*mm,
		1.2*mm, 1.1*mm, 1.0*mm, 0.95*mm, 0.9*mm, 0.85*mm, 0.8*mm, 0.75*mm, 0.7*mm, 0.65*mm,
		0.6*mm, 0.55*mm};

	// photon absortion length matrix for Lead Glass 
	G4double absorptionLength[nentries] = {
		50.0*mm, 45.5*mm, 41.4*mm, 37.7*mm, 34.3*mm, 31.2*mm, 28.4*mm, 25.8*mm,
		23.5*mm, 21.4*mm, 19.5*mm, 17.7*mm, 16.1*mm, 14.7*mm, 13.4*mm, 12.2*mm,
		11.1*mm, 10.1*mm, 9.2*mm,  8.4*mm,  7.6*mm,  6.9*mm,  6.3*mm,  5.7*mm,
		5.2*mm,  4.7*mm,  4.3*mm,  3.9*mm,  3.6*mm,  3.3*mm,  3.0*mm,  1.0*mm
	};

	// Rayleigh Scattering Length (mm) for Lead Glass
	G4double rayleighLength[nentries] = {
		1500*mm, 1400*mm, 1300*mm, 1200*mm, 1100*mm, 950*mm, 800*mm, 700*mm, 600*mm, 500*mm,
		450*mm, 400*mm, 350*mm, 300*mm, 270*mm, 230*mm, 200*mm, 180*mm, 150*mm, 120*mm,
		100*mm, 80*mm, 65*mm, 50*mm, 40*mm, 30*mm, 25*mm, 20*mm, 15*mm, 12*mm,
		10*mm, 8*mm};
	// Define reflectivity (Tyvek is highly reflective, ~98%)
	G4double reflectivity[nentries] = { 
		0.98, 0.98, 0.98, 0.98,
		0.98, 0.98, 0.98, 0.98,
		0.98, 0.98, 0.98, 0.98,
		0.98, 0.98, 0.98, 0.98,
		0.98, 0.98, 0.98, 0.98,
		0.98, 0.98, 0.98, 0.98,
		0.98, 0.98, 0.98, 0.98,
		0.98, 0.98, 0.98, 0.98
	};
	
	// Define reflectivity (Aluminum is defined as poorreflective, ~0%)
	G4double reflectivityAl[nentries] = { 
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0
	};

    G4MaterialPropertiesTable *mptLG = new G4MaterialPropertiesTable();
	mptLG->AddProperty("RINDEX", energy, rindexLG, nentries);
	//mptLG->AddProperty("ABSLENGTH", energy, absorptionLength, nentries);
	mptLG->AddProperty("RAYLEIGH", energy, rayleighLength, nentries);
	leadGlass->SetMaterialPropertiesTable(mptLG);

    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", energy, rindexWorld, nentries);
	air->SetMaterialPropertiesTable(mptWorld); 

	G4MaterialPropertiesTable *mptPMT1 = new G4MaterialPropertiesTable();
	mptPMT1->AddProperty("RINDEX", energy, rindexPMT, nentries);
	//mptPMT1->AddProperty("ABSLENGTH", energy, absorptionLengthPMT, nentries);	
	pyrex->SetMaterialPropertiesTable(mptPMT1);

	
	G4MaterialPropertiesTable *AluminumMPT = new G4MaterialPropertiesTable();
	AluminumMPT->AddProperty("REFLECTIVITY", energy, reflectivityAl, nentries);
	Al->SetMaterialPropertiesTable(AluminumMPT);

}

//------------------------------------------------------
void crystal_construct::ConstructGlass(){

    //Fixed Values
        G4double innerRad = 0.0*cm;
	    G4double glass_outerRad = 25.0*cm; // 50 cm diameter
	    G4double glass_h = 32.0*cm;
	    G4double startAngle = 0.0*deg;
	    G4double spanningAngle = 360.0*deg;
        G4double inner_Al = 25.0*cm;
        G4double outer_Al = 25.1*cm;
        G4double Al_h = 32.1*cm;
        G4double pmt_diam = 12.7*cm;
        G4double pmt_h = 10.*cm; 
        G4double pmt_ypos = 10.*cm;

    //Solids
        solidCrystal =  new G4Tubs("solidCrsytal", innerRad, glass_outerRad, 0.5*glass_h, startAngle, spanningAngle);
   	    solidCover = new G4Tubs("solidCover", inner_Al, outer_Al, 0.5*Al_h, startAngle, spanningAngle);
        solidPMT = new G4Tubs("solidPMT", innerRad, 0.5*pmt_diam, 0.5*pmt_h, startAngle, spanningAngle);
        solidLid = new G4Tubs("solidLid", innerRad, inner_Al, 0.5*0.1*cm, startAngle, spanningAngle);
        solidBottom = new G4Tubs("solidBottom", innerRad, inner_Al, 0.5*0.1*cm, startAngle, spanningAngle);
        G4Tubs *reduct = new G4Tubs("reduct", innerRad, 0.5*pmt_diam,0.5*0.1*cm, startAngle, spanningAngle);

    //Substract
        G4ThreeVector yTrans(0.,pmt_ypos,0.);
        G4ThreeVector yTrans_2(0.,-pmt_ypos,0.);
        G4SubtractionSolid *solidBot_red = new G4SubtractionSolid("solidLid_red_2", solidBottom, reduct, 0, yTrans);
        G4SubtractionSolid *solidBot_red_2 = new G4SubtractionSolid("solidLid_red", solidBot_red, reduct, 0, yTrans_2);
        
    //Logics
        logicCrystal = new G4LogicalVolume(solidCrystal, leadGlass, "logicCrystal");
        logicCover = new G4LogicalVolume(solidCover, Al, "logicCover");
        logicPMT = new G4LogicalVolume(solidPMT, pyrex, "logicPMT");
        logicLid = new G4LogicalVolume(solidLid, Al, "logicLid");
        logicBottom = new G4LogicalVolume(solidBot_red_2, Al, "logicBottom");

        fScoringVolume = logicCrystal;

    //PhysVol
        physCrystal = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicCrystal, "physCrystal", logicWorld, false, 0, true);
        physCover = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicCover, "physCover", logicWorld, false, 0, true);
        physLid = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.5*glass_h+0.5*0.1*cm), logicLid, "physLid", logicWorld, false, 0, true);
        physPMT = new G4PVPlacement(0, G4ThreeVector(0.,pmt_ypos,-0.5*glass_h-0.5*pmt_h), logicPMT, "physPMT", logicWorld, false, 0, true);
        physPMT = new G4PVPlacement(0, G4ThreeVector(0.,-1*pmt_ypos,-0.5*glass_h-0.5*pmt_h), logicPMT, "physPMT", logicWorld, false, 1, true);
        physBottom = new G4PVPlacement(0, G4ThreeVector(0.,0.,-0.5*glass_h - 0.5*0.1*cm), logicBottom, "physBottom", logicWorld, false, 0, true); 

    //Optical Tyvek
        const G4int nentries = 32;
        G4double sigmaAlpha = 1.0; 
	    G4double energy[nentries] = {1.77*eV, 1.84*eV, 1.90*eV, 1.97*eV, 2.03*eV, 2.10*eV, 2.16*eV, 2.23*eV,2.29*eV, 2.36*eV, 2.42*eV, 2.49*eV, 2.55*eV, 2.62*eV, 2.68*eV, 2.75*eV, 2.81*eV, 2.88*eV, 2.94*eV, 3.01*eV, 3.07*eV, 3.14*eV, 3.20*eV, 3.27*eV, 3.33*eV, 3.40*eV, 3.46*eV, 3.53*eV, 3.59*eV, 3.66*eV, 3.72*eV, 4.13*eV};
        G4double reflectivity[nentries] = {0.98, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98,0.98, 0.98, 0.98, 0.98,	0.98, 0.98, 0.98, 0.98};

        G4MaterialPropertiesTable* tyvekMPT = new G4MaterialPropertiesTable();
	    tyvekMPT->AddProperty("REFLECTIVITY", energy, reflectivity, nentries);

	    G4OpticalSurface *tyvek = new G4OpticalSurface("TyvekSurface");
	    tyvek->SetType(dielectric_dielectric);
	    tyvek->SetModel(unified);             
	    tyvek->SetFinish(groundfrontpainted); 
	    tyvek->SetSigmaAlpha(sigmaAlpha); 
	    tyvek->SetMaterialPropertiesTable(tyvekMPT);
    
    	G4LogicalBorderSurface *glass_al_surface = new G4LogicalBorderSurface("glass_al_surface", physCrystal, physCover,tyvek);
    	G4LogicalBorderSurface *glass_lid_surface = new G4LogicalBorderSurface("glass_lid_surface", physCrystal, physLid,tyvek);
    	G4LogicalBorderSurface *glass_bot_surface = new G4LogicalBorderSurface("glass_bot_surface", physCrystal, physBottom,tyvek);
        
    //Vis Attributes
        G4VisAttributes *lgVisAtt = new G4VisAttributes(G4Color(0.12, 0.56, 1.0, 0.5));
	    lgVisAtt->SetForceSolid(true);
	    G4VisAttributes *pmtVisAtt = new G4VisAttributes(G4Color(0.3, 0.3, 0.3, 0.5));
	    pmtVisAtt->SetForceSolid(true);
	    G4VisAttributes *covVisAtt = new G4VisAttributes(G4Color(0.6, 0.6, 0.6, 0.5));
	    covVisAtt->SetForceWireframe(true);

	    logicCover->SetVisAttributes(covVisAtt);
	    logicCrystal->SetVisAttributes(lgVisAtt);
        logicPMT->SetVisAttributes(pmtVisAtt);


}


//-----------------------------------------------------------------------------
G4VPhysicalVolume *crystal_construct::Construct(){
	
	//World
	G4double xsize = 1.5 * m; 
	G4double ysize = 1.5 * m; 
	G4double zsize = 1.5 * m; 
	
	solidWorld = new G4Box("solidWorld", xsize, ysize, zsize);
	logicWorld = new G4LogicalVolume(solidWorld, air, "logicWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);

    ConstructGlass();

	return physWorld;
}

//----------------------------------------------------------------------------------
void crystal_construct::ConstructSDandField(){

    //Sensitive Detector:PMT
    if(pmtSD.Get() == nullptr){
        constexpr auto PMT_SENSITIVE_DET_NAME = "pmtSD";
        auto *sensitiveDetector = new pmt_sens(PMT_SENSITIVE_DET_NAME);
        pmtSD.Put(sensitiveDetector);
    }

    G4SDManager::GetSDMpointer()->AddNewDetector(pmtSD.Get());
    SetSensitiveDetector(logicPMT, pmtSD.Get());

    if(lgSD.Get() == nullptr){
        constexpr auto LG_SENSITIVE_NAME = "lgSD";
        auto *sensitiveLG = new crystal_sens(LG_SENSITIVE_NAME);
        lgSD.Put(sensitiveLG);
    }

    G4SDManager::GetSDMpointer()->AddNewDetector(lgSD.Get());
    SetSensitiveDetector(logicCrystal, lgSD.Get());
}
