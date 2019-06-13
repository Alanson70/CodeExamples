//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LinksConnectorUnit.h"
#include <DateUtils.hpp>




//---------------------------------------------------------------------------
#pragma package(smart_init)



//TConnector *_firstConnector=NULL;
/*
TConnector *CreateConnector()
{
 if(_firstConnector==NULL)
  _firstConnector=new TLinksConnector(Application->MainForm);
 return _firstConnector;
}
*/
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TLinksConnector::TLinksConnector(TComponent* Owner)  : TConnector(Owner)
{
 //_Links=new TLink(this);
}
//--------------------------------------------------------------------------
__fastcall TLinksConnector::~TLinksConnector()
{
 TLink *link=_Links;

 for(;;)
 {
  if(link==NULL) break;
  //link->Remove();// LinkOff();
  //link=link->NextLink();
  LinkRemove(link);
 }
} 
//---------------------------------------------------------------------
/*
void TLinksConnector::InsertLinks(TLink *link)
{
 _Links=link;
 if(this->Connected()==true)
  LinksDoConnected();

 //return TConnector::DoConnect();
}
*/
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//---------------------------------------------------------------------
int TLinksConnector::DoConnect()
{
 return TConnector::DoConnect();
}
//---------------------------------------------------------------------
void TLinksConnector::DoConnecting()
{
 TConnector::DoConnecting();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TLinksConnector::DoCanWrite()
{
 TConnector::DoCanWrite();
 LinksDoCanWrite();
}

//---------------------------------------------------------------------------
void TLinksConnector::DoConnected()
{
 //_pingTime=0;
 //PingTimer->Enabled=true;

 TConnector::DoConnected();
 LinksDoConnected();
}

//---------------------------------------------------------------------------
void TLinksConnector::DoDisconnected()
{                     
// PingTimer->Enabled=false;

 TConnector::DoDisconnected();
 LinksDoDisconnected();
}

//---------------------------------------------------------------------------

void TLinksConnector::DoError(int errorCode)
{
 TConnector::DoError(errorCode);
 LinksDoError(errorCode);
}


//---------------------------------------------------------------------------
void TLinksConnector::DoReadReady()
{

/*
 IF(_receiveBuffer,"@Ping",5)
 {
  TDateTime t=Time();
  _pingTime=MilliSecondsBetween(t,_pingStart);
 }
 else     */
 IF(_receiveBuffer,"@n",2)
 {
  // pass it to client
  LinksDoReadReady();
 }
 else      
 TConnector::DoReadReady();
}
////////////////////////////////////////////////



//---------------------------------------------------------------------------
                                                         /*
 //---------------------------------------------------------------------------
int TLinksConnector::Write(char *buffer,int count)
{

 return TConnector::Write(buffer,count);
}

//---------------------------------------------------------------------------
int TLinksConnector::Write(ASS s)
{
 return TClient::Write(s);
}
*/

//---------------------------------------------------------------------------

/// Links ////////////


void TLinksConnector::LinkRemove(TLink *l)
{
 TLink *link,*before=NULL;

 link=_Links;

 for(;;)
 {
  if(link==NULL)            break;
  if(link==l)
  {
   if(before) before->_nextLink=link->_nextLink;
   else _Links=link->_nextLink;
   break;
  }
  before=link;
  link=link->_nextLink;
 }
// l->LinkOff();//=NULL;

 l->_nextLink=NULL;
 l->_Server=NULL;
}
//---------------------------------------------------------------------------

void TLinksConnector::LinkAdd(TLink *link)
{
 if(_Links==NULL) _Links=link;
 else
 {
  link->_nextLink=_Links->_nextLink;
  _Links->_nextLink=link;
 }
 link->_Server=this;
 //if(_connected==true)   link->DoConnected();
/*
 link->LinkTo(this);
 TLink *next=_Links;
 if(next==NULL) _Links=link;
 else
 for(;;)
 {
  if(next==next->NextLink())
  {
   next->NextLink(NULL);
  }
  if(next->NextLink()==NULL)
  {
   next->NextLink(link);
   break;
  }
  next=next->NextLink();
 }
 */
}

//---------------------------------------------------------------------------

void TLinksConnector::LinksDoConnected()
{

 TLink *link=_Links;
 for(;;)
 {
  if(link) link->DoConnected();// >LinkTo(this);// >DoConnected();
  else break;
  link=link->NextLink();
 }
}
//---------------------------------------------------------------------------

void TLinksConnector::LinksDoDisconnected()
{
 if(_Links)
 {
  TLink *link=_Links;

  for(;;)
  {
   if(link) link->DoDisconnected();//DoError(errorCode);
   else break;
   link=link->NextLink();
  }
 }
} 
//---------------------------------------------------------------------------

void TLinksConnector::LinksDoReadReady()
{
 TLink *link=_Links;
 unsigned long number=0;

 number=atol(_receiveBuffer+2);
 // remove @nXXXX
 for(int i=0;i<_receiveBufferCount;i++)
  if(_receiveBuffer[i]==' ')
  {
   _receiveBufferCount=Memcpy(_receiveBuffer,_receiveBuffer+i+1,_receiveBufferCount-(i+1));
   _receiveBuffer[_receiveBufferCount]=0;
   break;
  }

 for(;;)
 {
  if(!link) break;

  if(number==link->Number())
  {
   _receiveBuffer[_receiveBufferCount]=0;

   link->DoReadReady();
   return;
  }
  link=link->NextLink();
 }
}   
//---------------------------------------------------------------------------

void TLinksConnector::LinksDoCanWrite()
{
 if(_Links)
 {
  TLink *link=_Links;

  for(;;)
  {
   if(link) link->DoCanWrite();
   else break;
   link=link->NextLink();
  }
 }
}  
//---------------------------------------------------------------------------

void TLinksConnector::LinksDoError(int error)
{
 if(_Links)
 {
  TLink *link=_Links;

  for(;;)
  {
   if(link) link->DoError(error);
   else break;
   link=link->NextLink();
  }
 }
}  
//---------------------------------------------------------------------------



////////////////////
