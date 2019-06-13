//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ValuesFrameUnit1.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ValueEditFrameUnit"
#pragma resource "*.dfm"
TValuesFrame1 *ValuesFrame1;
//---------------------------------------------------------------------------
__fastcall TValuesFrame1::TValuesFrame1(TComponent* Owner)
        : TFrame(Owner)
{
 ValueEditFrame1->Type(0);
}
//---------------------------------------------------------------------------
void TValuesFrame1::ShowValues()
{
 long cutValue=(long)(pow(2,DigitsUpDown->Position)-1);
 _value=_value & cutValue;

 DecEdit->Text=_value;
 char buffer[200];  
 sprintf(buffer,"%8.8X",_value);
 HexEdit->Text=buffer;
 int d=0,cpos=0;
 for(int i=sizeof(_value);i>0;i--)
 {
  int v=(_value>>((i-1)*8))&0xFF;
  for(int j=7;j>=0;j--)
  {
   if((32-DigitsUpDown->Position)<=d)
   {
    if((v&(1<<j))!=0) buffer[cpos]='1';
    else              buffer[cpos]='0';
   }
   else
   {
    buffer[cpos]=' ';
   }
   cpos++;
   d++;
  }
  buffer[cpos++]=' ';
 }
 buffer[cpos]=0;
 BinEdit->Text=buffer;


 switch(FormatComboBox->ItemIndex)
 {
  case 0 :
  Edit1->Text=_value;
  break;
  case 1 :
  {
   char buffer[200];
   sprintf(buffer,"%8.8X",_value);
   Edit1->Text=buffer;
  }
  break;
  case 2 :
  {
   int c=0;
   for(int i=sizeof(_value);i>0;i--)
   {
    int v=(_value>>((i-1)*8))&0xFF;
    for(int j=7;j>=0;j--)
    {
     if((v&(1<<j))!=0) buffer[c]='1';
     else              buffer[c]='0';
     c++;
    }
    buffer[c++]=' ';
   }
   buffer[c]=0;
   Edit1->Text=buffer;
  }
  break;
 }
}
//---------------------------------------------------------------------------
void __fastcall TValuesFrame1::DecEditChange(TObject *Sender)
{
 TCustomEdit *edit=(TCustomEdit *)Sender;
 if(edit->Tag==1) return;
 edit->Tag=1;
 int pos=edit->SelStart;

 //unsigned long long value=0;

 char buffer[25];

 strncpy(buffer,edit->Text.c_str(),24);
 buffer[24]=0;
 int j=0;
 for(int i=0;i<strlen(buffer);i++)
 {
  if(isdigit(buffer[i])!=0) buffer[j++]=buffer[i];
 }
 buffer[j]=0;
 if(j!=0)
 {
  _value=atol(buffer);
  if(pos>strlen(buffer)) pos=strlen(buffer);
  ShowValues();
 }
 edit->Text=buffer; 
 edit->SelStart=pos;
 edit->Tag=0;
}
//---------------------------------------------------------------------------

void __fastcall TValuesFrame1::HexEditChange(TObject *Sender)
{
 TEdit *edit=(TEdit *)Sender;
 if(edit->Tag==1) return;
 edit->Tag=1;

 int pos=edit->SelStart;

// unsigned long value=0;
 char buffer[50];
 int maxPos=(DigitsUpDown->Position+3)/4;

 strncpy(buffer,edit->Text.c_str(),maxPos);
 buffer[maxPos]=0;
 int j=0;
 for(int i=0;i<strlen(buffer);i++)
 {
  if(isxdigit(buffer[i])!=0) buffer[j++]=buffer[i];
 }
 buffer[j]=0;
 if(j!=0)
 {
  sscanf(buffer,"%X",&_value);
  sprintf(buffer,"%X",_value);
  ShowValues();
 }
 edit->Text=buffer;
 if(pos>strlen(buffer)) pos=strlen(buffer);
 edit->SelStart=pos;

 edit->Tag=0;
}
//---------------------------------------------------------------------------
void __fastcall TValuesFrame1::Edit1Change(TObject *Sender)
{
 switch(FormatComboBox->ItemIndex)
 {
  case 0 :
  //DecEditChange(Sender);
  break;
  case 1 : 
  //HexEditChange(Sender);
  break;
  case 2 :
  //BinEditChange(Sender);
  break;
 }
}
//---------------------------------------------------------------------------


void __fastcall TValuesFrame1::FormatComboBoxChange(TObject *Sender)
{
 this->ShowValues();
 ValueEditFrame1->Type(FormatComboBox->ItemIndex);
}
//---------------------------------------------------------------------------


void __fastcall TValuesFrame1::DigitsEditChange(TObject *Sender)
{ 
 this->ShowValues();
 ValueEditFrame1->Digits(DigitsUpDown->Position);
}
//---------------------------------------------------------------------------

