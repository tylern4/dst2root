#define clas12_selector_cxx
// The class definition in clas12_selector.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("clas12_selector.C")
// root> T->Process("clas12_selector.C","some options")
// root> T->Process("clas12_selector.C+")
//

#include <TH2.h>
#include <TStyle.h>
#include "clas12_selector.h"

void clas12_selector::Begin(TTree* /*tree*/) {
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();
}

void clas12_selector::SlaveBegin(TTree* /*tree*/) {
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

  for (size_t i = 0; i < 6; i++) {
    fWq2[i] = new TH2D(Form("wq2_%zu", i), Form("W vs Q^{2} Sector: %zu", i + 1), 500, 0, 3.5, 500, 0, 4.0);
    fWq2[i]->SetDirectory(0);
    fWq2[i]->GetXaxis()->SetTitle("W");
    fWq2[i]->GetYaxis()->SetTitle("Q^{2}");
    fOutput->Add(fWq2[i]);
    fW[i] = new TH1D(Form("w_%zu", i), Form("W Sector: %zu", i + 1), 500, 0, 3.5);
    fW[i]->SetDirectory(0);
    fW[i]->GetXaxis()->SetTitle("W");
    fOutput->Add(fW[i]);
  }
}

Bool_t clas12_selector::Process(Long64_t entry) {
  // The Process() function is called for each entry in the tree (or possibly
  // keyed object in the case of PROOF) to be processed. The entry argument
  // specifies which entry in the currently loaded tree is to be processed.
  // When processing keyed objects with PROOF, the object is already loaded
  // and is available via the fObject pointer.
  //
  // This function should contain the \"body\" of the analysis. It can contain
  // simple or elaborate selection criteria, run algorithms on the data
  // of the event and typically fill histograms.
  //
  // The processing can be stopped by calling Abort().
  //
  // Use fStatus to set the return value of TTree::Process().
  //
  // The return value is currently not used.

  fReader.SetEntry(entry);

  if (ec_pcal_sec[0] > 0) {
    int sector = ec_pcal_sec[0] - 1;
    TLorentzVector e_mu_prime;
    e_mu_prime.SetXYZM(px[0], py[0], pz[0], 0.000511);
    fWq2[sector]->Fill(W_calc(e_mu_prime), Q2_calc(e_mu_prime));
    fW[sector]->Fill(W_calc(e_mu_prime));
  }

  return kTRUE;
}

void clas12_selector::SlaveTerminate() {
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
}

void clas12_selector::Terminate() {
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.
  gStyle->SetOptFit(1111);
  TCanvas* c1 = new TCanvas("c1", "WvsQ2 Canvas", 1600, 900);
  c1->Divide(3, 2);
  for (size_t i = 0; i < 6; i++) {
    TH2D* hf_wq2 = dynamic_cast<TH2D*>(fOutput->FindObject(Form("wq2_%zu", i)));
    c1->cd(i + 1);
    hf_wq2->Draw("colz");
  }

  TCanvas* c2 = new TCanvas("c2", "W Canvas", 1600, 900);
  c2->Divide(3, 2);
  for (size_t i = 0; i < 6; i++) {
    TH1D* hf_w = dynamic_cast<TH1D*>(fOutput->FindObject(Form("w_%zu", i)));
    c2->cd(i + 1);
    hf_w->Fit("gaus", "QMR+", "", 0.5, 1.05);
    hf_w->Draw();
  }
}
