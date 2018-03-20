//Run with 
//root --hsfit FitHSBGTime.C
//We want to remove the random data from our background shape
//To do this we fit on the time peak which is Gaussian for background
//(same distribution as for signal) and flat for random data 
{
  THSsPlot* RF=new THSsPlot("binFit"); 
  RF->SetOutDir("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/FittingOverFlow/FitEmptyTarget1FileV2/");
 ///////////////////////////////Load Variables
  RF->LoadVariable("GammaAveTagDiffTime[-80,20]");//should be same name as variable in tree
  RF->LoadBinVars("BeamEnergy",4,500,600);//should be same name as variable in tree 
  RF->LoadAuxVars("Coplanarity[-50,50]");
//  RF->LoadAuxVars("Phi[-180,180]");
//  RF->LoadAuxVars("DetErrs[0,0.5]");
//  RF->LoadAuxVars("Topo[0,1]");
//  RF->LoadAuxVars("InvMass[125,145]"); //Only for Neutron Case(Not used this time)
//  RF->LoadAuxVars("Costh[-1,1]");//Not to be fitted but limits applied to dataset (prev was 20bins)
//  RF->LoadAuxVars("Pol[-1,1]");

  RF->SetIDBranchName("UID");

    ///////////////////////////Load Data
  TChain chain("HSParticles");
  chain.Add("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/EmptyTarget/Dev1.0Files1PhysicsAll.root"); //and background data
  RF->SetIDBranchName("UID");
  //////////////////////////////Split data into bins and load them
  RF->MakeBinnedTrees(&chain,"Data");
  RF->ConfigureSavedBins(RF->GetOutDir());
  
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

  RF->GetWeights()->Save();
 
}
