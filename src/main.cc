
#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "FTFP_BERT.hh"

int main(int argc, char** argv)
{
  const bool interactive = (argc == 1);

  // Qt/OpenGL must be on master thread => use Serial for interactive vis
  auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Serial);

  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new FTFP_BERT());
  runManager->SetUserInitialization(new ActionInitialization());

  auto* ui = G4UImanager::GetUIpointer();

  if (interactive) {
    // Initialize here (no geometry macro needed unless you want one)
    runManager->Initialize();

    auto* uiExec = new G4UIExecutive(argc, argv);
    auto* vis = new G4VisExecutive();
    vis->Initialize();

    // Load visualization macro (can also set geometry/gun + a small beamOn)
    ui->ApplyCommand("/control/execute ../vis.mac");
    uiExec->SessionStart();

    delete vis;
    delete uiExec;
  } else {
    // Batch: macro MUST do /run/initialize after /det/... commands
    ui->ApplyCommand(G4String("/control/execute ") + argv[1]);
  }

  delete runManager;
  return 0;
}
