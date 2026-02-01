
#include "EventAction.hh"
#include "RootIO.hh"
#include "G4Event.hh"

void EventAction::BeginOfEventAction(const G4Event*)
{
  if (fIO) fIO->ClearEvent();
}

void EventAction::EndOfEventAction(const G4Event* evt)
{
  if (!fIO) return;
  fIO->eventID = static_cast<Long64_t>(evt->GetEventID());
  fIO->FillEvent();
}
