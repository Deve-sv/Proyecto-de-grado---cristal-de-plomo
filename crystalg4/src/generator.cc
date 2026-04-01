#include "generator.hh"
#include "G4RandomTools.hh"

generator::generator(){

	fParticleGun = new G4ParticleGun(1);
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle("mu-");

    fParticleGun->SetParticleDefinition(particle);
    //fParticleGun->SetParticleEnergy(10 *MeV);

    fMessenger = new G4GenericMessenger(this, "/generator/", "Primary generator control");
    fMessenger->DeclareProperty("deg", deg, "Incidence angle");
    
    deg=0;
}

generator::~generator(){

	delete fParticleGun;
}

void generator::GeneratePrimaries(G4Event *anEvent){

    //----------------------------------------------------------------
    G4double x,y,z;
    G4double rad_real=25.*cm;
    G4double rad=30.*cm;
    G4double half_height = 17.*cm;
    G4double theta = 0.0;
    G4double psi = 0.0;

    G4double sintheta,costheta, MaxTheta, MinTheta, Theta;
    G4double sinphi, cosphi, MaxPhi, MinPhi, Phi;
    G4double px,py,pz;

    G4double A,B,C,D,t1,t2;

    x=rad+100.;
    y=rad+100.;
    z=17*cm;

    MaxPhi = 2.*M_PI;
    MinPhi = 0.;

    MaxTheta = M_PI/2.;
    MinTheta = 0.;

    px=0; py=0; pz=0;

    G4bool check = false;

    //-------Angular incidence
    switch(deg){

        //Vertical
        case 0:
           
            while(std::sqrt((x*x)+(y*y)) > rad_real){
                x = G4UniformRand();
                y = G4UniformRand();
  
                x=(x*2.*rad_real)-rad_real;
                y=(y*2.*rad_real)-rad_real;
            }

            fParticleGun->SetParticlePosition(G4ThreeVector(x,y,z));
            fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,-1));
        
            break;

        //30 degrees
        case 1:

            while(std::sqrt(x*x + y*y) > rad_real){
                x=G4UniformRand();
                y=G4UniformRand();

                x=(x*2.*rad_real)-rad_real;
                y=(y*2.*rad_real)-rad_real;
            }

            while(check==false){
                theta = M_PI/6.;
                psi=G4UniformRand();
                Phi = MinPhi + (MaxPhi - MinPhi)*psi;

                sintheta = std::sin(theta);
                costheta = std::cos(theta);
                sinphi = std::sin(Phi);
                cosphi = std::cos(Phi);

                px = -sintheta * cosphi;
                py = -sintheta * sinphi;
                pz = -costheta;
        
                if (std::abs(px) < 1e-12 && std::abs(py) < 1e-12) {
                    check=true;
                }
                else{
                    A=px*px + py*py;
                    B=2*(px*x + py*y);
                    C=x*x + y*y - rad_real*rad_real;
                    D=B*B -2*A*C;
                    if(D>=0){
                        t1=(-B+std::sqrt(D))/(2*A);
                        t2=(-B-std::sqrt(D))/(2*A);
                        if (((z+pz*t1)<15*cm && (z+pz*t1)>-15*cm) || ((z+pz*t2)<15*cm && (z+pz*t2)>-15*cm)){
                            check=true;
                        }
                        else{
                            check=false;
                        }
                    }
                    else{
                        check=false;
                    }
                }
            }

            fParticleGun->SetParticlePosition(G4ThreeVector(x,y,z));
            fParticleGun->SetParticleMomentumDirection(G4ThreeVector(px,py,pz));
            
            break;
    default:

        G4cerr<<"Invalid angle option"<<G4endl;

    }

    fParticleGun->GeneratePrimaryVertex(anEvent);
}

