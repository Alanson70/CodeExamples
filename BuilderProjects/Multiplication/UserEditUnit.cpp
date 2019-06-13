//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UserEditUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TUserEditForm *UserEditForm;
//---------------------------------------------------------------------------
__fastcall TUserEditForm::TUserEditForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TUserEditForm::UserEditChange(TObject *Sender)
{
     if(UserEdit->Text.Length()>0)
        EditButton->Enabled=true;
     else
        EditButton->Enabled=false;
}
//---------------------------------------------------------------------------
