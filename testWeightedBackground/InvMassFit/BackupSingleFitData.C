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
  RF->LoadVariable("GammaAveTagDiffTime[-80,20]");//should be same name as variable in tree
  RooRealVar * var=RF->GetWorkSpace()->var("GammaAveTagDiffTime");
  var->setBins(100); //number of bins used in PDF histogram
  RF->SetIDBranchName("UID");

//Do I need this for a farmed fit!!! No set bin dir does this!!!!
 // RF->ConfigureSavedBins("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/Fitting/All3Binned1FilesProtonW10/"); 
  
 
  RF->Factory("Gaussian::TimeCoinc(GammaAveTagDiffTime, mean[-60,-80,20], SIMw[10,0,100] )");
  RF->LoadSpeciesPDF("TimeCoinc");

  RF->Factory("Chebychev::Random(GammaAveTagDiffTime,{a0[0.1,-0.4,0.4],a1[-0.1,-0.3,0.3]})");
  RF->LoadSpeciesPDF("Random");

  gBenchmark->Start("Binned");
//  RF->FitSavedBins(2);//argument gives number of parameter fits to perform
  RF->FitBatchBin(1);
  gBenchmark->Stop("Binned");
  gBenchmark->Print("Binned");

  RF->GetWeights()->Save();
 
}
