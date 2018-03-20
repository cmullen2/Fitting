//root --hsfit  FitHSMCModel.C
//Now try fitting after loading the random weights into the BG model
{
  THSsPlot* RF=new THSsPlot("SF");
  RF->SetOutDir("outSideBand/");
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
  chainmcb->Add(TString(gSystem->pwd())+"/BGData.root");
  /////////////////////////////////////////////////////////////
  //Need to create BG sideband weights
  THSWeights* wgtsBG=new THSWeights("BGTime");
   wgtsBG->SetFile("BGSideBand.root");
  wgtsBG->SetSpecies("SideBand");
  wgtsBG->SetIDName("fgID");
  wgtsBG->WeightBySelection(chainmcb,"(Time>-3&&Time<5)",1);
  wgtsBG->WeightBySelection(chainmcb,"(Time>-10&&Time<-5)||(Time>8&&Time<10)",-8./7); //Note : sideband weight is proportional to the time windows range ratio
  wgtsBG->Save();//Save to disc
  delete wgtsBG; wtgsBG=nullptr;
  /////////////////////////////////////////////////////////////
  
  pdfb->LoadWeights("SideBand","BGSideBand.root","BGTime");//load from disc
  pdfb->SetEvTree(chainmcb,RF->GetCut());
  RF->LoadSpeciesPDF("BG",1);

 //Add data to chain
  TChain chain("MyModel");
  chain.Add(TString(gSystem->pwd())+"/Data.root");
  RF->SetIDBranchName("fgID");//this is needed if ID != "UID"
  //import to RooFit
  RF->LoadDataSet(&chain);

  /////////////////////////////////////////////////////////////
  //Need to create BG sideband weights
  THSWeights* wgtsD=new THSWeights("DataTime");
  wgtsD->SetFile("DataSideBand.root");
  wgtsD->SetSpecies("SideBand");
  wgtsD->SetIDName("fgID");
  wgtsD->WeightBySelection(&chain,"(Time>-3&&Time<5)",1);
  wgtsD->WeightBySelection(&chain,"(Time>-10&&Time<-5)||(Time>8&&Time<10)",-8./7); //Note : sideband weight is proportional to the time windows range ratio
  wgtsD->Save();//Save to disc
  delete wgtsD; wtgsD=nullptr;
  /////////////////////////////////////////////////////////////

  RF->LoadWeights("DataSideBand.root","DataTime");
  RF->SetWeightName("SideBand"); //Events in timing coincidence
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
