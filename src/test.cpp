/*
 *
 * Author: Nick Tyler, University Of South Carolina
 */
// Standard libs
#include <time.h>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <vector>
// ROOT libs
#include "TFile.h"
#include "TTree.h"
// Hipo libs
#include "reader.h"

#include "clipp.h"
#include "constants.h"

// Detector
#define BMT 1
#define BST 2
#define CND 3
#define CTOF 4
#define CVT 5
#define DC 6
#define ECAL 7
#define FMT 8
#define FT 9
#define FTCAL 10
#define FTHODO 11
#define FTOF 12
#define FTTRK 13
#define HTCC 15
#define LTCC 16
#define RF 17
#define RICH 18
#define RTPC 19
#define HEL 20
#define BAND 21

// Layer
#define FTOF_1A 1
#define FTOF_1B 2
#define FTOF_2 3
#define PCAL 1
#define EC_INNER 4
#define EC_OUTER 7

int main(int argc, char **argv) {
  std::string InFileName = "";
  std::string OutFileName = "";
  bool is_mc = false;
  bool is_batch = false;
  bool print_help = false;
  bool good_rec = false;
  bool elec_first = false;
  bool cov = false;
  bool cvt = false;

  auto cli =
      (clipp::option("-h", "--help").set(print_help) % "print help",
       clipp::option("-mc", "--MC").set(is_mc) % "Convert dst and mc banks",
       clipp::option("-b", "--batch").set(is_batch) % "Don't show progress and statistics",
       clipp::option("-r", "--rec").set(good_rec) % "Only save events where number of partilces in the event > 0",
       clipp::option("-e", "--elec").set(elec_first) % "Only save events with good electron as first particle",
       clipp::option("-c", "--cov").set(cov) % "Save Covariant Matrix for kinematic fitting",
       clipp::option("-cvt", "--CVTDetector").set(cvt) % "Save CVT information for kinematic fitting",
       clipp::value("inputFile.hipo", InFileName), clipp::opt_value("outputFile.root", OutFileName));

  clipp::parse(argc, argv, cli);
  if (print_help || InFileName == "") {
    std::cout << clipp::make_man_page(cli, argv[0]);
    exit(0);
  }

  if (OutFileName == "") OutFileName = InFileName + ".root";

  std::vector<int> pid;
  std::vector<float> p;
  std::vector<float> p2;
  std::vector<float> px;
  std::vector<float> py;
  std::vector<float> pz;
  std::vector<float> vx;
  std::vector<float> vy;
  std::vector<float> vz;
  std::vector<int> charge;
  std::vector<float> beta;
  std::vector<float> chi2pid;
  std::vector<int> status;

  auto start_full = std::chrono::high_resolution_clock::now();
  TFile *OutputFile = new TFile(OutFileName.c_str(), "RECREATE");
  OutputFile->SetCompressionSettings(6);

  TTree *clas12 = new TTree("clas12", "clas12");
  hipo::reader *reader = new hipo::reader(InFileName);

  hipo::dictionary *dict = new hipo::dictionary();
  reader->readDictionary(*dict);

  hipo::event *event = new hipo::event();
  int counter = 0;

  hipo::bank *particles = new hipo::bank(dict->getSchema("REC::Particle"));

  while (reader->next() == true) {
    reader->read(*event);

    int l = particles->getRows();
    pid.resize(l);
    p.resize(l);
    p2.resize(l);
    px.resize(l);
    py.resize(l);
    pz.resize(l);
    vx.resize(l);
    vy.resize(l);
    vz.resize(l);
    charge.resize(l);
    beta.resize(l);
    chi2pid.resize(l);
    status.resize(l);
    for (int i = 0; i < l; i++) {
      pid[i] = particles->getInt("pid", i);
      p2[i] = (particles->getFloat("px", i) * particles->getFloat("px", i) +
               particles->getFloat("py", i) * particles->getFloat("py", i) +
               particles->getFloat("pz", i) * particles->getFloat("pz", i));
      p[i] = sqrt(p2[i]);
      px[i] = particles->getFloat("px", i);
      py[i] = particles->getFloat("py", i);
      pz[i] = particles->getFloat("pz", i);
      vx[i] = particles->getFloat("vx", i);
      vy[i] = particles->getFloat("vy", i);
      vz[i] = particles->getFloat("vz", i);
      charge[i] = particles->getInt("charge", i);
      beta[i] = ((particles->getFloat("beta", i) != -9999) ? particles->getFloat("beta", i) : NAN);
      chi2pid[i] = particles->getFloat("chi2pid", i);
      status[i] = particles->getInt("status", i);
    }
    counter++;
  }
  printf("processed events = %d\n", counter);
}
//### END OF GENERATED CODE
