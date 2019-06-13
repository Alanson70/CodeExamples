//---------------------------------------------------------------------------


#pragma hdrstop

#include "WinTtyDefs.hpp"
#include "TtyClient.h" 
#include "Functions.h"

#pragma package(smart_init)

#pragma link "WinTtyDefs"
//---------------------------------------------------------------------------
__fastcall TtyClient::TtyClient(TComponent *AOwner) : TOutputClient(AOwner)
{
 _baudRate=6;
 _byteSize=4;
 _stopBits=0;
 _parity=2;

 _receiveTimer=new TTimer(this);
 _receiveTimer->Interval=20;
 _receiveTimer->Enabled=true;
 _receiveTimer->OnTimer=ReceiveTimer;
 _opened=false;
 _ttyConnected=false;
 _receiveCount=0;
 _Handle=NULL;

 TestCheckSum(true);
}

__fastcall TtyClient::~TtyClient()
{
 Close();
}

//---------------------------------------------------------------------------
int TtyClient::InterfaceSet(char **argv,int argc)
{
 if(argc<1) return 0;

 
 _portName=argv[0];

 _interface="";//AnsiString(argv[0]);

  for(int i=0;i<argc;i++)
  {
   _interface+=AnsiString(" ")+AnsiString(argv[i]);

   if(argv[i][0]=='-')
   {
    switch(argv[i][1])
    {
     case 'r' :
     {
      long r=atol(argv[i]+2);
      for(int j=0;j<16;j++) if(BaudRatesReal[j]==r) _baudRate=j;
     }
     break;
     case 's' :
      if(atoi(argv[i]+2)==1) _stopBits=0;
      if(atoi(argv[i]+2)==2) _stopBits=2;
     break;
     case 'b' : _byteSize=atoi(argv[i]+2)-4;    break;
     case 'p' :
      switch(argv[i][2])
      {
       case '0' :
       case 'n' :
       case 'N' : _parity=2;break;
       case '1' :
       case 'o' :
       case 'O' : _parity=3;break;
       case '2' :
       case 'e' :
       case 'E' : _parity=0;break;
      }
     break;
    }
   }
  }

 return 1;
}

//---------------------------------------------------------------------------
bool  __fastcall TtyClient::Open()
{
 Close();

 DWORD dwDesiredAccess=GENERIC_READ|GENERIC_WRITE; // access (read-write) mode
 DWORD dwShareMode=0; // share mode
 LPSECURITY_ATTRIBUTES lpSecurityAttributes=NULL;// pointer to security attributes
 DWORD dwCreationDistribution=OPEN_EXISTING; // how to create
 DWORD dwFlagsAndAttributes=FILE_FLAG_OVERLAPPED;//FILE_ATTRIBUTE_NORMAL|;// file attributes
 HANDLE hTemplateFile=NULL; 	// handle to file with attributes to copy

 _Handle=CreateFile(_portName.c_str(),
  dwDesiredAccess,
  dwShareMode,
  lpSecurityAttributes,
  dwCreationDistribution,
  dwFlagsAndAttributes,
  hTemplateFile);

 if(_Handle==INVALID_HANDLE_VALUE)
 {
  _ErrorCode=GetLastError();
  char Result[1000];
   FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,_ErrorCode, 0, Result, 1000,NULL);
  _Handle=NULL;
  return false;
 }
 else
 {
  
  _opened=true;
  _ErrorCode=0;

  SetPortOption();
  SetPortTimeout();
  //_WriteOverlapped.hEvent=CreateEvent(NULL,false,false,NULL);
  _ReadOverlapped.hEvent=CreateEvent(NULL,true,false,NULL);
  //SetReading();

  PurgeComm(_Handle,PURGE_TXCLEAR|PURGE_RXCLEAR);
  if(ReadFile(_Handle,_InBuffer,1,&_BytesRead,&_ReadOverlapped)==false);

 }
 return true;
}

//---------------------------------------------------------------------------
AnsiString TtyClient::InterfaceName()
{
 return _interface;
}
//---------------------------------------------------------------------------
int TtyClient::Connect()
{        
 if(Open()==false)
 {
  DoError(2);
  return 0;
 }

 if(_opened==true)
 {
  _ttyConnected=true;
 //DoCanWrite();  
  //if(ReadFile(_Handle,_InBuffer,sizeof(_InBuffer),&_BytesRead,&_ReadOverlapped)==false);
  DoConnected();
  return 1;
 }
 return 0;
}

//---------------------------------------------------------------------------
int TtyClient::Disconnect()
{
 if(_ttyConnected==true)
 {
  _ttyConnected=false;
  DoDisconnected();
 } 
 Close();
 return 1;
}
//---------------------------------------------------------------------------
void __fastcall TtyClient::Close()
{
 if(_Handle)
 {
  CloseHandle(_Handle);
  _Handle=NULL;

//  Sleep(3000);  // must be if open starts after close immediately
 }

 _ErrorCode=GetLastError();
 _opened=false;
 _ttyConnected=false;
}
//---------------------------------------------------------------------------
void __fastcall TtyClient::ReceiveTimer(TObject *Sender)
{
 /*_receiveCount+=ReceiveFromPort(_receiveBuffer+_receiveCount,1+sizeof(_receiveBuffer)-_receiveCount);

 if(_receiveCount>=(sizeof(_receiveBuffer)-1)) _receiveCount=0;

 if(_receiveCount>0)
 */
 DoReadReady();
}

//---------------------------------------------------------------------------
int TtyClient::ReceiveFromPort(char *buffer,int count)
{
 if(_opened==false) return 0;
 if(_ttyConnected==false) return 0;

 if(GetOverlappedResult(_Handle,&_ReadOverlapped,&_BytesRead,false)==true)
 {
  count=0;
  for(;;)
  {
   if(_BytesRead!=0)
   {
    if(_BytesRead>(sizeof(_receiveBuffer)-_receiveCount))
    {
     _ErrorCode==0;
    }
    else
     _receiveCount+=Memcpy(_receiveBuffer+_receiveCount,_InBuffer,MIN(_BytesRead,sizeof(_receiveBuffer)-_receiveCount));
   }
   else break;

   ReadFile(_Handle,_InBuffer,sizeof(_InBuffer),&_BytesRead,&_ReadOverlapped);
  }

   _ErrorCode=GetLastError();
   //FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,_ErrorCode, 0, Result, 1000,NULL);
//  return 0;
  //}
 }

 count=Memcpy(buffer,_receiveBuffer,MIN(count,_receiveCount));
 _receiveCount=Memcpy(_receiveBuffer,_receiveBuffer+count,_receiveCount-count);

 return count;


}



//---------------------------------------------------------------------------
int TtyClient::SendToPort(char *buffer,int count)
{             
 if(_ttyConnected==false) return 0;

 if(_opened==false) return 0;
 if(WriteFile(_Handle,buffer,count,&_BytesWrite,&_WriteOverlapped)==false)
 {
  _ErrorCode=GetLastError();
  return 0;
 }

 return count;
}

//---------  Settings  -----------------------
//---------------------------------------------------------------------------
void TtyClient::SetPortOption()
{
 DCB dcb;

 if(GetCommState(_Handle,&dcb)==false)
  _ErrorCode=GetLastError();
 dcb.BaudRate=BaudRates[_baudRate];
 dcb.ByteSize=ByteSizes[_byteSize];
 dcb.Parity=Paritets[_parity];
 dcb.StopBits=StopBitss[_stopBits];
 dcb.fDtrControl=DTR_CONTROL_ENABLE	;
 dcb.fRtsControl=RTS_CONTROL_ENABLE;
 if(SetCommState(_Handle,&dcb)==false)
  _ErrorCode=GetLastError();
 if(GetCommState(_Handle,&dcb)==false)
  _ErrorCode=GetLastError();
 if(SetupComm(_Handle,4000,4000)==false)
  _ErrorCode=GetLastError();
}
   /*
void TtyClient::GetPortOption()
{
 DCB dcb;

 GetCommState(_Handle,&dcb);
 BaudRates[BaudRate]=dcb.BaudRate;
 ByteSize=dcb.ByteSize;
 Parity=dcb.Parity;
 StopBits=dcb.StopBits;
}

void TtyClient::SetOptions(int nBaudRate,int nByteSize,int nParity,int nStopBits)
{
 BaudRate=nBaudRate;
 ByteSize=nByteSize;
 StopBits=nStopBits;
 Parity=nParity;

 SetPortOption();
}

*/

//---------------------------------------------------------------------------
void TtyClient::SetPortTimeout()
{
 COMMTIMEOUTS CT;

 GetCommTimeouts(_Handle,&CT);
 CT.ReadIntervalTimeout=1;
 CT.ReadTotalTimeoutConstant=0;
 CT.ReadTotalTimeoutMultiplier=0;
 CT.WriteTotalTimeoutConstant=0;
 CT.WriteTotalTimeoutMultiplier=0;
 SetCommTimeouts(_Handle,&CT);
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
int TtyClient::Receive(char *buffer,int count)
{
 return ReceiveFromPort(buffer,count);
}
//---------------------------------------------------------------------------
int TtyClient::Send(char *buffer,int count)
{
 return SendToPort(buffer,count);
}







#pragma package(smart_init)
