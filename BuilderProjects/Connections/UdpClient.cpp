//---------------------------------------------------------------------------


#pragma hdrstop

#include "UdpClient.h"
//#include <Socket.h>

__fastcall UdpClient::UdpClient(TComponent *AOwner) : TOutputClient(AOwner)
{

 Timer=new TTimer(this);
 Timer->Interval=20;
 Timer->OnTimer=TimerReadReadyFunc;
 Timer->Enabled=false;
 Timer->Tag=0;

 _sockfd=socket(AF_INET, SOCK_DGRAM,0);
 int err=WSAGetLastError();

 struct sockaddr str={AF_INET,htons(0),INADDR_ANY};
}


//---------------------------------------------------------------------------
int UdpClient::InterfaceSet(char **argv,int argc)
{
 if(argc<2) return 0;


 int port;
 if(argc>1) port=atol(argv[1]);
 if(port!=_ipPort) Disconnect();
 if(_ipAddr!=argv[0]) Disconnect();

 _ipAddr=argv[0];//+AnsiString(" ")+AnsiString(_ipPort);
 _ipPort=port;

 if(_ipPort==0) return 0;

 return 1;
} 
//---------------------------------------------------------------------------
AnsiString UdpClient::InterfaceName()
{
 return _ipAddr+AnsiString(" ")+AnsiString(_ipPort);
}
//-----------------------------------------------------------------
int UdpClient::Connect()
{
 Timer->Enabled=true;
 Timer->Tag=0;
 return 1;
}
//---------------------------------------------------------------------------
int UdpClient::Disconnect()
{
 Timer->Enabled=false;
 return 1;
}
//---------------------------------------------------------------------------
void __fastcall UdpClient::ErrorFunc(TObject *Sender,int ErrorCode)
{
 ErrorCode=0;
 DoError(1);
}
//---------------------------------------------------------------------------
void __fastcall UdpClient::DisconnectFunc(TObject *Sender)
{
 DoError(1);
}  
//---------------------------------------------------------------------------
void __fastcall UdpClient::TimerReadReadyFunc(TObject *Sender)
{        
 if(Timer->Tag==0)
 {
  DoCanWrite(); 
  Timer->Tag=1;
 }
 else
  DoReadReady();
}
//---------------------------------------------------------------------------
void __fastcall UdpClient::ReadReadyFunc(TObject *Sender,PChar Buf,
      int &DataLen)
{
 DoReadReady();
}
//---------------------------------------------------------------------------

void __fastcall UdpClient::CanWriteFunc(TObject *Sender)
{
 DoCanWrite();
}
//---------------------------------------------------------------------------
int UdpClient::Receive(char *buffer,int count)
{
 struct timeval tv;
 fd_set  fdsetrd;
 struct sockaddr remoteAddr;

 //if(Socket==NULL) return 0;
 if(_sockfd<0)      return 0;
 //if(_opened==0)     return 0;
 
 tv.tv_sec=0;tv.tv_usec=0;  
 FD_ZERO(&fdsetrd); FD_SET(_sockfd,&fdsetrd);

 switch(select(_sockfd+1,&fdsetrd,NULL,NULL,&tv))
 {
  case 0  :
  case -1 : break;
  default :
  if(FD_ISSET(_sockfd,&fdsetrd))
  {
   for(;;)
   {
    int addrlen=sizeof(remoteAddr);

    count=recvfrom(_sockfd,buffer,count,0,(struct sockaddr *)&remoteAddr,&addrlen);

//    if(count) printf("receive count=%d\n",count);

    if(count<0)
    {
     int err=WSAGetLastError();
     //Close();
     return 0;
    }
    return count;
   }
  }
 }

 return 0;
}
//---------------------------------------------------------------------------
int UdpClient::Send(char *buffer,int count)
{
 //if(Socket) Socket->SendBuffer(buffer,count,5);

 struct timeval tv;
 fd_set  fdsetwd;

 struct sockaddr_in remoteAddr;
 //struct in_addr ipAddr;
 memset(&remoteAddr,0,sizeof(remoteAddr));
 remoteAddr.sin_addr.S_un.S_addr=inet_addr(_ipAddr.c_str());
 remoteAddr.sin_port=htons(_ipPort);
 remoteAddr.sin_family=AF_INET;


 int addrlen=sizeof(remoteAddr);

// printf("UDP Send (%d) %s\n",count,buffer);

 if(_sockfd<0)   return 0;
 //if(_opened==0)  return 0;

 tv.tv_sec=0;tv.tv_usec=0;
 FD_ZERO(&fdsetwd);
 FD_SET(_sockfd,&fdsetwd);

 switch(select(_sockfd+1,NULL,&fdsetwd,NULL,&tv))
 {
  case -1 : perror("send udp -1");break;
  case  0 : perror("send udp 0");break;
  default :
  if(FD_ISSET(_sockfd,&fdsetwd))
  {
   if(sendto(_sockfd,buffer,count,0,(struct sockaddr *)&remoteAddr,addrlen)>0)
   {
    return count;
   }
   else perror("send udp");
  }
  else perror("send udp 1");
 }
// printf("UDP Send no...\n");

 return 0;
}
//---------------------------------------------------------------------------
/*
void __fastcall UdpClient::OnReceive(TComponent *o,int bytes,AnsiString ip, int port)
//void __fastcall UdpClient::OnReceive(TObject *o,char * Buf, int &DataLen)
{
 DoReadReady();
}
*/
//---------------------------------------------------------------------------

#pragma package(smart_init)
