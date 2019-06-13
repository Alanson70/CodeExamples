//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DBtoValue1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdbForm *dbForm;
//---------------------------------------------------------------------------
__fastcall TdbForm::TdbForm(TComponent* Owner)
    : TForm(Owner)
{
 VIN=1;
 VOUT=1;
 R=1;
 DB=0;
 ChangeFlag=false;
}
//---------------------------------------------------------------------------
#include <math.h>
#include <stdio.h>

void __fastcall TdbForm::BitBtn1Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TdbForm::ScrollBarDChange(TObject *Sender)
{
 if(ChangeFlag==false)
 {
  ChangeFlag=true;
  DB=((ScrollBarD->Max-4000)-ScrollBarD->Position)/100.0;
  EditD->Text=DB;
  R=pow(10,0.1*DB);
  EditR->Text=R;
  if(R>100000) ScrollBarR->Position=ScrollBarR->Max-100000;
  else         ScrollBarR->Position=ScrollBarR->Max-R;
  VIN=1;
  if(R>1000) VIN=0.01;
  if(R<0.01) VIN=20;
  ScrollBarIN->Position=ScrollBarIN->Max-VIN*100.0;
  EditIN->Text=VIN;
  VOUT=VIN*R;
  ScrollBarOUT->Position=ScrollBarOUT->Max-VOUT*100.0;
  EditOUT->Text=VOUT;
  ChangeFlag=false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TdbForm::ScrollBarRChange(TObject *Sender)
{
 if(ChangeFlag==false)
 {
  ChangeFlag=true;
  R=1+ScrollBarR->Max-ScrollBarR->Position;
  EditR->Text=R;
  DB=10*log10(R);
  EditD->Text=DB;
  ScrollBarD->Position=(ScrollBarD->Max-4000)-DB*100.0;
  VIN=1;
  if(R>1000) VIN=0.01;
  if(R<0.01) VIN=20;
  ScrollBarIN->Position=ScrollBarIN->Max-VIN*100.0;
  EditIN->Text=VIN;
  VOUT=VIN*R;
  ScrollBarOUT->Position=ScrollBarOUT->Max-VOUT*100.0;
  EditOUT->Text=VOUT;
  ChangeFlag=false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TdbForm::ScrollBarINChange(TObject *Sender)
{
 if(ChangeFlag==false)
 {
  ChangeFlag=true;
  VIN=(1+ScrollBarIN->Max-ScrollBarIN->Position)/100.0;
  if(VIN>=0.01)
  {
   EditIN->Text=VIN;
   DB=10*log10(VOUT/VIN);
   EditD->Text=DB;
   ScrollBarD->Position=(ScrollBarD->Max-4000)-DB*100.0;
   R=pow(10,0.1*DB);
   EditR->Text=R;
   ScrollBarR->Position=ScrollBarR->Max-R;
  }
  ChangeFlag=false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TdbForm::ScrollBarOUTChange(TObject *Sender)
{
 if(ChangeFlag==false)
 {
  ChangeFlag=true;
  VOUT=(1+ScrollBarOUT->Max-ScrollBarOUT->Position)/100.0;
  if(VOUT>=0.01)
  {
   EditOUT->Text=VOUT;
   DB=10*log10(VOUT/VIN);
   EditD->Text=DB;
   ScrollBarD->Position=(ScrollBarD->Max-4000)-DB*100.0;
   R=pow(10,0.1*DB);
   EditR->Text=R;
   ScrollBarR->Position=ScrollBarR->Max-R;
  }
  ChangeFlag=false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TdbForm::FormClose(TObject *Sender, TCloseAction &Action)
{
// delete dbForm;
// dbForm=NULL;
}
//---------------------------------------------------------------------------

