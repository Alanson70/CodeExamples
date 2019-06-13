//---------------------------------------------------------------------------


#pragma hdrstop

#include "LinkUnit.h"
#include "Functions.h"
#include "LinksConnectorUnit.h"



unsigned long TLink::_n=1;

__fastcall TLink::TLink(TComponent *AOwner) : TClient(AOwner)
{
 _Server=NULL;
 _nextLink=NULL;
 _n++;
 _number=_n;
 _path="";
 _connected=false;
}

//---------------------------------------------------------------------------
__fastcall TLink::~TLink()
{
 if(_Server)  ((TLinksConnector *)_Server)->LinkRemove(this);
}

//---------------------------------------------------------------------------
TLink *TLink::NextLink()
{
 return _nextLink;
}
//---------------------------------------------------------------------------
void TLink::NextLink(TLink *link)
{
 _nextLink=link;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
AnsiString TLink::InterfaceName()
{
 return _Server->InterfaceName();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TLink::LinkTo(TConnector *server,ASS path)
{
 if(server==NULL)    return;
 if(server==_Server) return;
 this->_path=path;

 if(_Server) _Server->LinkRemove(this);

 _Server=(TLinksConnector *)server;

 if(_Server) _Server->LinkAdd(this);

 if(_Server->Connected()==true)
  this->DoConnected();
}
//---------------------------------------------------------------------------
/*
int TLink::DoDisconnect()
{
 _connected=false;
 DoDisconnected();
 return 1;
}
*/


//---------------------------------------------------------------------------
int TLink::Send(char *buffer,int count)
{
 if(_Server)  return _Server->Write(buffer,count);
 return 0;
}
//---------------------------------------------------------------------------
int TLink::Receive(char *buffer,int count)
{
 if(_Server)  return _Server->Read(buffer,count);
 return 0;
}
//---------------------------------------------------------------------------
int TLink::Read(char *buffer,int count)
{
 if(_Server)
 {
  count=Receive(buffer,count);

  if(_path.Length()>0)
  {
   // removing path information from buffer
   char path[100];
   strncpy(path,_path.c_str(),99);
   char *pathStruct[25];
   int pathCount=SplitCommand(path,pathStruct,24);
   int first=0;

   for(int c=0;c<pathCount;c++)
   {
    if(pathStruct[c]==NULL) break;
    if(!strnicmp(buffer+first,pathStruct[c],strlen(pathStruct[c])))
    {
     // remind this part of path
     for(int i=first;i<(count+1);i++)
     {
      if((buffer[i]==' ')||(buffer[i]==0))
      {
       first=i+1;
       break;
      }
     }
    }
   }
   count=Memcpy(buffer,buffer+first,count-first);
  }
  buffer[count]=0;
  return count;
 }
 return 0;
}

#include <stdio.h>

//---------------------------------------------------------------------------
int TLink::Write(char *buffer,int count)
{
 if(_Server==NULL) return 0;

 char buff[4096];
 if(count>=(4000-(_path.Length()))) return 0;
             
 sprintf(buff,"@n%d ",_number);

 if(_path.Length()>0) sprintf(buff+strlen(buff),"%s ",_path.c_str());

 int c=strlen(buff);

 Memcpy(buff+strlen(buff),buffer,count);
 count+=c;

 if(buff[count-1]!='\n')
 {
  buff[count]='\n';
  buff[count+1]=0;
  count++;
 }
 return Send(buff,count);//_Server->Write(buff,count);
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
