//Run with 
//root --hsfit StudyHSAsymmetry.C --MyNewPDF.cxx
{
  THSRooFit* RF=new THSRooFit("AFit");
  RF->SetOutDir("studyRes10/");
 ///////////////////////////////Load Variables
  RF->LoadVariable("Phi[-180,180]");//going to fit this
  RF->LoadVariable("Pol[0,1]");
  RF->GetWorkSpace()->var("Phi")->setBins(20);
  RF->GetWorkSpace()->var("Pol")->setBins(5);

  /////////////////////////////Make asymmetry model A and B are fit parameters
  RF->Factory("MyNewPDF::SigAsym( Phi,Pol,A[0.4,-1,1],B[-0.6,-1,1] )");
  RF->LoadSpeciesPDF("SigAsym",10000);
  RooHSEventsPDF* PDF=dynamic_cast<RooHSEventsPDF*>(RF->GetWorkSpace()->pdf("SigAsym"));
 
  TChain *chainMC=new TChain("MyModel");
  chainMC->Add("SimDataSymRes10.root");
  if(!PDF->SetEvTree(chainMC)) exit(0);
  //PDF->SetNInt(1E4);
  //PDF->SetConstInt();
  PDF->CheckIntegralParDep(4);
  // PDF->SetUseWeightsGen(kFALSE);
  gBenchmark->Start("Binned");
  RF->TotalPDF();
  RF->SetStudyPDF("SigAsym");
  //RF->SetStudyPlot();
  RF->SetNStudyTrials(2);
  RF->StudyFit();
  gBenchmark->Stop("Binned");
  gBenchmark->Print("Binned");

}
