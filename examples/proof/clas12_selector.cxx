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

void clas12_selector::Begin(TTree * /*tree*/) {
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();
}

void clas12_selector::SlaveBegin(TTree * /*tree*/) {
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

  fDeltaT_1a_prot = new TH2D("fDeltaT_1a_prot", "#Deltat Proton", 500, 0, 7.0, 500, -10, 10);
  fOutput->Add(fDeltaT_1a_prot);
  fDeltaT_1a_pip = new TH2D("fDeltaT_1a_pion", "#Deltat #pi^{+}", 500, 0, 7.0, 500, -10, 10);
  fOutput->Add(fDeltaT_1a_pip);
  fDeltaT_1a_pim = new TH2D("fDeltaT_1a_pion_m", "#Deltat #pi^{-}", 500, 0, 7.0, 500, -10, 10);
  fOutput->Add(fDeltaT_1a_pim);

  fDeltaT_1b_prot = new TH2D("fDeltaT_1b_prot", "#Deltat Proton", 500, 0, 7.0, 500, -10, 10);
  fOutput->Add(fDeltaT_1b_prot);
  fDeltaT_1b_pip = new TH2D("fDeltaT_1b_pion", "#Deltat #pi^{+}", 500, 0, 7.0, 500, -10, 10);
  fOutput->Add(fDeltaT_1b_pip);
  fDeltaT_1b_pim = new TH2D("fDeltaT_1b_pion_m", "#Deltat #pi^{-}", 500, 0, 7.0, 500, -10, 10);
  fOutput->Add(fDeltaT_1b_pim);

  fDeltaT_2_prot = new TH2D("fDeltaT_2_prot", "#Deltat Proton", 500, 0, 7.0, 500, -10, 10);
  fOutput->Add(fDeltaT_2_prot);
  fDeltaT_2_pip = new TH2D("fDeltaT_2_pion", "#Deltat #pi^{+}", 500, 0, 7.0, 500, -10, 10);
  fOutput->Add(fDeltaT_2_pip);
  fDeltaT_2_pim = new TH2D("fDeltaT_2_pion_m", "#Deltat #pi^{-}", 500, 0, 7.0, 500, -10, 10);
  fOutput->Add(fDeltaT_2_pim);

  fDeltaT_ctof_prot = new TH2D("fDeltaT_ctof_prot", "#Deltat Proton", 500, 0, 7.0, 500, -10, 10);
  fOutput->Add(fDeltaT_ctof_prot);
  fDeltaT_ctof_pip = new TH2D("fDeltaT_ctof_pion", "#Deltat #pi^{+}", 500, 0, 7.0, 500, -10, 10);
  fOutput->Add(fDeltaT_ctof_pip);
  fDeltaT_ctof_pim = new TH2D("fDeltaT_ctof_pion_m", "#Deltat #pi^{-}", 500, 0, 7.0, 500, -10, 10);
  fOutput->Add(fDeltaT_ctof_pim);

  fDeltaT_ctof_prot_component =
      new TH2D("fDeltaT_ctof_prot_component", "#Deltat Proton vs Component", 50, 0, 50, 500, -10, 10);
  fOutput->Add(fDeltaT_ctof_prot_component);
  fDeltaT_ctof_pip_component =
      new TH2D("fDeltaT_ctof_pion_component", "#Deltat #pi^{+} vs Component", 50, 0, 50, 500, -10, 10);
  fOutput->Add(fDeltaT_ctof_pip_component);
  fDeltaT_ctof_pim_component =
      new TH2D("fDeltaT_ctof_pion_m_component", "#Deltat #pi^{-} vs Component", 50, 0, 50, 500, -10, 10);
  fOutput->Add(fDeltaT_ctof_pim_component);
  fDeltaT_ctof_component = new TH2D("fDeltaT_ctof_component", "#Deltat vs Component", 50, 0, 50, 500, -10, 10);
  fOutput->Add(fDeltaT_ctof_component);

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
  double vertex = 0.0;
  int sector = 0;
  size_t len = 0;
  TLorentzVector e_mu_prime;

  for (auto l = p.begin(); l != p.end(); l++) len++;

  if (ec_pcal_sec[0] > 0) {
    sector = ec_pcal_sec[0] - 1;
    e_mu_prime.SetXYZM(px[0], py[0], pz[0], 0.000511);
    fWq2[sector]->Fill(W_calc(e_mu_prime), Q2_calc(e_mu_prime));
    fW[sector]->Fill(W_calc(e_mu_prime));
  }

  if (sc_ftof_1b_time[0] == sc_ftof_1b_time[0]) {
    vertex = vertex_time(sc_ftof_1b_time[0], sc_ftof_1b_path[0], 1.0);
  } else if (sc_ftof_1a_time[0] == sc_ftof_1a_time[0]) {
    vertex = vertex_time(sc_ftof_1a_time[0], sc_ftof_1a_path[0], 1.0);
  } else {
    return kFALSE;
  }

  for (size_t l = 1; l < len; l++) {
    if (p[l] == 0) continue;
    fDeltaT_ctof_component->Fill(sc_ctof_component[l],
                                 delta_t_calc(vertex, p[l], sc_ctof_time[l], sc_ctof_path[l], MASS_P));
    fDeltaT_ctof_component->Fill(sc_ctof_component[l],
                                 delta_t_calc(vertex, p[l], sc_ctof_time[l], sc_ctof_path[l], MASS_PIP));
    if (charge[l] == 1) {
      fDeltaT_1a_prot->Fill(p[l], delta_t_calc(vertex, p[l], sc_ftof_1a_time[l], sc_ftof_1a_path[l], MASS_P));
      fDeltaT_1a_pip->Fill(p[l], delta_t_calc(vertex, p[l], sc_ftof_1a_time[l], sc_ftof_1a_path[l], MASS_PIP));

      fDeltaT_1b_prot->Fill(p[l], delta_t_calc(vertex, p[l], sc_ftof_1b_time[l], sc_ftof_1b_path[l], MASS_P));
      fDeltaT_1b_pip->Fill(p[l], delta_t_calc(vertex, p[l], sc_ftof_1b_time[l], sc_ftof_1b_path[l], MASS_PIP));

      fDeltaT_2_prot->Fill(p[l], delta_t_calc(vertex, p[l], sc_ftof_2_time[l], sc_ftof_2_path[l], MASS_P));
      fDeltaT_2_pip->Fill(p[l], delta_t_calc(vertex, p[l], sc_ftof_2_time[l], sc_ftof_2_path[l], MASS_PIP));

      fDeltaT_ctof_prot->Fill(p[l], delta_t_calc(vertex, p[l], sc_ctof_time[l], sc_ctof_path[l], MASS_P));
      fDeltaT_ctof_pip->Fill(p[l], delta_t_calc(vertex, p[l], sc_ctof_time[l], sc_ctof_path[l], MASS_PIP));

      fDeltaT_ctof_prot_component->Fill(sc_ctof_component[l],
                                        delta_t_calc(vertex, p[l], sc_ctof_time[l], sc_ctof_path[l], MASS_P));
      fDeltaT_ctof_pip_component->Fill(sc_ctof_component[l],
                                       delta_t_calc(vertex, p[l], sc_ctof_time[l], sc_ctof_path[l], MASS_PIP));
    } else if (charge[l] == -1) {
      fDeltaT_1a_pim->Fill(p[l], delta_t_calc(vertex, p[l], sc_ftof_1a_time[l], sc_ftof_1a_path[l], MASS_PIP));
      fDeltaT_1b_pim->Fill(p[l], delta_t_calc(vertex, p[l], sc_ftof_1b_time[l], sc_ftof_1b_path[l], MASS_PIP));
      fDeltaT_2_pim->Fill(p[l], delta_t_calc(vertex, p[l], sc_ftof_2_time[l], sc_ftof_2_path[l], MASS_PIP));
      fDeltaT_ctof_pim->Fill(p[l], delta_t_calc(vertex, p[l], sc_ctof_time[l], sc_ctof_path[l], MASS_PIP));
      fDeltaT_ctof_pim_component->Fill(sc_ctof_component[l],
                                       delta_t_calc(vertex, p[l], sc_ctof_time[l], sc_ctof_path[l], MASS_PIP));
    }
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
  TCanvas *c1 = new TCanvas("c1", "WvsQ2 Canvas", 1600, 900);
  c1->Divide(3, 2);
  for (size_t i = 0; i < 6; i++) {
    TH2D *hf_wq2 = dynamic_cast<TH2D *>(fOutput->FindObject(Form("wq2_%zu", i)));
    c1->cd(i + 1);
    hf_wq2->Draw("colz");
  }

  TCanvas *c2 = new TCanvas("c2", "W Canvas", 1600, 900);
  c2->Divide(3, 2);
  for (size_t i = 0; i < 6; i++) {
    TH1D *hf_w = dynamic_cast<TH1D *>(fOutput->FindObject(Form("w_%zu", i)));
    c2->cd(i + 1);
    hf_w->Fit("gaus", "QMR+", "", 0.5, 1.05);
    hf_w->Draw();
  }

  TH2D *f_1a_prot = dynamic_cast<TH2D *>(fOutput->FindObject("fDeltaT_1a_prot"));
  TH2D *f_1a_pip = dynamic_cast<TH2D *>(fOutput->FindObject("fDeltaT_1a_pion"));
  TH2D *f_1a_pim = dynamic_cast<TH2D *>(fOutput->FindObject("fDeltaT_1a_pion_m"));

  TH2D *f_1b_prot = dynamic_cast<TH2D *>(fOutput->FindObject("fDeltaT_1b_prot"));
  TH2D *f_1b_pip = dynamic_cast<TH2D *>(fOutput->FindObject("fDeltaT_1b_pion"));
  TH2D *f_1b_pim = dynamic_cast<TH2D *>(fOutput->FindObject("fDeltaT_1b_pion_m"));

  TH2D *f_2_prot = dynamic_cast<TH2D *>(fOutput->FindObject("fDeltaT_2_prot"));
  TH2D *f_2_pip = dynamic_cast<TH2D *>(fOutput->FindObject("fDeltaT_2_pion"));
  TH2D *f_2_pim = dynamic_cast<TH2D *>(fOutput->FindObject("fDeltaT_2_pion_m"));

  TH2D *f_ctof_prot = dynamic_cast<TH2D *>(fOutput->FindObject("fDeltaT_ctof_prot"));
  TH2D *f_ctof_pip = dynamic_cast<TH2D *>(fOutput->FindObject("fDeltaT_ctof_pion"));
  TH2D *f_ctof_pim = dynamic_cast<TH2D *>(fOutput->FindObject("fDeltaT_ctof_pion_m"));

  TH2D *f_ctof_prot_component = dynamic_cast<TH2D *>(fOutput->FindObject("fDeltaT_ctof_prot_component"));
  TH2D *f_ctof_pip_component = dynamic_cast<TH2D *>(fOutput->FindObject("fDeltaT_ctof_pion_component"));
  TH2D *f_ctof_pim_component = dynamic_cast<TH2D *>(fOutput->FindObject("fDeltaT_ctof_pion_m_component"));
  TH2D *f_ctof_component = dynamic_cast<TH2D *>(fOutput->FindObject("fDeltaT_ctof_component"));

  TCanvas *c3 = new TCanvas("c3", "Delta_t Canvas", 1600, 900);
  c3->Divide(3, 3);
  int can3 = 1;
  c3->cd(can3++);
  f_1a_prot->Draw("colz");
  c3->cd(can3++);
  f_1a_pip->Draw("colz");
  c3->cd(can3++);
  f_1a_pim->Draw("colz");
  c3->cd(can3++);
  f_1b_prot->Draw("colz");
  c3->cd(can3++);
  f_1b_pip->Draw("colz");
  c3->cd(can3++);
  f_1b_pim->Draw("colz");
  c3->cd(can3++);
  f_2_prot->Draw("colz");
  c3->cd(can3++);
  f_2_pip->Draw("colz");
  c3->cd(can3++);
  f_2_pim->Draw("colz");

  TCanvas *c4 = new TCanvas("c4", "Delta_t Canvas", 1600, 900);
  c4->Divide(3);
  int can4 = 1;
  c4->cd(can4++);
  f_ctof_prot->Draw("colz");
  c4->cd(can4++);
  f_ctof_pip->Draw("colz");
  c4->cd(can4++);
  f_ctof_pim->Draw("colz");

  TCanvas *c5 = new TCanvas("c5", "c5", 1600, 900);
  c5->Divide(2, 2);
  c5->cd(1);
  f_ctof_prot_component->Draw("colz");
  c5->cd(2);
  f_ctof_pip_component->Draw("colz");
  c5->cd(3);
  f_ctof_pim_component->Draw("colz");
  c5->cd(4);
  f_ctof_component->Draw("colz");
}
