//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DateCalcFrameUnit.h"  
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "Functions.h" 
#include <DateUtils.hpp>  
#include <vcl\Clipbrd.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDateCalcFrame *DateCalcFrame;
//---------------------------------------------------------------------------
__fastcall TDateCalcFrame::TDateCalcFrame(TComponent* Owner)
        : TFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDateCalcFrame::PopupMenuItemClick(TObject *Sender)
{
 TMenuItem *item=(TMenuItem *)Sender;

 TControl *c=(TControl *)(((TPopupMenu *)(item->GetParentMenu()))->PopupComponent);
 TEdit *edit=NULL;
 if(c->InheritsFrom(__classid(TEdit))) edit=(TEdit *)c;
 else return;

 switch(item->Tag)
 {
  case 1 : // copy
  {
   char buffer[200];
   if(edit->SelLength>0) strncpy(buffer,edit->SelText.c_str(),199);
   else                  strncpy(buffer,edit->Text.c_str(),199);

   Clipboard()->SetTextBuf(buffer);
  }
  break;

  case 2 :  // paste
  {
   char buffer[100];
   strncpy(buffer,Clipboard()->AsText.c_str(),25);

   edit->Text=buffer;
  }
  break;

 }
}
//---------------------------------------------------------------------------
void __fastcall TDateCalcFrame::DateTimeStringEditChange(TObject *Sender)
{
 int day,mon,year,hour,min,sec;
 TDateTime dt;

 dt=DateTimeFromString(((TEdit *)Sender)->Text.c_str());

 if(((TEdit *)Sender)->Tag==0) _date1=dt;
 else                          _date2=dt;
}
//---------------------------------------------------------------------------
void __fastcall TDateCalcFrame::SumButtonClick(TObject *Sender)
{
 TDateTime dt;
 if(((TButton *)Sender)->Tag==0)
  dt=_date1+_date2;
 else
  dt=_date1-_date2;

 DateTimeStringEdit3->Text="0 дней и ";
 if(((double)dt)>=1.0)
 {
  //long cdt=(long)dt;
  //int years=0;
  //int mons=0;
  //int days=0;
  DateTimeStringEdit3->Text=AnsiString(dt.operator int())+AnsiString(" дн. и ");
 }
 AnsiString ts=dt.TimeString();
 DateTimeStringEdit3->Text=DateTimeStringEdit3->Text+ts;
}      
//---------------------------------------------------------------------------
TDateTime TDateCalcFrame::DateTimeFromString(char *text)
{
// int v1=0,v2=0,v3=0,v4=0,v5=0,v6=0;
 int day,mon,year,hour,min,sec;
 int v[6];
 int n=0;
 int timeOnly=false;
 unsigned i;

 if(!isdigit(text[0])) return 0;

 for(int i=0;i<6;i++) v[i]=0;

 for(i=0;i<strlen(text);i++)
 {
  if(n==6) break;
  for(;i<strlen(text);i++) if(isdigit(text[i]))  break;
  v[n++]=atoi(text+i);
  for(;i<strlen(text);i++) if(!isdigit(text[i])) break;
  if((text[i]==':') & (n<3)) timeOnly=true;
 }

 TDateTime dt;
 if(timeOnly==true)
 {
  hour=v[0];
  min=v[1];
  sec=v[2];
  dt=TDateTime(hour,min,sec,0);
 }
 else
 {
  year=v[2];
  mon=v[1];
  day=v[0];
  hour=v[3];
  min=v[4];
  sec=v[5];
  if(day==0 | mon==0) return 0;
  dt=TDateTime(year,mon,day)+TDateTime(hour,min,sec,0);
 }
 return dt;
}
//---------------------------------------------------------------------------@
