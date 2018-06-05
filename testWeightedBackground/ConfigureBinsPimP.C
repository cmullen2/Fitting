//root  --hsfit ConfigureBins.C
{

  THSRooFit* RF=new THSRooFit("SF");
  RF->SetOutDir("/w/work1/home/chris/LatestAnalysisRuns/Data/DataDec17ChargedPion/HaspectOutput/PiMinusP/Fitting/All3Binned20FilesProtonConeAngleMMW10Costh20PolNeg");
  ///////////////////////////////Load Variables
  RF->LoadVariable("PimTagDiffTime[-80,20]");
//  RF->LoadBinVars("Topo",1,0,1);
  RF->LoadBinVars("W",10,950,1850);
  RF->LoadBinVars("Costh",20,-1,1);
  RF->LoadBinVars("DCorrect",1,0,1);
  RF->LoadBinVars("AnyErrs",1,-0.25,0.25);
  RF->LoadBinVars("PolStateD",1,-1,0);
  RF->LoadAuxVars("Coplanarity[-80,80]");//Save Mmiss event between 0-10
  RF->LoadAuxVars("Phi[-180,180]");
  RF->LoadAuxVars("MissMass[0,2050]");
  RF->LoadAuxVars("ConeAngle[0,3.2]");
//  RF->LoadAuxVars("Costh[-1,1]");//Not to be fitted but limits applied to dataset (prev was 20bins)
 // RF->LoadAuxVars("Pol",1,-1,0);
//  RF->LoadAuxVars("Phi[-180,180]");


 
  RF->SetIDBranchName("UID");  //Save ID variable fgID

  //MC Signal files
  TChain *chainmc=new TChain("HSParticles","mcsignal");
  chainmc->Add("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/PPiM/FirstAttempt/TotalSim.root");
  RF->MakeBinnedTrees(chainmc,"Sig");//Note "Sig" will be used to name PDF
  //MC BG files
  TChain *chainmcb=new TChain("HSParticles","emptybg");
  chainmcb->Add("/w/work1/home/chris/LatestAnalysisRuns/Data/DataDec17ChargedPion/HaspectOutput/PiMinusP/EmptyTarget/Dev3.0Files1PhysicsAll.root");
  RF->MakeBinnedTrees(chainmcb,"BG"); //Note "BG" will be used to name PDF
  //"Real" Data files
  TChain chain("HSParticles");
  chain.Add("/w/work1/home/chris/LatestAnalysisRuns/Data/DataDec17ChargedPion/HaspectOutput/PiMinusP/ProdData/Dev3.0Files20PhysicsAll.root");
  RF->MakeBinnedTrees(&chain,"Data");

}
