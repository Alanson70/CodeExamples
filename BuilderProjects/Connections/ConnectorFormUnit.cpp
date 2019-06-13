//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ConnectorFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TConnectorForm *ConnectorForm;
//---------------------------------------------------------------------------
__fastcall TConnectorForm::TConnectorForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TConnectorForm::Connector(TConnector *c)
{
 _Connector=c;
 DrawParams();
 DrawTimer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TConnectorForm::DrawTimerTimer(TObject *Sender)
{
 TConnector *c=_Connector;

 ///////////////////  STATE /////////////////

 StatusCombo->ItemIndex=c->ConnectStatus();
 ReconnectRepeatLabel->Visible=c->_reconnectTimer->Enabled;
 ReconnectRepeatEdit->Visible=c->_reconnectTimer->Enabled;
 ReconnectRepeatEdit->Text=c->_reconnectTime-c->_reconnectTimer->Tag;
 if(c->_connectingTimer->Enabled==true)
 {
  ConnectingTimerLabel->Caption="Установление соединения, (с)";
  ConnectingTimerLabel->Visible=true;
  ConnectingTimerEdit->Visible=true;
  ConnectingTimerEdit->Text=c->_connectingTime-c->_connectingTimer->Tag;
 }
 else
 if(c->_disconnectTimer->Enabled==true)
 {
  ConnectingTimerLabel->Caption="Обрыв соединения, через(с)";
  ConnectingTimerLabel->Visible=true;
  ConnectingTimerEdit->Visible=true;
  ConnectingTimerEdit->Text=c->_disconnectTime-c->_disconnectTimer->Tag;
 }
 else
 {
  ConnectingTimerLabel->Visible=false;
  ConnectingTimerEdit->Visible=false;
 }
// StatusCombo->ItemIndex=_connectStatus;

 if(c->_connectStatus==connectIS)
 {
  StatusCombo->ItemIndex=2;
  TDateTime dt=Time()-c->_connectTime;
  TimeEdit->Text=dt.TimeString();
  char buf[20];
  sprintf(buf,"(%.1lf)",c->_sendedBytes/1024.0);
  SendCountEdit->Text=AnsiString(c->_sendedPackets)+AnsiString(buf);
  sprintf(buf,"(%.1lf)",c->_receivedBytes/1024.0);
  ReceiveCountEdit->Text=AnsiString(c->_receivedPackets)+AnsiString(buf);
//  PingEdit->Text=AnsiString(_pingTime);
  //return;
 }
 else
 {
  SendCountEdit->Text="0";
  ReceiveCountEdit->Text="0";
  TimeEdit->Text="0";
 } 

// PingEdit->Text="?";
 if(c->_connectStatus==connectNO)
 {
  IPTabSheet->Enabled=true;
  SettingsTabSheet->Enabled=true;

  ConnectButton->Enabled=true;
 }
 else
 {
  IPTabSheet->Enabled=false;
  SettingsTabSheet->Enabled=false;
  ConnectButton->Enabled=false;
 }

}

//---------------------------------------------------------------------------
void TConnectorForm::DrawParams()
{
 TConnector *c=_Connector;
 /////////////// INTERFACE /////////////////////////////
 IpTypeComboBox->ItemIndex=2;

 char buf[100];
 Strncpy(buf,c->InterfaceName().c_str(),99);
 char *argv[10];
 int argc=SplitBuffer(buf,argv,9," ");

 IF(argv[0],"IP",2)
 {
  IpAddrEdit->Text=argv[1];
  IpPortEdit->Text=argv[2];
  if(argc>3) ProtokolComboBox->ItemIndex=atoi(argv[3]);
 }
 else
 IF(argv[0],"TTY",3)
 {
  //for(int i=0;i<TtyPortCombo;i++)
 }
 else;




 ReconnectCheck->Checked=c->_reconnectAuto;
 ReconnectUpDown->Position=c->_reconnectTime;

 DisconnectCheck->Checked=c->_disconnectAuto;
 DisconnectUpDown->Position=c->_disconnectTime;

 ConnectingCheck->Checked=c->_connectingConfirmation;
 ConnectingUpDown->Position=c->_disconnectTime;




}
//---------------------------------------------------------------------------
void __fastcall TConnectorForm::ConnectButtonClick(TObject *Sender)
{
 _Connector->DoConnect();
}
//---------------------------------------------------------------------------
void __fastcall TConnectorForm::DisconnectButtonClick(TObject *Sender)
{
 _Connector->DoDisconnect();
}
//---------------------------------------------------------------------------
