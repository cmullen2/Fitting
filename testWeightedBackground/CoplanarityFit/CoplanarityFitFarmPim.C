{

  TString job=gSystem->Getenv("JOBNAME");
  TString fileDir=gSystem->Getenv("FILEDIR");
  TString prevFitDir=gSystem->Getenv("PREVFITNAME");
  TString weightsPath = fileDir + "/" + prevFitDir + "/Weights" + job + ".root";
  cout << " The weights from the previous fit that will be used for this fit are taken from " <<weightsPath <<endl; 
  
  THSsPlot* RF=new THSsPlot(job);
//  RF->LoadVariable("Coplanarity[-50,50]");//should be same name as variable in tree 
  RF->LoadVariable("Coplanarity[-50,50]");//should be same name as variable in tree 
  RooRealVar * var=RF->GetWorkSpace()->var("Coplanarity");
  var->setBins(100); //number of bins used in PDF histogram
  RF->SetIDBranchName("UID");//this is needed if ID != "UID"

  RF->SetBinDir(fileDir+"/"+job);
//  RF->ConfigureSavedBins("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/Fitting/All3Binned1FilesProtonW10/");
 
  RF->Factory("RooHSEventsHistPDF::Sig(Coplanarity,alpha[0,0,20],off[0,-2,2],scale[1,0.8,1.2])");
  RooHSEventsHistPDF* pdf=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("Sig"));
  RF->LoadSpeciesPDF("Sig",1);

//  cout << " Past the signal pdf "  <<endl; 
  RF->Factory("RooHSEventsHistPDF::BG(Coplanarity,alphaB[0,0,5],offB[0,0,0],scaleB[1.0,0.8,1.2])");
  RooHSEventsHistPDF* pdfb=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("BG"));
  RF->LoadSpeciesPDF("BG",1);

//  RF->Factory("Chebychev:BG(Coplanarity,{a0[0.1,-0.4,0.4],a1[-0.1,-0.3,0.3], a2[-0.1,-0.3,0.3]}  )");
//  RF->Factory("Polynomial:BG2(Coplanarity,a0[0.1,-0.4,0.4],a1[-0.1,-0.3,0.3])");
//  RF->LoadSpeciesPDF("BG2",1);
//  RF->LoadSpeciesPDF("BG",1);

//  cout << " Past the signal pdf2 "  <<endl; 
//  RF->GetWorkSpace()->var("scaleB")->setConstant();
//  RF->GetWorkSpace()->var("alphaB")->setConstant();
//  RF->GetWorkSpace()->var("offB")->setConstant();
  

//  cout << " Past the signal pdf3 "  <<endl; 
  RF->LoadWeights(weightsPath,"HSsWeights"); //Cp first to scratch or read from work? What is quicker? What is standard?
  //RF->LoadWeights("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/Fitting/FitProtonTiming10Bins1Files/binFitTweights.root","HSsWeights"); //Cp first to scratch or read from work? What is quicker? What is standard?
  RF->SetWeightName("TimeCoinc"); //Events in timing coincidence
  
  
//  cout << " Past the signal pdf4 "  <<endl; 
  gBenchmark->Start("Binned");
  RF->AddGausConstraint(pdf->AlphaConstraint());
  RF->AddGausConstraint(pdf->OffConstraint());
  RF->AddGausConstraint(pdf->ScaleConstraint());
//  RF->AddGausConstraint(pdfb->AlphaConstraint());
//  RF->AddGausConstraint(pdfb->OffConstraint());
//  RF->AddGausConstraint(pdfb->ScaleConstraint());
//  RF->FitSavedBins(2);
  RF->FitBatchBin(1);
  gBenchmark->Stop("Binned");
  gBenchmark->Print("Binned");

  RF->GetWeights()->Save(); //Added Cam 4th Feb 2018, think this is now needed to be able to load weights later

}
