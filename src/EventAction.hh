#pragma once
#include "G4UserEventAction.hh"

class G4Event;
class RootIO;

class EventAction : public G4UserEventAction {
public:
  explicit EventAction(RootIO* io) : fIO(io) {}
  ~EventAction() override = default;

  void BeginOfEventAction(const G4Event* evt) override;
  void EndOfEventAction(const G4Event* evt) override;

private:
  RootIO* fIO = nullptr; // not owned
};

