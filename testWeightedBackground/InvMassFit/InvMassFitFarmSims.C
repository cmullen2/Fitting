//Run with 
//root --hsfit FitHSDataTime.C
//We want to remove the random data from our background shape
//To do this we fit on the time peak which is Gaussian for background
//(same distribution as for signal) and flat for random data 
{
  TString job=gSystem->Getenv("JOBNAME");
  TString fileDir=gSystem->Getenv("FILEDIR");
  THSsPlot* RF=new THSsPlot(job); 
  RF->SetBinDir(fileDir + "/"+ job);
  RF->LoadVariable("InvMass[80,200]");//should be same name as variable in tree
  RooRealVar * var=RF->GetWorkSpace()->var("InvMass");
  var->setBins(100); //number of bins used in PDF histogram
  RF->SetIDBranchName("UID");

//Do I need this for a farmed fit!!! No set bin dir does this!!!!
 // RF->ConfigureSavedBins("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/Fitting/All3Binned1FilesProtonW10/"); 
  
 
//  RF->Factory("Gaussian::PPipPimT(InvMass, mean[135,80,160], SIMw[10,0,100] )");
  RF->Factory("BifurGauss::PEtaT(InvMass,SIMm[135,80,160], SIMwL[10,0,20], SIMwR[10,0,20]  )");
  RF->LoadSpeciesPDF("PEtaT");

  RF->Factory("Chebychev::Random(InvMass,{a0[0.1,-2,2],a1[-0.1,-2,2],a2[0.4,-2,2]})");
  RF->LoadSpeciesPDF("Random");

  gBenchmark->Start("Binned");
//  RF->FitSavedBins(2);//argument gives number of parameter fits to perform
  RF->FitBatchBin(1,"PEta");
  gBenchmark->Stop("Binned");
  gBenchmark->Print("Binned");

  RF->GetWeights()->Save();
 
}
