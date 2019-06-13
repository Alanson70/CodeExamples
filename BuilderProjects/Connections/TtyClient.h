//---------------------------------------------------------------------------

#ifndef TtyClientH
#define TtyClientH



#include <ExtCtrls.hpp>

#include "OutputClient.h"


class TtyClient : public TOutputClient
{
 protected :
  bool _ttyConnected;
  bool _opened;
  HANDLE _Handle;

  AnsiString _interface;


  char _receiveBuffer[4000];
  int _receiveCount;

  char _InBuffer[1024];
 // char _OutBuffer[1024];
  OVERLAPPED _ReadOverlapped;
  DWORD _BytesRead;
  DWORD _ErrorCode;
  OVERLAPPED _WriteOverlapped;
  DWORD _BytesWrite;

  int _baudRate;
  int _byteSize;
  int _parity;
  int _stopBits;


  TTimer *_receiveTimer;

 public :
 __fastcall TtyClient(TComponent *AOwner);
 virtual __fastcall ~TtyClient();


 int  InterfaceSet(char **argv,int arc);
 AnsiString InterfaceName();
 AnsiString _portName;
 
 virtual int Connect();
 virtual int Disconnect();

 bool __fastcall  Open();
 void  __fastcall Close();
 
 int SendToPort(char *buffer,int count);
 int ReceiveFromPort(char *buffer,int count);
 int Send(char *buffer,int count);
 int Receive(char *buffer,int count);

 void __fastcall ReceiveTimer(TObject *Sender);

 void SetPortOption();
 void SetPortTimeout();

// int Read(char *buffer,int count);
 //int Write(char *buffer,int count);
};








//---------------------------------------------------------------------------
#endif
