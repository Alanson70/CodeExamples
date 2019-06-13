//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ParamsFormUnit.h"
#include "OutputClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#include "Inifiles.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



TParamsForm *ParamsForm;
//---------------------------------------------------------------------------
__fastcall TParamsForm::TParamsForm(TComponent* Owner)
        : TForm(Owner)
{

}

//-------------------------------------------------------------------------

//---------------------------------------------------------------------------







//---------------------------------------------------------------------------


void __fastcall TParamsForm::StringEndOptionEditChange(TObject *Sender)
{
 //new var 8 byte
 TEdit *edit=(TEdit *)Sender;

 char s[25];
 s[0]=0;
 int start=edit->SelStart;
 int value;

 strncpy(s,edit->Text.c_str(),16);
 for(int i=0;i<16;i++)
 {
  value=(unsigned short)s[i];
  if(value==0) break;
  if(isdigit(value)!=0) continue;
  if(isxdigit(value)!=0) continue;
  for(int j=i;j<16;j++) s[j]=s[j+1];
  start--;
//  s[i]='0';
 }
 s[16]=0;

 edit->Text=s;

 if(start<(strlen(s)+1)) edit->SelStart=start;
 else                    edit->SelStart=0;

 /* old var - only 1 byte
 TEdit *edit=(TEdit *)Sender;

 char s[16];

 s[0]=0;
 int value;
 int start=edit->SelStart;

 strncpy(s,edit->Text.c_str(),2);
 sscanf(s,"%2X",&value);
 sprintf(s,"%2.2X",value);
 edit->Text=s;

 //start++;
 if(start<2) edit->SelStart=start;
 else        edit->SelStart=0;
 */
}
//---------------------------------------------------------------------------


void __fastcall TParamsForm::AdditionSendingOptionComboBoxChange(
      TObject *Sender)
{
 if(AdditionSendingOptionComboBox->ItemIndex==3)
 {
  StringEndSendingOptionEdit->Visible=true;
 }
 else
 {
  StringEndSendingOptionEdit->Visible=false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TParamsForm::AdditionReceivingOptionComboBoxChange(
      TObject *Sender)
{
 if(AdditionReceivingOptionComboBox->ItemIndex==3)
 {
  StringEndReceivingOptionEdit->Visible=true;
 }
 else
 {
  StringEndReceivingOptionEdit->Visible=false;
 }
}
//---------------------------------------------------------------------------

 /*
AnsiString TParamsForm::SendingAddition()
{
 char s[25];
 if(AdditionSendingOptionComboBox->ItemIndex==3)
 {
  int len=((StringEndSendingOptionEdit->Text.Length()+1)/2);
  StringToStruct(StringEndSendingOptionEdit->Text.c_str(),s,len);
  s[len]=0;
  return AnsiString(s);
 }
 else
  return AnsiString(termSetSendAdd[AdditionSendingOptionComboBox->ItemIndex]);
}
//---------------------------------------------------------------------------

AnsiString TParamsForm::ReceivingAddition()
{
 char s[25];
 if(AdditionReceivingOptionComboBox->ItemIndex==3)
 {
  int len=((StringEndReceivingOptionEdit->Text.Length()+1)/2);
  StringToStruct(StringEndReceivingOptionEdit->Text.c_str(),s,len);
  s[len]=0;
  return AnsiString(s);
 }
 else
  return AnsiString(termSetSendAdd[AdditionReceivingOptionComboBox->ItemIndex]);
}
*/
//---------------------------------------------------------------------------

