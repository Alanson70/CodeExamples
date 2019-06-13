/**************************************************************************/
/************************* ЗАО "РОСсвязьсистема" **************************/
/************************  Шапошников А.А. ********************************/
/************************* 2006-2012 **************************************/
/**************************************************************************/
//---------------------------------------------------------------------------


#pragma hdrstop

#include "Functions.h"
#include "Client.h"
//#include "ConnectFormUnit.h"



#pragma package(smart_init)

__fastcall TClient::TClient(TComponent *AOwner) : TComponent(AOwner)
{
 OnReadReady=NULL;
 OnCanWrite=NULL;
 OnConnected=NULL; 
 OnDisconnected=NULL;
 OnError=NULL;
 _connected=false;

 _error=0;
}

//---------------------------------------------------------------------------
void TClient::DoReadReady()
{
 if(OnReadReady) OnReadReady(this);
}
//---------------------------------------------------------------------------
void TClient::DoCanWrite()
{
 _error=false;
 if(OnCanWrite) OnCanWrite(this);
}
//---------------------------------------------------------------
int TClient::DoConnect()
{
 DoConnecting();
 //if(OnConnecting) OnConnecting(this);
 return 1;
}      
//---------------------------------------------------------------
void TClient::DoConnecting()
{
 if(OnConnecting) OnConnecting(this);
}
//---------------------------------------------------------------------------
void TClient::DoConnected()
{
 _error=false;
 if(_connected==false)
 {
  _connected=true;
  if(OnConnected) OnConnected(this);
  else
  if(OnCanWrite)  OnCanWrite(this);
 }
 else  // if connection was not destroyed
 {
  if(OnCanWrite)  // Be sure it's rigth : if OnConnected only can OnCanWrite
   OnCanWrite(this);
 }
}

//---------------------------------------------------------------------------
int TClient::DoDisconnect()
{
 DoDisconnected();
 return 1;
}
//---------------------------------------------------------------------------
void TClient::DoDisconnected()
{
 _connected=false;
 _error=1;
 if(OnDisconnected) OnDisconnected(this);
}
//---------------------------------------------------------------------------

void TClient::DoError(int errorCode)
{
 _error=1;
 if(OnError) OnError(this);
}

//---------------------------------------------------------------------------
int TClient::Read(char **s)
{
 char buffer[2001];
 int count=0;

 count=Read(buffer,2000);
 char *argv[50];
 int argc=0;

 argc=SplitCommand(buffer,count,argv,50);
 s=argv;
 return argc;
}
//---------------------------------------------------------------------------
int TClient::Read(char *buffer,int count)
{
 
 return 0;
}
//---------------------------------------------------------------------------
int TClient::Write(char *buffer,int count)
{
 
 return 0;
}
//---------------------------------------------------------------------------

int TClient::WriteString(AnsiString com)
{
 return Write(com.c_str(),com.Length());
} 
//---------------------------------------------------------------------------




