//run with
// setenv FILEDIR $PWD/outBins/
// setenv HSUSER $PWD
// root --THSBins.C HSSubmitBatch.C
void HSSubmitBatch(){
  //Open file containing binning information in a THSBins
  //This also contains entry lists for each event analysed
  TString fileDir=gSystem->Getenv("FILEDIR");
  TFile* file=new TFile(fileDir+"/DataEntries.root");
  THSBins* DataBins=(THSBins*)file->Get("HSDataBins");
 
  gSystem->Setenv("RUNMAC", TString(gSystem->Getenv("PWD"))+"/FitHSAsymmetryBinsFarm.C");
  // gInterpreter->AddIncludePath("./*");
  for(Int_t i=0;i<DataBins->GetN();i++){	
  // for(Int_t i=0;i<2;i++){	
    //loop through the bins and get the workspace files for fitting
    TString JobName=DataBins->GetBinName(i);
    cout<<"sending JobName "<<JobName<< endl;
    gSystem->Setenv("JOBNAME",JobName);
    //  gSystem->Exec("qsub pbs_run");
   gSystem->Exec("./pbs_run");
    gSystem->Exec("sleep 2");
    cout<<" sent job "<< JobName<<endl;
  }
}
 
