#ifndef NanoGenSelectorBase_h
#define NanoGenSelectorBase_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TH1.h>
#include <TH2.h>
#include <exception>
#include <iostream>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include <vector>
#include "Analysis/VVAnalysis/interface/ScaleFactor.h"
#include "Analysis/VVAnalysis/interface/SelectorBase.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "Analysis/VVAnalysis/interface/helpers.h"
#include "Analysis/VVAnalysis/interface/BranchManager.h"
#include "PhysicsTools/HepMCCandAlgos/interface/PDFWeightsHelper.h"

class NanoGenSelectorBase : public SelectorBase {
public :
    PDFWeightsHelper pdfweightshelper_;
    // Derived values
    reco::GenParticleCollection leptons;
    //std::unique_ptr<reco::GenParticleCollection> testleptons;
    reco::GenParticleCollection bareLeptons;
    reco::GenParticleCollection dressedLeptons;
    reco::GenParticleCollection neutrinos;
    std::vector<LorentzVector> jets;
    LorentzVector genMet;

    unsigned int nLeptons_ = 1;
    static const unsigned int N_LHESCALE_WEIGHTS_ = 10;
    static const unsigned int N_LHEPDF_WEIGHTS_ = 100;
    static const unsigned int N_LHEPDFAS_WEIGHTS_ = 102;
    static const unsigned int N_MC2HESSIAN_WEIGHTS_ = 60;
    float weight;
    bool doMC2H_ = false;
    bool doBareLeptons_ = false;
    bool doBornLeptons_ = false;
    bool doNeutrinos_ = false;

    TH1D* mcPdfWeights_;
    TH1D* hesPdfWeights_;
    TH1D* scaleWeights_;
    
    double LHEHessianPdfWeight[N_MC2HESSIAN_WEIGHTS_];
    // Values read from file
    TTreeReader     fReader;
    TTreeReaderValue<Float_t> genWeight = {fReader, "genWeight"};
    TTreeReaderValue<UInt_t> nLHEScaleWeight = {fReader, "nLHEScaleWeight"};
    TTreeReaderValue<UInt_t> nLHEPdfWeight = {fReader, "nLHEPdfWeight"};
    TTreeReaderArray<Float_t> LHEScaleWeight = {fReader, "LHEScaleWeight"};
    TTreeReaderArray<Float_t> LHEPdfWeight = {fReader, "LHEPdfWeight"};

    TTreeReaderValue<UInt_t> nGenDressedLepton = {fReader, "nGenDressedLepton"};
    TTreeReaderArray<Float_t> GenDressedLepton_pt = {fReader, "GenDressedLepton_pt"};
    TTreeReaderArray<Float_t> GenDressedLepton_eta = {fReader, "GenDressedLepton_eta"};
    TTreeReaderArray<Float_t> GenDressedLepton_phi = {fReader, "GenDressedLepton_phi"};
    TTreeReaderArray<Float_t> GenDressedLepton_mass = {fReader, "GenDressedLepton_mass"};
    TTreeReaderArray<Int_t> GenDressedLepton_pdgId = {fReader, "GenDressedLepton_pdgId"};
    TTreeReaderValue<UInt_t> nGenPart = {fReader, "nGenPart"};
    TTreeReaderArray<Float_t> GenPart_pt = {fReader, "GenPart_pt"};
    TTreeReaderArray<Float_t> GenPart_eta = {fReader, "GenPart_eta"};
    TTreeReaderArray<Float_t> GenPart_phi = {fReader, "GenPart_phi"};
    TTreeReaderArray<Float_t> GenPart_mass = {fReader, "GenPart_mass"};
    TTreeReaderArray<Int_t> GenPart_pdgId = {fReader, "GenPart_pdgId"};
    TTreeReaderArray<Int_t> GenPart_status = {fReader, "GenPart_status"};
    TTreeReaderValue<UInt_t> nGenJet = {fReader, "nGenJet"};
    TTreeReaderArray<Float_t> GenJet_pt = {fReader, "GenJet_pt"};
    TTreeReaderArray<Float_t> GenJet_eta = {fReader, "GenJet_eta"};
    TTreeReaderArray<Float_t> GenJet_phi = {fReader, "GenJet_phi"};
    TTreeReaderArray<Float_t> GenJet_mass = {fReader, "GenJet_mass"};
    //TTreeReaderValue<Float_t> GenMET_pt = {fReader, "GenMET_pt"};
    //TTreeReaderValue<Float_t> GenMET_phi = {fReader, "GenMET_phi"};
    TTreeReaderValue<Float_t> MET_fiducialGenPt = {fReader, "MET_fiducialGenPt"};
    TTreeReaderValue<Float_t> MET_fiducialGenPhi = {fReader, "MET_fiducialGenPhi"};
    float ht;
    
    BranchManager b;
    
    // Readers to access the data (delete the ones you do not need).
    virtual void    Init(TTree *tree) override;
    NanoGenSelectorBase(TTree * /*tree*/ =0) { }
    ~NanoGenSelectorBase() { }
    virtual void    SetupNewDirectory() override;

    ClassDefOverride(NanoGenSelectorBase,0);

protected:
    virtual void    SetBranchesNanoAOD() override;
    virtual void    FillHistograms(Long64_t entry, std::pair<Systematic, std::string> variation) override {}
    void LoadBranchesNanoAOD(Long64_t entry, std::pair<Systematic, std::string> variation) override;
    virtual void SetComposite() {}
    bool overlapsCollection(const LorentzVector& cand, reco::GenParticleCollection& collection, const float deltaRCut, size_t maxCompare);
    void buildHessian2MCSet();
};

#endif



