//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DamaMain1.h"
#include "FPEditUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFreqForm *FreqForm;
//---------------------------------------------------------------------------
#include <Inifiles.hpp>
#include <stdlib.h>
#include <stdio.h>

#include "DamaUnit.h"
__fastcall TFreqForm::TFreqForm(TComponent* Owner)
    : TForm(Owner)
{
 
}
//----------------------------------------------------------
char *GridTextCol[3]={"Диапазон","Начало","Конец"};
char *GridTextRow[3]={"1","2","3"};

void __fastcall TFreqForm::FormCreate(TObject *Sender)
{
 Dama=new TDama(Owner);

 for(int i=0;i<3;i++)
  StringGrid1->Cells[i][0]=GridTextCol[i];
 for(int i=1;i<4;i++)
  StringGrid1->Cells[0][i]=GridTextRow[i-1];
 for(int i=0;i<3;i++)
 {
  StringGrid1->Cells[1][i+1]=Dama->GetFPSBegin(FPRadioGroup->ItemIndex,i);
  StringGrid1->Cells[2][i+1]=Dama->GetFPSEnd(FPRadioGroup->ItemIndex,i);
 }
// LoadOnStart();
}
//---------------------------------------------------------------------------
void TFreqForm::LoadOnStart()
{
 /*FreqStruct *F;
 for(int i=0;i<MAX_FREQS;i++)
 {
  F=&FS[i];
  F->FC=84000;
  F->DR=9.70;
  F->FO=0;
  F->FRS=0;
  F->FEC=0;
  F->Band=0;
  F->CM=1;
  F->AN=1.0;
  F->Enabled=true;
 }
 FreqBeginScrollBar->Position=FreqBegin;
 FreqEndScrollBar->Position=FreqEnd;
 FreqStepScrollBar->Position=FreqStep;
 RadioGroup1->ItemIndex=0;
 AnyChoose(NULL);
 */
}
//----------------------------------------------------------
void __fastcall TFreqForm::AnyChoose(TObject *Sender)
{  /*
 FreqStruct *F;

 CurrentFreq=RadioGroup1->ItemIndex;

 F=&FS[CurrentFreq];

 FCScrollBar->Position=F->FC/10;
 DRScrollBar->Position=F->DR*10;
 FOComboBox->ItemIndex=F->FO;
 RSComboBox->ItemIndex=F->FRS;
 FECComboBox->ItemIndex=F->FEC;
 CMComboBox->ItemIndex=F->CM;
 ANUpDown->Position=F->AN*10;
 */
}
//---------------------------------------------------------------------------
void __fastcall TFreqForm::AnyChange(TObject *Sender)
{  /*
 double SFEC[4]={1.0/2,2.0/3.0,3.0/4,7.0/8.0};
 FreqStruct *F;
 TLineSeries *S;
 //char String[5];

 F=&FS[CurrentFreq];


 F->IR=F->DR+F->DR*F->FO/15+F->DR*F->FRS*(9.0/8-1);
 F->IR=F->IR*F->AN;
 F->SR=F->IR/((F->CM+1)*SFEC[F->FEC]);
 F->Band=F->SR*1.2;
 F->DI=F->SR*1.4;
 F->LB=F->FC-F->DI/2;
 F->RB=F->FC+F->DI/2;

 IREdit->Text=F->IR;
 SREdit->Text=F->SR;
 DIEdit->Text=F->DI;
 LBEdit->Text=F->LB;
 RBEdit->Text=F->RB;
 BandEdit->Text=F->Band;

 switch(CurrentFreq)
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
 S->Clear();
 if(F->Enabled==true)
 {
  S->AddXY(F->LB,-20," ",clTeeColor);
  S->AddXY(F->FC-F->SR/2,-3," ",clTeeColor);
  S->AddXY(F->FC,-2,1+CurrentFreq,clTeeColor);
  S->AddXY(F->FC,-20," ",clTeeColor);
  S->AddXY(F->FC,-2," ",clTeeColor);
  S->AddXY(F->FC+F->SR/2,-3," ",clTeeColor);
  S->AddXY(F->RB,-20," ",clTeeColor);
 }   */
}

//--------------------------------------------------------
void __fastcall TFreqForm::FCScrollBarChange(TObject *Sender)
{                /*
 FS[CurrentFreq].FC=FCScrollBar->Position*10;
 FCEdit->Text=FS[CurrentFreq].FC;
 AnyChange(Sender); */
}
//---------------------------------------------------------------------------


void __fastcall TFreqForm::DRScrollBarChange(TObject *Sender)
{                     /*
 FS[CurrentFreq].DR=DRScrollBar->Position/10.0;
 DREdit->Text=FS[CurrentFreq].DR;
 AnyChange(Sender);     */
}
//---------------------------------------------------------------------------



void __fastcall TFreqForm::FOComboBoxChange(TObject *Sender)
{                         /*
 FS[CurrentFreq].FO=FOComboBox->ItemIndex;
 AnyChange(Sender);         */
}
//---------------------------------------------------------------------------

void __fastcall TFreqForm::RSComboBoxChange(TObject *Sender)
{                             /*
 FS[CurrentFreq].FRS=RSComboBox->ItemIndex;
 AnyChange(Sender);             */
}
//---------------------------------------------------------------------------

void __fastcall TFreqForm::CMComboBoxChange(TObject *Sender)
{                                 /*
 FS[CurrentFreq].CM=CMComboBox->ItemIndex;
 AnyChange(Sender);                 */
}
//---------------------------------------------------------------------------

void __fastcall TFreqForm::FECComboBoxChange(TObject *Sender)
{                                     /*
 FS[CurrentFreq].FEC=FECComboBox->ItemIndex;
 AnyChange(Sender);                     */
}
//---------------------------------------------------------------------------

void __fastcall TFreqForm::ExitItemClick(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TFreqForm::OpenItemClick(TObject *Sender)
{      /*
 TIniFile *IniFile;
 char Section[10];

 if(OpenDialog1->Execute())
 {
  IniFile=new TIniFile(OpenDialog1->FileName);
  try
  {
   TitleEdit->Text=IniFile->ReadString("Common","Title","");
   for(int i=0;i<MAX_FREQS;i++)
   {
    sprintf(Section,"Freq%d",i+1);
    strncpy(FS[i].Name,IniFile->ReadString(Section,"Name",i+1).c_str(),24);
    FS[i].FC=IniFile->ReadFloat(Section,"Частота",85000);
    FS[i].DR=IniFile->ReadFloat(Section,"Скорость",128);
    FS[i].FO=IniFile->ReadBool(Section,"Оверхед",1);
    FS[i].FRS=IniFile->ReadBool(Section,"Рид-Соломон",0);
    FS[i].AN=max(0.1,min(30.0,(double)IniFile->ReadFloat(Section,"Коэффициент",1)));
    FS[i].CM=max(0,min(3,IniFile->ReadInteger(Section,"Модуляция",1)));
    FS[i].FEC=max(0,min(2,IniFile->ReadInteger(Section,"Кодирование",0)));
    FS[i].Enabled=IniFile->ReadBool(Section,"Наличие",1);
    RadioGroup1->ItemIndex=i;
    AnyChoose(NULL);
   }
   CheckBox1->Checked=FS[0].Enabled;
   CheckBox2->Checked=FS[1].Enabled;
   CheckBox3->Checked=FS[2].Enabled;
   CheckBox4->Checked=FS[3].Enabled;
   CheckBox5->Checked=FS[4].Enabled;
   CheckBox6->Checked=FS[5].Enabled;
   CheckBox7->Checked=FS[6].Enabled;
   CheckBox8->Checked=FS[7].Enabled;
   CheckBox9->Checked=FS[8].Enabled;
   CheckBox10->Checked=FS[9].Enabled;
   Edit1->Text=FS[0].Name;
   Edit2->Text=FS[1].Name;
   Edit3->Text=FS[2].Name;
   Edit4->Text=FS[3].Name;
   Edit5->Text=FS[4].Name;
   Edit6->Text=FS[5].Name;
   Edit7->Text=FS[6].Name;
   Edit8->Text=FS[7].Name;
   Edit9->Text=FS[8].Name;
   Edit10->Text=FS[9].Name;
   RadioGroup1->ItemIndex=0;
   AnyChoose(NULL);
   delete IniFile;
  }
  catch(...)
  {
   delete IniFile;
  }
 }       */
}
//---------------------------------------------------------------------------


void __fastcall TFreqForm::SaveItemClick(TObject *Sender)
{          /*
 TIniFile *IniFile;
 char Section[10];

 if(SaveDialog1->Execute())
 {
  IniFile=new TIniFile(SaveDialog1->FileName);
  try
  {
   IniFile->WriteString("Common","Title",TitleEdit->Text);
   for(int i=0;i<MAX_FREQS;i++)
   {
    sprintf(Section,"Freq%d",i+1);
    IniFile->WriteString(Section,"Name",FS[i].Name);
    IniFile->WriteFloat(Section,"Частота",FS[i].FC);
    IniFile->WriteFloat(Section,"Скорость",FS[i].DR);
    IniFile->WriteBool(Section,"Оверхед",FS[i].FO);
    IniFile->WriteBool(Section,"Рид-Соломон",FS[i].FRS);
    IniFile->WriteFloat(Section,"Коэффициент",FS[i].AN);
    IniFile->WriteInteger(Section,"Модуляция",FS[i].CM);
    IniFile->WriteInteger(Section,"Кодирование",FS[i].FEC);
    IniFile->WriteBool(Section,"Наличие",FS[i].Enabled);
   }
   delete IniFile;
  }
  catch(...)
  {
   delete IniFile;
  }
 }           */
}
//---------------------------------------------------------------------------

void __fastcall TFreqForm::Edit1Change(TObject *Sender)
{
// strncpy(FS[0].Name,Edit1->Text.c_str(),24);
}
//---------------------------------------------------------------------------

void __fastcall TFreqForm::Edit2Change(TObject *Sender)
{
 //strncpy(FS[1].Name,Edit2->Text.c_str(),24);
}
//---------------------------------------------------------------------------

void __fastcall TFreqForm::Edit3Change(TObject *Sender)
{
 //strncpy(FS[2].Name,Edit3->Text.c_str(),24);
}
//---------------------------------------------------------------------------

void __fastcall TFreqForm::Edit4Change(TObject *Sender)
{
 //strncpy(FS[3].Name,Edit4->Text.c_str(),24);
}
//---------------------------------------------------------------------------

void __fastcall TFreqForm::Edit5Change(TObject *Sender)
{
 //strncpy(FS[4].Name,Edit5->Text.c_str(),24);
}
//---------------------------------------------------------------------------

void __fastcall TFreqForm::Edit6Change(TObject *Sender)
{
 //strncpy(FS[5].Name,Edit6->Text.c_str(),24);
}
//---------------------------------------------------------------------------

void __fastcall TFreqForm::Edit7Change(TObject *Sender)
{
 //strncpy(FS[6].Name,Edit7->Text.c_str(),24);
}
//---------------------------------------------------------------------------

void __fastcall TFreqForm::Edit8Change(TObject *Sender)
{
 //strncpy(FS[7].Name,Edit8->Text.c_str(),24);
}
//---------------------------------------------------------------------------

void __fastcall TFreqForm::Edit9Change(TObject *Sender)
{
 //strncpy(FS[8].Name,Edit9->Text.c_str(),24);
}
//---------------------------------------------------------------------------

void __fastcall TFreqForm::Edit10Change(TObject *Sender)
{
 //strncpy(FS[9].Name,Edit10->Text.c_str(),24);
}
//---------------------------------------------------------------------------

void __fastcall TFreqForm::Edit1Click(TObject *Sender)
{
 TEdit *Edit=(TEdit *)Sender;

 RadioGroup1->ItemIndex=Edit->Tag;
 AnyChoose(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TFreqForm::CheckBox1Click(TObject *Sender)
{
 TCheckBox *CheckBox=(TCheckBox *)Sender;

 //FS[CheckBox->Tag].Enabled=CheckBox->Checked;
 AnyChange(NULL);
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall TFreqForm::ANEdit1Change(TObject *Sender)
{
 //FS[CurrentFreq].AN=(ANEdit1->Text.ToDouble()/10.0);
 //ANEdit->Text=FS[CurrentFreq].AN;
}
//---------------------------------------------------------------------------

void __fastcall TFreqForm::ANEditChange(TObject *Sender)
{
 AnyChange(Sender);
}
//---------------------------------------------------------------------------



void __fastcall TFreqForm::FormClose(TObject *Sender, TCloseAction &Action)
{
 //delete FreqForm;
 //FreqForm=NULL;   
}
//---------------------------------------------------------------------------

void __fastcall TFreqForm::FreqScroolBarChange(TObject *Sender)
{ /*
 FreqEnd=100000;
 FreqBegin=min(98000,FreqBeginScrollBar->Position);
 FreqEnd=max(FreqBegin+1000,(double)FreqEndScrollBar->Position);
 FreqStep=FreqStepScrollBar->Position;
 FreqBeginEdit->Text=FreqBegin;
 FreqEndEdit->Text=FreqEnd;
 FreqStepEdit->Text=FreqStep;
 Chart1->BottomAxis->Maximum=100000;
 Chart1->BottomAxis->Minimum=FreqBegin;
 Chart1->BottomAxis->Maximum=FreqEnd;
 */
}
//---------------------------------------------------------------------------

void __fastcall TFreqForm::FPEditButtonClick(TObject *Sender)
{
 FPForm=new TFPForm(this);

 FPForm->fpsn=FPRadioGroup->ItemIndex;
 try
 {
  FPForm->ShowModal();
 }
 catch(...)
 {
  delete FPForm;
 }
 delete FPForm;
}
//---------------------------------------------------------------------------

void __fastcall TFreqForm::FPRadioGroupClick(TObject *Sender)
{
 for(int i=0;i<3;i++)
 {
  StringGrid1->Cells[1][i+1]=Dama->GetFPSBegin(FPRadioGroup->ItemIndex,i);
  StringGrid1->Cells[2][i+1]=Dama->GetFPSEnd(FPRadioGroup->ItemIndex,i);
 }
}
//---------------------------------------------------------------------------

