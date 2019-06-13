//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DatesFrameUnit.h" 
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "Functions.h"
#include <DateUtils.hpp>
#include "ChooseTimeFormUnit.h"
#include "ChooseDateFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "HexEditFrameUnit"
#pragma resource "*.dfm"
TDatesFrame *DatesFrame;
//---------------------------------------------------------------------------
__fastcall TDatesFrame::TDatesFrame(TComponent* Owner)
        : TFrame(Owner)
{  
 _dt=Now();
 ShowDateTime();
 //DosHexEditFrame->_maxValue=4288610304L;
 //DosHexEditFrame->_minValue=2162688L;
 //WinHexEditFrame->OnValueChange=OnWinHexChange;
 //WinHexEditFrame1->OnValueChange=OnWinHexChange; 
 DosHexEditFrame->OnValueChange=OnDosHexChange;
 LinuxHexEditFrame->OnValueChange=OnLinuxHexChange;
}

//---------------------------------------------------------------------------
union
{
 double dv;
 struct
 {
  long   l1;
  long   l2; 
 }l;
 char s[8];
 long long ll;
}dtt;
//---------------------------------------------------------------------------
void TDatesFrame::ShowDateTime()
{
 DateTimeStringEdit->Tag=1;

 DateTimeStringEdit->Text=_dt.DateTimeString();
 WindowsEdit->Text=(double)_dt;
 dtt.dv=_dt;
 char buffer[100];
 sprintf(buffer,"%8.8X%8.8X",dtt.l.l2,dtt.l.l1);
 WindowsHexEdit->Text=buffer;
 //WinHexEditFrame->Value(dtt.l.l2);
 //WinHexEditFrame1->Value(dtt.l.l1);

 unsigned long t=DateTimeFromAscii(DateTimeStringEdit->Text.c_str(),1970);
 LinuxEdit->Text=AnsiString(t);
 //sprintf(buffer,"%8.8X",t);
 LinuxHexEditFrame->Value(t);

 t=DateTimeFromAscii(DateTimeStringEdit->Text.c_str(),1980);
 //t=DateTimeToFileDate(_dt);
 DosEdit->Text=AnsiString(t);
 //sprintf(buffer,"%8.8X",t);
 DosHexEditFrame->Value(t);


 DateTimeStringEdit->Tag=0;
}
//---------------------------------------------------------------------------
void __fastcall TDatesFrame::NowButtonClick(TObject *Sender)
{
 _dt=Now();
 ShowDateTime();
}
//---------------------------------------------------------------------------
void __fastcall TDatesFrame::WindowsEditChange(TObject *Sender)
{
 TEdit *edit=(TEdit *)Sender;

 if(DateTimeStringEdit->Tag==1) return;
 if(edit->Tag==1) return;
 edit->Tag=1;

 char buffer[25];
 int pos=edit->SelStart;

 strncpy(buffer,edit->Text.c_str(),24);
 buffer[24]=0;
 int j=0;
 int del=0;
 int count=strlen(buffer);
 for(int i=0;i<count;i++)
 {
  if(buffer[i]=='.') buffer[i]==',';
  if(del==0)
  {
   if(buffer[i]==',')
   {
    del=j;
    buffer[j++]=buffer[i];
    continue;
   }
   if(i>6) continue;
  }
  if(isdigit(buffer[i])!=0) buffer[j++]=buffer[i];
 }
 buffer[j]=0;
 //if(del==(j-1)) buffer[--j]=0;
 if(j!=0)
 {
  _dt=TDateTime(AnsiString(buffer).ToDouble());
  ShowDateTime();
  if(pos>strlen(buffer)) pos=strlen(buffer);
 }
 edit->Text=buffer;
 edit->SelStart=pos;
 edit->Tag=0;
}
//---------------------------------------------------------------------------
void __fastcall TDatesFrame::DosEditChange(TObject *Sender)
{
 TEdit *edit=(TEdit *)Sender;

 if(DateTimeStringEdit->Tag==1) return;
 if(edit->Tag==1) return;
 edit->Tag=1;

 char buffer[25];
 int pos=edit->SelStart;

 strncpy(buffer,edit->Text.c_str(),10);
 buffer[10]=0;
 int j=0;
 int count=strlen(buffer);

 for(int i=0;i<count;i++)
 {
  if(isdigit(buffer[i])!=0) buffer[j++]=buffer[i];
 }

 buffer[j]=0;
 if(j!=0)
 {
  long t=atol(buffer);
  //if((t>=2162688)&(t<=4288610304))    // biostime  12/31/2107
  {
   _dt=FileDateToDateTime(t);
   ShowDateTime();
   if(pos>strlen(buffer)) pos=strlen(buffer);
  }
 }
 edit->Text=buffer;
 edit->SelStart=pos;
 edit->Tag=0;
}
//---------------------------------------------------------------------------
void __fastcall TDatesFrame::LinuxEditChange(TObject *Sender)
{
 TEdit *edit=(TEdit *)Sender;

 if(DateTimeStringEdit->Tag==1) return;
 if(edit->Tag==1) return;
 edit->Tag=1;

 char buffer[25];
 int pos=edit->SelStart;

 strncpy(buffer,edit->Text.c_str(),10);
 buffer[10]=0;
 int j=0;
 int count=strlen(buffer);
 for(int i=0;i<count;i++)
 {
  if(isdigit(buffer[i])!=0) buffer[j++]=buffer[i];
 }
 buffer[j]=0;
 if(j!=0)
 {
  //_dt=UnixToDateTime(atol(buffer));
  unsigned long t=atol(buffer);

  unsigned int days=t/(3600*24);
  unsigned int secs=t-(days*(3600*24));
  unsigned int hour=secs/3600;
  unsigned int min=secs/60-hour*60;
  secs=secs-(hour*3600+min*60);

  _dt=(double)((double)TDateTime(1970,1,1)+TDateTime((double)days)+(double)TDateTime(hour,min,secs,0));


  ShowDateTime();
  if(pos>strlen(buffer)) pos=strlen(buffer);
 }
 edit->Text=buffer;
 edit->SelStart=pos;
 edit->Tag=0;
}     
//---------------------------------------------------------------------------
void __fastcall TDatesFrame::OnWinHexChange(TObject *Sender)
{
 
}
//---------------------------------------------------------------------------
void __fastcall TDatesFrame::OnDosHexChange(TObject *Sender)
{
 unsigned long t=DosHexEditFrame->_value;
 /*if((t>=2162688)&(t<=4288610304))    // biostime  12/31/2107
 {
  _dt=FileDateToDateTime(t);
 }
 */
 unsigned int days=t/(3600*24);
 unsigned int secs=t-(days*(3600*24));
 unsigned int hour=secs/3600;
 unsigned int min=secs/60-hour*60;
 secs=secs-(hour*3600+min*60);

 _dt=(double)((double)TDateTime(1980,1,1)+TDateTime((double)days)+(double)TDateTime(hour,min,secs,0));

 ShowDateTime();
}
//---------------------------------------------------------------------------
void __fastcall TDatesFrame::OnLinuxHexChange(TObject *Sender)
{
// _dt=UnixToDateTime((unsigned long)LinuxHexEditFrame->_value);
 unsigned long t=LinuxHexEditFrame->_value;
 unsigned int days=t/(3600*24);
 unsigned int secs=t-(days*(3600*24));
 unsigned int hour=secs/3600;
 unsigned int min=secs/60-hour*60;
 secs=secs-(hour*3600+min*60);

 _dt=(double)((double)TDateTime(1970,1,1)+TDateTime((double)days)+(double)TDateTime(hour,min,secs,0));

 ShowDateTime();
}
//---------------------------------------------------------------------------
void __fastcall TDatesFrame::ChooseTimeButtonClick(TObject *Sender)
{
 TChooseTimeForm *form=new TChooseTimeForm(this);
 form->SetTime(_dt);
 try
 {
  if(form->ShowModal()==mrOk)
  {
   _dt=form->GetTime()+_dt.operator int();
   ShowDateTime();
  }
  delete form;
 }
 catch(...)
 {
  delete form;
 }
}
//---------------------------------------------------------------------------
void __fastcall TDatesFrame::ChooseDateButtonClick(TObject *Sender)
{
 TChooseDateForm *form=new TChooseDateForm(this);
 form->SetDate(_dt);
 try
 {
  if(form->ShowModal()==mrOk)
  {
   _dt=form->GetDate()+(_dt-_dt.operator int());
   ShowDateTime();
  }
  delete form;
 }
 catch(...)
 {
  delete form;
 }
}
//---------------------------------------------------------------------------
#include <vcl\Clipbrd.hpp>
void __fastcall TDatesFrame::DatesMenuItemClick(TObject *Sender)
{
 TMenuItem *item=(TMenuItem *)Sender;

 TControl *c=(TControl *)(((TPopupMenu *)(item->GetParentMenu()))->PopupComponent);
 TMemo *edit=NULL;
 if(c->InheritsFrom(__classid(TMemo))) edit=(TMemo *)c;
 else return;

 switch(item->Tag)
 {
  case 0 : // copy
  {
   char buffer[200];
   if(edit->SelLength>0) strncpy(buffer,edit->SelText.c_str(),199);
   else                  strncpy(buffer,edit->Text.c_str(),199);

   Clipboard()->SetTextBuf(buffer);
  }
  break;

  case 1 :  // paste
  {
   char buffer[100];
   strncpy(buffer,Clipboard()->AsText.c_str(),25);

   edit->Text=buffer;
  }
  break;

 }
}
//---------------------------------------------------------------------------

void __fastcall TDatesFrame::DatesPopupMenuPopup(TObject *Sender)
{
 TControl *c=(TControl *)(((TPopupMenu *)Sender)->PopupComponent);
 TMemo *edit=NULL;

 PasteMenuItem->Visible=false;
 if((c!=WindowsHexEdit)&(c!=DateTimeStringEdit))  PasteMenuItem->Visible=true;

 PasteMenuItem->Enabled=false;
 if(c->InheritsFrom(__classid(TMemo)))
 {
  edit=(TMemo *)c;

  char buffer[100];
  strncpy(buffer,Clipboard()->AsText.c_str(),25);

  if(strlen(buffer)>edit->MaxLength) return;
  if(edit->MaxLength==2)
  for(int i=0;i<strlen(buffer);i++)
  {
   if(isxdigit(buffer[i])==0) return;
  }
 } 
 PasteMenuItem->Enabled=true;
}
//---------------------------------------------------------------------------

