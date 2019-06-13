//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFormUnit.h"
#include "AboutFormUnit.h"



//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ColorsFrameUnit"

#pragma link "DatesFrameUnit"
#pragma link "ValuesFrameUnit"
#pragma link "SymbolsFrameUnit"
#pragma link "DateCalcFrameUnit"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
 ColorsTabSheet->DoubleBuffered=true;
}
//---------------------------------------------------------------------------

                                       
void __fastcall TMainForm::AboutMenuItemClick(TObject *Sender)
{
 AboutForm=new TAboutForm(this);

 try
 {
  AboutForm->ShowModal();  
  delete AboutForm;
 }
 catch(...)
 {
  delete AboutForm;
 }
}
//---------------------------------------------------------------------------

