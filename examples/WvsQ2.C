#include <chrono>
#include "TCanvas.h"
#include "TChain.h"
#include "TH2.h"
#include "TLorentzVector.h"

std::vector<int> *pid;
std::vector<float> *p;
std::vector<float> *px;
std::vector<float> *py;
std::vector<float> *pz;
std::vector<float> *beta;
std::vector<int> *charge;
std::vector<float> *ec_tot_energy;

static const double MASS_E = 0.000511;
static const double MASS_P = 0.93827203;

// Calcuating Q^2
// q^mu^2 = (e^mu - e^mu')^2 = -Q^2
double Q2_calc(TLorentzVector e_mu, TLorentzVector e_mu_prime) {
  TLorentzVector q_mu = (e_mu - e_mu_prime);
  return -q_mu.Mag2();
}
//	Calcualting W
//	Gotten from s channel [(gamma - P)^2 == s == w^2]
//	Sqrt√[M_p^2 - Q^2 + 2 M_p gamma]
double W_calc(TLorentzVector e_mu, TLorentzVector e_mu_prime) {
  TLorentzVector q_mu = (e_mu - e_mu_prime);
  TVector3 p_mu_3(0, 0, 0);
  TLorentzVector p_mu;
  p_mu.SetVectM(p_mu_3, MASS_P);
  return (p_mu + q_mu).Mag();
}

TH2D *wq2 = new TH2D("wq2", "W vs Q^{2}", 500, 0, 2.2, 500, 0, 0.6);
TH1D *w = new TH1D("w", "W", 500, 0, 2.2);

TChain *clas12 = new TChain("clas12", "clas12");

int WvsQ2(double BEAM = 2.2) {
  TLorentzVector e_mu(0.0, 0.0, BEAM, BEAM);
  TLorentzVector e_mu_prime;
  clas12->Add("test.root");
  clas12->SetBranchAddress("pid", &pid);
  clas12->SetBranchAddress("p", &p);
  clas12->SetBranchAddress("px", &px);
  clas12->SetBranchAddress("py", &py);
  clas12->SetBranchAddress("pz", &pz);
  clas12->SetBranchAddress("beta", &beta);
  clas12->SetBranchAddress("charge", &charge);
  clas12->SetBranchAddress("ec_tot_energy", &ec_tot_energy);

  int num_of_events = (int)clas12->GetEntries();
  auto start_full = std::chrono::high_resolution_clock::now();
  for (int current_event = 0; current_event < num_of_events; current_event++) {
    clas12->GetEntry(current_event);
    if (pid->size() == 0 || pid->at(0) != 11) continue;
    double sf = (ec_tot_energy->at(0) / p->at(0));
    if (sf < 0.3 && sf > 0.2) {
      e_mu_prime.SetXYZM(px->at(0), py->at(0), pz->at(0), MASS_E);
      wq2->Fill(W_calc(e_mu, e_mu_prime), Q2_calc(e_mu, e_mu_prime));
      w->Fill(W_calc(e_mu, e_mu_prime));
    }
  }

  std::chrono::duration<double> elapsed_full = (std::chrono::high_resolution_clock::now() - start_full);
  std::cout << "Elapsed time for " << num_of_events << " events: " << elapsed_full.count() << " s" << std::endl;
  std::cout << "Events/Sec: " << (num_of_events / elapsed_full.count()) << " Hz" << std::endl;

  TCanvas *c1 = new TCanvas("c1", "c1");
  c1->cd();
  wq2->Draw("colz");

  TCanvas *c2 = new TCanvas("c2", "c2");
  c2->cd();
  w->Draw("same");

  return 0;
}
