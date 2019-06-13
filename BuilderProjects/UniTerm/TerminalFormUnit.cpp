//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TerminalFormUnit.h"
#include "Functions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTerminalForm *TerminalForm;
#include "Inifiles.hpp"
char *SendAddStrings[4]={"\r\n","\r","\n",""};
//---------------------------------------------------------------------------
__fastcall TTerminalForm::TTerminalForm(TComponent* Owner) : TForm(Owner)
{
 Caption="Безымянный";
 _profile="";

 _Client=new TControlClientForm(this);
 _Client->OnCanWrite=this->OnClientCanWrite;
 _Client->OnReadReady=this->OnClientReadReady;
 _Client->OnChangeConnectStatus=OnClientChangeConnectStatus;//(TObject *Sender);
// _Client->OnError=OnClientChangeConnectStatus;//OnClientError;
// _Client->OnDisconnected=OnClientChangeConnectStatus;//OnClientDisconnected;
// _Client->OnConnected=OnClientChangeConnectStatus;//OnClientConnected;
}
//---------------------------------------------------------------------------
void __fastcall TTerminalForm::FormShow(TObject *Sender)
{
 if(OnTerminalCreate) OnTerminalCreate(this);
}
//---------------------------------------------------------------------------
void TTerminalForm::LoadProfile(ASS fileName)
{
 if(fileName.Length()<1) return;
 _profile=fileName;
 Caption=ChangeFileExt(ExtractFileName(fileName),"");
 if(FileExists(fileName)==false | fileName=="Noname")
  fileName=ExtractFilePath(_argv[0])+ASS("Default.ini");
 TIniFile *iniFile=new TIniFile(fileName);//GetCurrentDir()+AnsiString("\\UniTerm.ini"));

 EchoCheckBox->Checked=iniFile->ReadBool("Defaults","Echo",false);

 delete iniFile;

 _Client->LoadInits(fileName);

 LoadCommands20();
}

//---------------------------------------------------------------------------

void TTerminalForm::SaveProfile()
{
 SaveProfileAs(_profile);
}
//---------------------------------------------------------------------------
void TTerminalForm::SaveProfileAs(ASS fileName)
{
 if(fileName.Length()<1) return;

 if(fileName=="Noname")
  fileName=ExtractFilePath(_argv[0])+ASS("Default.ini");
 else
 {
  _profile=fileName;
  Caption=ChangeFileExt(ExtractFileName(fileName),"");
 }

 TIniFile *iniFile=new TIniFile(fileName);//GetCurrentDir()+AnsiString("\\UniTerm.ini"));

 iniFile->WriteBool("Defaults","Echo",EchoCheckBox->Checked);//EchoCheckBox->Checked);
 delete iniFile;

 _Client->SaveInits(fileName);
}
//---------------------------------------------------------------------------
void __fastcall TTerminalForm::SendButtonClick(TObject *Sender)
{        
  // remember last command
  int was=0;
  for(int i=0;i<CommandCombo->Items->Count;i++)
  {
   if(CommandCombo->Items->Strings[i]==CommandCombo->Text) { was=1;break; }
  }
  if(was==0) CommandCombo->Items->Insert(0,CommandCombo->Text);

  AnsiString s=CommandCombo->Text;//+_sendAddition;//AnsiString("\n");
  if(EchoCheckBox->Checked==true)
   Memo->Lines->Add(CommandCombo->Text);

  _Client->Write(s.c_str(),s.Length());

  SaveCommands20();
  LoadCommands20();

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTerminalForm::ControlButtonClick(TObject *Sender)
{
 _Client->ShowModal();
 SaveProfile();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTerminalForm::FormClose(TObject *Sender,TCloseAction &Action)
{
 SaveProfile();
 Action=caFree;
 if(OnTerminalDestroy) OnTerminalDestroy(this);
}
//---------------------------------------------------------------------------
void TTerminalForm::SaveCommands20()
{
 TIniFile *iniFile=new TIniFile(_profile);//GetCurrentDir()+AnsiString("\\UniTerm.ini"));

 iniFile->WriteString("Commands","c0",CommandCombo->Text);
 AnsiString itemString;
 int i=1;

 for(int it=0;;it++)
 {
  if(it>=CommandCombo->Items->Count) break;
  if(i>=20) break;

  if(CommandCombo->Text==CommandCombo->Items->Strings[it]) continue;
  itemString="c"+AnsiString(i++);
  iniFile->WriteString("Commands",itemString,CommandCombo->Items->Strings[it]);
 }
 iniFile->WriteInteger("Commands","Count",i);
 delete iniFile;
}
//---------------------------------------------------------------------------
void TTerminalForm::LoadCommands20()
{
 CommandCombo->Clear();

 TIniFile *iniFile=new TIniFile(_profile);//GetCurrentDir()+AnsiString("\\UniTerm.ini"));

 AnsiString itemString;
 int count=iniFile->ReadInteger("Commands","Count",0);

 for(int it=0;it<count;it++)
 {
  itemString="c"+AnsiString(it);
  CommandCombo->AddItem(iniFile->ReadString("Commands",itemString,""),NULL);
 }
 if(CommandCombo->Items->Count>0) CommandCombo->ItemIndex=0;

 delete iniFile;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTerminalForm::OnClientReadReady(TObject *Sender)
{
 ASS s;
 s=_Client->Read();

 Memo->Lines->Add(s);
}
//---------------------------------------------------------------------------
void __fastcall TTerminalForm::OnClientCanWrite(TObject *Sender)
{
 ConnectStatus(2);
 SendButton->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TTerminalForm::OnClientChangeConnectStatus(TObject*Sender)
{
 ConnectStatus(_Client->ConnectStatus());
}
//---------------------------------------------------------------------------
void TTerminalForm::Connect()
{
 _Client->Connect();
}
//---------------------------------------------------------------------------
void TTerminalForm::ConnectStatus(int status)
{
 if(status==1)
  StatusTimer->Enabled=true;
 else
  StatusTimer->Enabled=false;
 if(status==0)
  StatusLampPanel->Color=clBtnFace;
 else
  StatusLampPanel->Color=clLime;

 if(status==2)
  SendButton->Enabled=true;
 else
  SendButton->Enabled=false;
}
//---------------------------------------------------------------------------
int TTerminalForm::ConnectStatus()
{
 return _Client->ConnectStatus();//_connectStatus;
}
//---------------------------------------------------------------------------

void __fastcall TTerminalForm::StatusTimerTimer(TObject *Sender)
{
 StatusTimer->Tag=1-StatusTimer->Tag;
 StatusLampPanel->Color=(StatusTimer->Tag==1)?clLime:clBtnFace;// ConnectStatus()==
}
//---------------------------------------------------------------------------

