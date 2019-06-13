//---------------------------------------------------------------------------

#ifndef ServerFormUnitH
#define ServerFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ScktComp.hpp>
//---------------------------------------------------------------------------
class TServerForm : public TForm
{
__published:	// IDE-managed Components
    TServerSocket *ServerSocket1;
    TMemo *Memo1;
    TButton *ClientButton;
    void __fastcall ServerSocket1ClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ClientButtonClick(TObject *Sender);
    void __fastcall ServerSocket1ClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ServerSocket1ClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ServerSocket1ClientError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
    void __fastcall ServerSocket1ThreadStart(TObject *Sender,
          TServerClientThread *Thread);
    void __fastcall ServerSocket1GetSocket(TObject *Sender, int Socket,
          TServerClientWinSocket *&ClientSocket);
    void __fastcall ServerSocket1Listen(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ServerSocket1Accept(TObject *Sender,
          TCustomWinSocket *Socket);
private:	// User declarations
public:		// User declarations
    __fastcall TServerForm(TComponent* Owner);

    TCustomWinSocket *pSocket;
};
//---------------------------------------------------------------------------
extern PACKAGE TServerForm *ServerForm;
//---------------------------------------------------------------------------
#endif
