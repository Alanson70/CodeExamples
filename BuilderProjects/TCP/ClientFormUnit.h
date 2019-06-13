//---------------------------------------------------------------------------

#ifndef ClientFormUnitH
#define ClientFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ScktComp.hpp>
//---------------------------------------------------------------------------
class TClientForm : public TForm
{
__published:	// IDE-managed Components
    TClientSocket *ClientSocket1;
    TEdit *SendEdit;
    TButton *SendButton;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ClientSocket1Connect(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ClientSocket1Disconnect(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall SendButtonClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
    __fastcall TClientForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TClientForm *ClientForm;
//---------------------------------------------------------------------------
#endif
