//---------------------------------------------------------------------------

#ifndef LinkUnitH
#define LinkUnitH

 
#include <Classes.hpp>	// Pascal unit  
#include <ExtCtrls.hpp>
#include <time.h>


#include "Client.h"
typedef void __fastcall (__closure *Callback)(TObject *Sender);


class TConnector;
class TLinksConnector;

class TLink :  public TClient
{
 private :
  int Receive(char *buffer,int count);
  int Send(char *buffer,int count);
 protected :
  TLink *_nextLink;
  AnsiString _path;
  TLinksConnector* _Server;
  bool _connected;
  static unsigned long _n;
  unsigned long _number;

 public :
  __fastcall virtual TLink(TComponent *AOwner);
  __fastcall virtual ~TLink();
  friend class TLinksConnector;

  TLink *NextLink();
  void NextLink(TLink *link);

  unsigned long Number() { return _number; }
  TConnector *Server() { return (TConnector *)_Server; }
  AnsiString Path() { return _path; }
  AnsiString InterfaceName();


  // processing
  int Read(char *buffer,int count);
  int Write(char *buffer,int count);
  //int DoDisconnect();
  void LinkTo(TConnector *server,ASS path="");
};

           
//---------------------------------------------------------------------------
#endif
