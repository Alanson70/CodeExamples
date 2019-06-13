//---------------------------------------------------------------------------

#ifndef NodeConnectorUnitH
#define NodeConnectorUnitH


#include "LinksConnectorUnit.h"


#define PROXY

#ifdef PROXY
#include "ProxyConnectorUnit.h"
#endif

//---------------------------------------------------------------------------
#ifdef PROXY
class TNodeConnector : public TProxyConnector
#else 
class TNodeConnector : public TLinksConnector
#endif
{
private:	// User declarations
protected:
public:		// User declarations
 __fastcall TNodeConnector(TComponent* Owner);
 __fastcall ~TNodeConnector();


protected:
 AnsiString _userName;
 int _userAccessRights;
public:
 int UserAccessRights() { return _userAccessRights; }
 AnsiString UserName() { return _userName; }
                    
 bool AccessFor(int purpose);
 bool AccessForRunning();
 bool AccessForCommonMonitor();
 bool AccessForSimpleControl();
 bool AccessForCommonLocalControl();
 bool AccessForCommonRemoteControl();
 bool AccessForFullLocalControl();
 bool AccessForFullRemoteControl();
 bool AccessForManagement();
 bool AccessForHiddenOptions();
 bool AccessForConfiguring();

};


#define usertypeDEVELOPER      0
#define usertypeADMINISTRATOR  1
#define usertypeENGINEER       2
#define usertypeMANAGER        3
#define usertypeOPERATOR       4
#define usertypeGUEST          5


#define purposeRunning 1
#define purposeCommonMonitor 2
#define purposeSimpleControl 3
#define purposeCommonLocalControl 4
#define purposeCommonRemoteControl 5
#define purposeFullLocalControl 6
#define purposeFullRemoteControl 7
#define purposeManagement 8
#define purposeHiddenOptions 9
#define purposeConfiguring 10

#endif
