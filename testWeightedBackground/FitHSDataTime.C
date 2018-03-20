//Run with 
//root --hsfit FitHSDataTime.C
//We want to remove the random data from our background shape
//To do this we fit on the time peak which is Gaussian for background
//(same distribution as for signal) and flat for random data 
{
  THSsPlot* RF=new THSsPlot("binFit"); 
  RF->SetOutDir("outDataTime/");
 ///////////////////////////////Load Variables
  RF->LoadVariable("Time[-10,10]");//should be same name as variable in tree
  RF->LoadBinVars("Eg",4,3,4);//should be same name as variable in tree 
  RF->SetIDBranchName("fgID");

    ///////////////////////////Load Data
  TChain chain("MyModel");
  chain.Add("Data.root"); //and background data
  RF->SetIDBranchName("fgID");
  //////////////////////////////Split data into bins and load them
  RF->MakeBinnedTrees(&chain,"Data");
  RF->ConfigureSavedBins(RF->GetOutDir());
  
  /////////////////////////////Make Model Signal
  RF->Factory("Gaussian::TimeCoinc( Time, mean[0,-10,10], SIMw[1,0.0001,10] )");
  RF->LoadSpeciesPDF("TimeCoinc");

  ////////////////////////////////Additional background
  RF->Factory("Chebychev::Random(Time,{a0[0.1,-0.4,0.4],a1[-0.1,-0.3,0.3]})");
  RF->LoadSpeciesPDF("Random");

  gBenchmark->Start("Binned");
  RF->FitSavedBins(2);//argument gives number of parameter fits to perform
  gBenchmark->Stop("Binned");
  gBenchmark->Print("Binned");

  //chain deleted so recreate for extra plots  
  TChain chain2("MyModel");
 // chain2.Add("BGData.root"); //Mention to Derek so can fix on git
  chain2.Add("Data.root");
  RF->LoadDataSet(&chain2);
 
  RF->DrawTreeVar("Mmiss",100,0,10);
  RF->DrawTreeVar("M1",100,0,10);
  RF->DrawTreeVar("M2",100,0,10);


  RF->GetWeights()->Save();
 
}
