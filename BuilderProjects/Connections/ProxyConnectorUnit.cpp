//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProxyConnectorUnit.h"
#include <DateUtils.hpp>
#include "LinkUnit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

TProxyConnector *TProxyConnector::_firstConnector=NULL;
TProxyConnector *TProxyConnector::NextConnector()
{
 return _nextConnector;
}

void TProxyConnector::NextConnector(TProxyConnector *next)
{
 TProxyConnector *connector=_firstConnector;
 if(next==NULL)         // delete this from list
 {
  for(;;)
  {
   if(connector==NULL) break;
   if(connector->_nextConnector==this)
   {
    connector->_nextConnector=this->NextConnector();
    break;
   }
   connector=connector->_nextConnector;
  }
 }
 else    // add to list
 {
  for(;;)
  {
   if(connector->_nextConnector==NULL) { connector->_nextConnector=next;   break;}
   connector=connector->_nextConnector;
  }
 }
}

//---------------------------------------------------------------------------
AnsiString TProxyConnector::ProxyIP()
{
 return _proxyIP;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TProxyConnector::TProxyConnector(TComponent* Owner)  : TLinksConnector(Owner)
{
 _nextConnector=NULL;
 if(_firstConnector==NULL) _firstConnector=this;
 else NextConnector(this);

 _pingTime=7;
 _pingTimer=new TTimer(this);
 _pingTimer->Interval=_pingTime*1000L;
 _pingTimer->OnTimer=PingTimerFunc;
 _pingTimer->Enabled=false;
}
//--------------------------------------------------------------------------
__fastcall TProxyConnector::~TProxyConnector()
{
 NextConnector(NULL);
} //////////////////////////  PING  /////////////////////////////////////
//---------------------------------------------------------------------------

void __fastcall TProxyConnector::PingTimerFunc(TObject *Sender)
{
// if(PingCheck->Checked==false) return;
 if(Connected()==true)
 {
  _pingStart=Time();
  char buff[25];
  /*
  if(_nodeID.Length()>2)
   sprintf(buff,"//%s ",_nodeID.c_str());
  else buff[0]=0;
  sprintf(buff+strlen(buff),"@ping %lu\n",_pingStart);
    */
  
  sprintf(buff,"@ping %lu\n",_pingStart);
  WriteString(buff);
 }
}
//--------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------
int TProxyConnector::DoConnect()
{
 ByProxy(false);
 if(_firstConnector!=this & (UseProxy()==true))
 {
  ByProxy(true);
 }

  /*
  else
  IF(IpTypeComboBox->Text.c_str(),"Спутник",7)
  {
   ByTunnel(true);
  } */
 else
  return TConnector::DoConnect();
 return 1;
}
//---------------------------------------------------------------------
void TProxyConnector::DoConnecting()
{
 if(ByProxy()==true) DoConnected();
 TLinksConnector::DoConnecting();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TProxyConnector::DoCanWrite()
{
 TLinksConnector::DoCanWrite();
 //ProxyDoCanWrite();
}

//---------------------------------------------------------------------------
void TProxyConnector::DoConnected()
{
 _pingTime=0;
 _pingTimer->Enabled=true;

 TLinksConnector::DoConnected();
 ProxyDoConnected();
}

//---------------------------------------------------------------------------
void TProxyConnector::DoDisconnected()
{                     
 _pingTimer->Enabled=false;
 TConnector::DoDisconnected();
 ProxyDoDisconnected();
}

//---------------------------------------------------------------------------

void TProxyConnector::DoError(int errorCode)
{
 TLinksConnector::DoError(errorCode);
// ProxyDoError(errorCode);
}
//---------------------------------------------------------------------------
void TProxyConnector::DoReadReady()
{
 IF(_receiveBuffer,"@Ping",5)
 {
  TDateTime t=Time();
  _pingTime=MilliSecondsBetween(t,_pingStart);
 }
 else
 IF(_receiveBuffer,"/:",2)
 {
  ProxyDoReadReady();
 }
 else
  TLinksConnector::DoReadReady();
}
////////////////////////////////////////////////

//---------------------------------------------------------------------------
int TProxyConnector::Receive(char *buffer,int count)
{
 if(ByProxy()==true)
  return _firstConnector->Read(buffer,count);

// else
 return TLinksConnector::Receive(buffer,count);

 //if(_client) return _client->Read(buffer,count);
 //else return 0;
}

//---------------------------------------------------------------------------
int TProxyConnector::Send(char *buffer,int count)
{
 char buff[4096];
 buff[0]=0;

 if(count>4000) return 0;

 buffer[count]=0;

 if(UseProxy()==true)
 {
  sprintf(buff,"/:%s %s",ProxyIP().c_str(),buffer);
  return _firstConnector->Write(buff,Strlen(buff));
 }
 return TLinksConnector::Send(buffer,count);
}

//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

/// Links ////////////
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


///////  TUNNELS //////////////////////////
   
//---------------------------------------------------------------------------
bool TProxyConnector::ByProxy()
{
 if(_firstConnector==this) return false;
 return _byProxy;
}
//---------------------------------------------------------------------------
void TProxyConnector::ByProxy(bool bt)
{
 if(_firstConnector==this) return;
 _byProxy=bt;
}
//---------------------------------------------------------------------------
void TProxyConnector::ProxyDoReadReady()
{
 if(this!=_firstConnector) return;

 char *argv[3];
 int argc=2;
 char buffer[4096];
 _receiveBuffer[_receiveBufferCount]=0;
 Strncpy(buffer,_receiveBuffer+2,Strlen(_receiveBuffer)-2);
 argc=SplitCommand(buffer,argv,argc);
 if(argc>1)
 {
  TProxyConnector *connector=(TProxyConnector *)(_firstConnector);//->NextConnector());
  for(;;)
  {
   connector=(TProxyConnector *)(connector->NextConnector());
   if(connector==NULL) return;
   if(connector->ProxyIP()==argv[0])
   {
    _receiveBufferCount=Strlen(argv[1]);
    Strncpy(_receiveBuffer,argv[1],_receiveBufferCount);
    connector->DoReadReady();
    return;
   }
  }
 }
}

//---------------------------------------------------------------------------
void TProxyConnector::ProxyDoConnected()
{
 if(this!=_firstConnector) return;

 TProxyConnector *connector=this;//(TProxyConnector *)(_firstConnector);//->NextConnector());
 for(;;)
 {
  connector=(TProxyConnector *)(connector->NextConnector());
  if(connector==NULL) return;
  connector->DoConnected();
 }
} 
//---------------------------------------------------------------------------
void TProxyConnector::ProxyDoDisconnected()
{
 if(this!=_firstConnector) return;

 TProxyConnector *connector=this;//(TProxyConnector *)(_firstConnector);//->NextConnector());
 for(;;)
 {
  connector=(TProxyConnector *)(connector->NextConnector());
  if(connector==NULL) return;
  connector->DoDisconnected();
 }
}
////////////////////
