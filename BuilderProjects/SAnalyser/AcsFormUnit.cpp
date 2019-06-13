//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AcsFormUnit.h"
#include "AnalyserMeterFrameUnit.h" 
#include "Inifiles.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAcsForm *AcsForm;
//---------------------------------------------------------------------------
__fastcall TAcsForm::TAcsForm(TComponent* Owner)
        : TForm(Owner)
{
 ASS fileName;

 SetCurrentDir(ExtractFilePath(_argv[0]));
 ForceDirectories(GetCurrentDir()+ASS("\\INI"));

 if(_argc<5) Application->Terminate();

 unsigned long freq=atol(_argv[1]);
 Caption="ÑÏÅÊÒÐÎÑ. ×àñòîòà "+ASS(_argv[1])+ASS(" êÃö");

 char buf[100];
 char *argv[5];
 int argc;
 Strncpy(buf,_argv[2],99);
 argc=SplitBuffer(buf,argv,3," ");
 char *ip=argv[1];
 char *port=argv[2];
 //Strncpy(buf,_argv[3],99);
 //argc=SplitBuffer(buf,argv,3);
 char *sendPrefix=_argv[3];
 char *recPrefix=_argv[4];


 _frame=new TAnalyserMeterFrame(this);
 _frame->Parent=this;
 _frame->Align=alClient;
 _fileName=ASS("INI\\spectros")+ip+port+recPrefix+ASS(".ini");

 TIniFile *iniFile=new TIniFile(_fileName);

 iniFile->WriteInteger("Connect","TermType",0);

 iniFile->WriteString("Connect","IpAddr",ip);
 iniFile->WriteString("Connect","IpPort",port);
 iniFile->WriteInteger("Connect","Protocol",0);//atoi(argv[2]));

 iniFile->WriteBool("Connect","AutoConnect",true);
 iniFile->WriteInteger("Connect","AdditionSending",2);
 iniFile->WriteInteger("Connect","AdditionReceiving",2);
 iniFile->WriteString("Connect","StringEndSending","");
 iniFile->WriteString("Connect","StringEndReceiving","");
 iniFile->WriteString("Connect","PrefixRec",recPrefix);
 iniFile->WriteString("Connect","PrefixSend",sendPrefix);

 iniFile->WriteBool("Connect","DoConnect",true);

 /*delete iniFile;

 TIniFile *iniFile=new TIniFile(fileName);//GetCurrentDir()+AnsiString("\\UniTerm.ini"));
   */
 Left=iniFile->ReadInteger("Defaults","Left",Left);
 Top=iniFile->ReadInteger("Defaults","Top",Top);
 Width=iniFile->ReadInteger("Defaults","Width",Width);
 Height=iniFile->ReadInteger("Defaults","Height",Height);

 delete iniFile;

((TAnalyserMeterFrame *)_frame)->ConnectTabSheet->Visible=false;

 _frame->LoadBaseInits(_fileName);
 _frame->SettsButton->Down=false; 
 _frame->CtrlButton->Down=false;
 _frame->SettsButtonClick(this);
 _frame->SettsButtonClick(this);
 _frame->CtrlButtonClick(this);
 _frame->CtrlButtonClick(this);

 _frame->MiddleFreq(freq);

 //((TAnalyserMeterFrame *)_frame)->SettsPageControl->Visible=false;
 //((TAnalyserMeterFrame *)_frame)->CtrlPanel->Visible=false;


}
//---------------------------------------------------------------------------
void __fastcall TAcsForm::FormClose(TObject *Sender, TCloseAction &Action)
{
 _frame->SaveBaseInits(_fileName);

 TIniFile *iniFile=new TIniFile(_fileName);

 iniFile->WriteInteger("Defaults","Left",Left);
 iniFile->WriteInteger("Defaults","Top",Top);
 iniFile->WriteInteger("Defaults","Width",Width);
 iniFile->WriteInteger("Defaults","Height",Height);

 
 delete iniFile;
}
//---------------------------------------------------------------------------

