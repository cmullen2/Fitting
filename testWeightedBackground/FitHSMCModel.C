//root --hsfit  FitHSMCModel.C
//Now try fitting after loading the random weights into the BG model
{
  THSsPlot* RF=new THSsPlot("SF");
  RF->SetOutDir("out/");
  ///////////////////////////////Load Variables
  RF->LoadVariable("Mmiss[0.5,9.5]");//should be same name as variable in tree 
  RF->LoadAuxVars("Eg[-100,100]");//Not to be fitted but limits applied to dataset
  // RF->LoadAuxVars("M2[-100,100]");//Not to be fitted but used in a cut
  RooRealVar * var=RF->GetWorkSpace()->var("Mmiss");
  var->setBins(100); //number of bins used in PDF histogram
  //  RF->SetIDBranchName("fgID");

  //////////////////////////////Make signal PDF
  RF->Factory("RooHSEventsHistPDF::Sig(Mmiss,alpha[0,0,20],off[0,-2,2],scale[1,0.8,1.2])");
  RooHSEventsHistPDF* pdf=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("Sig"));
  //Attach MC signal data
  TChain *chainmc=new TChain("MyModel","mcsignal");
  chainmc->Add("SigData.root");
  pdf->SetEvTree(chainmc,RF->GetCut());
  RF->LoadSpeciesPDF("Sig",1);

  //////////////////////////////Make background PDF
  RF->Factory("RooHSEventsHistPDF::BG(Mmiss,alphaB[0,0,5],offB[0,0,0],scaleB[1.0,0.8,1.2])");
  RF->GetWorkSpace()->var("scaleB")->setConstant();
  RF->GetWorkSpace()->var("alphaB")->setConstant();
  RF->GetWorkSpace()->var("offB")->setConstant();
  
  RooHSEventsHistPDF* pdfb=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("BG"));
  //Attach MC background data
  TChain *chainmcb=new TChain("MyModel","mcbackground");
  chainmcb->Add("BGData.root");
  //Add coincidence time weights to background PDF shape
  //This must be done before SetEvTree
  pdfb->LoadWeights("TimeCoinc","outBGTime/binFitTweights.root","HSsWeights");
  pdfb->SetEvTree(chainmcb,RF->GetCut());  //breaks on this line probs an issue with cut option 
  RF->LoadSpeciesPDF("BG",1);

 //Add data to chain
  TChain chain("MyModel");
  chain.Add("Data.root");
  RF->SetIDBranchName("fgID");//this is needed if ID != "UID"
  //import to RooFit
  RF->LoadDataSet(&chain);
  RF->LoadWeights("outDataTime/binFitTweights.root ","HSsWeights");
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
  RF->DrawTreeVar("Mmiss",100,0,10);
  RF->DrawTreeVar("M1",100,0,10);
  RF->DrawTreeVar("M2",100,0,10);

}
