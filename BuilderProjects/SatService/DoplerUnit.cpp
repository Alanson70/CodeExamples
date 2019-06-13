//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DoplerUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDoplerForm *DoplerForm;
//---------------------------------------------------------------------------
__fastcall TDoplerForm::TDoplerForm(TComponent* Owner)
    : TForm(Owner)
{
 PosFlag=-1;
}
//---------------------------------------------------------------------------
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI M_PI
#define RadToDeg  (180.0/PI)
#define DegToRad  (M_PI/180.0)

void __fastcall TDoplerForm::ScrollBarChange(TObject *Sender)
{
 char s[20];
 double R=6371.0;
 double H=42170.0;

 double KMIN,KMAX,SHMIN,SHMAX,DMIN,DMAX,UMIN,UMAX;

 if(CheckBox1->Checked==true)
  RATE=RATEScrollBar->Position*1000.0;
 else
  RATE=RATEScrollBar->Position*100.0;


 RAZMAH=DegToRad*(RAZMAHScrollBar->Position+dRAZMAH);
 sprintf(s,"%3.1d°%2.2d'",RAZMAHScrollBar->Position,RAZMAHScrollBar1->Position);
 RAZMAHEdit->Text=AnsiString(s);
 sprintf(s,"%3.1d,%2.2d",RAZMAHScrollBar->Position,RAZMAHScrollBar2->Position);
 RAZMAHEdit1->Text=AnsiString(s);

 DOL=DegToRad*(DOLScrollBar->Position+dDOL);
 sprintf(s,"%3.1d°%2.2d'",DOLScrollBar->Position,DOLScrollBar1->Position);
 DOLEdit->Text=AnsiString(s);
 sprintf(s,"%3.1d,%2.2d",DOLScrollBar->Position,DOLScrollBar2->Position);
 DOLEdit1->Text=AnsiString(s);

 SHIR=DegToRad*(SHIRScrollBar->Position+dSHIR);
 sprintf(s,"%3.1d°%2.2d'",SHIRScrollBar->Position,SHIRScrollBar1->Position);
 SHIREdit->Text=AnsiString(s);
 sprintf(s,"%3.1d,%2.2d",SHIRScrollBar->Position,SHIRScrollBar2->Position);
 SHIREdit1->Text=AnsiString(s);

 KA=DegToRad*(KAScrollBar->Position);
 sprintf(s,"%3.1d°",KAScrollBar->Position);
 KAEdit->Text=AnsiString(s);

 KZ=KZScrollBar->Position;
 sprintf(s,"%3d%%",KZScrollBar->Position);
 KZEdit->Text=AnsiString(s);

 if(SHIR<0)
  if(DOL>KA) AZ=RadToDeg*(atan(sin(KA-DOL)/(-1*sin(SHIR)*cos(KA-DOL)))+2*PI);
  else       AZ=RadToDeg*(atan(sin(KA-DOL)/(-1*sin(SHIR)*cos(KA-DOL))));
 if(SHIR>0)  AZ=RadToDeg*(atan(sin(KA-DOL)/(-1*sin(SHIR)*cos(KA-DOL)))+1*PI);
 if(SHIR==0)
  if(DOL>KA) AZ=90;
  else AZ=270;

 UM=RadToDeg*asin((H*cos(SHIR)*cos(KA-DOL)-R)/
    sqrt(R*R+H*H-2*R*H*cos(SHIR)*cos(KA-DOL)));

 UMIN=RadToDeg*asin((H*cos(SHIR-DegToRad*1.0)*cos(KA-DOL)-R)/
    sqrt(R*R+H*H-2*R*H*cos(SHIR-DegToRad*1.0)*cos(KA-DOL)));
 UMAX=RadToDeg*asin((H*cos(SHIR+DegToRad*1.0)*cos(KA-DOL)-R)/
    sqrt(R*R+H*H-2*R*H*cos(SHIR+DegToRad*1.0)*cos(KA-DOL)));
 KMIN=fabs(UMIN-UM);
 KMAX=fabs(UMAX-UM);
 SHMIN=DegToRad*(RadToDeg*SHIR-(RAZMAH/(2*DegToRad*KMIN)));
 SHMAX=DegToRad*(RadToDeg*SHIR+(RAZMAH/(2*DegToRad*KMAX)));
 DMIN=42644.0*sqrt(1.0-0.2954*cos(KA-DOL)*cos(SHMIN));
 DMAX=42644.0*sqrt(1.0-0.2954*cos(KA-DOL)*cos(SHMAX));
 DT=2.0*(DMAX-DMIN)/300.0;
 BUFFER=DT*100.0/KZ;

 sprintf(s,"%7.1lf мс",BUFFER);
 BUFFEREdit->Text=AnsiString(s);
 sprintf(s,"%7.1lf мс",BUFFER*2);
 BUFFEREdit1->Text=AnsiString(s);
 sprintf(s,"%6.1lf мс",DT);
 TIMEEdit->Text=AnsiString(s);
 sprintf(s,"%7.1lf",RATE/1000.0);
 RATEEdit->Text=AnsiString(s);
 sprintf(s,"%7.1lf Бит",RATE*BUFFER/1000.0);
 BUFFERREdit->Text=AnsiString(s);
 sprintf(s,"%7.1lf Бит",RATE*BUFFER*2/1000.0);
 BUFFERREdit1->Text=AnsiString(s);

 sprintf(s,"%3.1d°%2.2d'",(int)AZ,abs((int)((AZ-(int)AZ)*60)));
 AZEdit->Text=AnsiString(s);
 sprintf(s,"%3.1d°%2.2d'",(int)UM,abs((int)((UM-(int)UM)*60)));
 UMEdit->Text=AnsiString(s);
}
//---------------------------------------------------------------------------
//#include "AUUnit2.h"
/*
#include "AUGridUnit.h"
void __fastcall TUAForm::Button1Click(TObject *Sender)
{
 int CurPos;

 switch(PosFlag)
 {
  case 1  :
   CurPos=AUGridForm->Grid1->Row;
  break;
  default : AUGridForm->Grid1->RowCount++;
   CurPos=AUGridForm->Grid1->RowCount-1;
  break;
  case 2  :
   CurPos=AUGridForm->Grid1->Row;
   for(int j=CurPos;j<AUGridForm->Grid1->RowCount;j++)
   {
    for(int i=0;i<7;i++)
    {
     AUGridForm->Grid1->Cells[i][j]=AUGridForm->Grid1->Cells[i][j+1];
    }
   }
   AUGridForm->Grid1->RowCount--;
   Close();
   return;
 }
 AUGridForm->Grid1->Cells[1][CurPos]=KAEdit->Text;
 AUGridForm->Grid1->Cells[2][CurPos]=DOLEdit->Text;
 AUGridForm->Grid1->Cells[3][CurPos]=SHIREdit->Text;
 AUGridForm->Grid1->Cells[4][CurPos]=AZEdit->Text;
 AUGridForm->Grid1->Cells[5][CurPos]=UMEdit->Text;
 AUGridForm->Grid1->Cells[0][CurPos]=NAMEEdit->Text;
 AUGridForm->Grid1->Cells[6][CurPos]=COMMENTEdit->Text;
 AUGridForm->ChangeFlag=true;
 Close();
}
//---------------------------------------------------------------------------
*/
#define NOAUGRID 1

void __fastcall TDoplerForm::FormShow(TObject *Sender)
{
#ifndef NOAUGRID
 int CurPos;
 char S[10];
 char *Title="Азимут и Угол места на спутник";
 char *CommandTitle[3]={""," - Изменение"," - Удаление"};
 char *Command[3]={"Добавить в список","Изменить","Удалить"};

 switch(PosFlag)
 {
  default : PosFlag=0;
  case 0 :
  case 1 :
  case 2 :

  CurPos=AUGridForm->Grid1->Row;
  NAMEEdit->Text=AUGridForm->Grid1->Cells[0][CurPos];
  COMMENTEdit->Text=AUGridForm->Grid1->Cells[6][CurPos];
  strncpy(S,AnsiString(AUGridForm->Grid1->Cells[1][CurPos]).c_str(),9);
  KAScrollBar->Position=atoi(S);
  strncpy(S,AnsiString(AUGridForm->Grid1->Cells[2][CurPos]).c_str(),9);
  DOLScrollBar->Position=atoi(S);
  for(int i=0;i<8;i++)
  {
   if(S[i]=='°')
   {
    DOLScrollBar1->Position=atoi(S+i+1);
    break;
   }
   if(S[i]=='.')
   {
    DOLScrollBar2->Position=atoi(S+i+1);
    break;
   }
  }
  strncpy(S,AnsiString(AUGridForm->Grid1->Cells[3][CurPos]).c_str(),9);
  SHIRScrollBar->Position=atoi(S);
  for(int i=0;i<8;i++)
  {
   if(S[i]=='°')
   {
    SHIRScrollBar1->Position=atoi(S+i+1);
    break;
   }
   if(S[i]=='.')
   {
    SHIRScrollBar2->Position=atoi(S+i+1);
    break;
   }
  }
  break;
  /*case 0 :
  KAScrollBar->Position=90;
  DOLScrollBar->Position=90;
  ChangeFlag=false;
  break;*/
 }
 UAForm->Caption=AnsiString(Title)+AnsiString(CommandTitle[PosFlag]);
 //Button1->Caption=Command[PosFlag];
#else
 KAScrollBar->Position=90;
 DOLScrollBar->Position=40;
 SHIRScrollBar->Position=50;
 ChangeFlag=false;
#endif
 RAZMAHScrollBar->Position=5;
 KZScrollBar->Position=50;
}
//---------------------------------------------------------------------------

void __fastcall TDoplerForm::Button2Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TDoplerForm::DOLScrollBar1Change(TObject *Sender)
{
 if(ChangeFlag==true) return;
 ChangeFlag=true;
 dDOL=DOLScrollBar1->Position/60.0;
 DOLScrollBar2->Position=DOLScrollBar1->Position/0.6;
 ScrollBarChange(Sender);
 ChangeFlag=false;
}
//---------------------------------------------------------------------------

void __fastcall TDoplerForm::DOLScrollBar2Change(TObject *Sender)
{
 if(ChangeFlag==true) return;
 ChangeFlag=true;
 dDOL=DOLScrollBar2->Position/100.0;
 DOLScrollBar1->Position=DOLScrollBar2->Position*0.6;
 ScrollBarChange(Sender);
 ChangeFlag=false;
}
//---------------------------------------------------------------------------
void __fastcall TDoplerForm::SHIRScrollBar1Change(TObject *Sender)
{
 if(ChangeFlag==true) return;
 ChangeFlag=true;
 dSHIR=SHIRScrollBar1->Position/60.0;
 SHIRScrollBar2->Position=SHIRScrollBar1->Position/0.6;
 ScrollBarChange(Sender);
 ChangeFlag=false;
}

//---------------------------------------------------------------------------

void __fastcall TDoplerForm::SHIRScrollBar2Change(TObject *Sender)
{
 if(ChangeFlag==true) return;
 ChangeFlag=true;
 dSHIR=SHIRScrollBar2->Position/100.0;
 SHIRScrollBar1->Position=SHIRScrollBar2->Position*0.6;
 ScrollBarChange(Sender);
 ChangeFlag=false;
}
//---------------------------------------------------------------------------

void __fastcall TDoplerForm::RAZMAHScrollBar1Change(TObject *Sender)
{
 if(ChangeFlag==true) return;
 ChangeFlag=true;
 dRAZMAH=RAZMAHScrollBar1->Position/60.0;
 RAZMAHScrollBar2->Position=RAZMAHScrollBar1->Position/0.6;
 ScrollBarChange(Sender);
 ChangeFlag=false;
}
//---------------------------------------------------------------------------

void __fastcall TDoplerForm::RAZMAHScrollBar2Change(TObject *Sender)
{
 if(ChangeFlag==true) return;
 ChangeFlag=true;
 dRAZMAH=RAZMAHScrollBar2->Position/100.0;
 RAZMAHScrollBar1->Position=RAZMAHScrollBar2->Position*0.6;
 ScrollBarChange(Sender);
 ChangeFlag=false;
}
//---------------------------------------------------------------------------



