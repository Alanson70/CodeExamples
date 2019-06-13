//---------------------------------------------------------------------------


#pragma hdrstop

#include "TcpClient.h"
#include "Functions.h"

#pragma link "OutputClient"

#pragma package(smart_init)
//    TcpClient
__fastcall TcpClient::TcpClient(TComponent *AOwner) : TOutputClient(AOwner)
{
 _ipPort=8000;
 
 Socket=new TClientSocket(this);
 Socket->OnRead=ReadReadyFunc;
 Socket->OnConnect=OnConnectedFunc;//CanWriteFunc;
 Socket->OnDisconnect=OnDisconnectedFunc;
 Socket->OnError=ErrorFunc;
}
//---------------------------------------------------------------------------

 __fastcall TcpClient::~TcpClient()
{
 //Close();
}
//---------------------------------------------------------------------------
int TcpClient::InterfaceSet(char **argv,int argc)
{
 _ipPort=8000;

 if(Socket->Address!=argv[0]) DoDisconnect();
  Socket->Address=argv[0];


 if(argc>1) _ipPort=atol(argv[1]);

 if(Socket->Port!=_ipPort) DoDisconnect();
 Socket->Port=_ipPort;

 //_interface="IP"+AnsiString(" ")+argv[0]+AnsiString(" ")+AnsiString(port);
 _ipAddr=argv[0];//+AnsiString(" ")+AnsiString(_ipPort);

 if(_ipPort==0) return 0;
 return 1;
}
//---------------------------------------------------------------------------
/*
AnsiString TcpClient::Interface()
{
 return _interface;
}
*/
//---------------------------------------------------------------------------
AnsiString TcpClient::InterfaceName()
{
 return _ipAddr+AnsiString(" ")+AnsiString(_ipPort);
}
//---------------------------------------------------------------------------
int TcpClient::DoConnect()
{
 if(Socket->Active==true) DoConnected();
 Socket->Active=true;
 return 1;
}
//---------------------------------------------------------------------------
int TcpClient::DoDisconnect()
{
 Socket->Active=false;
 return 1;
}  
//---------------------------------------------------------------------------
void __fastcall TcpClient::OnConnectedFunc(TObject *Sender,TCustomWinSocket *Socket)
{
 DoConnected();
}  
//---------------------------------------------------------------------------
void __fastcall TcpClient::OnDisconnectedFunc(TObject *Sender,TCustomWinSocket *Socket)
{
 DoDisconnected();
}
//---------------------------------------------------------------------------
void __fastcall TcpClient::ErrorFunc(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
 ErrorCode=0;
 DoError(1);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TcpClient::ReadReadyFunc(TObject *Sender,TCustomWinSocket *Socket)
{
 DoReadReady();
}
//---------------------------------------------------------------------------

void __fastcall TcpClient::CanWriteFunc(TObject *Sender,TCustomWinSocket *Socket)
{
 DoCanWrite();
}
//---------------------------------------------------------------------------
//#include <DateUtils.hpp>

int TcpClient::Receive(char *buffer,int count)
{
 /*
 if(_tunnel.Length()>0)
 {
  count=Socket->Socket->ReceiveBuf(buffer,count);
  IF(buffer,"//",2)
  {
   for(int i=0;i<Strlen(buffer);i++)
   {
    if(buffer[i]==' ')
    {
     count-=(i+1);
     Memcpy(buffer,buffer+(i+1),count);
     break;
    }
   }
  }
 }
 else
 */
  count=Socket->Socket->ReceiveBuf(buffer,count);

 if(count>0)  return count;
 return 0;
}
//---------------------------------------------------------------------------
int TcpClient::Send(char *buffer,int count)
{
 if(count<1) return 0;
  /*
 AnsiString text;
 if(_tunnel.Length()>0)
  text=_tunnel+AnsiString(" ");
 text+=buffer;
 count=Socket->Socket->SendText(text);
//
*/
 count=Socket->Socket->SendBuf(buffer,count);

 return count;
}
//---------------------------------------------------------------------------

//




//---------------------------------------------------------------------------

#pragma package(smart_init)
