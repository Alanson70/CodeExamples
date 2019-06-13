//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "proba1unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
 TComponent *C=(TComponent *)Sender;
 int T=C->Tag;
 switch(T)
 {
  case 0 :
   return;
  case 1 :
   T=3;
 }
;///////////
}
//---------------------------------------------------------------------------
