//root --hsfit  FitHSMCModel.C
//Now try fitting after loading the random weights into the BG model
{
  THSsPlot* RF=new THSsPlot("SF");
  RF->SetOutDir("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/Fitting/DualFitProtonTiming10Bins1Files/");
  ///////////////////////////////Load Variables
  RF->LoadVariable("Coplanarity[-50,50]");//should be same name as variable in tree 
  //RF->LoadAuxVars("BeamEnergy[500,600]");//Not to be fitted but limits applied to dataset
  // RF->LoadAuxVars("M2[-100,100]");//Not to be fitted but used in a cut
  RooRealVar * var=RF->GetWorkSpace()->var("Coplanarity");
  var->setBins(100); //number of bins used in PDF histogram
  //  RF->SetIDBranchName("fgID");
  RF->SetIDBranchName("UID");//this is needed if ID != "UID"


  RF->ConfigureSavedBins("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/Fitting/All3Binned1FilesProtonW10/");
 
  //////////////////////////////Make signal PDF
  RF->Factory("RooHSEventsHistPDF::Sig(Coplanarity,alpha[0,0,20],off[0,-2,2],scale[1,0.8,1.2])");
  RooHSEventsHistPDF* pdf=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("Sig"));
  //Attach MC signal data
 // TChain *chainmc=new TChain("HSParticles","mcsignal");
 // chainmc->Add("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/Flat/SecondAttempt/Output2.root");
 // pdf->SetEvTree(chainmc,RF->GetCut());
  RF->LoadSpeciesPDF("Sig",1);

  //////////////////////////////Make background PDF
  RF->Factory("RooHSEventsHistPDF::BG(Coplanarity,alphaB[0,0,5],offB[0,0,0],scaleB[1.0,0.8,1.2])");
  RF->GetWorkSpace()->var("scaleB")->setConstant();
  RF->GetWorkSpace()->var("alphaB")->setConstant();
  RF->GetWorkSpace()->var("offB")->setConstant();
  
  RooHSEventsHistPDF* pdfb=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("BG"));
  //Attach MC background data
  //TChain *chainmcb=new TChain("HSParticles","mcbackground");
  //chainmcb->Add("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/EmptyTarget/Dev1.0Files1PhysicsAll.root");
//  TDirectory * saveDir=gDirectory;
//  TFile* filemcb=new TFile("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/EmptyTarget/Dev1.0Files1PhysicsAll.root");
//  TTree* treemcb=(TTree*) filemcb->Get("HSParticles");
//  saveDir->cd();

  //Add coincidence time weights to background PDF shape
  //This must be done before SetEvTree
//   pdfb->LoadWeights("TimeCoinc","/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/FittingOverFlow/FitEmptyTarget1File/binFitTweights.root","HSsWeights");
  //  pdfb->SetEvTree(chainmcb,RF->GetCut());  //breaks on this line probs an issue with cut option 
// pdfb->SetEvTree(treemcb,RF->GetCut());  //breaks on this line probs an issue with cut option 
  RF->LoadSpeciesPDF("BG",1);

 //Add data to chain
//  TChain chain("HSParticles");
//  chain.Add("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/TestMulti/Dev15.0Files1PhysicsAll.root");
  //import to RooFit
//  RF->LoadDataSet(&chain);
 // RF->LoadWeights("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/FittingOverFlow/FitProductionTarget1File/binFitTweights.root ","HSsWeights");
  RF->LoadWeights("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/Fitting/FitProtonTiming10Bins1Files/binFitTweights.root","HSsWeights");
  RF->SetWeightName("TimeCoinc"); //Events in timing coincidence
 // RF->SetDataWeight();
  
 
  
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
//  RF->FitAndStudy(1); //argument = number of test fits with random initial pars
  RF->FitSavedBins(2);
  gBenchmark->Stop("Binned");
  gBenchmark->Print("Binned");

  RF->GetWeights()->Save(); //Added Cam 4th Feb 2018, think this is now needed to be able to load weights later

}
