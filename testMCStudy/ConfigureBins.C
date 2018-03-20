//root --hsfit ConfigureBins.C 
{
  THSRooFit* RF=new THSRooFit("Binner");
  RF->SetOutDir("outRes10Bins/");
  ///////////////////////////////Load Variables
  RF->LoadVariable("Phi[-180,180]");//going to fit this
  RF->LoadVariable("Pol[0,1]");
  RF->LoadAuxVars("genPhi[-180,180]");
  RF->LoadAuxVars("genPol[0,1]");
  RF->LoadBinVars("Eg",1,3,4);//Must have at least 1 bin defined

  TChain *chainData=new TChain("MyModel");
  chainData->Add("DataSymRes10.root");
   
  TChain *chainMC=new TChain("MyModel");
  chainMC->Add("SimDataSymRes10.root");

  gBenchmark->Start("Trees");
  
  RF->MakeBinnedTrees(chainMC,"SigAsym");
  RF->MakeBinnedTrees(chainData,"Data");

  gBenchmark->Stop("Trees");
  gBenchmark->Print("Trees");
}
