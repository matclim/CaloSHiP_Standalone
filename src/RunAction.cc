
#include "RunAction.hh"
#include "RootIO.hh"

void RunAction::BeginOfRunAction(const G4Run*)
{
  if (fIO) fIO->Open("edep.root");
}

void RunAction::EndOfRunAction(const G4Run*)
{
  if (fIO) fIO->Close();
}
