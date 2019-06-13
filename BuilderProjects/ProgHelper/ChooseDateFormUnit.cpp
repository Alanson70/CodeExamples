//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ChooseDateFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CCALENDR"
#pragma resource "*.dfm"
TChooseDateForm *ChooseDateForm;
//---------------------------------------------------------------------------
__fastcall TChooseDateForm::TChooseDateForm(TComponent* Owner)
        : TForm(Owner)
{      
 _minDate=0;
 _maxDate=0;
}
//---------------------------------------------------------------------------
void TChooseDateForm::SetDate(TDateTime date)
{
 Calendar->CalendarDate=date;
 CalendarChange(this);
}  
//---------------------------------------------------------------------------
void TChooseDateForm::SetCurrentYearLimits(TDateTime date)
{
 unsigned short year,mon,day;
 //form->SetDate(date);
 date.DecodeDate(&year,&mon,&day);
 mon=1;day=1;
 date=TDateTime(year,mon,day);
 _minDate=date;
 mon=12;day=31;
 date=TDateTime(year,mon,day);
 _maxDate=date;
}
//---------------------------------------------------------------------------
TDateTime TChooseDateForm::GetDate()
{
 return Calendar->CalendarDate;
}
//---------------------------------------------------------------------------
void __fastcall TChooseDateForm::CalendarChange(TObject *Sender)
{
 MonthComboBox->ItemIndex=Calendar->Month-1;
 YearEdit->Text=Calendar->Year;
}
//---------------------------------------------------------------------------
void __fastcall TChooseDateForm::LeftButtonClick(TObject *Sender)
{
 Calendar->PrevMonth();
 if(((int)_minDate)!=0)
  if(Calendar->CalendarDate<_minDate)
   Calendar->NextMonth();
}
//---------------------------------------------------------------------------
void __fastcall TChooseDateForm::RightButtonClick(TObject *Sender)
{
 Calendar->NextMonth();
 if(((int)_maxDate)!=0)
  if(Calendar->CalendarDate>_maxDate) Calendar->PrevMonth();
}
//---------------------------------------------------------------------------

void __fastcall TChooseDateForm::YearEditChange(TObject *Sender)
{
 TEdit *edit=(TEdit *)Sender;

 if(edit->Tag==1) return;
 edit->Tag=1;

 char buffer[25];
 int pos=edit->SelStart;

 strncpy(buffer,edit->Text.c_str(),4);
 buffer[4]=0;
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
   if(Calendar->Month==2)
   {
    Calendar->Month=1; 
    Calendar->Year=t;
    Calendar->NextMonth();
   }
   else
    Calendar->Year=t;
   if(pos>strlen(buffer)) pos=strlen(buffer);
  }
 }
 edit->SelStart=pos;
 edit->Text=buffer;
 edit->Tag=0;
}
//---------------------------------------------------------------------------

void __fastcall TChooseDateForm::MonthComboBoxChange(TObject *Sender)
{
 switch(MonthComboBox->ItemIndex)
 {
  case 1 : case 3 : case 5 : case 8 : case 10 :
  Calendar->Month=MonthComboBox->ItemIndex;
  Calendar->NextMonth();
  break;
  default :
   Calendar->Month=MonthComboBox->ItemIndex+1;
  break; 
 }
}
//---------------------------------------------------------------------------

