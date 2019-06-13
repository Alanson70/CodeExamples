//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FreqParamFrameUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFreqParamFrame *FreqParamFrame;
//---------------------------------------------------------------------------
__fastcall TFreqParamFrame::TFreqParamFrame(TComponent* Owner)
        : TFrame(Owner)
{
 _changing=false;
                            
 this->FreqScrollBarKHZ->Max=FREQ_HZ_MAX/1000;
 this->FreqScrollBarKHZ->Min=FREQ_HZ_MIN/1000;
 this->BandScrollBarKHZ->Max=BAND_HZ_MAX/1000;
 this->BandScrollBarKHZ->Min=BAND_HZ_MIN/1000;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TFreqParamFrame::Set(BAND_SETTS &setts)
{
 _setts.Assign(setts);
 InfRateEdit->Text=setts.InfRate;
 this->OverheadCheck->Checked=setts.Overhead;
 this->OverheadDivisorUpDown->Position=setts.OverheadDivisor;
// this->OverheadDivisorEdit->Text=
 this->OverheadFactorUpDown->Position=setts.OverheadFactor;
// this->OverheadFactorEdit->Text=
 this->RSCheck->Checked=setts.RS;
 this->RSDivisorUpDown->Position=setts.RSDivisor;
// this->RSDivisorEdit->Text=
 this->RSFactorUpDown->Position=setts.RSFactor;
// this->RSFactorEdit->Text=
 this->CodingCheck->Checked=setts.Coding;
 this->CodingDivisorUpDown->Position=setts.CodingDivisor;
 //this->CodingDivisorEdit->Text=
 this->CodingFactorUpDown->Position=setts.CodingFactor;
// this->CodingFactorEdit->Text=
 this->ModulationCombo->ItemIndex=setts.Modulation;
 this->FreqEdit->Text=setts.Freq;  
 this->NameEdit->Text=setts.Name;
}
//---------------------------------------------------------------------------
void TFreqParamFrame::Recalc()
{
 _setts.Calculate();

 if(_setts.BandHandSet==false)
  BandEdit->Text=_setts.BandCalc;

 if(OnChanged)
  this->OnChanged(this);
}
//---------------------------------------------------------------------------
void __fastcall TFreqParamFrame::InfRateEditChange(TObject *Sender)
{
 if(Lock()) return;

 bool badValue=false;
 unsigned long v=0;
 try
 {
  v=InfRateEdit->Text.ToInt();
 }
 catch(...)
 {
  InfRateEdit->Text="1000";
  v=1000;
  badValue=true;
 }

 if(v<1200) badValue=true;
 if(v>10000000) badValue=true;

 if(badValue==false)
 {
  InfRateUpDownKHZ->Position=v/1000;
  InfRateUpDown->Position=(v-InfRateUpDownKHZ->Position*1000);

  _setts.InfRate=InfRateEdit->Text.ToInt();

  Recalc();
 }
 Unlock();
}
//---------------------------------------------------------------------------
void __fastcall TFreqParamFrame::InfRateUpDownKHZChangingEx(TObject *Sender,
      bool &AllowChange, short NewValue, TUpDownDirection Direction)
{
 if(Lock()) return;
 AllowChange=true; ///?????????

 unsigned long v=0;

 if(Sender==InfRateUpDownKHZ)
  v=InfRateUpDown->Position+(NewValue*1000);
 else
 if(Sender==InfRateUpDown)
  v=(InfRateUpDownKHZ->Position*1000)+NewValue;

 InfRateEdit->Text=v;

 Unlock();

 InfRateEditChange(Sender);

} 
//---------------------------------------------------------------------------

void __fastcall TFreqParamFrame::InfRateUpDownClick(TObject *Sender,
      TUDBtnType Button)
{
 if(Lock()) return; 

 unsigned long v=0;

/* if(Sender==InfRateUpDownKHZ)
  v=InfRateUpDown->Position+(NewValue*1000);
 else
 if(Sender==InfRateUpDown)
  v=(InfRateUpDownKHZ->Position*1000)+NewValue;
 */
 v=InfRateUpDown->Position+(InfRateUpDownKHZ->Position*1000);

 InfRateEdit->Text=v;

 Unlock();

 InfRateEditChange(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFreqParamFrame::OverheadChange(TObject *Sender)
{
 if(Lock()) return;

 _setts.Overhead=OverheadCheck->Checked;
 _setts.OverheadFactor=OverheadFactorEdit->Text.ToInt();
 _setts.OverheadDivisor=OverheadDivisorEdit->Text.ToInt();

 if(((TControl *)Sender)==OverheadFactorEdit)
 {
  if(_setts.OverheadFactor<=_setts.OverheadDivisor)
  {
   OverheadDivisorUpDown->Position=_setts.OverheadFactor-1;
  }
 }
 else
 {
  if(_setts.OverheadFactor<=_setts.OverheadDivisor)
  {
   OverheadFactorUpDown->Position=_setts.OverheadDivisor+1;
  }
 }
 _setts.OverheadFactor=OverheadFactorEdit->Text.ToInt();
 _setts.OverheadDivisor=OverheadDivisorEdit->Text.ToInt();
 Recalc();

 Unlock();
}
//---------------------------------------------------------------------------
void __fastcall TFreqParamFrame::RSCheckClick(TObject *Sender)
{
 if(Lock()) return;

 _setts.RS=RSCheck->Checked;
 _setts.RSFactor=RSFactorEdit->Text.ToInt();
 _setts.RSDivisor=RSDivisorEdit->Text.ToInt();

 if(((TControl *)Sender)==RSFactorEdit)
 {
  if( _setts.RSFactor<= _setts.RSDivisor)
  {
   RSDivisorUpDown->Position= _setts.RSFactor-1;
  }
 }
 else
 {
  if( _setts.RSFactor<= _setts.RSDivisor)
  {
   RSFactorUpDown->Position= _setts.RSDivisor+1;
  }
 }

 _setts.RSFactor=RSFactorEdit->Text.ToDouble();
 _setts.RSDivisor=RSDivisorEdit->Text.ToDouble();

 Recalc();

 Unlock();
}
//---------------------------------------------------------------------------
void __fastcall TFreqParamFrame::CodingCheckClick(TObject *Sender)
{
 if(Lock()) return;

 if(((TControl *)Sender)==CodingFactorEdit)
  CodingDivisorEdit->Text=CodingFactorEdit->Text.ToInt()+1;
 else
  if(((TControl *)Sender)==CodingDivisorEdit)
   CodingFactorEdit->Text=CodingDivisorEdit->Text.ToInt()-1;

 _setts.CodingDivisor=CodingDivisorEdit->Text.ToDouble();
 _setts.CodingFactor=CodingFactorEdit->Text.ToDouble();

 _setts.Coding=CodingCheck->Checked;

 Recalc();
 
 Unlock();
}
//---------------------------------------------------------------------------
void __fastcall TFreqParamFrame::ModulationComboChange(TObject *Sender)
{
 if(Lock()) return;

 _setts.Modulation=ModulationCombo->ItemIndex;

 Recalc();
 
 Unlock();
}
//---------------------------------------------------------------------------
void __fastcall TFreqParamFrame::FreqEditChange(TObject *Sender)
{
 if(Lock()) return;

 bool badValue=false;

 unsigned long freq;

 try
 {
  freq=FreqEdit->Text.ToInt();
 }
 catch(...)
 {
  badValue=true;
 }

 if(freq<FREQ_HZ_MIN) badValue=true;
 if(freq>FREQ_HZ_MAX) badValue=true;

 freq=long(freq/StepUpDown->Position)*StepUpDown->Position;

 if(badValue==false)
 {
  FreqEdit->Text=freq;

  _setts.Freq=freq;

  FreqScrollBarKHZ->Position=(FreqScrollBarKHZ->Max-freq/1000);
  FreqScrollBar->Position=FreqScrollBar->Max-(freq-(freq/1000)*1000); // min scroll

  Recalc();
 }

 Unlock();
}
//---------------------------------------------------------------------------
void __fastcall TFreqParamFrame::StepEditChange(TObject *Sender)
{
 if(Lock()) return;

 AllocStep=StepEdit->Text.ToInt();

 Recalc();

 Unlock();
}
//---------------------------------------------------------------------------
void __fastcall TFreqParamFrame::FreqScrollBarChange(TObject *Sender)
{
 if(Lock()) return;

 unsigned long v=(FreqScrollBarKHZ->Max-FreqScrollBarKHZ->Position)*1000+(FreqScrollBar->Max-FreqScrollBar->Position);

 Unlock();

 FreqEdit->Text=v;  
}
//---------------------------------------------------------------------------

void __fastcall TFreqParamFrame::NameEditChange(TObject *Sender)
{
 this->_setts.Name=NameEdit->Text;
 Recalc();
}
//---------------------------------------------------------------------------
void __fastcall TFreqParamFrame::BandScrollBarChange(TObject *Sender)
{
 if(Lock()) return;

 unsigned long v=(BandScrollBarKHZ->Max-BandScrollBarKHZ->Position)*1000+(BandScrollBar->Max-BandScrollBar->Position);

 Unlock();

 BandEdit->Text=v;
}
//---------------------------------------------------------------------------
void __fastcall TFreqParamFrame::BandEditChange(TObject *Sender)
{
 if(Lock()) return;

 bool badValue=false;

 unsigned long band;

 try
 {
  band=BandEdit->Text.ToInt();
 }
 catch(...)
 {
  badValue=true;
 }

 if(band<BAND_HZ_MIN) badValue=true;
 if(band>BAND_HZ_MAX) badValue=true;

 if(badValue==false)
 {
  BandEdit->Text=band;

  _setts.BandHand=band;

  BandScrollBarKHZ->Position=(BandScrollBarKHZ->Max-band/1000);
  BandScrollBar->Position=BandScrollBar->Max-(band-(band/1000)*1000); // min scroll

  Recalc();
 }

 Unlock();
}
//---------------------------------------------------------------------------

void __fastcall TFreqParamFrame::BandHandSetCheckBoxClick(TObject *Sender)
{
 _setts.BandHandSet=this->BandHandSetCheckBox->Checked;
 ParamPanel->Enabled=1-_setts.BandHandSet;
 BandEdit->ReadOnly=_setts.BandHandSet;
 BandScrollBar->Enabled=_setts.BandHandSet;
 BandScrollBarKHZ->Enabled=_setts.BandHandSet;
 if(_setts.BandHandSet==true)
  BandEdit->Text=_setts.BandHand;
 Recalc();
}
//---------------------------------------------------------------------------

