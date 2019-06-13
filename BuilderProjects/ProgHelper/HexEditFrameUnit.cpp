//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HexEditFrameUnit.h"  
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THexEditFrame *HexEditFrame;
//---------------------------------------------------------------------------
__fastcall THexEditFrame::THexEditFrame(TComponent* Owner)
        : TFrame(Owner)
{
 _locked=false;
 _digits=32;
 _value=0;  
 _sign=0;
 _maxValue=0;
 _minValue=0;
}       
//---------------------------------------------------------------------------
void THexEditFrame::Sign(int sign)
{
 _sign=sign;
 ShowValue();
}
//---------------------------------------------------------------------------
void THexEditFrame::Digits(int digits)
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
 
 HexEdit->MaxLength=((_digits-1)/4)+1;
}
//---------------------------------------------------------------------------
void THexEditFrame::Value(long value)
{
 if(_locked==true) return;
 _locked=true;
 _value=value;
 //Type(_type);
 ShowValue();   
 _locked=false;
}    
//---------------------------------------------------------------------------
void THexEditFrame::ShowValue()
{
 char buffer[200];
 char format[20];
// sprintf(format,);
 sprintf(buffer,"%*.*X",HexEdit->MaxLength,HexEdit->MaxLength,_value&((long)(pow(2,_digits)-1)));
 int pos=HexEdit->SelStart;
 HexEdit->Text=buffer;
 HexEdit->SelStart=pos;
}
//---------------------------------------------------------------------------
void __fastcall THexEditFrame::HexEditChange(TObject *Sender)
{               
 if(_locked==true) return;
 _locked=true;
 if(OnValueChange)  OnValueChange(this);
 _locked=false;
}
//---------------------------------------------------------------------------

void __fastcall THexEditFrame::HexEditKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
 int pos=HexEdit->SelStart;
 int newValue=-1;
 switch(Key)
 {
  case VK_BACK:  Key=VK_LEFT;
  break;
  case VK_DELETE: Key=0;
  case '0'  :  newValue=0;  break; 
  case '1'  :  newValue=1;  break;
  case '2'  :  newValue=2;  break;
  case '3'  :  newValue=3;  break;
  case '4'  :  newValue=4;  break;
  case '5'  :  newValue=5;  break;
  case '6'  :  newValue=6;  break;
  case '7'  :  newValue=7;  break;
  case '8'  :  newValue=8;  break;
  case '9'  :  newValue=9;  break;
  case 'A'  :
  case 'a'  :  newValue=0xa;Key='A';break;
  case 'B'  :
  case 'b'  :  newValue=0xb;Key='B';break;
  case 'C'  :
  case 'c'  :  newValue=0xc;Key='C';break;
  case 'D'  :
  case 'd'  :  newValue=0xd;Key='D';break;
  case 'E'  :
  case 'e'  :  newValue=0xe;Key='E';break;
  case 'F'  :
  case 'f'  :  newValue=0xf;Key='F';break;

  default:    break;
 }
 pos=(HexEdit->MaxLength-pos)-1;
// if(pos>7) return;
// pos++;
 if(newValue>=0)
 {
  long x=(((long)0xF)<<(pos*4));

  long value=_value&(~x);

  value=value|(newValue<<(pos*4));

  if(_maxValue!=0)
   if(value>_maxValue) return;//value=_maxValue;
  if(_minValue!=0)
   if(value<_minValue) return;//value=_maxValue;
   

  unsigned long cutValue=(long)(pow(2,_digits)-1);
  if(value==(value&cutValue)) _value=value;
  ShowValue();
 }
}  
//---------------------------------------------------------------------------
void THexEditFrame::InsertText(char *buffer)
{
 // test input
 for(int i=0;i<strlen(buffer);i++) if(isxdigit(buffer[i])==0) return;

 int diff=HexEdit->MaxLength-((HexEdit->Text.Length()-HexEdit->SelText.Length())+strlen(buffer));
 if(diff<0) return;


 char buf[100];
 int c=0;
 for(int i=0;i<diff;i++) buf[c++]='0';

 for(int i=0;i<HexEdit->SelStart;i++) buf[c++]=HexEdit->Text.operator [](i+1);
 for(int i=0;i<strlen(buffer);i++) buf[c++]=buffer[i];
 for(int i=(HexEdit->SelStart+HexEdit->SelLength);i<HexEdit->Text.Length();i++) buf[c++]=HexEdit->Text.operator [](i+1);
 buf[c]=0;
 long value;

 sscanf(buf,"%X",&value);   

 if(_maxValue!=0)
  if(value>_maxValue) value=_maxValue;

 unsigned long cutValue=(long)(pow(2,_digits)-1);
 if(value==(value&cutValue)) _value=value;
 ShowValue();

}
//---------------------------------------------------------------------------

