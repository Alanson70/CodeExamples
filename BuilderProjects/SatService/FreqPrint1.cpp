//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FreqPrint1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFreqPrintForm *FreqPrintForm;
//---------------------------------------------------------------------------
__fastcall TFreqPrintForm::TFreqPrintForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
#include "FreqPlan1.h"
#include <stdio.h>
void __fastcall TFreqPrintForm::FormActivate(TObject *Sender)
{
 TLineSeries *S;
 FreqStruct *F;
 char String[30];

 Chart1->Title->Text->Strings[0]=FreqForm->TitleEdit->Text;

 for(int i=0;i<MAX_FREQS;i++)
 {
  switch(i)
  {
   case 0 : S=Series1;break;
   case 1 : S=Series2;break;
   case 2 : S=Series3;break;
   case 3 : S=Series4;break;
   case 4 : S=Series5;break;
   case 5 : S=Series6;break;
   case 6 : S=Series7;break;
   case 7 : S=Series8;break;
   case 8 : S=Series9;break;
   case 9 : S=Series10;break;
  }
  F=&FreqForm->FS[i];
  S->Clear();
  S->ShowInLegend=false;
  if(F->Enabled==true)
  {
   S->ShowInLegend=true;
   sprintf(String,".%7.1lf к√ц,%6.1lf кЅит/с ",F->FC,F->DR);
   S->Title=AnsiString(i+1)+String+F->Name;
   S->AddXY(F->LB,-20," ",clTeeColor);
   S->AddXY(F->FC-F->SR/2,-3," ",clTeeColor);
   S->AddXY(F->FC-F->SR/4.2,-0.2," ",clTeeColor);
   S->AddXY(F->FC,0,1+i,clTeeColor);
   //
   S->AddXY(F->FC,-20," ",clTeeColor);
   S->AddXY(F->FC,0," ",clTeeColor);
   S->AddXY(F->FC+F->SR/4.2,-0.2," ",clTeeColor);
   S->AddXY(F->FC+F->SR/2,-3," ",clTeeColor);
   S->AddXY(F->RB,-20," ",clTeeColor);
  }
 }
}
//---------------------------------------------------------------------------
void __fastcall TFreqPrintForm::Button1Click(TObject *Sender)
{
 //TRect TR(Chart1->Left,Chart1->Top,Chart1->Left+Chart1);

 //Chart1->PrintOrientation(poLandscape);
 //Chart1->PrintLandscape(); TPrinterOrientation
 
}
//---------------------------------------------------------------------------
void __fastcall TFreqPrintForm::Button2Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TFreqPrintForm::Button3Click(TObject *Sender)
{
 if(PrinterSetupDialog1->Execute()==true)
 {
  Chart1->PrintMargins.Left=0;
  Chart1->PrintMargins.Right=0;
  Chart1->PrintMargins.Top=0;
  Chart1->PrintMargins.Bottom=0;
  Chart1->Print();
 }
 //PrintDialog1->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TFreqPrintForm::ScrollBar1Change(TObject *Sender)
{
 //Chart1->PrintResolution=100-ScrollBar1->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFreqPrintForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 //FreqPrintForm->Close();   
}
//---------------------------------------------------------------------------

