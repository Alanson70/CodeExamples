//---------------------------------------------------------------------------

#ifndef OutputClientH
#define OutputClientH

          
#include "Functions.h"
#include <Classes.hpp>	// Pascal unit
#include "Client.h"





class TOutputClient;



class TOutputClient : public TClient
{
 protected :

  bool _testCheckSum;
  
  char _sendAddition[25];
  char _recvAddition[25];

  int _receiveBufferCount;
  char _receiveBuffer[OC_MAX_COUNT];

 public :
  __fastcall virtual TOutputClient(TComponent *AOwner);
    // settings
 int InterfaceSet(AnsiString param);
 virtual int InterfaceSet(char **argv,int argc)=0;

     // data processing
  void DoReadReady();
  int Read(char *buffer,int count);
  int Write(char *buffer,int count);
  // further processing
  virtual int Send(char *buffer,int count)=0;
  virtual int Receive(char *buffer,int count)=0;


 int CheckSumTest(char *buffer);
 void CheckSumSet(char *buffer);
 void TestCheckSum(bool test);
 bool TestCheckSum();
};

//---------------------------------------------------------------------------
#endif
