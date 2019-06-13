//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ConnectorUnit.h"
#include "LinkUnit.h"
#include <DateUtils.hpp>
#include "OutputClient.h"
#include "Functions.h"


#include "TcpClient.h"
#include "TtyClient.h"



//---------------------------------------------------------------------------
#pragma package(smart_init)


#ifndef FIRSTCONNECTOR
#define FIRSTCONNECTOR 1

TConnector *_firstConnector=NULL;
/*
TConnector *FirstConnector()
{
 if(_firstConnector==NULL)
  _firstConnector=new TConnector(Application->MainForm);
 return _firstConnector;
}   */
#endif


//Connector *Connector;

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
__fastcall TConnector::TConnector(TComponent* Owner)
        : TClient(Owner)
{
 if(_firstConnector==NULL) _firstConnector=this;

 _client=NULL;

 //_receiveBufferCount=0;
 _connectStatus=connectNO;

 _reconnectAuto=false;
 _reconnectTime=10;
 _reconnectTimer=new TTimer(this);
 _reconnectTimer->Interval=1000;//_reconnectTime*1000L;
 _reconnectTimer->OnTimer=ReconnectTimerFunc;
 _reconnectTimer->Enabled=false;

 _connectingConfirmation=false;
 _connectingTime=10;
 _connectingTimer=new TTimer(this);
 _connectingTimer->Interval=1000;//_connectingTime*1000L;
 _connectingTimer->OnTimer=ConnectingTimerFunc;
 _connectingTimer->Enabled=false;

 _disconnectAuto=false;
 _disconnectTime=10;
 _disconnectTimer=new TTimer(this);
 _disconnectTimer->Interval=1000;//_disconnectTime*1000L;
 _disconnectTimer->OnTimer=DisconnectTimerFunc;
 _disconnectTimer->Enabled=false;

}
//--------------------------------------------------------------------------
__fastcall TConnector::~TConnector()
{

}
//--------------------------------------------------------------------------
void TConnector::InterfaceSet(AnsiString name)
{
 _interfaceString=name;
}
//--------------------------------------------------------------------------
AnsiString TConnector::InterfaceName()
{
 return _interfaceString;
} 
//--------------------------------------------------------------------------
bool TConnector::AccessFor(int purpose)
{
 return true;
}
//--------------------------------------------------------------------------




///// PROCESSING  //////

/////////// CLIENT ////////////////////////


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void  TConnector::Reconnect()
{
 if(_reconnectTimer->Tag>=_reconnectTime)
 {
  DoConnect();
 }
 else _reconnectTimer->Tag++;
             /*
 DoDisconnect();

 _reconnectTimer->Enabled=_reconnectAuto;
 _reconnectTimer->Tag=0;
 */
}
//---------------------------------------------------------------------------
void __fastcall TConnector::ReconnectTimerFunc(TObject *)
{
 Reconnect();
}
//---------------------------------------------------------------------------
void __fastcall TConnector::DisconnectTimerFunc(TObject *Sender)
{
 if(_isReceived==false)
 {
  _disconnectTimer->Tag++;
 }
 else
 {
  _disconnectTimer->Tag=0;
  _isReceived=false;
 }

 if(_disconnectTimer->Tag>=_disconnectTime)
 {
  _disconnectTimer->Tag=0;
  Reconnect();
 }
}
//---------------------------------------------------------------------------

void __fastcall TConnector::ConnectingTimerFunc(TObject *Sender)
{
 if((_connectingTimer->Tag>=_connectingTime)|(_isReceived==true))
 {
  if(_isReceived==true)
  {
   _connectingTimer->Enabled=false;
   _connectingTimer->Tag=0;
   _disconnectTimer->Tag=0;
   _disconnectTimer->Enabled=_disconnectAuto;// DisconnectCheck->Checked;
   _connectStatus=connectIS;
  }
  else
  {
   Reconnect();
  }
 }
 else _connectingTimer->Tag++;
}


/*********************                       */

//---------------------------------------------------------------------
int TConnector::DoConnect()
{
 // CreateClient

 /*
 char buf[100];
 int argc;
 char *argv[10];
 Strncpy(buf,_interfaceString.c_str(),99);
 argc=SplitBuffer(buf,argv,9," ");
 */
 char *buf=_interfaceString.c_str();

 AnsiString s;

 IF(buf,"IP",2)
 {
  _client=new TcpClient(this);
  _client->InterfaceSet(buf+3);//argv+1,argc-1);
 }
 else
 IF(buf,"TTY",3)
 {
  _client=new TtyClient(this);
  _client->InterfaceSet(buf+4);//argv+1,argc-1);
 }
 else
 IF(buf,"ATModem",3)
 {
 }
 else return 0;

 if(_client)
 {
  _client->OnError=OnClientError;
  _client->OnDisconnected=OnClientDisconnected;
  _client->OnConnected=OnClientConnected;
  _client->OnCanWrite=OnClientCanWrite;
  _client->OnReadReady=OnClientReadReady;
 }

 //if(_controlType==1) Close();
 DoConnecting();
 return 1;
}


//---------------------------------------------------------------------------
void TConnector::DoConnecting()
{
 _connectStatus=connectTRY;
 _isReceived=0;
 //if(==true)
 _connectingTimer->Enabled=_connectingConfirmation;//true;

 _reconnectTimer->Enabled=false;
 _disconnectTimer->Enabled=false;
 _connectingTimer->Tag=0;

 if(_client!=NULL) _client->DoConnect();
 TClient::DoConnecting();
}
 

//---------------------------------------------------------------------------
void TConnector::DoConnected()
{
 _connectTime=Time();
 _sendedPackets=0;
 _receivedPackets=0;
 _sendedBytes=0;
 _receivedBytes=0;

 if(OnConnected) OnConnected(this);

 _reconnectTimer->Enabled=false;
 _disconnectTimer->Enabled=false;

 _connectStatus=connectIS;
 TClient::DoConnected();
}

//---------------------------------------------------------------------------
int TConnector::DoDisconnect()
{
 if(_client) _client->DoDisconnect();

// if(ByTunnel()==true) DoDisconnected();
 //_reconnectTimer->Enabled=false;
 DoDisconnected();   
 _reconnectTimer->Enabled=false;

 // DeleteClient
 if(_client)
 {
  delete _client;
  _client=NULL;
 }
 return 1;
}

//---------------------------------------------------------------------------
void TConnector::DoDisconnected()
{
 _reconnectTimer->Enabled=_reconnectAuto;
 _reconnectTimer->Tag=0;

 _disconnectTimer->Enabled=false;
 _connectingTimer->Enabled=false;

 _connectStatus=connectNO;
 TClient::DoDisconnected();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TConnector::DoCanWrite()
{
 TClient::DoCanWrite();
}
//---------------------------------------------------------------------------

void TConnector::DoError(int errorCode)
{
 TClient::DoError(errorCode);
}
//---------------------------------------------------------------------------
void TConnector::DoReadReady()
{
 TClient::DoReadReady();
 _receiveBufferCount=0;
}
////////////////////////////////////////////////

//---------------------------------------------------------------------------
int TConnector::Read(char *buffer, int count)
{
// count=Receive(buffer,count);


 if(count<_receiveBufferCount) _receiveBufferCount=0;
 count=Memcpy(buffer,_receiveBuffer,_receiveBufferCount);
 buffer[count]=0;
 
 _receiveBufferCount=0;
 _receivedBytes+=count;
 _receivedPackets++;

 return count;
}


//---------------------------------------------------------------------------
int TConnector::Write(char *buffer,int count)
{
 _sendedBytes+=count;
 _sendedPackets++;
 return Send(buffer,count);
}

//---------------------------------------------------------------------------
int TConnector::Receive(char *buffer,int count)
{
// if(ByTunnel()==true)   return _firstConnector->Read(buffer,count);
 


 if(_client)
 {
  count=_client->Read(buffer,count);
  /*
  int addLen=Strlen(_recvAddition);
  count=count-addLen;

  IF(buffer+count,_sendAddition,addLen)
   buffer[count]=0;

    */
  return count;
 }

 else return 0;
}

//---------------------------------------------------------------------------
int TConnector::Send(char *buffer,int count)
{
// char buff[OC_MAX_COUNT];
// buff[0]=0;

 if(count>=OC_MAX_COUNT) return 0;

 buffer[count]=0;
 /*int sendAddLen=Strlen(_sendAddition);
 int addPos=Strlen(buffer)-sendAddLen;

 IF(buffer+addPos,_sendAddition,sendAddLen)
 {
  buffer[addPos]=0;
 }

 if(buffer[Strlen(buffer)-1]=='\n') buffer[Strlen(buffer)-1]=0;

 count=sprintf(buff,"%s%s",buffer,_sendAddition);
   */
 if(_client) return _client->Write(buffer,count);
 else return 0;
}

//---------------------------------------------------------------------------

//////// Cliebnt

// Client Events

//---------------------------------------------------------------------------
void  __fastcall TConnector::OnClientError(TObject *Sender)
{
 DoError(0);
}
//---------------------------------------------------------------------------
void  __fastcall TConnector::OnClientDisconnected(TObject *Sender)
{
 DoDisconnected();
}
//---------------------------------------------------------------------------
void  __fastcall TConnector::OnClientConnected(TObject *Sender)
{
 DoConnected();
}
//---------------------------------------------------------------------------
void  __fastcall TConnector::OnClientCanWrite(TObject *Sender)
{
 DoCanWrite();
}
//---------------------------------------------------------------------------
void  __fastcall TConnector::OnClientReadReady(TObject *Sender)
{
 _receiveBufferCount=Receive(_receiveBuffer,OC_MAX_COUNT);
 _receiveBuffer[_receiveBufferCount]=0;
 /*
 for(;;)
 {
  _receiveBufferCount=Receive(_receiveBuffer,(sizeof(_receiveBuffer)-1));
  _receiveBuffer[_receiveBufferCount]=0;

  if(_receiveBufferCount<1) return;

  _isReceived=true;



  _receiveBufferCount=0;
 }
 */
 if(_receiveBufferCount>0)
  DoReadReady();
}


//---------------------------------------------------------------------------

