#include <chrono>
#include "Math/SMatrix.h"
#include "TChain.h"
#include "TLorentzVector.h"

typedef ROOT::Math::SMatrix<double, 5, 5, ROOT::Math::MatRepSym<double, 5>> Covariant;

std::vector<int> *pid;
std::vector<float> *CovMat_11;
std::vector<float> *CovMat_12;
std::vector<float> *CovMat_13;
std::vector<float> *CovMat_14;
std::vector<float> *CovMat_15;
std::vector<float> *CovMat_22;
std::vector<float> *CovMat_23;
std::vector<float> *CovMat_24;
std::vector<float> *CovMat_25;
std::vector<float> *CovMat_33;
std::vector<float> *CovMat_34;
std::vector<float> *CovMat_35;
std::vector<float> *CovMat_44;
std::vector<float> *CovMat_45;
std::vector<float> *CovMat_55;

TChain *clas12 = new TChain("clas12", "clas12");

int CovMat(std::string file = "test.root") {
  clas12->Add(file.c_str());

  clas12->SetBranchAddress("pid", &pid);
  clas12->SetBranchAddress("CovMat_11", &CovMat_11);
  clas12->SetBranchAddress("CovMat_12", &CovMat_12);
  clas12->SetBranchAddress("CovMat_13", &CovMat_13);
  clas12->SetBranchAddress("CovMat_14", &CovMat_14);
  clas12->SetBranchAddress("CovMat_15", &CovMat_15);
  clas12->SetBranchAddress("CovMat_22", &CovMat_22);
  clas12->SetBranchAddress("CovMat_23", &CovMat_23);
  clas12->SetBranchAddress("CovMat_24", &CovMat_24);
  clas12->SetBranchAddress("CovMat_25", &CovMat_25);
  clas12->SetBranchAddress("CovMat_33", &CovMat_33);
  clas12->SetBranchAddress("CovMat_34", &CovMat_34);
  clas12->SetBranchAddress("CovMat_35", &CovMat_35);
  clas12->SetBranchAddress("CovMat_44", &CovMat_44);
  clas12->SetBranchAddress("CovMat_45", &CovMat_45);
  clas12->SetBranchAddress("CovMat_55", &CovMat_55);

  Covariant KinFitCov;

  int num_of_events = (int)clas12->GetEntries();
  auto start_full = std::chrono::high_resolution_clock::now();
  for (int current_event = 0; current_event < num_of_events; current_event++) {
    clas12->GetEntry(current_event);
    if (pid->size() == 0) continue;
    for (int part = 0; part < pid->size(); part++) {
      KinFitCov(0, 0) = CovMat_11->at(part);
      KinFitCov(0, 1) = CovMat_12->at(part);
      KinFitCov(0, 2) = CovMat_13->at(part);
      KinFitCov(0, 3) = CovMat_14->at(part);
      KinFitCov(0, 4) = CovMat_15->at(part);
      KinFitCov(1, 1) = CovMat_22->at(part);
      KinFitCov(1, 2) = CovMat_23->at(part);
      KinFitCov(1, 3) = CovMat_24->at(part);
      KinFitCov(1, 4) = CovMat_25->at(part);
      KinFitCov(2, 2) = CovMat_33->at(part);
      KinFitCov(2, 3) = CovMat_34->at(part);
      KinFitCov(2, 4) = CovMat_35->at(part);
      KinFitCov(3, 3) = CovMat_44->at(part);
      KinFitCov(3, 4) = CovMat_45->at(part);
      KinFitCov(4, 4) = CovMat_55->at(part);
      if (KinFitCov(0, 0) == KinFitCov(0, 0)) std::cout << KinFitCov << '\n';
    }
  }

  std::chrono::duration<double> elapsed_full = (std::chrono::high_resolution_clock::now() - start_full);
  std::cout << "Elapsed time for " << num_of_events << " events: " << elapsed_full.count() << " s" << std::endl;
  std::cout << "Events/Sec: " << (num_of_events / elapsed_full.count()) << " Hz" << std::endl;

  return 0;
}
