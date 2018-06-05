//run with
// setenv FILEDIR $PWD/outBins/
// root --THSBins HSSubmitBatch.C
void HSSubmitBatchPim(){
  //Open file containing binning information in a THSBins
  //This also contains entry lists for each event analysed
  TString fileDir=gSystem->Getenv("FILEDIR");
  TFile* file=new TFile(fileDir+"/DataEntries.root");
  THSBins* DataBins=(THSBins*)file->Get("HSDataBins");
 
  gSystem->Setenv("RUNMAC", TString(gSystem->Getenv("PWD"))+"/ConeAngleFitFarmPim.C");
  // gInterpreter->AddIncludePath("./*");
  TString FitName = "ConeAngle";
  cout << " Performing Fit  "<< FitName << endl;
  gSystem->Setenv("FITNAME",FitName);
  gSystem->Exec("mkdir $FILEDIR/$FITNAME"); 

 //Get Previous fit name to determine weights
  TString PrevFitName = "TimingProton";
//  TString PrevFitName = "TimingNeutron";
  cout << "Previous fit directory to take weights from is " << PrevFitName << endl;
  gSystem->Setenv("PREVFITNAME",PrevFitName);

  for(Int_t i=0;i<DataBins->GetN();i++){	
  // for(Int_t i=0;i<2;i++){	
    //loop through the bins and get the workspace files for fitting
    TString JobName=DataBins->GetBinName(i);
    cout<<"sending JobName "<<JobName<< endl;
    gSystem->Setenv("JOBNAME",JobName);
    gSystem->Exec("qsub pbs_run");
   // gSystem->Exec("./pbs_run");
    gSystem->Exec("sleep 2");
    cout<<" sent job "<< JobName<<endl;
  }
}
 
