//---------------------------------------------------------------------------

#ifndef LinksConnectorUnitH
#define LinksConnectorUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>

   

#include "ConnectorUnit.h"
#include "LinkUnit.h"

class TLink;
//---------------------------------------------------------------------------
class TLinksConnector : public TConnector
{
__published:	// IDE-managed Components
private:	// User declarations


protected:
public:		// User declarations
 __fastcall TLinksConnector(TComponent* Owner);
 __fastcall ~TLinksConnector();

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
protected:


public:  
 // links
 TLink *_Links;
 void InsertLinks(TLink *link);
 void LinkRemove(TLink *link);
 void LinkAdd(TLink *link);
 void LinksDoConnected();
 void LinksDoDisconnected();
 void LinksDoReadReady();
 void LinksDoCanWrite();
 void LinksDoError(int error);

 /////////////////
 
 //int Write(char *buffer,int count);
// int Write(AnsiString s);

// statistics
public:

// TDateTime _pingStart;
// unsigned long _pingTime;

};
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#endif
