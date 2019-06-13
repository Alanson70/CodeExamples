//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ClientFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TClientForm *ClientForm;
//---------------------------------------------------------------------------
__fastcall TClientForm::TClientForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TClientForm::FormShow(TObject *Sender)
{
    ClientSocket1->Active = true;

    
}
//---------------------------------------------------------------------------
void __fastcall TClientForm::ClientSocket1Connect(TObject *Sender,
      TCustomWinSocket *Socket)
{
    SendButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TClientForm::ClientSocket1Disconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{  
    SendButton->Enabled = false;

}
//---------------------------------------------------------------------------
void __fastcall TClientForm::SendButtonClick(TObject *Sender)
{
     ClientSocket1->Socket->SendText(SendEdit->Text);
}
//---------------------------------------------------------------------------
void __fastcall TClientForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
     ClientSocket1->Active = false;

     this->Release();
}
//---------------------------------------------------------------------------
