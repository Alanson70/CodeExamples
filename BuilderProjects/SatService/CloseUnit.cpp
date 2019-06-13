//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CloseUnit.h"
#include "AUGridUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCloseForm *CloseForm;
//---------------------------------------------------------------------------
__fastcall TCloseForm::TCloseForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TCloseForm::Button1Click(TObject *Sender)
{
 AUGridForm->CloseFlag=true;
 AUGridForm->ChangeFlag=true;
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TCloseForm::Button2Click(TObject *Sender)
{
 AUGridForm->CloseFlag=true;
 AUGridForm->ChangeFlag=false;
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TCloseForm::Button3Click(TObject *Sender)
{
 AUGridForm->CloseFlag=false;
 AUGridForm->ChangeFlag=true;
 Close();
}
//---------------------------------------------------------------------------

