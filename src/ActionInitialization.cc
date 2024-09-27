
#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "EventAction.hh"


ActionInitialization::ActionInitialization(SimulationParameters* aSP): G4VUserActionInitialization(), SP (aSP)
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::BuildForMaster() const
{

    RunAction* runAction = new RunAction(SP);
    SetUserAction(runAction);
}

void ActionInitialization::Build() const
{
  PrimaryGeneratorAction* PrimaryParticleGenerator = new PrimaryGeneratorAction(SP);
  SetUserAction(PrimaryParticleGenerator);

  RunAction* runAction = new RunAction(SP);
  SetUserAction(runAction);

  EventAction* eventAction = new EventAction(SP);
  SetUserAction(eventAction);

  SteppingAction* steppingAction = new SteppingAction(runAction, SP);
  SetUserAction(steppingAction);
}
