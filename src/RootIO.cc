
#include "RootIO.hh"
#include <stdexcept>

void RootIO::Open(const char* filename)
{
  fFile = TFile::Open(filename, "RECREATE");
  if (!fFile || fFile->IsZombie()) throw std::runtime_error("Failed to open ROOT file");

  fTree = new TTree("events", "Per-event interaction vectors");

  fTree->Branch("eventID", &eventID);
  fTree->Branch("layer",   &v_layer);
  fTree->Branch("layertype",   &v_layertype);
  fTree->Branch("bar",     &v_bar);
  fTree->Branch("edep",    &v_edep);
  fTree->Branch("x",       &v_x);
  fTree->Branch("y",       &v_y);
  fTree->Branch("z",       &v_z);
}

void RootIO::ClearEvent()
{
  eventID = -1;
  v_layer.clear();
  v_bar.clear();
  v_edep.clear();
  v_x.clear();
  v_y.clear();
  v_z.clear();
  v_layertype.clear();
}

void RootIO::FillEvent()
{
  if (!fTree) return;
  fTree->Fill();
}

void RootIO::Close()
{
  if (!fFile) return;
  fFile->cd();
  if (fTree) fTree->Write();
  fFile->Close();
  delete fFile;
  fFile = nullptr;
  fTree = nullptr;
}
