//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "PXY.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPXYForm *PXYForm;
//---------------------------------------------------------------------------
__fastcall TPXYForm::TPXYForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPXYForm::FormCreate(TObject *Sender)
{
 L=0.07741;
 D=5.0;
 P=0.5;
 S=1.91;
 PT=0.05;
 LScrollBar->Position=L*10000;
 DScrollBar->Position=D*10.0;
 PScrollBar->Position=P*100.0;
 SScrollBar->Position=S*10;
 PTEdit->Text=PT;
}
//---------------------------------------------------------------------------
void __fastcall TPXYForm::LScrollBarChange(TObject *Sender)
{
 L=LScrollBar->Position/10000.0;
 LEdit->Text=AnsiString(L*1000.0);
 Change();
}
//---------------------------------------------------------------------------
void __fastcall TPXYForm::DScrollBarChange(TObject *Sender)
{
 D=DScrollBar->Position/10.0;
 DEdit->Text=AnsiString(D);
 Change();
}
//---------------------------------------------------------------------------
void __fastcall TPXYForm::PScrollBarChange(TObject *Sender)
{
 P=PScrollBar->Position/100.0;
 PEdit->Text=AnsiString(P);
 Change();
}
//---------------------------------------------------------------------------
void __fastcall TPXYForm::SScrollBarChange(TObject *Sender)
{
 S=SScrollBar->Position/10.0;
 SEdit->Text=AnsiString(S);
 //Change();
}
//---------------------------------------------------------------------------
void __fastcall TPXYForm::TScrollBarChange(TObject *Sender)
{
 PT=TScrollBar->Position/100.0;
 PTEdit->Text=AnsiString(PT);
 Change();
}
//---------------------------------------------------------------------------
#include <math.h>
void __fastcall TPXYForm::Change()
{
 double Pmin,Pmax;
 PXY=(2522.62*L*sqrt( (-1)*log(pow(10.0,(P/-10.0))) ))/(S*D);
 PXYEdit->Text=AnsiString((long(PXY*1000))/1000.0);

 Pmin=(2522.62*L*sqrt( (-1)*log(pow(10.0,((PT*2)/-10.0))) ))/(S*D);
 Pmax=(2522.62*L*sqrt( (-1)*log(pow(10.0,((P*0.5)/-10.0))) ))/(S*D);
 StepEdit1->Text=AnsiString((int(Pmin*10))/10.0);
 StepEdit2->Text=AnsiString((int(Pmax*10))/10.0);
}
//---------------------------------------------------------------------------
#include "SensUnit.h"

void __fastcall TPXYForm::Button1Click(TObject *Sender)
{
 TSensForm *SensForm;

 SensForm=new TSensForm(this);
 try
 {
  SensForm->ShowModal();
  delete SensForm;
 }
 catch(...)
 {
  delete SensForm;
 }
}
//---------------------------------------------------------------------------


