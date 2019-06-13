//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BinEditFrameUnit.h" 
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBinEditFrame *BinEditFrame;
//---------------------------------------------------------------------------
__fastcall TBinEditFrame::TBinEditFrame(TComponent* Owner)
        : TFrame(Owner)
{
 _locked=false;
 _digits=32;
 _value=0;
 _pos=0;
 _sign=0;
 Value(0);
}     
//---------------------------------------------------------------------------
void TBinEditFrame::Sign(int sign)
{
 _sign=sign;
 ShowValue();
}
//---------------------------------------------------------------------------
void TBinEditFrame::Digits(int digits)
{

 // adding minus if it needs
 if(_sign==1)
  if((_value&(1<<(_digits-1)))!=0) // is minus
  {
   _value|=(1<<(_digits-1));
   _value|=(1<<(digits-1));
  }

 _digits=digits;

 // cutting
 unsigned long cutValue=(long)(pow(2,_digits)-1);
 _value=_value & cutValue;

 
 BinEdit->MaxLength=_digits;
 if(_digits>24) BinEdit->MaxLength++;
 if(_digits>16) BinEdit->MaxLength++;
 if(_digits>8)  BinEdit->MaxLength++;

 ShowValue();
}
//---------------------------------------------------------------------------
void TBinEditFrame::Value(long value)
{
 if(_locked==true) return;
 _locked=true;
 _value=value;
 //Type(_type);
 ShowValue();   
 _locked=false;
}   
//---------------------------------------------------------------------------

void __fastcall TBinEditFrame::BinEditChange(TObject *Sender)
{                
 if(_locked==true) return;
 _locked=true;
 if(OnValueChange) OnValueChange(this);
 _locked=false;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TBinEditFrame::ShowValue()
{
 int c=0;
 char buffer[100];

 /*for(int i=sizeof(_value);i>0;i--)
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
 buffer[c-1]=0;
 */
 /*for(int i=32;i>_digits;i--)
 {
  buffer[c++]=' ';
 } */

 for(int i=_digits;i>0;i--)
 {
  if(((i&0x7)==0x0)&(i!=_digits))  buffer[c++]=' ';
  if((_value&(1<<(i-1)))!=0)      buffer[c]='1';
  else                            buffer[c]='0';
  c++;
 }
 buffer[c]=0;

 int pos=BinEdit->SelStart;
 BinEdit->Text=buffer;
 BinEdit->SelStart=pos;


 
}
//---------------------------------------------------------------------------

void __fastcall TBinEditFrame::BinEditKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
 int pos=BinEdit->SelStart;
 int newValue=-1;
 switch(Key)
 {
  case VK_BACK:  Key=VK_LEFT;
  break;
  case VK_DELETE: Key=0;
  case '0'  :
  newValue=0;
  break;
  case VK_INSERT: Key=0;
  case '1' :
  newValue=1;
  break;
  default:    break;
 }

 pos=(BinEdit->MaxLength-pos)-1;


 if(newValue>=0)
 {
  if(pos==-1) return;
  if(pos==8) return;
  if(pos==17) return;
  if(pos==26) return;

  if(pos>26) pos--;
  if(pos>17) pos--;
  if(pos>8)  pos--;


  long x=(0x1<<pos);

  if(newValue==0) _value=_value&(~x);
  else            _value=_value|x;
  ShowValue();
 }


// BinEdit->SelStart=pos;
}
//---------------------------------------------------------------------------
void TBinEditFrame::InsertText(char *buffer)
{
}
//---------------------------------------------------------------------------

