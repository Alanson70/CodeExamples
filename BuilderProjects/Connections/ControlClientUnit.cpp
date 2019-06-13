//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ControlClientUnit.h"
#include "LinkUnit.h"
#include <DateUtils.hpp>
#include "OutputClient.h"
#include "Functions.h"


#include "TcpClient.h"
#include "TtyClient.h"

#define connectNO  0
#define connectTRY 1
#define connectIS  2


//---------------------------------------------------------------------------
#pragma package(smart_init)


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TControlClient::TControlClient(TComponent* Owner)
        : TClient(Owner)
{
 _client=NULL;

 _receiveBufferCount=0;
 _connectStatus=connectNO;
}
//--------------------------------------------------------------------------
__fastcall TControlClient::~TControlClient()
{

}
//--------------------------------------------------------------------------
void TControlClient::InterfaceSet(AnsiString name)
{
 _interfaceString=name;
}
//--------------------------------------------------------------------------
AnsiString TControlClient::InterfaceName()
{
 return _interfaceString;
}
//--------------------------------------------------------------------------

///// PROCESSING  //////

/////////// CLIENT ////////////////////////


//---------------------------------------------------------------------------


/*
int TControlClient::Connect()
{
 if(DoConnect()==1)
  DoConnecting();
 else return 0;
 return 1;
}
*/

//---------------------------------------------------------------------------

//---------------------------------------------------------------------
int TControlClient::DoConnect()
{
 TOutputClient *client=(TOutputClient *)_client;
 _client=NULL;

 if(client)
 {
  client->DoDisconnect();
  delete client;
 }
 ConnectStatus(0);
 // CreateClient

 char buf[100];
 int argc;
 char *argv[10];
 Strncpy(buf,_interfaceString.c_str(),99);
 argc=SplitBuffer(buf,argv,9," ");

 AnsiString s;

 IF(argv[0],"IP",2)
 {
  _client=new TcpClient(this);
  _client->InterfaceSet(argv+1,argc-1);
 }
 else
 IF(argv[0],"TTY",2)
 {
  _client=new TtyClient(this);
  _client->InterfaceSet(argv+1,argc-1);
 }
 else
 IF(argv[0],"ATModem",3)
 {
 }
 else return 0;

 if(_client)
 {
  _client->OnError=OnClientError;
  _client->OnDisconnected=OnClientDisconnect;
  _client->OnConnected=OnClientConnect;
  _client->OnCanWrite=OnClientCanWrite;
  _client->OnReadReady=OnClientReadReady;
 }

 //if(_controlType==1) Close();
 DoConnecting();
 return 1;
}


//---------------------------------------------------------------------------
void TControlClient::DoConnecting()
{
 _connectStatus=connectTRY;

 if(_client!=NULL) _client->DoConnect();
 TClient::DoConnecting();
}
 

//---------------------------------------------------------------------------
void TControlClient::DoConnected()
{
 if(OnConnected) OnConnected(this);

 _connectStatus=connectIS;
 TClient::DoConnected();
}

//---------------------------------------------------------------------------
int TControlClient::DoDisconnect()
{
 if(_client) _client->DoDisconnect();

 DoDisconnected();

 // DeleteClient
 if(_client)
 {
  delete _client;
  _client=NULL;
 }
 return 1;
}

//---------------------------------------------------------------------------
void TControlClient::DoDisconnected()
{
 _connectStatus=connectNO;
 TClient::DoDisconnected();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TControlClient::DoCanWrite()
{
 TClient::DoCanWrite();
}
//---------------------------------------------------------------------------

void TControlClient::DoError(int errorCode)
{
 TClient::DoError(errorCode);
}
//---------------------------------------------------------------------------
void TControlClient::DoReadReady()
{
 TClient::DoReadReady();
 _receiveBufferCount=0;
}
////////////////////////////////////////////////

//---------------------------------------------------------------------------
int TControlClient::Read(char *Buffer, int Count)
{
 char buffer[OC_MAX_COUNT];
 int count=Receive(buffer,OC_MAX_COUNT-1);
 if(count>Count) return 0;

 buffer[count]=0;

 

  // remove postfix
 char end[200];
 strncpy(end,_rcvAddition.c_str(),199);
 int len=strlen(end);

 if(memcmp(buffer+count-len,end,len)==0)
  buffer[count-len]=0;
  // remove end symbols
 for(int i=(count-1);i>0;i--)
 {
  if(buffer[i]=='\n') { buffer[i]=0;count--; }
  else
  if(buffer[i]=='\r') { buffer[i]=0;count--; }
  else break;
 }
// remove prefix
 len=_rcvPrefix.Length();

 if(len>0)
  strncpy(end,_rcvPrefix.c_str(),199);

 IF(buffer,end,len);
 else    len=0;

 count=Memcpy(Buffer,buffer+len,count-len);

 return count;
}


//---------------------------------------------------------------------------
int TControlClient::Write(char *buffer,int count)
{
 ASS buff;

 if(count>4000) return 0;

 buffer[count]=0;
 if(buffer[Strlen(buffer)-1]=='\n') buffer[Strlen(buffer)-1]=0;

 if(_sendPrefix.Length()>0)
  buff=_sendPrefix+buffer;
 else
  buff=buffer;

 buff=buff+_sendAddition;
 return Send(buff.c_str(),buff.Length());
}

//---------------------------------------------------------------------------
int TControlClient::Receive(char *buffer,int count)
{
 if(_client) return _client->Read(buffer,count);
 else return 0;
}

//---------------------------------------------------------------------------
int TControlClient::Send(char *buffer,int count)
{    
 if(_client) return _client->Write(buffer,count);
 else return 0;
}

//---------------------------------------------------------------------------

//////// Cliebnt

// Client Events

//---------------------------------------------------------------------------
void  __fastcall TControlClient::OnClientError(TObject *Sender)
{
 DoError(0);
}
//---------------------------------------------------------------------------
void  __fastcall TControlClient::OnClientDisconnect(TObject *Sender)
{
 DoDisconnected();
}
//---------------------------------------------------------------------------
void  __fastcall TControlClient::OnClientConnect(TObject *Sender)
{
 DoConnected();
}  
//---------------------------------------------------------------------------
void  __fastcall TControlClient::OnClientCanWrite(TObject *Sender)
{
 this->DoCanWrite();// DoConnected();
}
//---------------------------------------------------------------------------
void  __fastcall TControlClient::OnClientReadReady(TObject *Sender)
{
 DoReadReady();

 /*
 //for(;;)
 {
  _receiveBufferCount=Receive(_receiveBuffer,(sizeof(_receiveBuffer)-1));

  if(_receiveBufferCount<1) return;



  _receiveBufferCount=0;
 }
 */
}


//---------------------------------------------------------------------------

