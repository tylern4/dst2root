#include <chrono>
#include "TH2.h"
#include "TLorentzVector.h"

std::vector<int> *pid;
std::vector<float> *p;
std::vector<int> *charge;

std::vector<float> *sc_ftof_time;
std::vector<float> *sc_ftof_path;

static const double MASS_P = 0.93827203;
static const double MASS_PIP = 0.13957018;
const double c_special_units = 29.9792458;

double vertex_time(double sc_time, double sc_pathlength, double relatavistic_beta) {
  return sc_time - sc_pathlength / (relatavistic_beta * c_special_units);
}

int deltat() {
  TH2D *deltaT_prot = new TH2D("deltaT_prot", "#Deltat Proton", 500, 0, 7.0, 500, -10, 10);
  TH2D *deltaT_pip = new TH2D("deltaT_pion", "#Deltat #pi^{+}", 500, 0, 7.0, 500, -10, 10);
  TH2D *deltaT_pim = new TH2D("deltaT_pion_m", "#Deltat #pi^{-}", 500, 0, 7.0, 500, -10, 10);

  TChain *clas12 = new TChain("clas12", "clas12");

  clas12->Add("test.root");
  clas12->SetBranchAddress("pid", &pid);
  clas12->SetBranchAddress("p", &p);
  clas12->SetBranchAddress("charge", &charge);

  clas12->SetBranchAddress("sc_ftof_time", &sc_ftof_time);
  clas12->SetBranchAddress("sc_ftof_path", &sc_ftof_path);

  int num_of_events = (int)clas12->GetEntries();
  auto start_full = std::chrono::high_resolution_clock::now();
  double beta = 0.0;
  double dt_P, dt_PIP;
  for (int current_event = 0; current_event < num_of_events; current_event++) {
    clas12->GetEntry(current_event);
    if (pid->size() == 0) continue;
    double vertex = vertex_time(sc_ftof_time->at(0), sc_ftof_path->at(0), 1.0);
    for (size_t part = 0; part < pid->size(); part++) {
      if (p->at(part) == 0) continue;
      if (charge->at(part) == 1) {
        beta = 1.0 / sqrt(1.0 + (MASS_P / p->at(part)) * (MASS_P / p->at(part)));
        dt_P = vertex - vertex_time(sc_ftof_time->at(part), sc_ftof_path->at(part), beta);
        deltaT_prot->Fill(p->at(part), dt_P);
        beta = 1.0 / sqrt(1.0 + (MASS_PIP / p->at(part)) * (MASS_PIP / p->at(part)));
        dt_PIP = vertex - vertex_time(sc_ftof_time->at(part), sc_ftof_path->at(part), beta);
        deltaT_pip->Fill(p->at(part), dt_PIP);
      } else if (charge->at(part) == -1) {
        beta = 1.0 / sqrt(1.0 + (MASS_PIP / p->at(part)) * (MASS_PIP / p->at(part)));
        dt_PIP = vertex - vertex_time(sc_ftof_time->at(part), sc_ftof_path->at(part), beta);
        deltaT_pip->Fill(p->at(part), dt_PIP);
      }
    }
  }

  std::chrono::duration<double> elapsed_full = (std::chrono::high_resolution_clock::now() - start_full);
  std::cout << "Elapsed time for " << num_of_events << " events: " << elapsed_full.count() << " s" << std::endl;
  std::cout << "Events/Sec: " << num_of_events / elapsed_full.count() << " Hz" << std::endl;

  TCanvas *c1 = new TCanvas("c1", "c1");
  c1->cd();
  deltaT_prot->Draw("colz");

  TCanvas *c2 = new TCanvas("c2", "c2");
  c2->cd();
  deltaT_pip->Draw("colz");

  TCanvas *c3 = new TCanvas("c3", "c3");
  c3->cd();
  deltaT_pim->Draw("colz");

  return 0;
}
