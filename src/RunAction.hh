
#pragma once
#include "G4UserRunAction.hh"

class G4Run;
class RootIO;

class RunAction : public G4UserRunAction {
public:
  explicit RunAction(RootIO* io) : fIO(io) {}
  ~RunAction() override = default;

  void BeginOfRunAction(const G4Run*) override;
  void EndOfRunAction(const G4Run*) override;

private:
  RootIO* fIO = nullptr; // not owned
};
