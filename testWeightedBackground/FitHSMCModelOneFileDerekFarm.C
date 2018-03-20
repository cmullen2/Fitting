{

  TString job=gSystem->Getenv("JOBNAME");
  TString fileDir=gSystem->Getenv("FILEDIR");
  THSsPlot* RF=new THSsPlot(job);
  RF->LoadVariable("Coplanarity[-50,50]");//should be same name as variable in tree 
  RooRealVar * var=RF->GetWorkSpace()->var("Coplanarity");
  var->setBins(100); //number of bins used in PDF histogram
  RF->SetIDBranchName("UID");//this is needed if ID != "UID"

  RF->SetBinDir(fileDir+"/"+job);
//  RF->ConfigureSavedBins("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/Fitting/All3Binned1FilesProtonW10/");
 
  RF->Factory("RooHSEventsHistPDF::Sig(Coplanarity,alpha[0,0,20],off[0,-2,2],scale[1,0.8,1.2])");
  RooHSEventsHistPDF* pdf=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("Sig"));
  RF->LoadSpeciesPDF("Sig",1);

  RF->Factory("RooHSEventsHistPDF::BG(Coplanarity,alphaB[0,0,5],offB[0,0,0],scaleB[1.0,0.8,1.2])");
  RooHSEventsHistPDF* pdfb=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("BG"));
  RF->LoadSpeciesPDF("BG",1);

  RF->GetWorkSpace()->var("scaleB")->setConstant();
  RF->GetWorkSpace()->var("alphaB")->setConstant();
  RF->GetWorkSpace()->var("offB")->setConstant();
  

  RF->LoadWeights("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/Fitting/FitProtonTiming10Bins1Files/binFitTweights.root","HSsWeights"); //Cp first to scratch or read from work? What is quicker? What is standard?
  RF->SetWeightName("TimeCoinc"); //Events in timing coincidence
  
  
  gBenchmark->Start("Binned");
  RF->AddGausConstraint(pdf->AlphaConstraint());
  RF->AddGausConstraint(pdf->OffConstraint());
  RF->AddGausConstraint(pdf->ScaleConstraint());
  RF->AddGausConstraint(pdfb->AlphaConstraint());
  RF->AddGausConstraint(pdfb->OffConstraint());
  RF->AddGausConstraint(pdfb->ScaleConstraint());
//  RF->FitSavedBins(2);
  RF->FitBatchBin(1);
  gBenchmark->Stop("Binned");
  gBenchmark->Print("Binned");

  RF->GetWeights()->Save(); //Added Cam 4th Feb 2018, think this is now needed to be able to load weights later

}
