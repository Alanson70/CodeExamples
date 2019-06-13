//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DecEditFrameUnit.h"  
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
//#include "imm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDecEditFrame *DecEditFrame;
//---------------------------------------------------------------------------
__fastcall TDecEditFrame::TDecEditFrame(TComponent* Owner)
        : TFrame(Owner)
{     
 _locked=false;
 _digits=32;
 _sign=0;
 _value=0; 
 _maxValue=0;
 _minValue=0;
}
//---------------------------------------------------------------------------
void TDecEditFrame::Digits(int digits)
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
}
    
//---------------------------------------------------------------------------
void TDecEditFrame::Sign(int sign)
{
 _sign=sign;
 ShowValue();
}
//---------------------------------------------------------------------------
void TDecEditFrame::Value(long value)
{
 if(_locked==true) return;
 _locked=true;
 _value=value;
 //Type(_type);
 ShowValue();
 _locked=false;
}

//---------------------------------------------------------------------------
void __fastcall TDecEditFrame::DecEditChange(TObject *Sender)
{             
 if(_locked==true) return;
 _locked=true;
 if(OnValueChange) OnValueChange(this);
 _locked=false;
}
//---------------------------------------------------------------------------
void TDecEditFrame::ShowValue()
{
 char buffer[200];
 /*if(_sign==1)
  sprintf(buffer,"%ld",_value);
 else
  sprintf(buffer,"%lu",_value);
  */
 if(_sign==1)
 {
  if((_value&(1<<(_digits-1)))!=0) // is minus
  {
//   unsigned long cutValue=(long)(pow(2,_digits-1)-1);
   unsigned long value=(long)(pow(2,_digits)-1)+1-_value&((long)(pow(2,_digits-1)-1));
   sprintf(buffer,"-%lu",value);
  }
  else
  { 
   sprintf(buffer,"+%lu",_value);
  }


 }
 else
 {
  sprintf(buffer,"%lu",_value);
 }


 DecEdit->Text=buffer;
 DecEdit->SelStart=DecEdit->Text.Length();
}
//---------------------------------------------------------------------------
void __fastcall TDecEditFrame::DecEditKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
/*
 long value;
 if(DecEdit->SelLenght>0)
 {
  char buffer[20];
  sprintf(buffer,"%s",DecEdit->Text.c_str()+DecEdit->SelelLenght_value,newValue);
 }
  */
 int newValue=-3;
 char formatString[25];

 if(_sign==0) strcpy(formatString,"%lu");
 else         strcpy(formatString,"%ld");


 switch(Key)
 {
  case VK_BACK:
  case VK_DELETE: Key=0;newValue=-2;break;
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

  case VK_SUBTRACT  :
  case 189  :  if(_sign>0)  newValue=-1;
  default :    Key=0;break;
 }
 if(newValue<-2) return;

 char buffer[20];
 if(newValue==-2)
 {
  sprintf(buffer,formatString,_value);
  int pos=strlen(buffer)-1;
  if(pos<0) pos=0;
   buffer[pos]=0;
 }
 else
 if(newValue==-1)
 {
  //_value=_value^0x80000000;
  //if((_value&0x80000000)==0)
  _value=_value*(-1);
  sprintf(buffer,formatString,_value);
 }
 else
 {
  strcat(formatString,"%d");
  sprintf(buffer,formatString,_value,newValue);
 }
 double v=atof(buffer);
 if(TestValue(v)==false) return;

 _value=(unsigned long)v;

 ShowValue();
}

//---------------------------------------------------------------------------
bool TDecEditFrame::TestValue(double v)
{
 double maxV=(double)(unsigned long)0xFFFFFFFF;
 double minV=(double)(signed long)0x80000000;

 if(_sign==0) minV=0;
 else         maxV=(double)(unsigned long)0x7FFFFFFF;

 if(v>0)   if(v>maxV) return false;
 if(v<0)   if(v<minV) return false;

 unsigned long value=(unsigned long)v;
 unsigned long cutValue=(long)(pow(2,_digits)-1);
 if(value!=(value&cutValue)) return false;   

 if(_maxValue!=0)
  if(value>_maxValue) return false;

 return true;
}
//---------------------------------------------------------------------------

void __fastcall TDecEditFrame::DecEditClick(TObject *Sender)
{
 DecEdit->SelStart=DecEdit->Text.Length();
}
//---------------------------------------------------------------------------
void TDecEditFrame::InsertText(char *buffer)
{
 char buf[100];
 int c=0;

 // test value
 int first=0;
 if(buffer[0]=='-')  first=1;
 if(buffer[0]=='+')  first=1;
 for(int i=first;i<strlen(buffer);i++) if(isdigit(buffer[i])==0) return;

 // form new value

 for(int i=0;i<DecEdit->SelStart;i++) buf[c++]=DecEdit->Text.operator [](i+1);
 for(int i=0;i<strlen(buffer);i++) buf[c++]=buffer[i];
 for(int i=(DecEdit->SelStart+DecEdit->SelLength);i<DecEdit->Text.Length();i++) buf[c++]=DecEdit->Text.operator [](i+1);
 buf[c]=0;

 double v=atof(buf);

 if(TestValue(v)==false) return;

 _value=(unsigned long)v;

 ShowValue();
}
//---------------------------------------------------------------------------

