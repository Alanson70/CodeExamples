//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AUForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAUGridForm *AUGridForm;
//---------------------------------------------------------------------------
__fastcall TAUGridForm::TAUGridForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
AnsiString AUGridText[7]=
{
 "������������",
 "������� ��",
 "������� ��",
 "������ ��",
 "������",
 "���� �����",
 "����������"
};

void __fastcall TAUGridForm::FormCreate(TObject *Sender)
{
 for(int j=0;j<7;j++)
 {
  Grid1->Cells[j][0]=AUGridText[j];
 }
}
//---------------------------------------------------------------------------
