//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UgolAzimut.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TUAForm *UAForm;
//---------------------------------------------------------------------------
__fastcall TUAForm::TUAForm(TComponent* Owner)
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

void __fastcall TUAForm::ScrollBarChange(TObject *Sender)
{
 char s[20];
 double R=6371.0;
 double H=42170.0;

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

 if(SHIR<0)
  if(DOL>KA) AZ=RadToDeg*(atan(sin(KA-DOL)/(-1*sin(SHIR)*cos(KA-DOL)))+2*PI);
  else       AZ=RadToDeg*(atan(sin(KA-DOL)/(-1*sin(SHIR)*cos(KA-DOL))));
 if(SHIR>0)  AZ=RadToDeg*(atan(sin(KA-DOL)/(-1*sin(SHIR)*cos(KA-DOL)))+1*PI);
 if(SHIR==0)
  if(DOL>KA) AZ=90;
  else AZ=270;

 UM=RadToDeg*asin((H*cos(SHIR)*cos(KA-DOL)-R)/
    sqrt(R*R+H*H-2*R*H*cos(SHIR)*cos(KA-DOL)));

 sprintf(s,"%3.1d°%2.2d'",(int)AZ,abs((int)((AZ-(int)AZ)*60)));
 AZEdit->Text=AnsiString(s);
 sprintf(s,"%3.1d°%2.2d'",(int)UM,abs((int)((UM-(int)UM)*60)));
 UMEdit->Text=AnsiString(s);
}
//---------------------------------------------------------------------------


void __fastcall TUAForm::DOLScrollBar2Change(TObject *Sender)
{
 if(ChangeFlag==true) return;
 ChangeFlag=true;
 dDOL=DOLScrollBar2->Position/100.0;
 DOLScrollBar1->Position=DOLScrollBar2->Position*0.6;
 ScrollBarChange(Sender);
 ChangeFlag=false;
}
//---------------------------------------------------------------------------

void __fastcall TUAForm::SHIRScrollBar2Change(TObject *Sender)
{
 if(ChangeFlag==true) return;
 ChangeFlag=true;
 dSHIR=SHIRScrollBar2->Position/100.0;
 SHIRScrollBar1->Position=SHIRScrollBar2->Position*0.6;
 ScrollBarChange(Sender);
 ChangeFlag=false;
}
//---------------------------------------------------------------------------

void __fastcall TUAForm::DOLScrollBar1Change(TObject *Sender)
{
 if(ChangeFlag==true) return;
 ChangeFlag=true;
 dDOL=DOLScrollBar1->Position/60.0;
 DOLScrollBar2->Position=DOLScrollBar1->Position/0.6;
 ScrollBarChange(Sender);
 ChangeFlag=false;
}
//---------------------------------------------------------------------------

void __fastcall TUAForm::SHIRScrollBar1Change(TObject *Sender)
{
 if(ChangeFlag==true) return;
 ChangeFlag=true;
 dSHIR=SHIRScrollBar1->Position/60.0;
 SHIRScrollBar2->Position=SHIRScrollBar1->Position/0.6;
 ScrollBarChange(Sender);
 ChangeFlag=false;
}
//---------------------------------------------------------------------------
//#include "AUUnit2.h"
#include "AUGridUnit.h"
void __fastcall TUAForm::Button1Click(TObject *Sender)
{
 int CurPos;
 /*
 switch(PosFlag)
 {
  case 1 : AUDataModule1->AUTable->Edit();break;
  default : AUDataModule1->AUTable->Append();break;
  case 2 : AUDataModule1->AUTable->Delete();
           Close();return;
 }

 AUDataModule1->AUTable->FieldValues["Number"]=1;
 AUDataModule1->AUTable->FieldValues["Satt.Dolgota"]=KAEdit->Text;
 AUDataModule1->AUTable->FieldValues["Dolgota ES"]=DOLEdit->Text;
 AUDataModule1->AUTable->FieldValues["Shirota ES"]=SHIREdit->Text;
 AUDataModule1->AUTable->FieldValues["Azimut ES"]=AZEdit->Text;
 AUDataModule1->AUTable->FieldValues["Ugol Mesta ES"]=UMEdit->Text;
 AUDataModule1->AUTable->FieldValues["Name"]=NAMEEdit->Text;
 AUDataModule1->AUTable->FieldValues["Comments"]=COMMENTEdit->Text;
 AUDataModule1->AUTable->Post();
 */
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

void __fastcall TUAForm::FormShow(TObject *Sender)
{
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
  case 2 :  /*
  NAMEEdit->Text=AUDataModule1->AUTable->FieldValues["Name"];
  COMMENTEdit->Text=AUDataModule1->AUTable->FieldValues["Comments"];
  strncpy(S,AnsiString(AUDataModule1->AUTable->FieldValues["Satt.Dolgota"]).c_str(),9);
  KAScrollBar->Position=atoi(S);
  strncpy(S,AnsiString(AUDataModule1->AUTable->FieldValues["Dolgota ES"]).c_str(),9);
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

  strncpy(S,AnsiString(AUDataModule1->AUTable->FieldValues["Shirota ES"]).c_str(),9);
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
  }           */
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
 Button1->Caption=Command[PosFlag];
}
//---------------------------------------------------------------------------

void __fastcall TUAForm::Button2Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

