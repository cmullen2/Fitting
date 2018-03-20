//Run with 
//root --hsfit FitHSAsymmetryBins.C --SKProtoPDF.cxx
{
  //Create THSRooFit manager 
  THSRooFit* RF=new THSRooFit("AFit");
  RF->SetOutDir("outBins/Fits"); //give output directory
  // RF->SetBinnedFit();
  ///////////////////////////////Load Variables
  RF->LoadVariable("Phi[-180,180]");//going to fit this
  RF->LoadVariable("Pol[0,1]");
  RF->LoadVariable("PolState[Polp=1,Polm=-1]");//Load a category
  
  RF->GetWorkSpace()->var("Phi")->setBins(36);
  RF->GetWorkSpace()->var("Pol")->setBins(5);
  
  RF->ConfigureSavedBins("outBins/"); 

/////////////////////////////Make asymmetry model A and B are fit parameters
  //Note Sim is same name given in ConfigureBins
  RF->Factory("SKNewPDF::Sim( Phi,Pol,PolState, A[0.1,-1,1],B[0.6,-1,1] )");
  RooHSEventsPDF* PDF=dynamic_cast<RooHSEventsPDF*>(RF->GetWorkSpace()->pdf("Sim"));
  RF->LoadSpeciesPDF("Sim");

  //make Extended PDF
  RF->TotalPDF();

  RF->FitSavedBins(1);
  // gBenchmark->Stop("Binned");
  // gBenchmark->Print("Binned");
}
