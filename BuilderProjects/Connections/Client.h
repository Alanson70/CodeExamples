/**************************************************************************/
/************************* ЗАО "РОСсвязьсистема" **************************/
/************************  Шапошников А.А. ********************************/
/************************* 2006-2012 **************************************/
/**************************************************************************/
//---------------------------------------------------------------------------

#ifndef ClientH
#define ClientH

 
#include <Classes.hpp>	// Pascal unit  
#include <ExtCtrls.hpp>
#include <time.h>
#include "Functions.h"
#define OC_MAX_COUNT 8200// 4096

//typedef void __fastcall (__closure *Callback)(TObject *Sender);


class TClient : public TComponent
{
 protected :
  bool _connected;
  int _error;


 public :
  __fastcall TClient(TComponent *AOwner);
  // processing
  virtual int DoConnect();
  virtual void DoConnecting();
  virtual void DoConnected();
  virtual void DoReadReady();
  virtual void DoCanWrite();  
  virtual int  DoDisconnect();// { return 0; }
  virtual void DoDisconnected();
  virtual void DoError(int errorCode); // after disconnecting

  virtual int Read(char *buffer,int count);
  int Read(char **s);
  virtual int Write(char *buffer,int count);
  virtual int WriteString(ASS com);

  //virtual int Connect()    { return 0; }
  //virtual int Disconnect() { return 0; }
  int Error() { return _error; }
  bool Connected() { return _connected; }

  virtual AnsiString InterfaceName()=0;
                     
  Callback OnConnecting;
  Callback OnConnected;
  Callback OnDisconnected;
  Callback OnReadReady;
  Callback OnCanWrite;
  Callback OnError;

  virtual int Send(char *buffer,int count)    { return 0; }
  virtual int Receive(char *buffer,int count) { return 0; }

};

//---------------------------------------------------------------------------
#endif
