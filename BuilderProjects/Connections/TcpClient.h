//---------------------------------------------------------------------------

#ifndef TcpClientH
#define TcpClientH


#include "OutputClient.h"

#include <ScktComp.hpp>

class TcpClient : public TOutputClient
{
 protected :
  TClientSocket *Socket;       
  AnsiString _ipAddr;
  int _ipPort;

  int Receive(char *buffer,int count);
  int Send(char *buffer,int count);
 public :
  __fastcall TcpClient(TComponent *AOwner);
  __fastcall ~TcpClient();
  int  InterfaceSet(char **argv,int arc);
  AnsiString InterfaceName();
  virtual int DoConnect();
  virtual int DoDisconnect();

  void __fastcall ErrorFunc(TObject *Sender,TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode);
  void __fastcall CanWriteFunc(TObject *Sender,TCustomWinSocket *Socket);
  void __fastcall ReadReadyFunc(TObject *Sender,TCustomWinSocket *Socket);
  void __fastcall OnConnectedFunc(TObject *Sender,TCustomWinSocket *Socket);
  void __fastcall OnDisconnectedFunc(TObject *Sender,TCustomWinSocket *Socket);

};


//---------------------------------------------------------------------------
#endif
