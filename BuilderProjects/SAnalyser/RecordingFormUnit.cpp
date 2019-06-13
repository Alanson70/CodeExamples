//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RecordingFormUnit.h"
#include "AnalyserMeterFrameUnit.h"   
#include "Functions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRecordingForm *RecordingForm;
//---------------------------------------------------------------------------
__fastcall TRecordingForm::TRecordingForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TRecordingForm::RecTimerTimer(TObject *Sender)
{
 RecTimer->Tag--;

 if((RecTimer->Tag&0x1)>0)
  RecStaticText->Visible=true;
 else
  RecStaticText->Visible=false;

 TAnalyserMeterFrame *frame=(TAnalyserMeterFrame *)_srcFrame;
 
 if(frame)
 {
  if(frame->_recCount>=frame->RecMaxCountEdit->Text.ToInt())
   Close();

  TDateTime dt=Now();
  dt=dt-frame->_recStartTime;
  if(((double)dt)>(0.0))
   RecTimeEdit->Text=ASS((int )dt)+ASS(". ")+TDateTime(dt-(int)dt);
  else
   RecTimeEdit->Text=TDateTime(dt-(int)dt);
  RecCountEdit->Text=frame->_recCount;
 }
}
//---------------------------------------------------------------------------
void __fastcall TRecordingForm::Button1Click(TObject *Sender)
{
 Close();       
}
//---------------------------------------------------------------------------
