#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <fstream>

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TStyle.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TGraphErrors.h>

#include "UserCode/Stop4Body/interface/json.hpp"
#include "UserCode/Stop4Body/interface/SampleReader.h"
#include "UserCode/Stop4Body/interface/doubleWithUncertainty.h"
#define _USE_CERN_ROOT
#include "UserCode/Stop4Body/interface/ValueWithSystematics.h"

using json = nlohmann::json;

class NullBuffer : public std::streambuf
{
  public:
    int overflow(int c) { return c; }
};

class NullStream : public std::ostream
{
  public:
    NullStream():std::ostream(&m_sb) {}
  private:
    NullBuffer m_sb;
};

int main(int argc, char** argv)
{
  std::string jsonFileName = "";
  std::string inputDirectory = "";
  std::string outputDirectory = "./OUT/";
  std::string suffix = "";
  double luminosity = -1.0;
  bool verbose = false;
  double SRCut = 0.4;
  double CRCut = 0.2;
  bool isHighDM = false;
  bool doVR1 = false; // Swap the Met and LepPt for this VR
  bool doVR2 = false; // Invert the Met for this VR
  bool doVR3 = false; // Invert the LepPt for this VR
  bool unblind = false;

  if(argc < 2)
  {
    std::cout << "You did not pass enough parameters" << std::endl;
    //printHelp();
    return 0;
  }

  for(int i = 1; i < argc; ++i)
  {
    std::string argument = argv[i];

    /*if(argument == "--help")
    {
      printHelp();
      return 0;
    }// */

    if(argument == "--json")
      jsonFileName = argv[++i];

    if(argument == "--outDir")
      outputDirectory = argv[++i];

    if(argument == "--inDir")
      inputDirectory = argv[++i];

    if(argument == "--suffix")
      suffix = argv[++i];

    if(argument == "--unblind")
      unblind = true;

    if(argument == "--lumi")
    {
      std::stringstream convert;
      convert << argv[++i];
      convert >> luminosity;
    }

    if(argument == "--signalRegionCut")
    {
      std::stringstream convert;
      convert << argv[++i];
      convert >> SRCut;
    }

    if(argument == "--controlRegionCut")
    {
      std::stringstream convert;
      convert << argv[++i];
      convert >> CRCut;
    }

    if(argument == "--doVR1")
    {
      doVR1 = true;
    }

    if(argument == "--isHighDeltaM")
    {
      isHighDM = true;
    }

    if(argument == "--doVR2")
    {
      doVR2 = true;
    }

    if(argument == "--doVR3")
    {
      doVR3 = true;
    }

    if(argument == "--verbose")
    {
      verbose = true;
    }
  }

  if(doVR3 && isHighDM)
  {
    std::cerr << "VR3 is not defined for the high DM region. Please revise your options" << std::endl;
    return 1;
  }

  if((doVR1 && doVR2) || (doVR1 && doVR3) || (doVR2 && doVR3))
  {
    std::cerr << "You can not simultaneously do multiple validation regions" << std::endl;
    return 1;
  }

  if(SRCut < CRCut)
  {
    std::cout << "The SR cut (BDT > " << SRCut << ") overlaps with the CR cut (BDT < " << CRCut << ")" << std::endl;
    std::cout << "Changing the CR cut so that they do not overlap." << std::endl;
    CRCut = SRCut;
  }

  gStyle->SetOptStat(000000);
  gStyle->SetOptTitle(0);

  std::cout << "Reading json files" << std::endl;
  SampleReader samples(jsonFileName, inputDirectory, suffix);

  std::string tightSelection = "(isTight == 1)";
  std::string looseSelection = "(isLoose == 1) && !(isTight == 1)";
  std::string promptSelection = "(isPrompt == 1)";
  std::string fakeSelection = "!(isPrompt == 1)";
  std::string VR1Trigger = "(HLT_Mu == 1)";

  // Build selection strings, with the systematic variations
  ValueWithSystematics<std::string> Met          = std::string("Met");
  ValueWithSystematics<std::string> DPhiJet1Jet2 = std::string("DPhiJet1Jet2");
  ValueWithSystematics<std::string> Jet1Pt       = std::string("Jet1Pt");
  ValueWithSystematics<std::string> Jet2Pt       = std::string("Jet2Pt");
  ValueWithSystematics<std::string> HT           = std::string("HT");
  ValueWithSystematics<std::string> NbLoose      = std::string("NbLoose");
  ValueWithSystematics<std::string> NbTight      = std::string("NbTight");
  ValueWithSystematics<std::string> BDT          = std::string("BDT");
  ValueWithSystematics<std::string> LepPt        = std::string("LepPt");
  { // Loading the systematic variations of the quantities above
    std::vector<std::string> variations = {"JES_Up", "JES_Down", "JER_Up", "JER_Down"};
    for(auto& syst : variations)
    {
      Met.Systematic(syst)          = Met.Value() + "_" + syst;
      DPhiJet1Jet2.Systematic(syst) = DPhiJet1Jet2.Value() + "_" + syst;
      Jet1Pt.Systematic(syst)       = Jet1Pt.Value() + "_" + syst;
      Jet2Pt.Systematic(syst)       = Jet2Pt.Value() + "_" + syst;
      HT.Systematic(syst)           = HT.Value() + "_" + syst;
      NbLoose.Systematic(syst)      = NbLoose.Value() + "_" + syst;
      NbTight.Systematic(syst)      = NbTight.Value() + "_" + syst;
      BDT.Systematic(syst)          = BDT.Value() + "_" + syst;
    }
  }

  ValueWithSystematics<std::string> metSelection = std::string("(");
  if(doVR2)
    metSelection += Met + " > 200 && " + Met + " < 280)";
  else
    metSelection += Met + " > 280)";

  ValueWithSystematics<std::string> lepSelection = std::string("(");
  if(isHighDM)
  {
    if(doVR1)
      lepSelection += LepPt + " < 280";
    else
      lepSelection += "1)";
  }
  else
  {
    if(doVR3)
      lepSelection += LepPt + " > 30)";
    else
      lepSelection += LepPt + " < 30)";
  }

  ValueWithSystematics<std::string> wjetsEnrich = std::string("(");
  wjetsEnrich += NbLoose + " == 0)";

  ValueWithSystematics<std::string> ttbarEnrich = std::string("(");
  ttbarEnrich += NbTight + " > 0)";

  ValueWithSystematics<std::string> crSelection = std::string("(");
  {
    std::stringstream converter;
    converter << CRCut;
    crSelection += BDT + " < " + converter.str() + ")";
  }

  ValueWithSystematics<std::string> srSelection = std::string("(");
  {
    std::stringstream converter;
    converter << SRCut;
    srSelection += BDT + " > " + converter.str() + ")";
  }

  ValueWithSystematics<std::string> baseSelection = std::string("(");
  baseSelection += DPhiJet1Jet2 + " < 2.5 || " + Jet2Pt + " < 60) && (" + HT + " > 200) && (" + Jet1Pt + " > 110) && ";
  baseSelection += metSelection + " && ";
  baseSelection += lepSelection;
  if(doVR1)
    baseSelection += " && " + VR1Trigger;

  auto printSel = [&](std::string name, ValueWithSystematics<std::string> selection) -> void
  {
    std::cout << "The used " << name << ":" << std::endl;
    std::cout << "  " << selection.Value() << std::endl;
    for(auto& syst : selection.Systematics())
      std::cout << "   - " << syst << ": " << selection.Systematic(syst) << std::endl;
    std::cout << std::endl;
    return;
  };

  printSel("base selection", baseSelection);
  printSel("CR selection", crSelection);
  printSel("SR selection", srSelection);
  printSel("ttbar enrichment", ttbarEnrich);
  printSel("wjets enrichment", wjetsEnrich);
  printSel("tight selection", tightSelection);
  printSel("loose selection", looseSelection);
  printSel("prompt selection", promptSelection);
  printSel("fake selection", fakeSelection);


  std::vector<std::string> systematics = {"JES", "JER"};
  {
    auto loadSystName = [&systematics](std::string baseName, int bins, int min = 1) -> void
    {
      for(int i = min; i <= bins; ++i)
      {
        std::stringstream converter;
        converter << baseName << i;
        systematics.push_back(converter.str());
      }
      return;
    };

    systematics.push_back("PU");

    loadSystName("Q2_", 8);

    systematics.push_back("CFErr1");
    systematics.push_back("CFErr2");
    systematics.push_back("HF");
    systematics.push_back("HFStats1");
    systematics.push_back("HFStats2");
    systematics.push_back("LF");
    systematics.push_back("LFStats1");
    systematics.push_back("LFStats2");

    systematics.push_back("FullFast");
    systematics.push_back("FullFast_HIIP_AltCorr");
    systematics.push_back("FullFast_ID_AltCorr");
    loadSystName("FullFast_HIIP_Electron_Bin", 40);
    loadSystName("FullFast_HIIP_Muon_Bin", 48);
    loadSystName("FullFast_ID_Electron_Bin", 35);
    loadSystName("FullFast_ID_Muon_Bin", 42);

    systematics.push_back("LeptonIDSF_AltCorr");
    systematics.push_back("LeptonISOSF_AltCorr");
    loadSystName("LeptonIDSF_Electron_Bin", 98);
    loadSystName("LeptonIDSF_Muon_Bin", 56);
    loadSystName("LeptonISOSF_Electron_Bin", 12);
    loadSystName("LeptonISOSF_Muon_Bin", 6);

    systematics.push_back("ISRweight_AltCorr");
    loadSystName("ISRweight_Bin", 6);

    systematics.push_back("EWKISRweight_AltCorr");
    loadSystName("EWKISRweight_Bin", 7);

    systematics.push_back("TightLoose_AltCorr");
    loadSystName("TightLoose_Electron_Bin", 16);
    loadSystName("TightLoose_Muon_Bin", 18);

    systematics.push_back("TightLoose_NU_AltCorr");
    loadSystName("TightLoose_NU_Bin", 5);

    systematics.push_back("triggerEfficiency");

    systematics.push_back("triggerEfficiency_stat");
  }
  std::vector<std::string> variations;
  {
    for(auto& syst : systematics)
    {
      variations.push_back(syst+"_Up");
      variations.push_back(syst+"_Down");
    }
  }
  ValueWithSystematics<std::string> weight = std::string("weight");
  for(auto& syst : variations)
  {
    weight.Systematic(syst) = weight.Value() + "_" + syst;
  }

  if(verbose)
    std::cout << "Splitting samples according to type" << std::endl;
  auto MC = samples.getMCBkg();
  auto Sig = samples.getMCSig();
  auto Data = samples.getData();

  if(verbose)
    std::cout << "Building background process map" << std::endl;
  std::map<std::string, size_t> bkgMap;
  bool foundTTbar = false, foundWJets = false;
  for(size_t i = 0; i < MC.nProcesses(); ++i)
  {
    if(MC.process(i).tag().find("ttbar") != std::string::npos)
    {
      bkgMap["ttbar"] = i;
      foundTTbar = true;
    }
    else
      bkgMap[MC.process(i).tag()] = i;

    if(MC.process(i).tag() == "WJets")
      foundWJets = true;
  }
  if(!foundTTbar)
  {
    std::cout << "There isn't a ttbar sample in the JSON file" << std::endl;
    return 1;
  }
  if(!foundWJets)
  {
    std::cout << "There isn't a wjets sample in the JSON file" << std::endl;
    return 1;
  }


  if(verbose)
    std::cout << "Filtering the trees" << std::endl;

  TChain* tmpChain = Data.getChain();
  TTree* dataTree = tmpChain->CopyTree(baseSelection.Value().c_str());
  delete tmpChain;

  tmpChain = MC.getChain();
  ValueWithSystematics<TTree*> bkgTree = tmpChain->CopyTree(baseSelection.Value().c_str()); // Do we even need a specific tree for background?
  for(auto& syst : baseSelection.Systematics())
  {
    bkgTree.Systematic(syst) = tmpChain->CopyTree(baseSelection.Systematic(syst).c_str());
  }
  delete tmpChain;

  std::vector<ValueWithSystematics<TTree*>> sigTree;
  for(size_t i = 0; i < Sig.nProcesses(); ++i)
  {
    tmpChain = Sig.process(i).getChain();
    sigTree.push_back(tmpChain->CopyTree(baseSelection.Value().c_str()));
    for(auto& syst : baseSelection.Systematics())
    {
      sigTree[i].Systematic(syst) = tmpChain->CopyTree(baseSelection.Systematic(syst).c_str());
    }
    delete tmpChain;
  }

  std::vector<ValueWithSystematics<TTree*>> mcTree;
  for(size_t i = 0; i < MC.nProcesses(); ++i)
  {
    tmpChain = MC.process(i).getChain();
    mcTree.push_back(tmpChain->CopyTree(baseSelection.Value().c_str()));
    for(auto& syst : baseSelection.Systematics())
    {
      mcTree[i].Systematic(syst) = tmpChain->CopyTree(baseSelection.Systematic(syst).c_str());
    }
    delete tmpChain;
  }

  if(verbose)
    std::cout << "Done filtering" << std::endl << std::endl;

  if(verbose)
    std::cout << "Preparing to compute all the analysis yields" << std::endl;

  auto getYield = [&](ValueWithSystematics<TTree*> tree, ValueWithSystematics<std::string> weight) -> ValueWithSystematics<double>
  {
    ValueWithSystematics<double> retVal = 0.0;
    std::vector<std::string> mySystematics = {"central"};
    loadSystematics(mySystematics, tree);
    loadSystematics(mySystematics, weight);

    for(auto& syst : mySystematics)
    {
      TH1D tmpHist("tmpHist", "tmpHist", 1, 0.0, 20.0);
      tmpHist.Sumw2();

      tree.GetSystematicOrValue(syst)->Draw("weight>>tmpHist", weight.GetSystematicOrValue(syst).c_str());

      double val = tmpHist.GetBinContent(0) + tmpHist.GetBinContent(1) + tmpHist.GetBinContent(2);
      double unc = tmpHist.GetBinError(0) + tmpHist.GetBinError(1) + tmpHist.GetBinError(2);

      if(syst == "central")
      {
        retVal.Value() = val;
        retVal.Systematic("Stat") = unc;
      }
      else
      {
        retVal.Systematic(syst) = val;
      }
    }

    return retVal;
  };

  // The selection cuts for the several regions of interest
  ValueWithSystematics<std::string> theSRSelection = std::string("(");
  theSRSelection += srSelection + " && " + tightSelection + ") * " + weight;
  ValueWithSystematics<std::string> theSRWJetsSelection = std::string("(");
  theSRWJetsSelection += srSelection + " && " + wjetsEnrich + " && " + tightSelection + ") * " + weight;
  ValueWithSystematics<std::string> theSRTTbarSelection = std::string("(");
  theSRTTbarSelection += srSelection + " && " + ttbarEnrich + " && " + tightSelection + ") * " + weight;
  ValueWithSystematics<std::string> theCRWJetsSelection = std::string("(");
  theCRWJetsSelection += crSelection + " && " + wjetsEnrich + " && " + tightSelection + ") * " + weight;
  ValueWithSystematics<std::string> theCRTTbarSelection = std::string("(");
  theCRTTbarSelection += crSelection + " && " + ttbarEnrich + " && " + tightSelection + ") * " + weight;

  // The output file
  TFile outFile((outputDirectory + "/yields.root").c_str(), "RECREATE");

  auto dataSR      = getYield(dataTree, theSRSelection.Value());
  auto dataSRWJets = getYield(dataTree, theSRWJetsSelection.Value());
  auto dataSRTTbar = getYield(dataTree, theSRTTbarSelection.Value());
  auto dataCRWJets = getYield(dataTree, theCRWJetsSelection.Value());
  auto dataCRTTbar = getYield(dataTree, theCRTTbarSelection.Value());
  if(unblind || doVR1 || doVR2 || doVR3)
  {
    dataSR.SaveTTree("SR_data", &outFile);
    dataSRWJets.SaveTTree("SR_WJets_data", &outFile);
    dataSRTTbar.SaveTTree("SR_TTbar_data", &outFile);
  }
  dataCRWJets.SaveTTree("CR_WJets_data", &outFile);
  dataCRTTbar.SaveTTree("CR_TTbar_data", &outFile);

  return 0;
}
