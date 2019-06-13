//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AUGridUnit.h"
#include "QR2Unit.h"
#include "CloseUnit.h"
#include "UgolAzimut.h"

#include <stdlib.h>
#include <algorithm>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAUGridForm *AUGridForm;
//---------------------------------------------------------------------------
__fastcall TAUGridForm::TAUGridForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
AnsiString AUGridText[7]=
{
 "Наименование",
 "Долгота КА",
 "Долгота ЗС",
 "Широта ЗС",
 "Азимут",
 "Угол места",
 "Примечание"
};

#include "inifiles.hpp"

void __fastcall TAUGridForm::FormCreate(TObject *Sender)
{
 UAForm=new TUAForm(this);
 RForm2=new TRForm2(this);
 CloseForm=new TCloseForm(this);

 ChangeFlag=false;
 for(int j=0;j<7;j++)
 {
  Grid1->Cells[j][0]=AUGridText[j];
 }
 LoadFromIniFile();
}
//---------------------------------------------------------------------------
void __fastcall TAUGridForm::LoadFromIniFile()
{
 int Count;
 //AnsiString FileName;
 AnsiString Item;
 AnsiString Section;
 TIniFile *IniFile;

 FileName=GetCurrentDir();
 if(FileName[1]=='A') FileName="A:\\AUGrid.ini";
 else  FileName=GetCurrentDir()+"\\AUGrid.ini";

 IniFile=new TIniFile(FileName);
 try
 {
  Count=IniFile->ReadInteger("Common","Count",0);
  Grid1->RowCount=Count+1;
  for(int i=1;i<(Count+1);i++)
  {
   //if(i>=Grid1->RowCount) Grid1->RowCount++;
   Section="Unit"+AnsiString(i);
   Grid1->Cells[0][i]=IniFile->ReadString(Section,"Name",Section);
   Grid1->Cells[1][i]=IniFile->ReadString(Section,"DolKA","0");
   Grid1->Cells[2][i]=IniFile->ReadString(Section,"Dol","0");
   Grid1->Cells[3][i]=IniFile->ReadString(Section,"Shir","0");
   Grid1->Cells[4][i]=IniFile->ReadString(Section,"Azimut","0");
   Grid1->Cells[5][i]=IniFile->ReadString(Section,"Ugol","0");
   Grid1->Cells[6][i]=IniFile->ReadString(Section,"Comment","");
  }
  delete IniFile;
 }
 catch(...)
 {
  delete IniFile;
 }
}
//---------------------------------------------------------------------------
void __fastcall TAUGridForm::SaveToIniFile()
{
 //AnsiString FileName;
 AnsiString Item;
 AnsiString Section;
 TIniFile *IniFile;
 //FileName=GetCurrentDir()+"\\AUGrid.ini";

 IniFile=new TIniFile(FileName);
 try
 {
  IniFile->WriteInteger("Common","Count",Grid1->RowCount-1);
  for(int i=1;i<Grid1->RowCount;i++)
  {
   Section="Unit"+AnsiString(i);
   IniFile->WriteString(Section,"Name",Grid1->Cells[0][i]);
   IniFile->WriteString(Section,"DolKA",Grid1->Cells[1][i]);
   IniFile->WriteString(Section,"Dol",Grid1->Cells[2][i]);
   IniFile->WriteString(Section,"Shir",Grid1->Cells[3][i]);
   IniFile->WriteString(Section,"Azimut",Grid1->Cells[4][i]);
   IniFile->WriteString(Section,"Ugol",Grid1->Cells[5][i]);
   IniFile->WriteString(Section,"Comment",Grid1->Cells[6][i]);
  }
  delete IniFile;
 }
 catch(...)
 {
  delete IniFile;
 }
}
//---------------------------------------------------------------------------


void __fastcall TAUGridForm::AddItemClick(TObject *Sender)
{
 if(Grid1->Row==0) Grid1->Row=1;
 UAForm->PosFlag=0;
 UAForm->ShowModal();
 FormChange();
}
//---------------------------------------------------------------------------

void __fastcall TAUGridForm::ChangeItemClick(TObject *Sender)
{
 if(Grid1->Row==0) Grid1->Row=1;
 UAForm->PosFlag=1;
 UAForm->ShowModal();
 FormChange();
}
//---------------------------------------------------------------------------
void __fastcall TAUGridForm::DeleteItemClick(TObject *Sender)
{
 if(Grid1->Row==0) Grid1->Row=1;
 UAForm->PosFlag=2;
 UAForm->ShowModal();
 FormChange();
}
//---------------------------------------------------------------------------
void __fastcall TAUGridForm::CloseItemClick(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TAUGridForm::FormChange()
{
 AUGridForm->Height=std::min(50+19*16,50+19*(Grid1->RowCount-1));
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TAUGridForm::PrintItemClick(TObject *Sender)
{
 if(Grid1->Row==0) Grid1->Row=1;
 RForm2->ShowModal();

}
//---------------------------------------------------------------------------

void __fastcall TAUGridForm::FormShow(TObject *Sender)
{
 AUGridForm->Caption=FileName;
 FormChange();
}
//---------------------------------------------------------------------------

void __fastcall TAUGridForm::SaveItemClick(TObject *Sender)
{
 SaveToIniFile();
}
//---------------------------------------------------------------------------


void __fastcall TAUGridForm::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
 CloseFlag=true;
 if(ChangeFlag==true)
   CloseForm->ShowModal();

 if(ChangeFlag==true)
  if(CloseFlag==true)  { SaveToIniFile();CanClose=true; }
  else                 CanClose=false;
 else
  if(CloseFlag==true)  CanClose=true;
  else                 CanClose=false;
}
//---------------------------------------------------------------------------

void __fastcall TAUGridForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 delete UAForm;
 delete CloseForm;
 delete RForm2;   
}
//---------------------------------------------------------------------------

