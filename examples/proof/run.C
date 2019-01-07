
void run(std::string files = "files.root") {
  TChain *ch = new TChain("clas12", "My Chain");
  ch->Add(files.c_str());

  auto plite = TProof::Open("");
  ch->SetProof();
  ch->Process("clas12_selector.cxx++");
  // gROOT->ProcessLine(".q;");
}
