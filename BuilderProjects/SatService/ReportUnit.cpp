//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ReportUnit.h"
#include "AUUnit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TReportForm *ReportForm;
//---------------------------------------------------------------------------
__fastcall TReportForm::TReportForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TReportForm::QuickRep1Preview(TObject *Sender)
{
 AnsiString N;

 N=AUDataModule1->AUTable->FieldValues["Name"];
}
//---------------------------------------------------------------------------

void __fastcall TReportForm::QuickRep1StartPage(TQuickRep *Sender)
{
 AnsiString N;

 N=AUDataModule1->AUTable->FieldValues["Name"];
}
//---------------------------------------------------------------------------

void __fastcall TReportForm::QuickRep1EndPage(TQuickRep *Sender)
{
 AnsiString N;

 N=AUDataModule1->AUTable->FieldValues["Name"];
}
//---------------------------------------------------------------------------

