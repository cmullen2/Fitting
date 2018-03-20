{

TString FileName="baba";
gSystem->Setenv("FiLeName",FileName);
TString fileDir=gSystem->Getenv("FILEDIR");


//gSystem->Exec("mkdir $FileName");

TString Total ="haha" + fileDir  ;
cout <<Total << endl;





}
