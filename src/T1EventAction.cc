
#include "T1EventAction.hh"
#include "T1RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"



#include <G4SDManager.hh>
#include "T1TPCDigi.hh"
#include <G4VPrimitiveScorer.hh>
#include "CEEPSStartTime.hh"
#include "CEEPSStep.hh"
#include <G4SystemOfUnits.hh>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include <fstream>
using namespace std;
extern ofstream shuchu;

T1EventAction::T1EventAction(T1RunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

T1EventAction::~T1EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void T1EventAction::BeginOfEventAction(const G4Event* evt)
{
  shuchu.open("results/track1-EventID"+to_string(evt->GetEventID())+".txt",ios_base::app);
  shuchu<<"EventID:  "<<evt->GetEventID()<<endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void T1EventAction::EndOfEventAction(const G4Event* evt)
{
  shuchu.close();

	G4SDManager* SDMan = G4SDManager::GetSDMpointer();
	if(!SDMan) { G4cerr<<"No SDManager!"<<G4endl;return; }

	G4String fileName = "results/Event" + std::to_string(evt->GetEventID()) + ".txt";
	std::ofstream evtOut;
	G4cout << "Outputing result to file " << fileName << G4endl;
	evtOut.open(fileName, std::ofstream::out|std::ofstream::trunc);
	evtOut << "### Event " << evt->GetEventID() << std::endl;

	{ //TPC
		T1TPCDigi* tpcDigi = dynamic_cast<T1TPCDigi*>(SDMan->FindSensitiveDetector("CEE_TPC_logic_det"));
		evtOut << "### MultiFunctionalDet  " << tpcDigi->GetName() << std::endl;
		if(!tpcDigi) { G4cerr << "No TPCDigi!" << G4endl;return; }
		//tpcDigi->GetPrimitive(0)->PrintAll();
		//tpcDigi->GetPrimitive(1)->PrintAll();
		CEEPSStartTime* startTime = dynamic_cast<CEEPSStartTime*>(tpcDigi->GetPrimitive(0));
		CEEPSStep* stepScorer = dynamic_cast<CEEPSStep*>(tpcDigi->GetPrimitive(1));
		{//StartTime
			evtOut << "## PrimitiveScorer " << startTime->GetName() << std::endl;
			evtOut << "# Number of entries " << startTime->GetMap()->entries() << std::endl;
			std::map<G4int,G4double*>::iterator itr = startTime->GetMap()->GetMap()->begin();
			for(; itr != startTime->GetMap()->GetMap()->end(); itr++) {
			  evtOut << " >   copy no.: " << itr->first
			         << " >> start time: "
			         << *(itr->second)/startTime->GetUnitValue()
			         << " [" << startTime->GetUnit()<<"]"
			         << std::endl;
			}
		}
		{//Step
			evtOut << "## PrimitiveScorer " << stepScorer->GetName() << std::endl;
			evtOut << "# Number of entries " << stepScorer->GetMap()->entries() << std::endl;
			for(auto copyItr: *(stepScorer->GetMap()->GetMap()))
			{
				evtOut 	<< " >   copy no.: " << copyItr.first << std::endl;
				for(auto trackItr: *copyItr.second)
				{
					evtOut 	<< " >> TID=" << trackItr->trackID
						<< " t=" << trackItr->time/ns
						<< "ns x=" << trackItr->position.x()/mm
						<< "mm y=" << trackItr->position.y()/mm
						<< "mm z=" << trackItr->position.z()/mm
						<< "mm dE=" << trackItr->deltaEnergy/MeV
						<< "MeV eD=" << trackItr->energyDeposit/MeV << "MeV" << std::endl;
				}
			}
		}
	}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
