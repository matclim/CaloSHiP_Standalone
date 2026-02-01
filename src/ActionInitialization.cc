
#include "ActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "RootIO.hh"

void ActionInitialization::Build() const
{
  // Shared output object (lifetime for the run)
  auto* io = new RootIO();

  SetUserAction(new PrimaryGeneratorAction());
  SetUserAction(new RunAction(io));
  SetUserAction(new EventAction(io));
  SetUserAction(new SteppingAction(io));
}
