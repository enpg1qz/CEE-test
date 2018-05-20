
#include "T1SteppingAction.hh"
#include "T1EventAction.hh"
#include "T1DetectorConstruction.hh"

#include "G4Step.hh"
//#include "G4StepPoint.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

#include<fstream>
using namespace std;
extern ofstream shuchu;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T1SteppingAction::T1SteppingAction(T1EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T1SteppingAction::~T1SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void T1SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  G4int trackid = (aStep->GetTrack()->GetTrackID()) ;
  if (trackid !=1) return;

  G4LogicalVolume* volume
    = aStep->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
  G4String Vname = volume->GetName();
  G4String Materialname = volume->GetMaterial()->GetName();
  G4int curStepNumber = (aStep->GetTrack()->GetCurrentStepNumber());

  G4String particlename = (aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName());

  shuchu<<"<--------------------------------------------------------------\n";
  shuchu<<"TrackID:"<<trackid<<"\n";
  shuchu<<"GetCurrentStepNumber:"<<curStepNumber<<"\n";
  shuchu<<"LogicalVolumeName:"<<Vname<<"\n";
  shuchu<<"Materialname:"<<Materialname<<"\n";

  shuchu <<"PreStepPoint:"<<'{'
      <<(aStep->GetPreStepPoint()->GetPosition().x()) <<','
      <<(aStep->GetPreStepPoint()->GetPosition().y())<<','
      <<(aStep->GetPreStepPoint()->GetPosition().z())<<'}'<<"mm"<<"   "
	    <<"GetTotalEnergy:"<<aStep->GetPreStepPoint()->GetTotalEnergy()/MeV<<"MeV"<<"    "<<"GetKineticEnergy:"<<aStep->GetPreStepPoint()->GetKineticEnergy()/MeV<<"MeV"<<"    \n";
  shuchu <<"PostStepPoint:"<<'{'
      <<(aStep->GetPostStepPoint()->GetPosition().x()) <<','
      <<(aStep->GetPostStepPoint()->GetPosition().y())<<','
      <<(aStep->GetPostStepPoint()->GetPosition().z())<<'}'<<"mm"<<"   "
	    <<"GetTotalEnergy:"<<aStep->GetPostStepPoint()->GetTotalEnergy()/MeV<<"MeV"<<"    "<<"GetKineticEnergy:"<<aStep->GetPostStepPoint()->GetKineticEnergy()/MeV<<"MeV"<<"    \n";
  shuchu <<"GetTrack->GetDynamicParticle->GetTotalEnergy:"
      <<(aStep->GetTrack()->GetDynamicParticle()->GetTotalEnergy()/MeV)<<"MeV"<<"    \n";

  shuchu <<"GetTrack->GetDynamicParticle->GetKineticEnergy:"
      <<(aStep->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/MeV)<<"MeV"<<"    \n";
  shuchu<<"GetTotalEnergyDeposit:"<<aStep->GetTotalEnergyDeposit()/MeV<<"    \n";
  shuchu <<"GetDeltaEnergy:"<<aStep->GetDeltaEnergy()/MeV<<"MeV"<<"    \n";

  shuchu <<"GetTrackLength:"<<aStep->GetTrack()->GetTrackLength()/mm<<"mm"<<"    \n";
  shuchu <<"GetGlobalTime:"<<aStep->GetTrack()->GetGlobalTime()/ns<<"ns"<<"    \n";
  shuchu <<"GetLocalTime:"<<aStep->GetTrack()->GetLocalTime()/ns<<"ns"<<"    \n";
  shuchu <<"GetProperTime:"<<aStep->GetTrack()->GetProperTime()/ns<<"ns"<<"    \n";
  //shuchu <<"GetProperTime:"<<aStep->GetTrack()->GetProperTime()/ns<<"ns"<<"    \n";


  G4double len = (aStep->GetStepLength())/mm;
  //shuchu <<(aStep->GetDeltaEnergy()/MeV)/len<<"MeV/mm"<<endl;

  G4double prez = aStep->GetPreStepPoint()->GetPosition().z()/mm;
  G4double postz = aStep->GetPostStepPoint()->GetPosition().z()/mm;

  G4double deposit_de =aStep->GetTotalEnergyDeposit()/MeV;

  shuchu<<"-------------------------------------------------------------->\n";



}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
