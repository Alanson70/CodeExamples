//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AUdb1.h"
#include "AUUnit2.h"
#include "ReportUnit.h"
#include "QR2Unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TUADBForm *UADBForm;
//---------------------------------------------------------------------------
__fastcall TUADBForm::TUADBForm(TComponent* Owner)
    : TForm(Owner)
{
 //if(DBGrid1->Align==alNone) return;
 //if(DBGrid1->ReadOnly==true) return;
 //if(DBGrid1->BorderStyle==bsSingle) return;
}
//---------------------------------------------------------------------------


#include "UgolAzimut.h"

void __fastcall TUADBForm::AddItemClick(TObject *Sender)
{
 UAForm->PosFlag=0;
 UAForm->ShowModal();
 FormChange();
}
//---------------------------------------------------------------------------

void __fastcall TUADBForm::ChangeItemClick(TObject *Sender)
{
 UAForm->PosFlag=1;
 UAForm->ShowModal();
 FormChange();
}
//---------------------------------------------------------------------------
void __fastcall TUADBForm::DeleteItemClick(TObject *Sender)
{
 UAForm->PosFlag=2;
 UAForm->ShowModal();
 FormChange();
}
//---------------------------------------------------------------------------

void __fastcall TUADBForm::FormChange()
{
 UADBForm->Height=
  min(48+18*16,48+(18*AUDataModule1->AUTable->RecordCount));
}
//---------------------------------------------------------------------------

void __fastcall TUADBForm::FormShow(TObject *Sender)
{
 FormChange();
}
//---------------------------------------------------------------------------

void __fastcall TUADBForm::PrintItemClick(TObject *Sender)
{
 AnsiString N;

 //ReportForm->QuickRep1->Preview();

 N=AUDataModule1->AUTable->FieldValues["Name"];
 //RForm2->QuickRep1->Preview();
 RForm2->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TUADBForm::CloseItemClick(TObject *Sender)
{
 Close();   
}
//---------------------------------------------------------------------------

