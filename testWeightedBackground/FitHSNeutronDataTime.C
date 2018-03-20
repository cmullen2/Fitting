//Run with 
//root --hsfit FitHSDataTime.C
//We want to remove the random data from our background shape
//To do this we fit on the time peak which is Gaussian for background
//(same distribution as for signal) and flat for random data 
{
  THSsPlot* RF=new THSsPlot("binFit"); 
  RF->SetOutDir("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/Fitting/FitProtonTiming10Bins1Files/");
 ///////////////////////////////Load Variables
  RF->LoadVariable("GammaAveTagDiffTime[-80,20]");//should be same name as variable in tree
//  RF->LoadBinVars("Eg",4,3,4);//should be same name as variable in tree 
//  RF->LoadAuxVars("Phi[-180,180]");
//  RF->LoadAuxVars("InvMass[125,145]"); //Only for Neutron Case(Not used this time)
//  RF->LoadAuxVars("Costh[-1,1]");//Not to be fitted but limits applied to dataset (prev was 20bins)
//  RF->LoadAuxVars("Pol[-1,1]");
 //maybe need this next two lines from after configuring bins
  RooRealVar * var=RF->GetWorkSpace()->var("GammaAveTagDiffTime");
  var->setBins(100); //number of bins used in PDF histogram
  RF->SetIDBranchName("UID");


    ///////////////////////////Load Data
//  TChain chain("MyModel");
//  chain.Add("Data.root"); //and background data
//  RF->SetIDBranchName("fgID");
  //////////////////////////////Split data into bins and load them
//  RF->MakeBinnedTrees(&chain,"Data");
//  RF->ConfigureSavedBins(RF->GetOutDir());
  RF->ConfigureSavedBins("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/Fitting/All3Binned1FilesProtonW10/"); 
  
 
  /////////////////////////////Make Model Signal
  RF->Factory("Gaussian::TimeCoinc(GammaAveTagDiffTime, mean[-60,-80,20], SIMw[10,0,100] )");
  RF->LoadSpeciesPDF("TimeCoinc");

  ////////////////////////////////Additional background
  RF->Factory("Chebychev::Random(GammaAveTagDiffTime,{a0[0.1,-0.4,0.4],a1[-0.1,-0.3,0.3]})");
  RF->LoadSpeciesPDF("Random");

  gBenchmark->Start("Binned");
  RF->FitSavedBins(2);//argument gives number of parameter fits to perform
  gBenchmark->Stop("Binned");
  gBenchmark->Print("Binned");

  //chain deleted so recreate for extra plots  
//  TChain chain2("MyModel");
 // chain2.Add("BGData.root"); //Mention to Derek so can fix on git
//  chain2.Add("Data.root");
//  RF->LoadDataSet(&chain2);
 
//  RF->DrawTreeVar("Mmiss",100,0,10);
//  RF->DrawTreeVar("M1",100,0,10);
//  RF->DrawTreeVar("M2",100,0,10);


  RF->GetWeights()->Save();
 
}
