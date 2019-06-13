//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ConnectFrameUnit.h" 
#include "Inifiles.hpp"    
#include "OutputClient.h"  
#include "TtyClient.h"
#include "TcpClient.h"
#include "UdpClient.h"
#include "AnalyserMeterFrameUnit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TConnectFrame *ConnectFrame;
//---------------------------------------------------------------------------
__fastcall TConnectFrame::TConnectFrame(TComponent* Owner)
        : TFrame(Owner)
{
}
//-------
__fastcall TConnectFrame::~TConnectFrame()
{
 if(this->_outputClient) delete this->_outputClient;
}
//---------------------------------------------------------------------------
void TConnectFrame::LoadInits(ASS fileName)
{
 TIniFile *iniFile=new TIniFile(fileName);

 TtyPortComboBox->Text=iniFile->ReadString("Connect","TtyName","COM1");
 TtyRateComboBox->Text=iniFile->ReadString("Connect","TtyRate","19200");
 TtyParityComboBox->Text=iniFile->ReadString("Connect","TtyParity","Odd");
 IpAddrEdit->Text=iniFile->ReadString("Connect","IpAddr","127.0.0.0");
 IpPortEdit->Text=iniFile->ReadString("Connect","IpPort","10000");

 TermPageControl->ActivePageIndex=iniFile->ReadInteger("Connect","TermType",1);

 IpComboBox->ItemIndex=iniFile->ReadInteger("Connect","Protocol",0);

 AdditionSendingOptionComboBox->ItemIndex=iniFile->ReadInteger("Connect","AdditionSending",0);
 AdditionReceivingOptionComboBox->ItemIndex=iniFile->ReadInteger("Connect","AdditionReceiving",0);
 StringEndSendingOptionEdit->Text=iniFile->ReadString("Connect","StringEndSending",0);
 StringEndReceivingOptionEdit->Text=iniFile->ReadString("Connect","StringEndReceiving",0);
 PrefixReceivingEdit->Text=iniFile->ReadString("Connect","PrefixRec","");
 PrefixSendingEdit->Text=iniFile->ReadString("Connect","PrefixSend","");

 AutoConnectCheckBox->Checked=iniFile->ReadBool("Connect","AutoConnect",false);

 bool doConnect=iniFile->ReadBool("Connect","DoConnect",false);
                       /*
 if(_addSend==3)
  _sendAddition=_addSendString;
 else
  _sendAddition=SendAddStrings[_addSend];

 if(_addRec==3)
  _recAddition=_addRecString;
 else
  _recAddition=SendAddStrings[_addRec];
                         */
 delete iniFile;

 AdditionOptionComboBoxChange(this);

 if(doConnect)
  this->ConnectButtonClick(this);
}
//---------------------------------------------------------------------------
void TConnectFrame::SaveInits(ASS fileName)
{
 TIniFile *iniFile=new TIniFile(fileName);

 iniFile->WriteString("Connect","TtyName",this->TtyPortComboBox->Text);
 iniFile->WriteString("Connect","TtyRate",this->TtyRateComboBox->Text);
 iniFile->WriteString("Connect","TtyParity",this->TtyParityComboBox->Text);

 iniFile->WriteInteger("Connect","TermType",TermPageControl->ActivePageIndex);

 iniFile->WriteBool("Connect","AutoConnect",AutoConnectCheckBox->Checked);

 iniFile->WriteString("Connect","IpAddr",IpAddrEdit->Text);
 iniFile->WriteString("Connect","IpPort",IpPortEdit->Text);
 iniFile->WriteInteger("Connect","Protocol",IpComboBox->ItemIndex);

 iniFile->WriteInteger("Connect","AdditionSending",AdditionSendingOptionComboBox->ItemIndex);
 iniFile->WriteInteger("Connect","AdditionReceiving",AdditionReceivingOptionComboBox->ItemIndex);
 iniFile->WriteString("Connect","StringEndSending",StringEndSendingOptionEdit->Text);
 iniFile->WriteString("Connect","StringEndReceiving",StringEndReceivingOptionEdit->Text);
 iniFile->WriteString("Connect","PrefixRec",PrefixReceivingEdit->Text);
 iniFile->WriteString("Connect","PrefixSend",PrefixSendingEdit->Text);

 iniFile->WriteBool("Connect","DoConnect",this->ConnectStatus()==2?true:false);

 delete iniFile;
}
//---------------------------------------------------------------------------
void __fastcall TConnectFrame::AdditionOptionComboBoxChange(TObject *Sender)
{
 if(AdditionSendingOptionComboBox->ItemIndex==3)
 {
  StringEndSendingOptionEdit->Visible=true;
 }
 else
 {
  StringEndSendingOptionEdit->Visible=false;
 }
 if(AdditionReceivingOptionComboBox->ItemIndex==3)
 {
  StringEndReceivingOptionEdit->Visible=true;
 }
 else
 {
  StringEndReceivingOptionEdit->Visible=false;
 }

 if(AdditionSendingOptionComboBox->ItemIndex==3)
  _sendAddition=StringEndSendingOptionEdit->Text;
 else
  _sendAddition=SendAddStrings[AdditionSendingOptionComboBox->ItemIndex];

 if(AdditionReceivingOptionComboBox->ItemIndex==3)
  _recAddition=StringEndReceivingOptionEdit->Text;
 else
  _recAddition=SendAddStrings[AdditionReceivingOptionComboBox->ItemIndex];
}


//---------------------------------------------------------------------------
void __fastcall TConnectFrame::StringEndOptionEditChange(TObject *Sender)
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

 AdditionOptionComboBoxChange(this);
}








//---------------------------------------------------------------------------
void __fastcall TConnectFrame::DisconnectButtonClick(TObject *Sender)
{
 Disconnect();
}
//---------------------------------------------------------------------------
void TConnectFrame::Disconnect()
{
 TOutputClient *client=(TOutputClient *)_outputClient;
 _outputClient=NULL;
 if(client)
 {
  client->Close();
  delete client;
 }         
 //StatusLabel->Caption="";
 ConnectStatus(0);

 IPConnectTimer->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TConnectFrame::ConnectButtonClick(TObject *Sender)
{
 Connect();
}

//---------------------------------------------------------------------------
void TConnectFrame::Connect()
{
 TOutputClient *client=(TOutputClient *)_outputClient;
 _outputClient=NULL;

 if(client)
 {
  client->Close();
  delete client;
 }
 ConnectStatus(0);

 if(_connectStatus!=1)
 {
  ConnectStatus(1);

  AnsiString par;

  if(TermPageControl->ActivePage==TtyTabSheet)
  {
   client=new TtyClient(this);
   par=this->TtyPortComboBox->Text+ASS(" -r")+this->TtyRateComboBox->Text+ASS(" -p")+this->TtyParityComboBox->Text.operator [](1);
  }
  else
  {
   if(this->IpComboBox->ItemIndex==0)
   {
    client=new TcpClient(this);
   }
   else
   {
    client=new UdpClient(this);
   }
   par=this->IpAddrEdit->Text+ASS(" ")+this->IpPortEdit->Text;
  }

  client->OnReadReady=ReadReady;
  client->OnCanWrite=CanWrite;
  client->OnError=IsError;
  client->Set(par);
  _outputClient=client;
  //StatusLabel->Caption=par;
  client->Open();
 }
 if(this->TermPageControl->ActivePage!=IPTabSheet)
  IPConnectTimer->Enabled=false;
 else
  IPConnectTimer->Enabled=this->AutoConnectCheckBox->Checked;
 //ConnectButton->Enabled=false;
 //DisconnectButton->Enabled=true;
}  
//---------------------------------------------------------------------------

void __fastcall TConnectFrame::ReadReady(TObject *Sender)
{
 _receiveCount+=Read(_receiveBuffer+_receiveCount,OC_MAX_COUNT-_receiveCount);

 if(_receiveCount)
  StatusEdit->Text=Time().TimeString();

 char end[200];
 int len;
 strncpy(end,_recAddition.c_str(),199);
 len=strlen(end);

 for(int i=0;i<_receiveCount;i++)
 {
  if(memcmp(_receiveBuffer+i,end,len)==0)
  {
   _receiveBuffer[i]=0;
   int prefixLen=this->PrefixReceivingEdit->Text.Length();

   if(prefixLen>0)
   {
    strncpy(end,PrefixReceivingEdit->Text.c_str(),199);
    
    IF(_receiveBuffer,end,prefixLen)
     prefixLen++;             // space else
    else
     prefixLen=-1; // error!!!
   }
   if(len!=-1)
    ((TAnalyserMeterFrame *)Owner)->Translate(_receiveBuffer+prefixLen,i-prefixLen);
  // Memo->Lines->Add(_receiveBuffer);

   i+=len;
   _receiveCount=Memcpy(_receiveBuffer,_receiveBuffer+i,_receiveCount-i);
   i=-1;
  }
 }
 _canWrite=true;
}

//---------------------------------------------------------------------------
void __fastcall TConnectFrame::CanWrite(TObject *Sender)
{          
 _canWrite=true;
 ConnectStatus(2);
}

//---------------------------------------------------------------------------
void __fastcall TConnectFrame::IsError(TObject *Sender)
{
 ConnectStatus(0);  
}          
//---------------------------------------------------------------------------
void TConnectFrame::Write(char *buffer,int count)
{
 if(_connectStatus!=2) return;
 if(_outputClient==NULL) return;

 ((TOutputClient *)_outputClient)->Write(buffer,count);
}
//---------------------------------------------------------------------------
int TConnectFrame::Read(char *buffer,int count)
{
 if(_connectStatus!=2) return 0;
 if(_outputClient==NULL) return 0;

 return ((TOutputClient *)_outputClient)->Read(buffer,count);
}
//---------------------------------------------------------------------------
void TConnectFrame::ConnectStatus(int status)
{
 _connectStatus=status;
 switch(status)
 {
  case 0 : // no connect
   ConnectButton->Enabled=true;
   DisconnectButton->Enabled=false;
   StatusEdit->Visible=false;
   StatusLampPanel->Color=clBtnFace;
   StatusTimer->Enabled=false; 
   TermPageControl->Enabled=true;
  break;
  case 1 : // connecting
   ConnectButton->Enabled=false;
   DisconnectButton->Enabled=true;
   TermPageControl->Enabled=false;
   StatusEdit->Visible=false;
   StatusTimer->Enabled=true;
   StatusLampPanel->Color=clLime;
  break;
  case 2: // connected        
   TermPageControl->Enabled=false;
   ConnectButton->Enabled=false;
   DisconnectButton->Enabled=true;
   StatusTimer->Enabled=false;
   StatusLampPanel->Color=clLime;
   StatusEdit->Text="00:00:00";
   StatusEdit->Visible=true;
  break;
 }
}
//---------------------------------------------------------------------------
int TConnectFrame::ConnectStatus()
{
 return _connectStatus;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TConnectFrame::StatusTimerTimer(TObject *Sender)
{
 StatusTimer->Tag=1-StatusTimer->Tag;
 StatusLampPanel->Color=(StatusTimer->Tag==1)?clLime:clBtnFace;       
}
//---------------------------------------------------------------------------
void __fastcall TConnectFrame::CanWriteTimerTimer(TObject *Sender)
{
 _canWrite=true;       
}

//---------------------------------------------------------------------------
//unsigned long _lastSended;
//int _lastReceived;

void __fastcall TConnectFrame::OnCanSend(TObject *Sender)
{
 if(_canWrite==true)
 {
  AnsiString s;
                /*
  _lastSended=time(NULL);
  s=ASS("1 optionaldevice1 LAST ")+ASS(_lastSended)+ASS("\n");
  Write(s.c_str(),s.Length());
                 */
  AnsiString com=((TAnalyserMeterFrame *)Owner)->GetCommand();
  if(com.Length()<1) return;
  
  if(this->PrefixSendingEdit->Text.Length()>0)
   s=PrefixSendingEdit->Text+ASS(" ")+com;
  else s=com;

 /* if(_prefix.Length()>0)
   s=s+_prefix+ASS(" ")+com;
   */
  //s=s+com;

  s=s+_sendAddition;;
  //CommandCombo->Text+_sendAddition;//AnsiString("\n");
  Write(s.c_str(),s.Length());
  _canWrite=false;
  CanWriteTimer->Enabled=false;
 }
 else
  CanWriteTimer->Enabled=true;
}

//---------------------------------------------------------------------------
void __fastcall TConnectFrame::IPConnectTimerTimer(TObject *Sender)
{
 if(_connectStatus!=2)
  Connect();
}
//---------------------------------------------------------------------------

