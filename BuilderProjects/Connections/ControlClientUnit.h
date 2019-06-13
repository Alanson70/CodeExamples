//---------------------------------------------------------------------------

#ifndef ControlClientUnitH
#define ControlClientUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>

   

#include "Client.h"

class TOutputClient;
//---------------------------------------------------------------------------
class TControlClient : public TClient
{
__published:	// IDE-managed Components
private:	// User declarations
 AnsiString _interfaceString;
protected:
  int _receiveBufferCount;
  char _receiveBuffer[4096];
  int _connectStatus; // 0 - no, 1 - set on, established

public:		// User declarations
 __fastcall TControlClient(TComponent* Owner);
 __fastcall ~TControlClient();
 void InterfaceSet(AnsiString name);
 AnsiString InterfaceName();


 virtual int  DoConnect();
 virtual void DoConnecting();
 virtual void DoReadReady();
 virtual void DoCanWrite();
 virtual void DoConnected();
 virtual void DoDisconnected();
 virtual void DoError(int errorCode); // after disconnecting
 virtual int DoDisconnect();

 int ConnectStatus() { return _connectStatus; }
 void ConnectStatus(int connectStatus) { _connectStatus=connectStatus; }

 // read-write
public:
// int Read(char **s);
 int Read(char *buffer,int count);
 int Write(char *buffer,int count);
 //int Write(AnsiString s);

protected:
 int Send(char *buffer,int count);
 int Receive(char *buffer,int count);

 /////
 
protected:
  TOutputClient *_client;
public:  
 void  __fastcall OnClientConnect(TObject *Sender);
 void  __fastcall OnClientError(TObject *Sender);
 void  __fastcall OnClientDisconnect(TObject *Sender);
 void  __fastcall OnClientCanWrite(TObject *Sender);
 void  __fastcall OnClientReadReady(TObject *Sender);


// statistics
public:
  ASS _sendAddition;
  ASS _rcvAddition;
  ASS _sendPrefix;
  ASS _rcvPrefix;

};
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#endif
