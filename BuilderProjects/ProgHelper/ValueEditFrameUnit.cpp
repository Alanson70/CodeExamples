//---------------------------------------------------------------------------

#include <vcl.h>  
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#pragma hdrstop

#include "ValueEditFrameUnit.h"
#include "Functions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TValueEditFrame *ValueEditFrame;
//---------------------------------------------------------------------------
__fastcall TValueEditFrame::TValueEditFrame(TComponent* Owner)
        : TFrame(Owner)
{
 _maxValue=0xFFFFFFFF;
 _maxPos=12;
} 
//---------------------------------------------------------------------------
void TValueEditFrame::Type(int type)
{
 _type=type;
 ShowValue();
}
//---------------------------------------------------------------------------
int TValueEditFrame::Type()
{
 return _type;
}
//---------------------------------------------------------------------------
void TValueEditFrame::Digits(unsigned int value)
{
 _digits=value;
 _maxValue=(long)(pow(2,value)-1);
 if(_value>_maxValue) _value=_maxValue;
 ShowValue();
}
//---------------------------------------------------------------------------
unsigned long TValueEditFrame::MaxValue()
{
 return _maxValue;
}
//---------------------------------------------------------------------------
void TValueEditFrame::Value(unsigned long value)
{
 _value=value;
 if(value>_maxValue) value=_maxValue; 
 ShowValue();
}
//---------------------------------------------------------------------------
unsigned long TValueEditFrame::Value()
{
 return _value;
}
//---------------------------------------------------------------------------
void __fastcall TValueEditFrame::EditChange(TObject *Sender)
{
 if(Edit->Tag==1) return;
 Edit->Tag=1;
 switch(_type)
 {
  case 0 :
   DecEdit();
  break;

  case 1 :
   HexEdit();
  break;

  case 2 :
   BinEdit();
  break;
 }  
 Edit->Tag=0;
} 
//---------------------------------------------------------------------------
void TValueEditFrame::ShowValue()
{
 switch(_type)
 {
  case 0 :
   Edit->Text=_value;
  break;

  case 1 :
  {
   char buffer[200];
   sprintf(buffer,"%*.*X",(_digits+3)/4,(_digits+3)/4,_value);
   //sprintf(buffer,"%4.4X",16,16,_value);
   Edit->Text=buffer;
  }
  break;

  case 2 :
   BinEdit();
  break;
 }
}
//---------------------------------------------------------------------------
void TValueEditFrame::DecEdit()
{
 int pos=Edit->SelStart;

 char buffer[25];

 strncpy(buffer,Edit->Text.c_str(),24);
 buffer[24]=0;
 int j=0;
 for(int i=0;i<strlen(buffer);i++)
 {
  if(isdigit(buffer[i])!=0) buffer[j++]=buffer[i];
 }
 buffer[j]=0;
 if(j!=0)
 {
  unsigned long value=atol(buffer);
  if(value<=_maxValue) _value=value;
  if(pos>strlen(buffer)) pos=strlen(buffer);
  ShowValue();
 }
 else
  Edit->Text=buffer;
 Edit->SelStart=pos;
}
//---------------------------------------------------------------------------
void TValueEditFrame::HexEdit()
{
 int pos=Edit->SelStart;

 char buffer[50];

 int maxPos=9;//_maxValue/8; (DigitsUpDown->Position+3)/4;
 strncpy(buffer,Edit->Text.c_str(),maxPos);
 buffer[maxPos]=0;
 //
 int j=0;
 maxPos=strlen(buffer);
 for(int i=0;i<maxPos;i++)
 {
  if(isxdigit(buffer[i])!=0) buffer[j++]=buffer[i];
 }
 buffer[j]=0;
 if(j!=0)
 {
  unsigned long value;
  sscanf(buffer,"%X",&value);
  if(value<=_maxValue) _value=value;
  //sprintf(buffer,"%X",_value);
  ShowValue();
 }
 else
 {
  Edit->Text="";
 }
 char *b=Edit->Text.c_str();
 if(pos>strlen(b)) pos=strlen(b);
 for(int i=0;i<strlen(b);i++) if(b[i]=='0') pos++;else break;


// else  Edit->Text=buffer;
 //if(pos>strlen(buffer)) pos=strlen(buffer);
 //for(int i=0;i<strlen(buffer);i++) if(buffer[i]=='0') pos--;
 Edit->SelStart=pos;

}
//---------------------------------------------------------------------------
void TValueEditFrame::BinEdit()
{
}
//---------------------------------------------------------------------------

void __fastcall TValueEditFrame::EditKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
 _pos=Edit->SelStart;
 
 int maxPos=_maxPos;
 int type=3;
 unsigned long value=_value;
 char buffer[25];
 int pos=_pos;

 memcpy(buffer,_buffer,25);

 switch(Key)
 {
  case VK_LBUTTON :
   _pos=Edit->SelStart;
  break;
  case VK_LEFT    : _pos--;
  break;
  case VK_RIGHT   : _pos++;
  break;
  case VK_BACK    : _pos--;
  break;
  case VK_END     : _pos=maxPos-1;
  break;
  case VK_HOME    : _pos=0;
  break;
  case VK_DELETE  : _pos--;
  break;

  case '0' :
  case '1' : type=2;break;

  case '2' :
  case '3' :
  case '4' :
  case '5' :
  case '6' :
  case '7' :
  case '8' :
  case '9' : type=0;break;

  case 'a' :
  case 'A' :
  case 'b' :
  case 'B' :
  case 'c' :
  case 'C' :
  case 'd' :
  case 'D' :
  case 'e' :
  case 'E' :
  case 'f' :
  case 'F' : type=1;break;
 }

 if(pos<0) pos=0;
 if(pos>maxPos) pos=maxPos;


 switch(_type)
 {
  case 0 :
  {
   if((type&0x1)!=0) break;
   for(int i=maxPos;i>pos;i--) buffer[i]=buffer[i-1];
   buffer[pos++]=Key;
   maxPos=MIN(24,MAX(pos,maxPos+1));
   buffer[maxPos]=0;
   value=atol(buffer);
   if(value<=_maxValue);
   {
    Edit->Text=value;
    Edit->SelStart=pos;
    memcpy(_buffer,buffer,25);
    _value=value;
    _maxPos=strlen(_buffer);
    _pos=pos;
   }
  }
  break;

  case 1 :
  {
   _buffer[_pos]=0;
   //char buffer[200];
   //sprintf(buffer,"%*.*X",_maxPos-1,_maxPos-1,_value);
   Edit->Text=buffer;
  }
  break;

  case 2 :
  break;

  default :
  Edit->SelStart=_pos;
  break;
 }
}
//---------------------------------------------------------------------------



