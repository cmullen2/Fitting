{

  TString job=gSystem->Getenv("JOBNAME");
  TString fileDir=gSystem->Getenv("FILEDIR");
  TString prevFitDir=gSystem->Getenv("PREVFITNAME");
  TString weightsPath = fileDir + "/" + prevFitDir + "/Weights" + job + ".root";
  cout << " The weights from the previous fit that will be used for this fit are taken from " <<weightsPath <<endl; 
  
  THSsPlot* RF=new THSsPlot(job);
//  RF->LoadVariable("Coplanarity[-50,50]");//should be same name as variable in tree 
  RF->LoadVariable("MissMass[1850,2850]");//should be same name as variable in tree 
  RooRealVar * var=RF->GetWorkSpace()->var("MissMass");
  var->setBins(100); //number of bins used in PDF histogram
  RF->SetIDBranchName("UID");//this is needed if ID != "UID"

  RF->SetBinDir(fileDir+"/"+job);
//  RF->ConfigureSavedBins("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/Fitting/All3Binned1FilesProtonW10/");
 
  RF->Factory("RooHSEventsHistPDF::Sig(MissMass,alpha[0,0,40],off[0,-50,50],scale[1,0.8,1.2])");
  RooHSEventsHistPDF* pdf=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("Sig"));
  RF->LoadSpeciesPDF("Sig",1);

  cout << " Past the signal pdf "  <<endl; 
  RF->Factory("RooHSEventsHistPDF::BG(MissMass,alphaB[0,0,5],offB[0,0,0],scaleB[1.0,0.8,1.2])");
  RooHSEventsHistPDF* pdfb=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("BG"));
  RF->LoadSpeciesPDF("BG",1);


  // Multi Pion BG's
  RF->Factory("RooHSEventsHistPDF::PEta(MissMass,alphaPEta[0,0,20],offPEta[0,-20,20],scalePEta[1,0.8,1.2])"); //4
  RooHSEventsHistPDF* pdfPEta=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("PEta")); //2
  RF->LoadSpeciesPDF("PEta",1); //1


  RF->Factory("RooHSEventsHistPDF::NEta(MissMass,alphaNEta[0,0,20],offNEta[0,-20,20],scaleNEta[1,0.8,1.2])");
  RooHSEventsHistPDF* pdfNEta=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("NEta"));
  RF->LoadSpeciesPDF("NEta",1);


  RF->Factory("RooHSEventsHistPDF::NPi0Pi0(MissMass,alphaNPi0Pi0[0,0,20],offNPi0Pi0[0,-20,20],scaleNPi0Pi0[1,0.8,1.2])");
  RooHSEventsHistPDF* pdfNPi0Pi0=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("NPi0Pi0"));
  RF->LoadSpeciesPDF("NPi0Pi0",1);


  RF->Factory("RooHSEventsHistPDF::NPipPim(MissMass,alphaNPipPim[0,0,20],offNPipPim[0,-20,20],scaleNPipPim[1,0.8,1.2])");
  RooHSEventsHistPDF* pdfNPipPim=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("NPipPim"));
  RF->LoadSpeciesPDF("NPipPim",1);


  RF->Factory("RooHSEventsHistPDF::NPipPi0(MissMass,alphaNPipPi0[0,0,20],offNPipPi0[0,-20,20],scaleNPipPi0[1,0.8,1.2])");
  RooHSEventsHistPDF* pdfNPipPi0=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("NPipPi0"));
  RF->LoadSpeciesPDF("NPipPi0",1);


  RF->Factory("RooHSEventsHistPDF::PPi0Pi0(MissMass,alphaPPi0Pi0[0,0,20],offPPi0Pi0[0,-20,20],scalePPi0Pi0[1,0.8,1.2])");
  RooHSEventsHistPDF* pdfPPi0Pi0=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("PPi0Pi0"));
  RF->LoadSpeciesPDF("PPi0Pi0",1);


  RF->Factory("RooHSEventsHistPDF::PPipPim(MissMass,alphaPPipPim[0,0,20],offPPipPim[0,-20,20],scalePPipPim[1,0.8,1.2])");
  RooHSEventsHistPDF* pdfPPipPim=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("PPipPim"));
  RF->LoadSpeciesPDF("PPipPim",1);


  RF->Factory("RooHSEventsHistPDF::PPi0Pim(MissMass,alphaPPi0Pim[0,0,20],offPPi0Pim[0,-20,20],scalePPi0Pim[1,0.8,1.2])");
  RooHSEventsHistPDF* pdfPPi0Pim=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("PPi0Pim"));
  RF->LoadSpeciesPDF("PPi0Pim",1);

//  RF->Factory("Chebychev:BG(Coplanarity,{a0[0.1,-0.4,0.4],a1[-0.1,-0.3,0.3], a2[-0.1,-0.3,0.3]}  )");
//  RF->Factory("Polynomial:BG2(Coplanarity,a0[0.1,-0.4,0.4],a1[-0.1,-0.3,0.3])");
//  RF->LoadSpeciesPDF("BG2",1);
//  RF->LoadSpeciesPDF("BG",1);

  cout << " Past the signal pdf2 "  <<endl; 
  RF->GetWorkSpace()->var("scaleB")->setConstant();
  RF->GetWorkSpace()->var("alphaB")->setConstant();
  RF->GetWorkSpace()->var("offB")->setConstant();

// Multi pion bg

  RF->GetWorkSpace()->var("scalePEta")->setConstant();
  RF->GetWorkSpace()->var("alphaPEta")->setConstant();
  RF->GetWorkSpace()->var("offPEta")->setConstant();
  
  RF->GetWorkSpace()->var("scaleNEta")->setConstant();
  RF->GetWorkSpace()->var("alphaNEta")->setConstant();
  RF->GetWorkSpace()->var("offNEta")->setConstant();

  RF->GetWorkSpace()->var("scaleNPi0Pi0")->setConstant();
  RF->GetWorkSpace()->var("alphaNPi0Pi0")->setConstant();
  RF->GetWorkSpace()->var("offNPi0Pi0")->setConstant();

  RF->GetWorkSpace()->var("scaleNPipPim")->setConstant();
  RF->GetWorkSpace()->var("alphaNPipPim")->setConstant();
  RF->GetWorkSpace()->var("offNPipPim")->setConstant();

  RF->GetWorkSpace()->var("scaleNPipPi0")->setConstant();
  RF->GetWorkSpace()->var("alphaNPipPi0")->setConstant();
  RF->GetWorkSpace()->var("offNPipPi0")->setConstant();

  RF->GetWorkSpace()->var("scalePPi0Pi0")->setConstant();
  RF->GetWorkSpace()->var("alphaPPi0Pi0")->setConstant();
  RF->GetWorkSpace()->var("offPPi0Pi0")->setConstant();


  RF->GetWorkSpace()->var("scalePPipPim")->setConstant();
  RF->GetWorkSpace()->var("alphaPPipPim")->setConstant();
  RF->GetWorkSpace()->var("offPPipPim")->setConstant();


  RF->GetWorkSpace()->var("scalePPi0Pim")->setConstant();
  RF->GetWorkSpace()->var("alphaPPi0Pim")->setConstant();
  RF->GetWorkSpace()->var("offPPi0Pim")->setConstant();

  cout << " Past the signal pdf3 "  <<endl; 
  RF->LoadWeights(weightsPath,"HSsWeights"); //Cp first to scratch or read from work? What is quicker? What is standard?
  //RF->LoadWeights("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/Fitting/FitProtonTiming10Bins1Files/binFitTweights.root","HSsWeights"); //Cp first to scratch or read from work? What is quicker? What is standard?
  RF->SetWeightName("TimeCoinc"); //Events in timing coincidence
  
  
  cout << " Past the signal pdf4 "  <<endl; 
  gBenchmark->Start("Binned");
  RF->AddGausConstraint(pdf->AlphaConstraint());
  RF->AddGausConstraint(pdf->OffConstraint());
  RF->AddGausConstraint(pdf->ScaleConstraint());
  RF->AddGausConstraint(pdfb->AlphaConstraint());
  RF->AddGausConstraint(pdfb->OffConstraint());
  RF->AddGausConstraint(pdfb->ScaleConstraint());


//Multi pion bg
  RF->AddGausConstraint(pdfPEta->AlphaConstraint());
  RF->AddGausConstraint(pdfPEta->OffConstraint());
  RF->AddGausConstraint(pdfPEta->ScaleConstraint());

  RF->AddGausConstraint(pdfNEta->AlphaConstraint());
  RF->AddGausConstraint(pdfNEta->OffConstraint());
  RF->AddGausConstraint(pdfNEta->ScaleConstraint());

  RF->AddGausConstraint(pdfNPi0Pi0->AlphaConstraint());
  RF->AddGausConstraint(pdfNPi0Pi0->OffConstraint());
  RF->AddGausConstraint(pdfNPi0Pi0->ScaleConstraint());

  RF->AddGausConstraint(pdfNPipPim->AlphaConstraint());
  RF->AddGausConstraint(pdfNPipPim->OffConstraint());
  RF->AddGausConstraint(pdfNPipPim->ScaleConstraint());

  RF->AddGausConstraint(pdfNPipPi0->AlphaConstraint());
  RF->AddGausConstraint(pdfNPipPi0->OffConstraint());
  RF->AddGausConstraint(pdfNPipPi0->ScaleConstraint());

  RF->AddGausConstraint(pdfPPi0Pi0->AlphaConstraint());
  RF->AddGausConstraint(pdfPPi0Pi0->OffConstraint());
  RF->AddGausConstraint(pdfPPi0Pi0->ScaleConstraint());

  RF->AddGausConstraint(pdfPPipPim->AlphaConstraint());
  RF->AddGausConstraint(pdfPPipPim->OffConstraint());
  RF->AddGausConstraint(pdfPPipPim->ScaleConstraint());

  RF->AddGausConstraint(pdfPPi0Pim->AlphaConstraint());
  RF->AddGausConstraint(pdfPPi0Pim->OffConstraint());
  RF->AddGausConstraint(pdfPPi0Pim->ScaleConstraint());





//  RF->FitSavedBins(2);
  RF->FitBatchBin(1);
  gBenchmark->Stop("Binned");
  gBenchmark->Print("Binned");

  RF->GetWeights()->Save(); //Added Cam 4th Feb 2018, think this is now needed to be able to load weights later

}
