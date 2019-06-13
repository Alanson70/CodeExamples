//---------------------------------------------------------------------------

#ifndef ProxyConnectorUnitH
#define ProxyConnectorUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>

   

#include "LinksConnectorUnit.h"

class TLink;
//---------------------------------------------------------------------------
class TProxyConnector : public TLinksConnector
{
__published:	// IDE-managed Components
private:	// User declarations
 ASS _proxyIP;

protected:
 static TProxyConnector *_firstConnector;
 TProxyConnector *_nextConnector;
public:
 TProxyConnector *NextConnector();
 void NextConnector(TProxyConnector *connector);
 TProxyConnector *BaseConnector() { return _firstConnector; }


protected:
public:		// User declarations
 __fastcall TProxyConnector(TComponent* Owner);
 __fastcall ~TProxyConnector();

protected:
public:

 // processing
  
 virtual int DoConnect();
 virtual void DoConnecting();
 virtual void DoReadReady();
 virtual void DoCanWrite();
 virtual void DoConnected();
 virtual void DoDisconnected(); 
 //virtual void DoDisconnecting();
 virtual void DoError(int errorCode); // after disconnecting


 // read-write
public:
protected:
 int Send(char *buffer,int count);
 int Receive(char *buffer,int count);

/////////////////
// Proxy
public :
 bool UseProxy() { return _useProxy; }
 void UseProxy(bool use) { _useProxy=use; }
protected :
 bool _useProxy;

 void ProxyDoConnected();
 void ProxyDoDisconnected();
 AnsiString ProxyIP();
 void ProxyDoReadReady();

 bool _byProxy;
 bool ByProxy();
 void ByProxy(bool bt);

// pingcv
 TTimer *_pingTimer;
 TDateTime _pingStart;
 unsigned long _pingTime;
 void __fastcall PingTimerFunc(TObject *);
public:


};
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#endif
