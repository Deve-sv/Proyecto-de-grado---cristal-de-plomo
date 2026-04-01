#include "construction.hh"

crystal_construct::crystal_construct(){

    DefineMaterials();
    pmtSD.Put(nullptr);
    lgSD.Put(nullptr);
}

crystal_construct::~crystal_construct(){
}


void crystal_construct::DefineMaterials(){

    G4NistManager *nist = G4NistManager::Instance();

    //Materials
    leadGlass = nist->FindOrBuildMaterial("G4_GLASS_LEAD");
	worldMat = nist->FindOrBuildMaterial("G4_AIR");
	covMat = nist->FindOrBuildMaterial("G4_Al");
	pmtMat = nist->FindOrBuildMaterial("G4_Pyrex_Glass");

	//properties of materials
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

	// Define diffuse reflection (Lambertian)
    // 1.0 means maximum diffusion

    G4MaterialPropertiesTable *mptLG = new G4MaterialPropertiesTable();
	mptLG->AddProperty("RINDEX", energy, rindexLG, nentries);
	//mptLG->AddProperty("ABSLENGTH", energy, absorptionLength, nentries);
	mptLG->AddProperty("RAYLEIGH", energy, rayleighLength, nentries);
	leadGlass->SetMaterialPropertiesTable(mptLG);

    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", energy, rindexWorld, nentries);
	worldMat->SetMaterialPropertiesTable(mptWorld); 

	G4MaterialPropertiesTable *mptPMT1 = new G4MaterialPropertiesTable();
	mptPMT1->AddProperty("RINDEX", energy, rindexPMT, nentries);
	//mptPMT1->AddProperty("ABSLENGTH", energy, absorptionLengthPMT, nentries);	
	pmtMat->SetMaterialPropertiesTable(mptPMT1);

	
	G4MaterialPropertiesTable *AluminumMPT = new G4MaterialPropertiesTable();
	AluminumMPT->AddProperty("REFLECTIVITY", energy, reflectivityAl, nentries);
	covMat->SetMaterialPropertiesTable(AluminumMPT);

}

G4VPhysicalVolume *crystal_construct::Construct(){

    G4bool checkOverlaps = true;

	// Lead glass geometry define	
	G4double innerRadius = 0.0 * cm; // Solid lead glass cylinder
	G4double outerRadius = 25.0 * cm; // 50 cm diameter
	G4double halfHeight = 15.75 * cm; // ~32 cm total height
	G4double startAngle = 0.0 * deg;
	G4double spanningAngle = 360.0 * deg;

	// Aluminum Cover geometry define	
	G4double innerRadiusAl = 25.0 * cm; // Aluminum foil cylinder
	G4double outerRadiusAl = 25.5 * cm; // 1 cm diameter
	G4double halfHeightAl = 16.0 * cm; // ~32 cm total height
	G4double startAngleAl = 0.0 * deg;
	G4double spanningAngleAl = 360.0 * deg;
	
	// WORLD geometry define
	G4double xsize = 1.5 * m; 
	G4double ysize = 1.5 * m; 
	G4double zsize = 1.5 * m; 

	// PMTs geometry define
	G4double pmtinnerRadius = 0.0 * cm; 
	G4double pmtouterRadius = 6.35 * cm; // 12.70 cm diameter
	G4double pmthalfHeight = 5.0 * cm; // 5 cm total height
	G4double pmtstartAngle = 0.0 * deg;
	G4double pmtspanningAngle = 360.0 * deg;	

	solidWorld = new G4Box("solidWorld", xsize, ysize, zsize);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0. ,0.), logicWorld, "physWorld", 0, false, 0, checkOverlaps);
	
	CylinderCover = new G4Tubs("AluminumCov", innerRadiusAl, outerRadiusAl, halfHeightAl, startAngleAl, spanningAngleAl);
	logicCover = new G4LogicalVolume(CylinderCover, covMat, "logicCover");
    PhysCover = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicCover, "physCover", logicWorld, false, 0, checkOverlaps);

	//===============================> Setting Visual Attributes

	G4VisAttributes *lgVisAtt = new G4VisAttributes(G4Color(0.12, 0.56, 1.0, 0.5));
	lgVisAtt->SetForceSolid(true);
	G4VisAttributes *pmtVisAtt = new G4VisAttributes(G4Color(0.3, 0.3, 0.3, 0.5));
	pmtVisAtt->SetForceSolid(true);
	G4VisAttributes *covVisAtt = new G4VisAttributes(G4Color(0.6, 0.6, 0.6, 0.5));
	covVisAtt->SetForceSolid(true);
	logicCover->SetVisAttributes(covVisAtt);

	//===============================> Setting up Sensitive detectors

	solidRadiator = new G4Tubs("LeadGlass", innerRadius, outerRadius, halfHeight, startAngle, spanningAngle);
	logicRadiator = new G4LogicalVolume(solidRadiator, leadGlass, "logicRadiator");
    PhysRadiator = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicRadiator, "physRadiator", logicWorld, false, 1.0, checkOverlaps);

	logicRadiator->SetVisAttributes(lgVisAtt);

	// Attach Optical Surface to the Cylinder
// Create an Optical Surface

//Properties
	const G4int nentries = 32;
    G4double sigmaAlpha = 1.0; 

	// photon energy matrix	
	G4double energy[nentries] = {
		1.77*eV, 1.84*eV, 1.90*eV, 1.97*eV, 2.03*eV, 2.10*eV, 2.16*eV, 2.23*eV,
		2.29*eV, 2.36*eV, 2.42*eV, 2.49*eV, 2.55*eV, 2.62*eV, 2.68*eV, 2.75*eV,
		2.81*eV, 2.88*eV, 2.94*eV, 3.01*eV, 3.07*eV, 3.14*eV, 3.20*eV, 3.27*eV,
		3.33*eV, 3.40*eV, 3.46*eV, 3.53*eV, 3.59*eV, 3.66*eV, 3.72*eV, 4.13*eV
	};

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

    G4MaterialPropertiesTable* tyvekMPT = new G4MaterialPropertiesTable();
	tyvekMPT->AddProperty("REFLECTIVITY", energy, reflectivity, nentries);

	G4OpticalSurface *tyvekSurface = new G4OpticalSurface("TyvekSurface");
	tyvekSurface->SetType(dielectric_dielectric); // Tyvek interacts with light
	tyvekSurface->SetModel(unified);              // Use the UNIFIED model
	tyvekSurface->SetFinish(groundbackpainted);   // Diffuse reflection
	tyvekSurface->SetSigmaAlpha(sigmaAlpha);      // Diffusion parameter
	tyvekSurface->SetMaterialPropertiesTable(tyvekMPT);

	G4LogicalBorderSurface *opSurf = new G4LogicalBorderSurface("TyvekOpticalSurface", PhysRadiator, physWorld, tyvekSurface);

	solidDetector = new G4Tubs("solidDetector", pmtinnerRadius, pmtouterRadius, pmthalfHeight, pmtstartAngle, pmtspanningAngle);
	logicDetector = new G4LogicalVolume(solidDetector, pmtMat, "logicalDetector");
	physDetector = new G4PVPlacement(0, G4ThreeVector(0.,10.0*cm,20.75*cm), logicDetector, "physDetector", logicWorld, false, 2, checkOverlaps);

	solidDetector1 = new G4Tubs("solidDetector1", pmtinnerRadius, pmtouterRadius, pmthalfHeight, pmtstartAngle, pmtspanningAngle);
	logicDetector1 = new G4LogicalVolume(solidDetector1, pmtMat, "logicalDetector1");
	physDetector1 = new G4PVPlacement(0, G4ThreeVector(0.,-10.0*cm,20.75*cm), logicDetector1, "physDetector1", logicWorld, false, 3, checkOverlaps);

	logicDetector->SetVisAttributes(pmtVisAtt);
	logicDetector1->SetVisAttributes(pmtVisAtt);

    fScoringVolume = logicRadiator;

	// Fotocathode surface

	// QE realista R1512 (pico ~27%)
	G4double efficiency[nentries] = {
		0.02,0.05,0.10,0.18,0.24,0.27,0.26,0.25,
		0.24,0.23,0.21,0.19,0.17,0.15,0.13,0.11,
		0.09,0.07,0.06,0.05,0.04,0.03,0.02,0.015,
		0.01,0.007,0.005,0.003,0.002,0.001,0.0,0.0
	};

	G4double PMTreflectivity[nentries];
	for (int i = 0;i < nentries;i++) reflectivity[i] = 0.2; // Reflectivity of the photocathode (assumed)

	auto photocathodeSurface = new G4OpticalSurface("PhotocathodeSurface");
	photocathodeSurface->SetType(dielectric_metal);
	photocathodeSurface->SetModel(unified);
	photocathodeSurface->SetFinish(polished);

	auto mptPC = new G4MaterialPropertiesTable();
	//mptPC->AddProperty("EFFICIENCY", energy, efficiency, nentries);
	mptPC->AddProperty("REFLECTIVITY", energy, PMTreflectivity, nentries);

	photocathodeSurface->SetMaterialPropertiesTable(mptPC);

	// Asociar a ambos PMTs
	new G4LogicalBorderSurface("PC1", PhysRadiator, physDetector, photocathodeSurface);
	new G4LogicalBorderSurface("PC2", PhysRadiator, physDetector1, photocathodeSurface);
		
	return physWorld;
}

void crystal_construct::ConstructSDandField(){

    //Sensitive Detector:PMT
    if(pmtSD.Get() == nullptr){
        constexpr auto PMT_SENSITIVE_DET_NAME = "pmtSD";
        auto *sensitiveDetector = new pmt_sens(PMT_SENSITIVE_DET_NAME);
        pmtSD.Put(sensitiveDetector);
    }

    G4SDManager::GetSDMpointer()->AddNewDetector(pmtSD.Get());
    SetSensitiveDetector(logicDetector, pmtSD.Get());
    SetSensitiveDetector(logicDetector1, pmtSD.Get());

    if(lgSD.Get() == nullptr){
        constexpr auto LG_SENSITIVE_NAME = "lgSD";
        auto *sensitiveLG = new crystal_sens(LG_SENSITIVE_NAME);
        lgSD.Put(sensitiveLG);
    }

    G4SDManager::GetSDMpointer()->AddNewDetector(lgSD.Get());
    SetSensitiveDetector(logicRadiator, lgSD.Get());
}
