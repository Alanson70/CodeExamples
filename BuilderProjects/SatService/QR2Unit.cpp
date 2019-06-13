//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "QR2Unit.h"
//#include "AUUnit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRForm2 *RForm2;
//---------------------------------------------------------------------------
__fastcall TRForm2::TRForm2(TComponent* Owner)
    : TForm(Owner)
{

}
#include "AUGridUnit.h"

//---------------------------------------------------------------------------

void __fastcall TRForm2::FormShow(TObject *Sender)
{
 int CurPos=AUGridForm->Grid1->Row;
 
 Caption=AUGridForm->Grid1->Cells[0][CurPos];
 RichEdit1->Lines->Clear();
 RichEdit1->Lines->Add("");
 RichEdit1->Lines->Add("Наименование ЗС     "+AUGridForm->Grid1->Cells[0][CurPos]);
 RichEdit1->Lines->Add("Долгота КА          "+AUGridForm->Grid1->Cells[1][CurPos]);
 RichEdit1->Lines->Add("Долгота ЗС          "+AUGridForm->Grid1->Cells[2][CurPos]);
 RichEdit1->Lines->Add("Широта ЗС           "+AUGridForm->Grid1->Cells[3][CurPos]);
 RichEdit1->Lines->Add("Азимут              "+AUGridForm->Grid1->Cells[4][CurPos]);
 RichEdit1->Lines->Add("Угол места          "+AUGridForm->Grid1->Cells[5][CurPos]);
 RichEdit1->Lines->Add("  "+AUGridForm->Grid1->Cells[6][CurPos]);
}
//---------------------------------------------------------------------------

void __fastcall TRForm2::Button2Click(TObject *Sender)
{
 if(SaveDialog1->Execute())
  RichEdit1->Lines->SaveToFile(SaveDialog1->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TRForm2::Button1Click(TObject *Sender)
{
 AnsiString FileName="001temp.prn";
 DeleteFile(FileName);
 RichEdit1->Lines->SaveToFile(FileName);
 if(PrintDialog1->Execute())
  RichEdit1->Print(FileName);
 DeleteFile(FileName);
}
//---------------------------------------------------------------------------

void __fastcall TRForm2::Button3Click(TObject *Sender)
{
 Close();  
}
//---------------------------------------------------------------------------

void __fastcall TRForm2::CutItemClick(TObject *Sender)
{
 RichEdit1->CutToClipboard();
}
//---------------------------------------------------------------------------

void __fastcall TRForm2::CopyItemClick(TObject *Sender)
{
 RichEdit1->CopyToClipboard();
}
//---------------------------------------------------------------------------

void __fastcall TRForm2::PasteItemClick(TObject *Sender)
{
 RichEdit1->PasteFromClipboard();
}
//---------------------------------------------------------------------------

