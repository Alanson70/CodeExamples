//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ControlFormUnit.h"
#include "OutputClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#include "Inifiles.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



TControlForm *ControlForm;
//---------------------------------------------------------------------------
__fastcall TControlForm::TControlForm(TComponent* Owner)
        : TForm(Owner)
{
 for(int i=2;i<16;i++)
 {
  TtyPortComboBox->Items->Add(ASS("COM")+ASS(i+1));
 }

}

//---------------------------------------------------------------------------
/*
void TControlForm::LoadProfile(ASS fileName)
{
 TIniFile *iniFile=new TIniFile(fileName);//GetCurrentDir()+AnsiString("\\UniTerm.ini"));

 TtyPortComboBox->Text=iniFile->ReadString("Defaults","PortName","COM1");
 TtyRateComboBox->Text=iniFile->ReadString("Defaults","PortRate","19200");
 IpAddrEdit->Text=iniFile->ReadString("Defaults","IpAddr","127.0.0.0");
 IpPortEdit->Text=iniFile->ReadString("Defaults","IpPort","10000");
 if(iniFile->ReadBool("Defaults","TTY",false)==true)
  PageControl1->TabIndex=0;
 else
  PageControl1->TabIndex=1;

 PageControl1->Pages[1-PageControl1->TabIndex]->Visible=false;

 //RadioButton1->Checked=iniFile->ReadBool("Defaults","TTY",false);
 //RadioButton2->Checked=~(iniFile->ReadBool("Defaults","TTY",true));
 IpComboBox->ItemIndex=iniFile->ReadInteger("Defaults","Protocol",0);

 //AdditionSendingOptionComboBox->ItemIndex=iniFile->ReadInteger("Defaults","AdditionSending",0);
 //AdditionReceivingOptionComboBox->ItemIndex=iniFile->ReadInteger("Defaults","AdditionReceiving",0);
 //StringEndSendingOptionEdit->Text=iniFile->ReadString("Defaults","StringEndSending",0);
 //StringEndReceivingOptionEdit->Text=iniFile->ReadString("Defaults","StringEndReceiving",0);
 //EchoCheckBox->Checked=iniFile->ReadBool("Defaults","Echo",false);

 delete iniFile;
}
*/
//---------------------------------------------------------------------------
/*
void TControlForm::SaveProfile()
{
 SaveProfileAs(_fileName);
}
//---------------------------------------------------------------------------
void TControlForm::SaveProfileAs(ASS fileName)
{
 TIniFile *iniFile=new TIniFile(fileName);//GetCurrentDir()+AnsiString("\\UniTerm.ini"));

 iniFile->WriteString("Defaults","PortName",TtyPortComboBox->Text);
 iniFile->WriteString("Defaults","PortRate",TtyRateComboBox->Text);
 //iniFile->WriteBool("Defaults","TTY",RadioButton1->Checked);
 if(PageControl1->TabIndex==0)
  iniFile->WriteBool("Defaults","TTY",true);
 else 
  iniFile->WriteBool("Defaults","TTY",false);
  

 iniFile->WriteString("Defaults","IpAddr",IpAddrEdit->Text);
 iniFile->WriteString("Defaults","IpPort",IpPortEdit->Text);
// iniFile->WriteBool("Defaults","TTY",RadioButton1->Checked);
 iniFile->WriteInteger("Defaults","Protocol",IpComboBox->ItemIndex);


 //iniFile->WriteInteger("Defaults","AdditionSending",AdditionSendingOptionComboBox->ItemIndex);
 //iniFile->WriteInteger("Defaults","AdditionReceiving",AdditionReceivingOptionComboBox->ItemIndex);
 //iniFile->WriteString("Defaults","StringEndSending",StringEndSendingOptionEdit->Text);
 //iniFile->WriteString("Defaults","StringEndReceiving",StringEndReceivingOptionEdit->Text);
 //iniFile->WriteBool("Defaults","Echo",EchoCheckBox->Checked);

 delete iniFile;
}
//---------------------------------------------------------------------------
void TControlForm::CloseProfile()
{
}
*/
//-------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TControlForm::CancelButtonClick(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------





void TControlForm::Mode(int mode)
{
 switch(mode)
 {
  case 0 : // no connect
   ConnectButton->Enabled=true;
   DisconnectButton->Enabled=false;
   OkButton->Enabled=true;
  break;
  case 1 : // connecting
   ConnectButton->Enabled=false;
   DisconnectButton->Enabled=true;
   OkButton->Enabled=false;
  break;
  case 2: // connected  
   ConnectButton->Enabled=false;
   DisconnectButton->Enabled=true; 
   OkButton->Enabled=true;
  break;
 }
}
//---------------------------------------------------------------------------

void __fastcall TControlForm::DisconnectButtonClick(TObject *Sender)
{
 OnDisconnect(this);
}
//---------------------------------------------------------------------------
void __fastcall TControlForm::FormShow(TObject *Sender)
{
 ModalResult=mrNone;
}
//---------------------------------------------------------------------------


void __fastcall TControlForm::StringEndOptionEditChange(TObject *Sender)
{
 //new var 8 byte
 TEdit *edit=(TEdit *)Sender;

 char s[25];
 s[0]=0;
 int start=edit->SelStart;
 int value;

 strncpy(s,edit->Text.c_str(),16);
 for(int i=0;i<16;i++)
 {
  value=(unsigned short)s[i];
  if(value==0) break;
  if(isdigit(value)!=0) continue;
  if(isxdigit(value)!=0) continue;
  for(int j=i;j<16;j++) s[j]=s[j+1];
  start--;
//  s[i]='0';
 }
 s[16]=0;

 edit->Text=s;

 if(start<(strlen(s)+1)) edit->SelStart=start;
 else                    edit->SelStart=0;

 /* old var - only 1 byte
 TEdit *edit=(TEdit *)Sender;

 char s[16];

 s[0]=0;
 int value;
 int start=edit->SelStart;

 strncpy(s,edit->Text.c_str(),2);
 sscanf(s,"%2X",&value);
 sprintf(s,"%2.2X",value);
 edit->Text=s;

 //start++;
 if(start<2) edit->SelStart=start;
 else        edit->SelStart=0;
 */
}
//---------------------------------------------------------------------------



//char *termSetSendAdd[4]={"\r\n","\r","\n",""};
      /*
AnsiString TControlForm::SendingAddition()
{    
 char s[25];
 if(AdditionSendingOptionComboBox->ItemIndex==3)
 {
  int len=((StringEndSendingOptionEdit->Text.Length()+1)/2);
  StringToStruct(StringEndSendingOptionEdit->Text.c_str(),s,len);
  s[len]=0;
  return AnsiString(s);
 }
 else
  return AnsiString(termSetSendAdd[AdditionSendingOptionComboBox->ItemIndex]);
}         */
//---------------------------------------------------------------------------
        /*
AnsiString TControlForm::ReceivingAddition()
{
 char s[25];
 if(AdditionReceivingOptionComboBox->ItemIndex==3)
 {
  int len=((StringEndReceivingOptionEdit->Text.Length()+1)/2);
  StringToStruct(StringEndReceivingOptionEdit->Text.c_str(),s,len);
  s[len]=0;
  return AnsiString(s);
 }
 else
  return AnsiString(termSetSendAdd[AdditionReceivingOptionComboBox->ItemIndex]);   
}    */
//---------------------------------------------------------------------------



void TControlForm::TtyRate(ASS rate)
{
 for(int i=0;i<TtyRateComboBox->Items->Count;i++)
 {
  if(TtyRateComboBox->Items->Strings[i]==rate)
  {
   TtyRateComboBox->ItemIndex=i;
   return;
  }
 }
 TtyRateComboBox->ItemIndex=0;
} 
//---------------------------------------------------------------------------
ASS TControlForm::TtyRate()
{
 return this->TtyRateComboBox->Text;
}
//---------------------------------------------------------------------------
void TControlForm::TtyName(ASS port)
{

 for(int i=0;i<TtyPortComboBox->Items->Count;i++)
 {
  if(TtyPortComboBox->Items->Strings[i]==port)
  {
   TtyPortComboBox->ItemIndex=i;
   return;
  }
 }
 TtyPortComboBox->ItemIndex=0;
} 
//---------------------------------------------------------------------------
ASS TControlForm::TtyName()
{
 return this->TtyPortComboBox->Text;
} 
//---------------------------------------------------------------------------
void TControlForm::TtyParity(ASS par)
{
 for(int i=0;i<TtyParityComboBox->Items->Count;i++)
 {
  if(TtyParityComboBox->Items->Strings[i]==par)
  {
   TtyParityComboBox->ItemIndex=i;
   return;
  }
 }
 TtyParityComboBox->ItemIndex=0;
}
//---------------------------------------------------------------------------
ASS TControlForm::TtyParity()
{
 return TtyParityComboBox->Text;
}
//---------------------------------------------------------------------------

void __fastcall TControlForm::ParamsButtonClick(TObject *Sender)
{
 if(OnParams) OnParams(this);       
}
//---------------------------------------------------------------------------

