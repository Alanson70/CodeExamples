//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ControlClientFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


char *StringAdditions[4]={"\r\n","\r","\n",""};
//---------------------------------------------------------------------------
__fastcall TControlClientForm::TControlClientForm(TComponent* Owner)   : TForm(Owner)
{
 _Client=new TControlClient(this);
 _Client->OnCanWrite=this->OnClientCanWrite;
 _Client->OnReadReady=this->OnClientReadReady;
 _Client->OnError=OnClientChangeConnectStatus;//OnClientError;
 _Client->OnDisconnected=OnClientChangeConnectStatus;//OnClientDisconnected;
 _Client->OnConnected=OnClientChangeConnectStatus;//OnClientConnected;
}


//---------------------------------------------------------------------------
void TControlClientForm::LoadInits(ASS fileName)
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
                       
 delete iniFile;

 AdditionOptionComboBoxChange(this);

 if(doConnect)
  this->ConnectButtonClick(this);
}
//---------------------------------------------------------------------------
void TControlClientForm::SaveInits(ASS fileName)
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
void TControlClientForm::ConnectStatus(int status)
{
 _connectStatus=status;
 switch(status)
 {
  case 0 : // no connect
   ConnectButton->Enabled=true;
   DisconnectButton->Enabled=false;
   StatusEdit->Visible=false;
   StatusLabel->Visible=false;
   StatusLampPanel->Color=clBtnFace;
   StatusTimer->Enabled=false; 
   TtyPanel->Enabled=true;
   IpPanel->Enabled=true;
  break;
  case 1 : // connecting
   ConnectButton->Enabled=false;
   DisconnectButton->Enabled=true;
   TtyPanel->Enabled=false;
   IpPanel->Enabled=false;
   StatusEdit->Visible=false;
   StatusLabel->Visible=false;
   StatusTimer->Enabled=true;
   StatusLampPanel->Color=clLime;
  break;
  case 2: // connected        
   TtyPanel->Enabled=false;
   IpPanel->Enabled=false;
   ConnectButton->Enabled=false;
   DisconnectButton->Enabled=true;
   StatusTimer->Enabled=false;
   StatusLampPanel->Color=clLime;
 //  StatusEdit->Text="00:00:00";
 //  StatusEdit->Visible=true;
 //  StatusLabel->Visible=true;
  break;
 }
}
//---------------------------------------------------------------------------
int TControlClientForm::ConnectStatus()
{
 return _connectStatus;
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TControlClientForm::AdditionOptionComboBoxChange(TObject *Sender)
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
  _Client->_sendAddition=StringEndSendingOptionEdit->Text;
 else
  _Client->_sendAddition=StringAdditions[AdditionSendingOptionComboBox->ItemIndex];

 if(AdditionReceivingOptionComboBox->ItemIndex==3)
  _Client->_rcvAddition=StringEndReceivingOptionEdit->Text;
 else
  _Client->_rcvAddition=StringAdditions[AdditionReceivingOptionComboBox->ItemIndex];
}
//---------------------------------------------------------------------------
void __fastcall TControlClientForm::StringEndOptionEditChange(TObject *Sender)
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
void __fastcall TControlClientForm::PrefixEditChange(TObject *Sender)
{
 _Client->_rcvPrefix=PrefixReceivingEdit->Text;
 _Client->_sendPrefix=PrefixSendingEdit->Text;
}
//---------------------------------------------------------------------------

void __fastcall TControlClientForm::ConnectButtonClick(TObject *Sender)
{
 Connect();
}
//---------------------------------------------------------------------------
void __fastcall TControlClientForm::DisconnectButtonClick(TObject *Sender)
{
 Disconnect();
}

//---------------------------------------------------------------------------
void TControlClientForm::Connect()
{
 ASS par;
 if(TermPageControl->ActivePage==TtyTabSheet)
 {
  par="TTY "+this->TtyPortComboBox->Text+ASS(" -r")+this->TtyRateComboBox->Text+ASS(" -p")+this->TtyParityComboBox->Text.operator [](1);
 }
 else
 {
  par="IP "+this->IpAddrEdit->Text+ASS(" ")+this->IpPortEdit->Text;
  if(this->IpComboBox->ItemIndex==0)
   par=par+ASS(" TCP");
  else
   par=par+ASS(" UDP");
 }
 _Client->InterfaceSet(par);
 _Client->DoConnect();
 IPConnectTimer->Enabled=true;
}
//---------------------------------------------------------------------------
void TControlClientForm::Disconnect()
{
 _Client->DoDisconnect(); 
 IPConnectTimer->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TControlClientForm::OnClientReadReady(TObject *Sender)
{
 if(OnReadReady) OnReadReady(this);
}
//---------------------------------------------------------------------------
void __fastcall TControlClientForm::OnClientCanWrite(TObject *Sender)
{
 if(OnCanWrite) OnCanWrite(this);
}
//---------------------------------------------------------------------------
void __fastcall TControlClientForm::OnClientChangeConnectStatus(TObject *Sender)
{
 ConnectStatus(_Client->ConnectStatus());
 if(OnChangeConnectStatus) OnChangeConnectStatus(this);
}
/*
//---------------------------------------------------------------------------
void __fastcall TControlClientForm::OnClientConnected(TObject *Sender)
{
 if(OnConnected) OnConnected(this);
}
//---------------------------------------------------------------------------
void __fastcall TControlClientForm::OnClientDisconnected(TObject *Sender)
{
 if(OnDisconnected) OnDisconnected(this);
}
//---------------------------------------------------------------------------
void __fastcall TControlClientForm::OnClientError(TObject *Sender)
{
 if(OnError) OnError(this);
}
*/
//---------------------------------------------------------------------------
int TControlClientForm::Read(char *buffer,int count)
{
 return _Client->Read(buffer,count);
}         
//---------------------------------------------------------------------------
ASS TControlClientForm::Read()
{
 char buffer[2000];
 _Client->Read(buffer,1999);
 ASS s=buffer;
 return s;
}
//---------------------------------------------------------------------------
int TControlClientForm::Write(char *buffer,int count)
{
 return _Client->Write(buffer,count);
}
//---------------------------------------------------------------------------

void __fastcall TControlClientForm::IPConnectTimerTimer(TObject *Sender)
{
 if(this->AutoConnectCheckBox->Enabled==true)
  if(ConnectStatus()!=2)
   this->Connect();
}
//---------------------------------------------------------------------------

void __fastcall TControlClientForm::StatusTimerTimer(TObject *Sender)
{
 StatusTimer->Tag=1-StatusTimer->Tag;
}
//---------------------------------------------------------------------------

