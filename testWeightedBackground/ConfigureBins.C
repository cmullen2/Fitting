//root  --hsfit ConfigureBins.C
{

  THSRooFit* RF=new THSRooFit("SF");
  RF->SetOutDir("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/Fitting/All11Binned20FilesProtonAllAuxInvMassW10Costh20PolNeg");
  ///////////////////////////////Load Variables
  RF->LoadVariable("GammaAveTagDiffTime[-80,20]");
  RF->LoadBinVars("Topo",1,0,1);
  RF->LoadBinVars("W",10,950,1850);
  RF->LoadBinVars("Costh",20,-1,1);
  RF->LoadBinVars("DCorrect",1,0,1);
  RF->LoadBinVars("AnyErrs",1,-0.25,0.25);
  RF->LoadBinVars("PolStateD",1,-1,0);

  RF->LoadAuxVars("Coplanarity[-80,80]");//Save Mmiss event between 0-10
//  RF->LoadAuxVars("PseudoVertexZ[-500,500]");

//  RF->LoadAuxVars("Phi[-180,180]");
  RF->LoadAuxVars("MissMass[0,2960]");
  RF->LoadAuxVars("ConeAngle[0,3.2]");
  RF->LoadAuxVars("InvMass[0,1000]");

//  RF->LoadAuxVars("Costh[-1,1]");//Not to be fitted but limits applied to dataset (prev was 20bins)
 // RF->LoadAuxVars("Pol",1,-1,0);
//  RF->LoadAuxVars("Phi[-180,180]");


 
  RF->SetIDBranchName("UID");  //Save ID variable fgID

//MC BG Files

  TChain *chainmcPEta=new TChain("HSParticles","mcPEta");
  chainmcPEta->Add("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/PEta/TotalSim.root");
  RF->MakeBinnedTrees(chainmcPEta,"PEta");//Note "Sig" will be used to name PDF

  TChain *chainmcNEta=new TChain("HSParticles","mcNEta");
  chainmcNEta->Add("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/NEta/TotalSim.root");
  RF->MakeBinnedTrees(chainmcNEta,"NEta");//Note "Sig" will be used to name PDF

  TChain *chainmcNPi0Pi0=new TChain("HSParticles","mcNPi0Pi0");
  chainmcNPi0Pi0->Add("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/NPi0Pi0/TotalSim.root");
  RF->MakeBinnedTrees(chainmcNPi0Pi0,"NPi0Pi0");//Note "Sig" will be used to name PDF

  TChain *chainmcPPi0Pi0=new TChain("HSParticles","mcPPi0Pi0");
  chainmcPPi0Pi0->Add("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/PPi0Pi0/TotalSim.root");
  RF->MakeBinnedTrees(chainmcPPi0Pi0,"PPi0Pi0");//Note "Sig" will be used to name PDF

  TChain *chainmcNPipPim=new TChain("HSParticles","mcNPipPim");
  chainmcNPipPim->Add("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/NPipPim/TotalSim.root");
  RF->MakeBinnedTrees(chainmcNPipPim,"NPipPim");//Note "Sig" will be used to name PDF

  TChain *chainmcPPipPim=new TChain("HSParticles","mcPPipPim");
  chainmcPPipPim->Add("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/PPipPim/TotalSim.root");
  RF->MakeBinnedTrees(chainmcPPipPim,"PPipPim");//Note "Sig" will be used to name PDF

  TChain *chainmcNPipPi0=new TChain("HSParticles","mcNPipPi0");
  chainmcNPipPi0->Add("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/NPipPi0/TotalSim.root");
  RF->MakeBinnedTrees(chainmcNPipPi0,"NPipPi0");//Note "Sig" will be used to name PDF

  TChain *chainmcPPi0Pim=new TChain("HSParticles","mcPPi0Pim");
  chainmcPPi0Pim->Add("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/PPi0Pim/TotalSim.root");
  RF->MakeBinnedTrees(chainmcPPi0Pim,"PPi0Pim");//Note "Sig" will be used to name PDF






  //MC Signal files
  TChain *chainmc=new TChain("HSParticles","mcsignal");
//  chainmc->Add("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/NPi0/SecondAttempt/TotalSim.root");
//  chainmc->Add("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/Flat/TwelthAttempt/TotalSim.root");
  chainmc->Add("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/PPi0/VertexAttempt/TotalSim.root");
  RF->MakeBinnedTrees(chainmc,"Sig");//Note "Sig" will be used to name PDF
  //MC BG files
  TChain *chainmcb=new TChain("HSParticles","emptybg");
  chainmcb->Add("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/EmptyTarget/Dev3.0Files12PhysicsAllVertexCut.root");
//  chainmcb->Add("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/EmptyTarget/Dev3.0Files12PhysicsAll.root");
//  chainmcb->Add("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/EmptyTarget/Dev3.0Files12PhysicsAllVertexInfoCut.root");
  RF->MakeBinnedTrees(chainmcb,"BG"); //Note "BG" will be used to name PDF
  //"Real" Data files
  TChain chain("HSParticles");
  chain.Add("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/TestMulti/Dev19.0Files20PhysicsAllVertexInfo.root");
  RF->MakeBinnedTrees(&chain,"Data");

}
