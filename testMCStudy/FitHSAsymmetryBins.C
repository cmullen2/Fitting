//Run with 
//root --hsfit FitHSAsymmetryBins.C --MyNewPDF.cxx
{
  THSRooFit* RF=new THSRooFit("AFit");
  RF->SetOutDir("outRes10Bins/Fits");
 ///////////////////////////////Load Variables
  RF->LoadVariable("Phi[-180,180]");//going to fit this
  RF->LoadVariable("Pol[0,1]");//but fix polarisation event-by-event
  RF->GetWorkSpace()->var("Phi")->setBins(20);
  RF->GetWorkSpace()->var("Pol")->setBins(5);
  //////////////////////////////Load Bins
  RF->ConfigureSavedBins("outRes10Bins/"); 
  
  /////////////////////////////Make asymmetry model A and B are fit parameters
  RF->Factory("MyNewPDF::SigAsym( Phi,Pol,A[0.4,-1,1],B[-0.8,-1,1] )");
  RF->LoadSpeciesPDF("SigAsym");
  RF->TotalPDF();
  
  //PDF->CheckIntegralParDep(4);
  RF->SetStudyPDF("SigAsym");
  RF->SetNStudyTrials(5);
  RF->FitSavedBins(1);
  
 
}
