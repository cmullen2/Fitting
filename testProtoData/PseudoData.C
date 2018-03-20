
//For example Run with 
//root 'PseudoData.C( "Data.root" ,10000,10,1,0,kFALSE)'
//root 'PseudoData.C("SimData.root",500000,10,1,0,kTRUE)'
//Change filename Data.root ->DifferentName.root
//Change Number of events 10000 ->NEVENTS
//Change Phi resolution 10 -> Differerent Phi res in degrees
//Change acceptance to symmetric function 1 -> 2, 100% acceptance 1->0
//PolState Asymmetry change 0 -> between (-1,1)
//Run PseudoSim (flat phi) kFALSE -> kTRUE
//Change model parameters below : fPhip->SetParameters(0.4,-0.6,1);
Int_t Detector(Double_t genPhi,Double_t* phi);
Double_t PhiRes=0;//resolution in deg
Int_t IsAcc=0;

void PseudoData(TString filename,Long64_t Nev=10000,Double_t res=0,Int_t acc=1,Double_t APol=0,Bool_t fIsMC=kFALSE){
  IsAcc=acc;
  PhiRes=res;
  APol=0.5*APol+0.5;//map -1,1 onto 0,1 for PolState asymmetry
    
  gRandom->SetSeed(301);
  TFile* file=new TFile(filename,"recreate");

  Double_t Eg,Mmiss,M1,M2,fgID,Sig,Phi,Pol,genPhi,genPol;
  Int_t PolState,Acc;
  TTree* tree=new TTree("MyModel","MyModel");
  tree->Branch("Eg",&Eg,"Eg/D");
  // tree->Branch("Mmiss",&Mmiss,"Mmiss/D");
  //tree->Branch("M1",&M1,"M1/D");
  // tree->Branch("M2",&M2,"M2/D");
  tree->Branch("UID",&fgID,"UID/D");
  tree->Branch("Phi",&Phi,"Phi/D");
  tree->Branch("Acc",&Acc,"Acc/I");
  if(fIsMC){
    tree->Branch("genPhi",&genPhi,"genPhi/D");
    //   tree->Branch("genPol",&genPol,"genPol/D");
  }
  else{
    tree->Branch("Pol",&Pol,"Pol/D");
    tree->Branch("PolState",&PolState,"PolState/I");
  }
  //signal
  // TF1* fM1s=new TF1("m1s","gaus(0)+gaus(3)+[6]",0,10);
  // fM1s->SetParameters(1,3,0.5,0.5,7,2,0.1);
  // TF1* fM2s=new TF1("m2s","gaus(0)+[3]*x",0,10);
  // fM2s->SetParameters(1,5,0.1,0.1);
  // TF1* fMmisss=new TF1("mmisss","gaus(0)",0,10);
  // //fMmisss->SetParameters(1,0.1,1);
  // fMmisss->SetParameters(1,5,0.7);
  TF1* fPhip=new TF1("phip","1+[2]*([0]*cos(2*TMath::DegToRad()*x)+[1]*sin(2*TMath::DegToRad()*x))",-180,180); 
  // fPhip->SetNpx(10000);
  if(!fIsMC){
    fPhip->SetParameters(0.4,-0.6,1);
  }
  else
    fPhip->SetParameters(0,0,1);
  

  for(Int_t i=0;i<Nev;i++){
    if(i%100==0)cout<<i<<" of "<<Nev<<endl;
    fgID=i;
    Eg=gRandom->Uniform(3,4);
    genPol=Eg/2-1; //should be 0.5-1
    if(gRandom->Uniform()>APol) PolState=1;
    else PolState=-1;
    
    // M1=fM1s->GetRandom();
    // M2=fM2s->GetRandom();
    // Mmiss=fMmisss->GetRandom();

    fPhip->SetParameter(2,genPol*PolState);
    genPhi=gRandom->Uniform(-180,180);

    while(fPhip->Eval(genPhi)<gRandom->Uniform(0,2))
      genPhi=gRandom->Uniform(-180,180);
    
      //genPhi=fPhip->GetRandom();
 
    Pol=genPol;
    Acc=1;
    Acc=Detector(genPhi,&Phi);
    if(Acc) tree->Fill();
    //tree->Fill();
  }

  tree->Write();
  file->Close();

}

Int_t Detector(Double_t genPhi,Double_t* phi){

  //  *phi=genPhi;
  // return 1;
  if(IsAcc==0){
    *phi=genPhi+gRandom->Gaus(0,PhiRes);
    if(*phi>180) {*phi=-360+ *phi;}
    if(*phi<-180) *phi=360+ *phi;
  }
  else if(IsAcc==1){
    if(400*gRandom->Uniform()<180-(genPhi))
      {*phi=0;return 0;}
    //accepted!
    *phi=genPhi+gRandom->Gaus(0,PhiRes);
    
   if(*phi>180) {*phi=-360+ *phi;return 0;}
    if(*phi<-180) *phi=360+ *phi;
  }
  else{
    if(250*gRandom->Uniform()<180-TMath::Abs(genPhi))
      {*phi=0;return 0;}
    //accepted!
    *phi=genPhi+gRandom->Gaus(0,PhiRes);
    if(*phi>180) *phi=-360+ *phi;
     if(*phi<-180) *phi=360+ *phi;
  
  }
  return 1;
}
