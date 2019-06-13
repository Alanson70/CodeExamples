//---------------------------------------------------------------------------
#include <vcl.h>
//#include <vcl\oleauto.hpp>
//#include <vcl\comobj.hpp>
#pragma hdrstop

#include "ServiceMain.h"
//#include "AUdb1.h"
#include "QR2Unit.h"
#include "UgolAzimut.h"
//#include "AUUnit2.h"
#include "AUGridUnit.h"
#include "CloseUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TServiceForm *ServiceForm;
//---------------------------------------------------------------------------
__fastcall TServiceForm::TServiceForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TServiceForm::Image1DblClick(TObject *Sender)
{
 Close();
}

#include "Inifiles.hpp"
#include <stdlib.h>

//---------------------------------------------------------------------------
void __fastcall TServiceForm::FormCreate(TObject *Sender)
{
 Application->OnIdle=ApplicationIdle;
}

void __fastcall TServiceForm::FormShow(TObject *Sender)
{
 TIniFile *TI;

 TI=new TIniFile("SatSer.INI");
 try
 {
  Left=TI->ReadInteger("Common","Left",Left);
  Top=TI->ReadInteger("Common","Top",Top);
  delete TI;
 }
 catch(...)
 {
  delete TI;
 }
 DragStatus=false;
}
char * TitleText=
"Полезные утилиты для инженеров спутниковой связи.  ";

void __fastcall TServiceForm::ApplicationIdle(TObject *Sender,bool &Done)
{
 //--------
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TServiceForm::Image1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 DragStatus=false;
}
//---------------------------------------------------------------------------

void __fastcall TServiceForm::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if(Button==mbLeft)
 {
  DragStatus=true;
  XStart=X;
  YStart=Y;
  DX=0;
  DY=0;
 }
}
//---------------------------------------------------------------------------
/*
struct _MP_
{
 int X;
 int Y;
}MP[205];
*/
void __fastcall TServiceForm::Image1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
 int dx=X-XStart;
 int dy=Y-YStart;

 if(DragStatus==true)
 {
  DX+=dx;
  DY+=dy;
  if((abs(DX)>1)||(abs(DY)>1))
  {
 /*  MP[Count].X=X;
   MP[Count].Y=Y;
   Count++;
   if(Count>200)
   {
    Count=0;
   }  */
   Left+=DX;
   Top+=DY;

   DX=0;
   DY=0;

//   XStart=X;
//   YStart=Y;
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TServiceForm::closeItemClick(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TServiceForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 TIniFile *TI;

 TI=new TIniFile("SatSer.INI");
 try
 {
  TI->WriteInteger("Common","Left",Left);
  TI->WriteInteger("Common","Top",Top);
  delete TI;
 }
 catch(...)
 {
  delete TI;
 }
}
//---------------------------------------------------------------------------
void __fastcall TServiceForm::Timer1Timer(TObject *Sender)
{
 Application->Title=(TitleText+TitleCount)+AnsiString(TitleText);
 TitleCount++;
 if(TitleCount>=strlen(TitleText)) TitleCount=0;
}
//---------------------------------------------------------------------------

void __fastcall TServiceForm::CallItemClick(TObject *Sender)
{
 system("Calc.exe");
 //Variant MSCalc;

 //MSCalc=CreateOleObject("Calc.basic");

}
//---------------------------------------------------------------------------
#include "DBtoValue1.h"
void __fastcall TServiceForm::dbItemClick(TObject *Sender)
{
 if(dbForm==NULL) dbForm=new TdbForm(this);
 dbForm->Show();
}
//---------------------------------------------------------------------------
#include "d1.h"
void __fastcall TServiceForm::toKAItemClick(TObject *Sender)
{
 if(tosputnikForm==NULL) tosputnikForm=new TtosputnikForm(this);
 tosputnikForm->Show();
}
//---------------------------------------------------------------------------
#include "FreqPlan1.h"
void __fastcall TServiceForm::fpItemClick(TObject *Sender)
{
 if(FreqForm==NULL) FreqForm=new TFreqForm(this);
 FreqForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TServiceForm::ESItemClick(TObject *Sender)
{
 AUGridForm=new TAUGridForm(this);
 AUGridForm->Show();
}
//---------------------------------------------------------------------------
#include "DoplerUnit.h"
void __fastcall TServiceForm::DopplerItemClick(TObject *Sender)
{
 if(DoplerForm==NULL) DoplerForm=new TDoplerForm(this);

 DoplerForm->Show();
}
//---------------------------------------------------------------------------
#include "PXY.h"
void __fastcall TServiceForm::PXYItemClick(TObject *Sender)
{
 if(PXYForm==NULL) PXYForm=new TPXYForm(this);

 PXYForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TServiceForm::OnTimerClick(TObject *Sender)
{
 if(PXYForm!=NULL) if(PXYForm->Enabled==false) { delete PXYForm;PXYForm=NULL;}
 if(DoplerForm!=NULL) if(DoplerForm->Enabled==false) { delete DoplerForm;DoplerForm=NULL;}
 if(AUGridForm!=NULL) if(AUGridForm->Enabled==false) { delete AUGridForm;AUGridForm=NULL;}
 if(dbForm!=NULL) if(dbForm->Enabled==false) { delete dbForm;dbForm=NULL;}
 if(tosputnikForm!=NULL) if(tosputnikForm->Enabled==false) { delete tosputnikForm;tosputnikForm=NULL;}
 if(FreqForm!=NULL) if(FreqForm->Enabled==false) { delete FreqForm;FreqForm=NULL;}
 //if(PXYForm!=NULL) if(PXYForm->Enabled==false) { delete PXYForm;PXYForm=NULL;}
 //if(PXYForm!=NULL) if(PXYForm->Enabled==false) { delete PXYForm;PXYForm=NULL;}
}
//---------------------------------------------------------------------------

