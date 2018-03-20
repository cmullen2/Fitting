//root --hsfit  FitHSMCModel.C
//Now try fitting after loading the random weights into the BG model

//CAM -> Topo is done in configure bins so is Eg and costh and DetErrs

{
  THSsPlot* RF=new THSsPlot("SF");
  RF->SetOutDir("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/FittingOverFlow/DualFitProtonTiming20Bins1Files/");
  ///////////////////////////////Load Variables
  RF->LoadVariable("Coplanarity[-50,50]");//should be same name as variable in tree
  RF->LoadAuxVars("Phi[-180,180]");
//  RF->LoadAuxVars("InvMass[125,145]"); //Only for Neutron Case(Not used this time)
  RF->LoadAuxVars("Costh[-1,1]");//Not to be fitted but limits applied to dataset (prev was 20bins)
  RF->LoadAuxVars("Pol[-1,1]");
  RooRealVar * var=RF->GetWorkSpace()->var("Coplanarity");
  var->setBins(100); //number of bins used in PDF histogram
  //RF->SetIDBranchName("UID");

 //RF->ConfigureSavedBins("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/FittingOverFlow/FitEmptyTargetBins1File/"); 



  //////////////////////////////Make signal PDF
  RF->Factory("RooHSEventsHistPDF::Sig(Coplanarity,alpha[0,0,20],off[0,-2,2],scale[1,0.8,1.2])");
  RooHSEventsHistPDF* pdf=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("Sig"));
  //Attach MC signal data
  TChain *chainmc=new TChain("HSParticles","mcsignal");
  chainmc->Add("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/Flat/SecondAttempt/Output2.root");
  pdf->SetEvTree(chainmc,RF->GetCut());
  RF->LoadSpeciesPDF("Sig",1);


 RF->ConfigureSavedBins("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/FittingOverFlow/FitEmptyTargetBins1File/"); 


  //////////////////////////////Make background PDF
  RF->Factory("RooHSEventsHistPDF::BG(Coplanarity,alphaB[0,0,5],offB[0,0,0],scaleB[1.0,0.8,1.2])");
  RF->GetWorkSpace()->var("scaleB")->setConstant();
  RF->GetWorkSpace()->var("alphaB")->setConstant();
  RF->GetWorkSpace()->var("offB")->setConstant();
  
  RooHSEventsHistPDF* pdfb=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("BG"));
  //Attach MC background data
  TChain *chainmcb=new TChain("HSParticles","mcbackground");
  chainmcb->Add("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/EmptyTarget/Dev1.0Files1PhysicsAll.root");
  //Add coincidence time weights to background PDF shape
  //This must be done before SetEvTree
  pdfb->LoadWeights("TimeCoinc","/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/FittingOverFlow/FitEmptyTargetBins1File/binFitTweights.root","HSsWeights");
  cout <<" Before the EvTree " <<endl;
  pdfb->SetEvTree(chainmcb,RF->GetCut());
 cout <<" After the bit has finished " <<endl;
  //breaks on this line probs an issue with cut option 
  RF->LoadSpeciesPDF("BG",1);


 RF->ConfigureSavedBins("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/FittingOverFlow/FitEmptyTargetBins1File/"); 


 //Add data to chain
  TChain chain("HSParticles");
  chain.Add("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/TestMulti/Dev15.0Files1PhysicsAll.root");
  RF->SetIDBranchName("UID");//this is needed if ID != "UID"
  //import to RooFit
  RF->LoadDataSet(&chain);
  RF->LoadWeights("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/FittingOverFlow/FitProtonTiming20Bins1FilesV2/binFitTweights.root ","HSsWeights");
  RF->SetWeightName("TimeCoinc"); //Events in timing coincidence
  RF->SetDataWeight();
  
 
  
  gBenchmark->Start("Binned");
  //Add constraints to PDF fudge parameters
  //These are derived from the alpha off and scale parameter initial val and limits
  //i.e. intital val = gaussian mean; range = 10*sigma
  RF->AddGausConstraint(pdf->AlphaConstraint());
  RF->AddGausConstraint(pdf->OffConstraint());
  RF->AddGausConstraint(pdf->ScaleConstraint());
  RF->AddGausConstraint(pdfb->AlphaConstraint());
  RF->AddGausConstraint(pdfb->OffConstraint());
  RF->AddGausConstraint(pdfb->ScaleConstraint());
  RF->FitAndStudy(1); //argument = number of test fits with random initial pars
  gBenchmark->Stop("Binned");
  gBenchmark->Print("Binned");
//  RF->DrawTreeVar("Mmiss",100,0,10);
//  RF->DrawTreeVar("M1",100,0,10);
//  RF->DrawTreeVar("M2",100,0,10);

}
