//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SensUnit.h"
#include "Functions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSensForm *SensForm;
#include "stdlib.h"
#include "algorithm.h"
//---------------------------------------------------------------------------
__fastcall TSensForm::TSensForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSensForm::GScrollBarChange(TObject *Sender)
{
 G=GScrollBar->Position*60+GScrollBar1->Position;
 GEdit->Text=MinToText(G);
}
//---------------------------------------------------------------------------
void __fastcall TSensForm::GMINScrollBarChange(TObject *Sender)
{
 int GMIN,GMAX;
 GMIN=GMINScrollBar->Position*60+GMINScrollBar1->Position;
 GMINEdit->Text=MinToText(GMIN);
 GMAX=GMAXScrollBar->Position*60+GMAXScrollBar1->Position;
 GMAXEdit->Text=MinToText(GMAX);
 G=std::max(1,abs(GMIN-GMAX));
 GEdit->Text=MinToText(G);
}//---------------------------------------------------------------------------
AnsiString __fastcall TSensForm::MinToText(long int M)
{
 AnsiString S;
 S=AnsiString(M/60)+AnsiString("°")
  +AnsiString(M-((M/60)*60))+AnsiString("'");
 return S;
}
//---------------------------------------------------------------------------
void __fastcall TSensForm::FormCreate(TObject *Sender)
{
 I=1;
 G=1;
 GScrollBar->Position=3;
 IScrollBar->Position=155;
}
//---------------------------------------------------------------------------
void __fastcall TSensForm::IScrollBarChange(TObject *Sender)
{
 I=IScrollBar->Position;
 IEdit->Text=I;
}
//---------------------------------------------------------------------------
void __fastcall TSensForm::IMINScrollBarChange(TObject *Sender)
{
 int IMIN,IMAX;

 IMIN=IMINScrollBar->Position;
 IMINEdit->Text=IMIN;
 IMAX=IMAXScrollBar->Position;
 IMAXEdit->Text=IMAX;
 I=std::max(1,abs(IMAX-IMIN));
 IEdit->Text=I;
}
//---------------------------------------------------------------------------
void __fastcall TSensForm::IEditChange(TObject *Sender)
{
 Sens=(1.0*G)/I;
 SensEdit->Text=((int)(Sens*1000))/1000.0;
}
//---------------------------------------------------------------------------
void __fastcall TSensForm::Button2Click(TObject *Sender)
{
 Close();   
}
//---------------------------------------------------------------------------
#include "PXYFormUnit.h"
void __fastcall TSensForm::Button1Click(TObject *Sender)
{
 PXYForm->S=Sens;
 PXYForm->SEdit->Text=((int)(Sens*1000))/1000.0;
 Close();
}
//---------------------------------------------------------------------------
