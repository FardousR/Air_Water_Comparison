#include  "SimulationParameters.hh"
#include  "DetectorConstruction.hh"
#include  "ActionInitialization.hh"
#include  "PrimaryGeneratorAction.hh"
#include  "Analysis.hh"
#include  "G4PhysListFactory.hh"
#include  "G4StepLimiterPhysics.hh"

#include  "G4SystemOfUnits.hh"
#include  "G4RunManagerFactory.hh"
#include  "G4UImanager.hh"
#include  "QBBC.hh"
#include  "G4VisExecutive.hh"
#include  "G4UIExecutive.hh"
#include  "G4UserSpecialCuts.hh"



using namespace std;

int main(int argc,char** argv)
{
  SimulationParameters* SMP = new SimulationParameters(argc, argv);
  // SMP->PrintParameters();
  // SMP->PrintSpotsParameters();


  // Set the Random engine
  // The following guarantees random generation also for different runs
  // in multithread
  CLHEP::RanluxEngine defaultEngine( 1234567, 4 );
  G4Random::setTheEngine( &defaultEngine );
  G4int seed = (G4int) time( NULL );
  G4Random::setTheSeed( seed );

  // Construct the default run manager
  #ifdef G4MULTITHREADED
  G4MTRunManager *runManager = new G4MTRunManager();
    runManager->SetNumberOfThreads(SMP->GetSetup().n_thread);
  #else
    G4RunManager* runManager = new G4RunManager();
  #endif


  // Set mandatory initialization classes
  runManager->SetUserInitialization(new DetectorConstruction(SMP));

  G4PhysListFactory physListFactory;
  const G4String phylistname = SMP->GetPhysics().phy_list;
  G4VModularPhysicsList* physicsList = physListFactory.GetReferencePhysList(phylistname);
  G4StepLimiterPhysics* stepLimitPhys = new G4StepLimiterPhysics();
  stepLimitPhys->SetApplyToAll(SMP->GetPhysics().use_sl_neutral);
  physicsList->RegisterPhysics(stepLimitPhys);
  runManager->SetUserInitialization(physicsList);
  // User action initialization
  runManager->SetUserInitialization(new ActionInitialization(SMP));

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (SMP->GetSetup().use_gui)
  {
    // Initialize visualization
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    G4VisManager* visManager = new G4VisExecutive;
    // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
    // G4VisManager* visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete visManager;
    delete ui;
  }

  else
  {
    G4String ProgressCounter = "/run/printProgress " + to_string(SMP->GetSetup().n_progress);
    // G4cout << ProgressCounter<<"\n\n";
    G4String beamOn = "/run/beamOn " + to_string(SMP->GetSetup().n_particle);
    // G4cout << beamOn<<"\n\n";
    //
    UImanager->ApplyCommand("/run/initialize");
    UImanager->ApplyCommand(ProgressCounter);
    UImanager->ApplyCommand(beamOn);
  }

  // system("clear");
  delete runManager;
}
