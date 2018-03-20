//root  --hsfit ConfigureBins.C
{

  THSRooFit* RF=new THSRooFit("SF");
  RF->SetOutDir("outBins/");
  ///////////////////////////////Load Variables
  RF->LoadAuxVars("Phi[-10,10]");
  RF->LoadAuxVars("Pol[-10,10]");
  RF->LoadAuxVars("PolState[-10,10]");
  RF->LoadBinVars("Eg",4,3,4);//Make 4 bins in Eg between 3 and 4 
  RF->SetIDBranchName("UID");  //Save ID variable fgID

  //"Real" Data files
  TChain chain("MyModel");
  chain.Add("DataASymRes10PS02.root");
  RF->MakeBinnedTrees(&chain,"Data");

  RF->LoadAuxVars("genPhi[-10,10]");
  //MC Signal files
  TChain *chainmc=new TChain("MyModel","mcsignal");
  chainmc->Add("SimASymRes10.root");
  RF->MakeBinnedTrees(chainmc,"Sim");//Note "Sim" will be used to name PDF
}
