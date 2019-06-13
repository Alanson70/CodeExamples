//---------------------------------------------------------------------------


#pragma hdrstop

#include "OutputClient.h"








//---------------------------------------------------------------------------

__fastcall TOutputClient::TOutputClient(TComponent *AOwner) : TClient(AOwner)
{
 _testCheckSum=false;
 _receiveBufferCount=0;
 //_isConnect=false; 
 sprintf(_sendAddition,"\n");
 sprintf(_recvAddition,"\n");
}
//---------------------------------------------------------------------------
int TOutputClient::InterfaceSet(AnsiString param)
{
// AnsiString path=param+="";
 char buffer[100];
// AnsiString path;
 char *argv[10];
 int argc=10;

 Strncpy(buffer,param.c_str(),99);

 argc=SplitCommand(buffer,argv,10);
 return InterfaceSet(argv,argc);
}
//---------------------------------------------------------------------------
void TOutputClient::DoReadReady()
{
 char buffer[OC_MAX_COUNT];
 int count=Receive(buffer,(sizeof(buffer)-1));
 int addCount=Strlen(_recvAddition);

 if(count<1) return;

 int first=0;

 for(int i=0;i<(1+count-addCount);i++)
 {
  if(_receiveBufferCount==-1) ///???????????
  {
   IF(buffer+i,_recvAddition,addCount)
   //if(buffer[i]=='\n')
   {
    _receiveBufferCount=0;
    first=i+1;
   }
  }
  else
  {
   if((i+1)>=(sizeof(_receiveBuffer)-_receiveBufferCount)) ///???
   {
    _receiveBufferCount=-1; // too much bytes
   }
   else
   {
    IF(buffer+i,_recvAddition,addCount)
    //if(buffer[i]=='\n')
    {
     _receiveBufferCount+=Memcpy(_receiveBuffer+_receiveBufferCount,buffer+first,((i-first)+1));

     _receiveBufferCount-=addCount;
     _receiveBuffer[_receiveBufferCount]=0;

     if(OnReadReady) OnReadReady(this);

     _receiveBufferCount=0;
     first=i+addCount;
    }
   }
  }
 }
 _receiveBufferCount+=Memcpy(_receiveBuffer+_receiveBufferCount,buffer+first,count-first);
}



//---------------------------------------------------------------------------
int TOutputClient::Read(char *buffer, int count)
{
 if(count<_receiveBufferCount)
  _receiveBufferCount=0;
 count=Memcpy(buffer,_receiveBuffer,_receiveBufferCount);
 _receiveBufferCount=0;
 return count;
}
//---------------------------------------------------------------------------
int TOutputClient::Write(char *buffer,int count)
{
 if(count>(OC_MAX_COUNT-25)) return 0;
 int addCount=Strlen(_sendAddition);
 IF(buffer+count-addCount,_sendAddition,addCount);
 else strncat(buffer,_sendAddition,addCount);
 return Send(buffer,count);
}



//---------------------------------------------------------------------------
void TOutputClient::TestCheckSum(bool test)
{
 _testCheckSum=test;
}
//---------------------------------------------------------------------------
bool TOutputClient::TestCheckSum()
{
 return _testCheckSum;
}



#pragma package(smart_init)
