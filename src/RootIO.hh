#pragma once
#include <vector>
#include "TFile.h"
#include "TTree.h"

class RootIO {
public:
  RootIO() = default;
  ~RootIO() = default;

  void Open(const char* filename);
  void Close();

  // Per-event data (filled by EventAction / SteppingAction)
  Long64_t eventID = -1;
  std::vector<int>    v_layer;
  std::vector<int>    v_layertype;
  std::vector<int>    v_bar;
  std::vector<double> v_edep; // MeV
  std::vector<double> v_x;    // mm
  std::vector<double> v_y;    // mm
  std::vector<double> v_z;    // mm
  std::vector<double> v_x_local;    // mm
  std::vector<double> v_y_local;    // mm
  std::vector<double> v_z_local;    // mm

  void ClearEvent();
  void FillEvent();

private:
  TFile* fFile = nullptr;
  TTree* fTree = nullptr;
};
