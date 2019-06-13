//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "d1.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TtosputnikForm *tosputnikForm;
//---------------------------------------------------------------------------
__fastcall TtosputnikForm::TtosputnikForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TtosputnikForm::Edit1Change(TObject *Sender)
{
 A=Edit1->Text.ToDouble()+(Edit5->Text.ToDouble()/60.0);
 B=Edit2->Text.ToDouble()+(Edit6->Text.ToDouble()/60.0);
 G=Edit3->Text.ToDouble()+(Edit7->Text.ToDouble()/60.0);
 d=42644.0 * sqrt (1.0-0.2954*cos((A*2*M_PI)/360)*cos(2*M_PI*fabs(B-G)/360));
 Edit4->Text=d;
}
//---------------------------------------------------------------------------
void __fastcall TtosputnikForm::BitBtn1Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TtosputnikForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
// delete tosputnikForm;
 //tosputnikForm=NULL;
}
//---------------------------------------------------------------------------

