//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ServerFormUnit.h"
#include "ClientFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TServerForm *ServerForm;
//---------------------------------------------------------------------------
__fastcall TServerForm::TServerForm(TComponent* Owner)
    : TForm(Owner)
{
    pSocket = NULL;

    ServerSocket1->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::ServerSocket1ClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
    AnsiString s=AnsiString(GetCurrentThreadId())+AnsiString(" : ")+AnsiString(Socket->ReceiveText());
    Memo1->Lines->Add(s);
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::ClientButtonClick(TObject *Sender)
{
   TClientForm *form = new TClientForm(this);

   //form->Name = AnsiString((long)form);

   form->Show();
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::ServerSocket1ClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
     
    AnsiString s=AnsiString(GetCurrentThreadId())+AnsiString(" : connected to ")+AnsiString(Socket->RemotePort);

    Memo1->Lines->Add(s);
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::ServerSocket1ClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
    AnsiString s=AnsiString(GetCurrentThreadId())+AnsiString(" : disconnected with ")+AnsiString(Socket->RemotePort);

    Memo1->Lines->Add(s);
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::ServerSocket1ClientError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
    AnsiString s=AnsiString(GetCurrentThreadId())+AnsiString(" : error of ")+AnsiString(Socket->RemotePort);

    Memo1->Lines->Add(s);
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::ServerSocket1ThreadStart(TObject *Sender,
      TServerClientThread *Thread)
{
    AnsiString s=AnsiString(GetCurrentThreadId())+AnsiString(" : thread start  ")+Thread->ThreadID;// Socket->RemotePort;

    Memo1->Lines->Add(s);
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::ServerSocket1GetSocket(TObject *Sender,
      int Socket, TServerClientWinSocket *&ClientSocket)
{
    AnsiString s=AnsiString(GetCurrentThreadId())+AnsiString(" : get socket ");//+AnsiString(ClientSocket->RemotePort);

    Memo1->Lines->Add(s);
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::ServerSocket1Listen(TObject *Sender,
      TCustomWinSocket *Socket)
{
    //AnsiString s=AnsiString(GetCurrentThreadId())+AnsiString(" : listen ")+AnsiString(Socket->RemotePort);

   // Memo1->Lines->Add(s);

    AnsiString s=AnsiString(GetCurrentThreadId())+AnsiString(" : listen ")+AnsiString(Socket->LocalPort);

    Memo1->Lines->Add(s);
}
//---------------------------------------------------------------------------
void __fastcall TServerForm::ServerSocket1Accept(TObject *Sender,
      TCustomWinSocket *Socket)
{
    AnsiString s=AnsiString(GetCurrentThreadId())+AnsiString(" : accepted to ")+AnsiString(Socket->RemotePort);

    Memo1->Lines->Add(s);

    Socket->ReceiveText();

    
    Memo1->Lines->Add(s);

    
}
//---------------------------------------------------------------------------
