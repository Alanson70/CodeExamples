//---------------------------------------------------------------------------

#ifndef ConnectorUnitH
#define ConnectorUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>


#define connectNO  0
#define connectTRY 1
#define connectIS  2   

#include "Client.h"

class TOutputClient;
class TConnectorForm;
//---------------------------------------------------------------------------
class TConnector : public TClient
{
__published:	// IDE-managed Components
private:	// User declarations
 AnsiString _interfaceString;
protected:
  //TOutputClient *_client;
  int _receiveBufferCount;
  char _receiveBuffer[OC_MAX_COUNT];
  bool _isReceived;
  int _connectStatus; // 0 - no, 1 - set on, established
  bool _reconnecting;

  bool _reconnectAuto;
  int _reconnectTime;
  TTimer *_reconnectTimer;

 // int _disconnectTime;
  bool _disconnectAuto;
  TTimer *_disconnectTimer;
  int _disconnectTime;

  bool _connectingConfirmation;
  int _connectingTime;
  TTimer *_connectingTimer;

  //int _connectingInterval;
public:		// User declarations
 __fastcall TConnector(TComponent* Owner);
 __fastcall ~TConnector();
 friend TConnectorForm;

 void InterfaceSet(AnsiString name);
 AnsiString InterfaceName();

 void Reconnect();

 virtual int  DoConnect();
 virtual void DoConnecting();
 virtual void DoReadReady();
 virtual void DoCanWrite();
 virtual void DoConnected();
 virtual void DoDisconnected();
 virtual void DoError(int errorCode); // after disconnecting
 virtual int DoDisconnect();
 void __fastcall ReconnectTimerFunc(TObject *); 
 void __fastcall ConnectingTimerFunc(TObject *);
 void __fastcall DisconnectTimerFunc(TObject *);

 int ConnectStatus() { return _connectStatus; }
 // read-write
public:
// int Read(char **s);
 virtual int Read(char *buffer,int count);
 virtual int Write(char *buffer,int count);

protected:

 int Send(char *buffer,int count);
 int Receive(char *buffer,int count);

 /////
 
protected:
  TOutputClient *_client;
public:  
 void  __fastcall OnClientConnected(TObject *Sender);
 void  __fastcall OnClientError(TObject *Sender);
 void  __fastcall OnClientDisconnected(TObject *Sender);
 void  __fastcall OnClientCanWrite(TObject *Sender);
 void  __fastcall OnClientReadReady(TObject *Sender);


// statistics
public:
 TDateTime _connectTime;
 unsigned long _sendedPackets;
 unsigned long _receivedPackets;
 unsigned long long _sendedBytes;
 unsigned long long _receivedBytes;

 // access
                 /*
 virtual bool AccessForRunning();
 virtual bool AccessForCommonMonitor();
 virtual bool AccessForSimpleControl();
 virtual bool AccessForCommonLocalControl();
 virtual bool AccessForCommonRemoteControl();
 virtual bool AccessForFullLocalControl();
 virtual bool AccessForFullRemoteControl();
 virtual bool AccessForManagement();
 virtual bool AccessForHiddenOptions();
 virtual bool AccessForConfiguring();
                               */
 virtual bool AccessFor(int purpose);

};


TConnector *FirstConnector();
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#endif
