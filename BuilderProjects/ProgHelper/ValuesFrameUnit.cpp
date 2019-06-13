//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ValuesFrameUnit.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ValueEditFrameUnit"
#pragma link "BinEditFrameUnit"
#pragma link "DecEditFrameUnit"
#pragma link "HexEditFrameUnit"
#pragma resource "*.dfm"
TValuesFrame *ValuesFrame;
//---------------------------------------------------------------------------
__fastcall TValuesFrame::TValuesFrame(TComponent* Owner)
        : TFrame(Owner)
{
 _digits=32;

 DecFrame1->Value(0);
 HexFrame1->Value(0);
 BinFrame1->Value(0);

 DecFrame1->OnValueChange=OnValue1Change;
 HexFrame1->OnValueChange=OnValue1Change;
 BinFrame1->OnValueChange=OnValue1Change;

 DecFrame2->Value(0);
 HexFrame2->Value(0);
 BinFrame2->Value(0);

 DecFrame2->OnValueChange=OnValue2Change;
 HexFrame2->OnValueChange=OnValue2Change;
 BinFrame2->OnValueChange=OnValue2Change;

 DecFrame3->Value(0);
 HexFrame3->Value(0);
 BinFrame3->Value(0);

 DecFrame3->OnValueChange=OnValue3Change;
 HexFrame3->OnValueChange=OnValue3Change;
 BinFrame3->OnValueChange=OnValue3Change;
}
//---------------------------------------------------------------------------
void __fastcall TValuesFrame::OnValue1Change(TObject *Sender)
{
 if(Sender->InheritsFrom(__classid(TDecEditFrame)))
  _value1=((TDecEditFrame *)Sender)->_value;
 else
 if(Sender->InheritsFrom(__classid(THexEditFrame)))
  _value1=((THexEditFrame *)Sender)->_value;
 else
 if(Sender->InheritsFrom(__classid(TBinEditFrame)))
  _value1=((TBinEditFrame *)Sender)->_value;

 BinFrame1->Value(_value1);
 DecFrame1->Value(_value1);
 HexFrame1->Value(_value1);
}
//---------------------------------------------------------------------------
void __fastcall TValuesFrame::OnValue2Change(TObject *Sender)
{
 if(Sender->InheritsFrom(__classid(TDecEditFrame)))
  _value2=((TDecEditFrame *)Sender)->_value;
 else
 if(Sender->InheritsFrom(__classid(THexEditFrame)))
  _value2=((THexEditFrame *)Sender)->_value;
 else
 if(Sender->InheritsFrom(__classid(TBinEditFrame)))
  _value2=((TBinEditFrame *)Sender)->_value;

 BinFrame2->Value(_value2);
 DecFrame2->Value(_value2);
 HexFrame2->Value(_value2);
}
//---------------------------------------------------------------------------
void __fastcall TValuesFrame::OnValue3Change(TObject *Sender)
{
 if(Sender->InheritsFrom(__classid(TDecEditFrame)))
  _value3=((TDecEditFrame *)Sender)->_value;
 else
 if(Sender->InheritsFrom(__classid(THexEditFrame)))
  _value3=((THexEditFrame *)Sender)->_value;
 else
 if(Sender->InheritsFrom(__classid(TBinEditFrame)))
  _value3=((TBinEditFrame *)Sender)->_value;

 BinFrame3->Value(_value3);
 DecFrame3->Value(_value3);
 HexFrame3->Value(_value3);
}
//---------------------------------------------------------------------------
void TValuesFrame::ShowValues()
{
 /*
 long cutValue=(long)(pow(2,DigitsUpDown->Position)-1);
 _value1=_value1 & cutValue;

 DecEdit->Text=_value1;
 char buffer[200];  
 sprintf(buffer,"%8.8X",_value1);
 HexEdit->Text=buffer;
 int d=0,cpos=0;
 for(int i=sizeof(_value1);i>0;i--)
 {
  int v=(_value1>>((i-1)*8))&0xFF;
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
  Edit1->Text=_value1;
  break;
  case 1 :
  {
   char buffer[200];
   sprintf(buffer,"%8.8X",_value1);
   Edit1->Text=buffer;
  }
  break;
  case 2 :
  {
   int c=0;
   for(int i=sizeof(_value1);i>0;i--)
   {
    int v=(_value1>>((i-1)*8))&0xFF;
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
 */
}
//---------------------------------------------------------------------------



void __fastcall TValuesFrame::FormatComboBoxChange(TObject *Sender)
{
 /*this->ShowValues();
 ValueEditFrame1->Type(FormatComboBox->ItemIndex);
 BinFrame->Type(FormatComboBox->ItemIndex);
 */
}
//---------------------------------------------------------------------------


void __fastcall TValuesFrame::DigitsEditChange(TObject *Sender)
{
 int digits=DigitsUpDown->Position;
 DecFrame1->Digits(digits);
 HexFrame1->Digits(digits);
 BinFrame1->Digits(digits); 
 DecFrame2->Digits(digits);
 HexFrame2->Digits(digits);
 BinFrame2->Digits(digits);
 DecFrame3->Digits(digits);
 HexFrame3->Digits(digits);
 BinFrame3->Digits(digits);

 _digits=digits;
 /*this->ShowValues();
 ValueEditFrame1->Digits(DigitsUpDown->Position);
 */
}
//---------------------------------------------------------------------------



void __fastcall TValuesFrame::OperationButtonClick(TObject *Sender)
{
 switch(((TControl *)Sender)->Tag)
 {
  case 0 :  _value3=_value1+_value2;  break;
  case 1 :  _value3=_value1-_value2;  break;
  case 2 :  _value3=_value1*_value2;  break;
  case 3 :  if(_value2==0) _value3=0; else _value3=_value1/_value2;  break;
  case 4 :  _value3=_value1&_value2;  break;
  case 5 :  _value3=_value1|_value2;  break;
  case 6 :  _value3=_value1^_value2;  break;
//  case 7 :  _value3=_value1+_value2;  break;
  default: return;
 }
 unsigned long cutValue=(long)(pow(2,_digits)-1);
 _value3=_value3&cutValue;
 BinFrame3->Value(_value3);
 DecFrame3->Value(_value3);
 HexFrame3->Value(_value3);
}
//---------------------------------------------------------------------------

void __fastcall TValuesFrame::ResultButtonClick(TObject *Sender)
{
 switch(((TControl *)Sender)->Tag)
 {
  case 0 :  _value3=sqrt(_value3);  break;
  case 1 :  _value3=_value3*_value3;  break;
  case 2 :  _value3=_value3<<1;  break;
  case 3 :  _value3=_value3>>1;  break;
  case 4 :  _value3=~_value3;  break;
  default: return;
 }        
 unsigned long cutValue=(long)(pow(2,_digits)-1);
 _value3=_value3&cutValue;
 BinFrame3->Value(_value3);
 DecFrame3->Value(_value3);
 HexFrame3->Value(_value3);
}
//---------------------------------------------------------------------------

void __fastcall TValuesFrame::SignComboBoxChange(TObject *Sender)
{
 DecFrame1->Sign(SignComboBox->ItemIndex);
 DecFrame2->Sign(SignComboBox->ItemIndex);
 DecFrame3->Sign(SignComboBox->ItemIndex); 
 HexFrame1->Sign(SignComboBox->ItemIndex);
 HexFrame2->Sign(SignComboBox->ItemIndex);
 HexFrame3->Sign(SignComboBox->ItemIndex);
 BinFrame1->Sign(SignComboBox->ItemIndex);
 BinFrame2->Sign(SignComboBox->ItemIndex);
 BinFrame3->Sign(SignComboBox->ItemIndex);
}
//---------------------------------------------------------------------------
#include <vcl\Clipbrd.hpp>

void __fastcall TValuesFrame::PopupMenuItemClick(TObject *Sender)
{
 TMenuItem *item=(TMenuItem *)Sender;
 TControl *c=(TControl *)PopupMenu1->PopupComponent;
 TMemo *memo=NULL;
 if(c->InheritsFrom(__classid(TMemo))) memo=(TMemo *)c;
 else return;

 switch(item->Tag)
 {
  case 0 :
  switch(c->Tag)
  {
   case 0 :  // zeroize
   DecFrame1->Value(0);
   HexFrame1->Value(0);
   BinFrame1->Value(0);
   break;
   case 1 :
   DecFrame2->Value(0);
   HexFrame2->Value(0);
   BinFrame2->Value(0);
   break;
   case 2 :
   DecFrame3->Value(0);
   HexFrame3->Value(0);
   BinFrame3->Value(0);
   break;
  }
  break;

  case 1 : // copy
  {
   char buffer[200];
   if(memo->SelLength>0) strncpy(buffer,memo->SelText.c_str(),199);
   else                  strncpy(buffer,memo->Text.c_str(),199);

   Clipboard()->SetTextBuf(buffer);
  }
  break;

  case 2 : // paste
  {
   char buffer[100];

   strncpy(buffer,Clipboard()->AsText.c_str(),25);
   if(c->Parent->InheritsFrom(__classid(TBinEditFrame)))
   {
    ((TBinEditFrame *)c->Parent)->InsertText(buffer);
   }
   else
   if(c->Parent->InheritsFrom(__classid(THexEditFrame)))
   {          
    ((THexEditFrame *)c->Parent)->InsertText(buffer);
   }
   else
   if(c->Parent->InheritsFrom(__classid(TDecEditFrame)))
   {
    ((TDecEditFrame *)c->Parent)->InsertText(buffer);
   }
  }


  break;
 }
}
//---------------------------------------------------------------------------

void __fastcall TValuesFrame::PopupMenu1Popup(TObject *Sender)
{
 TControl *c=(TControl *)PopupMenu1->PopupComponent;
 if(c->Parent->InheritsFrom(__classid(TBinEditFrame)))
  PasteMenuItem->Enabled=false;
 else
  PasteMenuItem->Enabled=true;
}
//---------------------------------------------------------------------------

