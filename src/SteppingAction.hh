#pragma once
#include "G4UserSteppingAction.hh"

class G4Step;
class RootIO;

class SteppingAction : public G4UserSteppingAction {
public:
  explicit SteppingAction(RootIO* io) : fIO(io) {}
  ~SteppingAction() override = default;

  void UserSteppingAction(const G4Step* step) override;

private:
  RootIO* fIO = nullptr; // not owned
};
