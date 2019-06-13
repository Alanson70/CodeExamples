//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FPEditUnit.h"
#include "DamaUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFPForm *FPForm;
//---------------------------------------------------------------------------
__fastcall TFPForm::TFPForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFPForm::FormShow(TObject *Sender)
{
 FreqBeginScrollBar1->Position=Dama->GetFPSBegin(fpsn,0);
 FreqEndScrollBar1->Position=Dama->GetFPSEnd(fpsn,0);
 FreqBeginScrollBar2->Position=Dama->GetFPSBegin(fpsn,1);
 FreqEndScrollBar2->Position=Dama->GetFPSEnd(fpsn,1);
 FreqBeginScrollBar3->Position=Dama->GetFPSBegin(fpsn,2);
 FreqEndScrollBar3->Position=Dama->GetFPSEnd(fpsn,2);
 
 
}
//---------------------------------------------------------------------------
void __fastcall TFPForm::FreqBeginScrollBarChange(TObject *Sender)
{
 FreqBeginScrollBar1->Position=Dama->GetFPSBegin(fpsn,0);
 //FreqBeginEdit1->Position
}
//---------------------------------------------------------------------------
