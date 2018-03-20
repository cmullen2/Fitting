{
  THSWeights* wts=new THSWeights("TotalWeights");
  wts->Merge("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/FittingOverFlow/FitEmptyTarget1File/WeightsBeamEnergy","/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/FittingOverFlow/FitEmptyTarget1File/WeightsTotal.root","HSsWeights");
 
  TChain chain("HSParticles");
  chain.AddFile("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/EmptyTarget/Dev1.0Files1PhysicsAll.root");
  Double_t ID,Coplanarity;
  chain.SetBranchAddress("UID",&ID);
  chain.SetBranchAddress("Coplanarity",&Coplanarity);
  
  TH1F* histM1S=new TH1F("CoplanarityS","CoplanarityS",100,-50,50);
  TH1F* histM1B=new TH1F("CoplanarityB","CoplanarityB",100,-50,50);
  Double_t weight=0;
  
  for(Int_t i=0;i<chain.GetEntries();i++){
    chain.GetEntry(i);
    if(wts->GetEntryBinarySearch(ID)){//find the weight for this event
      histM1S->Fill(Coplanarity,wts->GetWeight("TimeCoinc"));
      histM1B->Fill(Coplanarity,wts->GetWeight("Random"));
    }
  }


  TFile* outfile = new TFile("Coplan.root","recreate");
 


  histM1S->Draw();
  histM1B->Draw();
  histM1S->Write();
  histM1B->Write()
}
