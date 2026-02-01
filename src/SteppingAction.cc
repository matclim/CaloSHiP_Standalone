
#include "SteppingAction.hh"
#include "RootIO.hh"

#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4TouchableHandle.hh"

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fIO) return;

  const auto edep = step->GetTotalEnergyDeposit();
  if (edep <= 0.) return;



  int layerID = -1;
  int layertype = -1;
  
  auto touch = step->GetPreStepPoint()->GetTouchableHandle();
  for (int d = 0; d <= touch->GetHistoryDepth(); ++d) {
    auto* vol = touch->GetVolume(d);
    if (!vol) continue;
  
    const auto& nm = vol->GetName();
    if (nm.rfind("WideLayerPV", 0) == 0) { layertype = 0; layerID = vol->GetCopyNo(); break; }
    if (nm.rfind("ThinLayerPV", 0) == 0) { layertype = 1; layerID = vol->GetCopyNo(); break; }
  }
  
  if (layerID < 0) return;
  
  // make it 1..40
  layerID += 1;


  // Bar is always at depth 0
  const int barID = touch->GetVolume(0)->GetCopyNo();

  // Debug (leave on for 1 event then remove)
  // G4cout << "bar=" << barID << " layer=" << layerID << " type=" << layertype << G4endl;

 
  const auto worldPos = step->GetPreStepPoint()->GetPosition();
  const auto localPos =
    step->GetPreStepPoint()->GetTouchableHandle()
      ->GetHistory()->GetTopTransform().TransformPoint(worldPos);

  fIO->v_z_local.push_back(localPos.z()/mm);


  fIO->v_layer.push_back(layerID);
  fIO->v_layertype.push_back(layertype);
  fIO->v_bar.push_back(barID);
  fIO->v_edep.push_back(edep / MeV);
  fIO->v_x.push_back(localPos.x() / mm);
  fIO->v_y.push_back(localPos.y() / mm);
  fIO->v_z.push_back(localPos.z() / mm);
}
