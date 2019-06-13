//---------------------------------------------------------------------------

#ifndef UdpClientH
#define UdpClientH


 
#include "OutputClient.h"


#include <ScktComp.hpp>
#include <ExtCtrls.hpp>
#include <Sockets.hpp> 
//#include <NMUDP.hpp>

class UdpClient : public TOutputClient
{
 protected :
  int _sockfd;       
  AnsiString _ipAddr;
  int _ipPort;
 TTimer *Timer;
 
 int Receive(char *buffer,int count);
 int Send(char *buffer,int count);
 public :
 __fastcall UdpClient(TComponent *AOwner);
  int  InterfaceSet(char **argv,int arc);
  AnsiString InterfaceName();
  virtual int Connect();
  virtual int Disconnect();

 void __fastcall ErrorFunc(TObject *Sender,int ErrorCode);
 void __fastcall DisconnectFunc(TObject *Sender);
 void __fastcall CanWriteFunc(TObject *Sender);
 void __fastcall ReadReadyFunc(TObject *Sender,PChar Buf,int &DataLen);
 void __fastcall TimerReadReadyFunc(TObject *Sender);


};

//---------------------------------------------------------------------------
#endif
