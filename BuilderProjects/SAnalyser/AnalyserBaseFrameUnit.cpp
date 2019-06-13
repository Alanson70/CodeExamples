//---------------------------------------------------------------------------

#define _WIN32_WINNT    0x0501
#define WINVER          0x0501
#include <vcl.h>
#pragma hdrstop



#include "AnalyserBaseFrameUnit.h"
#include "ApiFunctionsUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FreqParamFrameUnit"
#pragma resource "*.dfm"
TAnalyserBaseFrame *AnalyserFrame1;


#include "Inits.c"   
#include "Saves.c"


//---------------------------------------------------------------------------
__fastcall TAnalyserBaseFrame::TAnalyserBaseFrame(TComponent* Owner)
        : TFrame(Owner)
{
 _startFreq=72000L;
 _span=2000;  
 _ratio=10;
 _changing=false;
 _bands=new TBAND(this);

 BandsRadioGroup->ItemIndex=0;

 RecalcBand();
 //BandsRadioGroupClick(this);

 for(int i=15;i>=0;i--)
 {
  _Series[i]=new TLineSeries(this);
  if(i==0) _Series[i]->SeriesColor=clLime;
  //else _Series[i]->SeriesColor=TColor(0x0000B000-(0x00000800*(i)));
  else _Series[i]->SeriesColor=TColor(0x0000FF00-(0x00000800*(i))  );
  _Series[i]->Active=true;
  _Series[i]->LinePen->Width=2;
  _Series[i]->VertAxis=aLeftAxis;
  _Series[i]->HorizAxis=aBottomAxis;
  _Series[i]->XValues->Order= loNone ;
  Chart1->AddSeries(_Series[i]);

  ShadowSeries->DataSource=_Series[1];
 }
 _Series[0]->Marks->Visible=false;

 _SeriesFP=new TLineSeries(this);
 _SeriesFP->SeriesColor=clWhite;
 _SeriesFP->Active=true;
 _SeriesFP->LinePen->Width=2;
 _SeriesFP->VertAxis=aRightAxis;
 _SeriesFP->HorizAxis=aBottomAxis;
 _SeriesFP->XValues->Order= loNone ;
 Chart1->AddSeries(_SeriesFP);


}




///////////////////  INFO SIGNAL  
//---------------------------------------------------------------------------

#include <Math.h>
//---------------------------------------------------------------------------
void TAnalyserBaseFrame::SetLevel(int n,int level)
{
 _Levels[n]=level;
}
//---------------------------------------------------------------------------
int TAnalyserBaseFrame::GetLevel(int n)
{
 return _Levels[n];
}
//---------------------------------------------------------------------------
void TAnalyserBaseFrame::DrawSignal()
{

 if(LevelAutoFitCheckBox->Checked==true)
 {
  int maxLevel=0;
  int minLevel=0;

  for(int i=0;i<_lastCount;i++)
  {
   if(i>0)  maxLevel=MAX(maxLevel,_Levels[i]);
   else     maxLevel=_Levels[i];

   if(i>0)  minLevel=MIN(minLevel,_Levels[i]);
   else     minLevel=_Levels[i];
  }
  maxLevel*=0.1;
  minLevel*=0.1;

  maxLevel+=((maxLevel-minLevel)*0.1);
  minLevel-=((maxLevel-minLevel)*0.1);

  int newMin=minLevel;//10*floor(0.01*minLevel);
  if(Chart1->LeftAxis->Minimum<newMin)
  if(Chart1->LeftAxis->Maximum<newMin)  Chart1->LeftAxis->Maximum=newMin+1;
  Chart1->LeftAxis->Minimum=newMin;
  Chart1->LeftAxis->Maximum=maxLevel;//10*ceil(0.01*maxLevel);
 }

 for(int i=15;i>0;i--)
 {
  _Series[i]->Clear();
  _Series[i]->AssignValues(_Series[i-1]);
  _Series[i]->RefreshSeries();
 }
 _Series[0]->Clear();



/*
  struct tm *tt;
  tt = localtime(&(time_t)_timeOfMeasuringLocal);
  char buf[25];
  sprintf(buf,"%2.2d:%2.2d:%2.2d",tt->tm_hour,tt->tm_min,tt->tm_sec);

*/


  //ClockLabel->Caption=buf;
 // sprintf(buf,"%2.2d.%2.2d.%4.4d",tt->tm_mday,tt->tm_mon+1,tt->tm_year+1900);
  //DateLabel->Caption=buf;
  ASS buf=_lastMeasuringTime.DateTimeString();
  SignalInfoLabel->Caption=ASS("»змерено : ")+ASS(buf);

   _printedLast=0;

  if(BeamCheckBox->Checked==false)
  {
   DrawSignalEnds();
   /*
   for(int i=0;i<_lastCount;i++)
   {
    _Series[0]->AddXY(_lastStartFreq+(_lastStep*i),0.1*_Levels[i],"",clTeeColor);
   }
   _Series[0]->RefreshSeries();
   */
  }
  else
  {
   BeamTimer->Interval=100;

   _printQuota=ceil(1.0*_lastCount/((MAX(0.1,GetBeamDrawInterval())*1000)/BeamTimer->Interval));
   _printedLast=0;
   BeamTimer->Enabled=true;
  }
  
}
//---------------------------------------------------------------------------
void __fastcall TAnalyserBaseFrame::BeamTimerTimer(TObject *Sender)
{
 for(int i=0;i<_printQuota;i++)
 {
  if(_printedLast>=_lastCount)
  {
   BeamTimer->Enabled=false;
   return;
  }
  _Series[0]->AddXY(_lastStartFreq+(_lastStep*_printedLast),0.1*_Levels[_printedLast],"",clTeeColor);
  _printedLast++;
 }
 _Series[0]->RefreshSeries();
}
//---------------------------------------------------------------------------
void TAnalyserBaseFrame::DrawSignalEnds()     // if we are late to do bprevious function
{
 for(int i=0;i<_lastCount;i++)
 {
  if(_printedLast>=_lastCount)
  {
   break;;
  }
  _Series[0]->AddXY(_lastStartFreq+(_lastStep*_printedLast),0.1*_Levels[_printedLast],"",clTeeColor);
  _printedLast++;
 }
 BeamTimer->Enabled=false;
}
 
//---------------------------------------------------------------------------









//////////////////////// LEVELS
//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::LevelCenterScrollBarChange(TObject *Sender)
{
 Chart1->LeftAxis->Maximum=200;
 Chart1->LeftAxis->Minimum=(LevelCenterScrollBar->Position-LevelAmpScrollBar->Position)/1;
 Chart1->LeftAxis->Maximum=(LevelCenterScrollBar->Position+LevelAmpScrollBar->Position)/1;
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::LevelAmpScrollBarChange(TObject *Sender)
{
 Chart1->LeftAxis->Maximum=200;
 Chart1->LeftAxis->Minimum=(LevelCenterScrollBar->Position-LevelAmpScrollBar->Position)/1;
 Chart1->LeftAxis->Maximum=(LevelCenterScrollBar->Position+LevelAmpScrollBar->Position)/1;
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::LevelAutoFitCheckBoxClick(TObject *Sender)
{
 LevelCenterScrollBar->Enabled=~LevelAutoFitCheckBox->Checked;
 LevelAmpScrollBar->Enabled=~LevelAutoFitCheckBox->Checked;
}
////////////////////// BAND

//---------------------------------------------------------------------------
void __fastcall TAnalyserBaseFrame::UserMinFreqEditChange(TObject *Sender)
{
 if(BandsRadioGroup->ItemIndex==5)
 {
  //BandEditButton->Caption="¬вести";
  BandCancelButton->Enabled=true;
 }
 char s[25];
 long n=atol(UserMinFreqEdit->Text.c_str());

 UserMinFreqEdit->Text=n;

}
//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::BandsRadioGroupClick(TObject *Sender)
{
 if(BandsRadioGroup->Enabled==false) return;

 RecalcBand();

 if(BandsRadioGroup->ItemIndex==5) BandPanel->Enabled=true;
 else BandPanel->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::BandEditButtonClick(TObject *Sender)
{
 if(BandsRadioGroup->ItemIndex!=5) // edit
 {
  BandPanel->Enabled=true;
  BandEditButton->Caption="¬вести";
  BandsRadioGroup->Enabled=false;
  BandsRadioGroup->ItemIndex=5;
  return;
 }
 else // apply
 { 
  BandsRadioGroup->Enabled=true;
  BandPanel->Enabled=false;
  BandEditButton->Caption="»зменить";
 }

 unsigned long minFreq=50000L;
 unsigned long maxFreq=90000L;

 if(BandsRadioGroup->ItemIndex==5)
 {
  _userMinFreq=UserMinFreqEdit->Text.ToDouble();
  _userMaxFreq=UserMaxFreqEdit->Text.ToDouble();

  minFreq=UserMinFreqEdit->Text.ToDouble();
  maxFreq=UserMaxFreqEdit->Text.ToDouble();
 }

 if(Lock()) return;

 LeftScrollBar->Min=0;
 LeftScrollBar->Max=MAX_FREQ;
 RightScrollBar->Min=0;
 RightScrollBar->Max=MAX_FREQ;
 CentralScrollBar->Min=0;
 CentralScrollBar->Max=MAX_FREQ;
 SpanScrollBar->Min=0;
 SpanScrollBar->Max=MAX_FREQ;

 LeftScrollBar->Min=minFreq/_ratio;
 LeftScrollBar->Max=maxFreq/_ratio-2*_ratio;
 RightScrollBar->Min=minFreq/_ratio+2*_ratio;
 RightScrollBar->Max=maxFreq/_ratio;
 CentralScrollBar->Min=minFreq/_ratio;
 CentralScrollBar->Max=maxFreq/_ratio;
 SpanScrollBar->Min=2;//_ratio;//minBand;
 SpanScrollBar->Max=(maxFreq-minFreq)/_ratio;
// StepScrollBar->Min=minStep;
// StepScrollBar->Max=maxStep;
 Unlock();

 LeftScrollBar->Position=MAX(LeftScrollBar->Min,MIN(LeftScrollBar->Position,LeftScrollBar->Max));
 RightScrollBar->Position=MAX(RightScrollBar->Min,MIN(RightScrollBar->Position,RightScrollBar->Max));

 OnChangeSpan();

// QualRadioGroupClick(this);
 //BandsRadioGroupClick(this);
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::BandCancelButtonClick(TObject *Sender)
{
 BandsRadioGroup->Enabled=true;
 BandPanel->Enabled=false;
 BandEditButton->Caption="»зменить";

 BandsRadioGroup->ItemIndex=5;
 
}

//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::RatioComboBoxChange(TObject *Sender)
{
 unsigned long pos1=RStartFreq()*_ratio;
 unsigned long pos2=(RStartFreq()+RSpan())*_ratio;

 _ratio=RatioComboBox->Text.ToInt();

 if(_span<10 & _ratio>1) RatioComboBox->ItemIndex=0;
 else
 if(_span<100 & _ratio>10) RatioComboBox->ItemIndex=1;
 else
 if(_span<1000 & _ratio>100) RatioComboBox->ItemIndex=2;
 else
 if(_span<10000 & _ratio>1000) RatioComboBox->ItemIndex=3;

 _ratio=RatioComboBox->Text.ToInt();

 RecalcBand();

 LeftScrollBar->Position=pos1/_ratio;
 RightScrollBar->Position=pos2/_ratio;
}
//---------------------------------------------------------------------------
void TAnalyserBaseFrame::RecalcBand()
{
 unsigned long minFreq=50000L;
 unsigned long maxFreq=90000L;


 switch(BandsRadioGroup->ItemIndex)
 {
  case 1 :
   minFreq=100000L;
   maxFreq=180000L;
  break;
  case 2 :
   minFreq=1000000L;
   maxFreq=2000000L;
  break;
  case 3 :
   minFreq=3400000L;
   maxFreq=4200000L;
  break;
  case 4 :
   minFreq=5850000L;
   maxFreq=6725000L;
  break;
  case 5 :
   minFreq=_userMinFreq;
   maxFreq=_userMaxFreq;
  break;
 }
 UserMinFreqEdit->Text=minFreq;
 UserMaxFreqEdit->Text=maxFreq;

 if(Lock()) return;
      // prepare to change
 LeftScrollBar->Min=0;
 LeftScrollBar->Max=MAX_FREQ;
 RightScrollBar->Min=0;
 RightScrollBar->Max=MAX_FREQ;
 CentralScrollBar->Min=0;
 CentralScrollBar->Max=MAX_FREQ;
 SpanScrollBar->Min=0;
 SpanScrollBar->Max=MAX_FREQ;

 LeftScrollBar->Position=minFreq/_ratio;
 RightScrollBar->Position=maxFreq/_ratio-1;
          // change in _ratio
 LeftScrollBar->Min=minFreq/_ratio;
 LeftScrollBar->Max=maxFreq/_ratio-1;
 RightScrollBar->Min=minFreq/_ratio+1;
 RightScrollBar->Max=maxFreq/_ratio;
 CentralScrollBar->Min=minFreq/_ratio;
 CentralScrollBar->Max=maxFreq/_ratio;
 SpanScrollBar->Min=2;//_ratio;//minBand;
 SpanScrollBar->Max=(maxFreq-minFreq)/_ratio;

 //LeftScrollBar->Position=0;
 //RightScrollBar->Position=MAX_FREQ;

 Unlock();

}








///////////////////// FREQ


//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::CentralScrollBarChange(TObject *Sender)
{
 if(Lock()) return;


 if(CentralScrollBar->Position-(RSpan()/2)<CentralScrollBar->Min)
  CentralScrollBar->Position=CentralScrollBar->Min+(RSpan()/2);
 if(CentralScrollBar->Position+(RSpan()/2)>CentralScrollBar->Max)
  CentralScrollBar->Position=CentralScrollBar->Max-(RSpan()/2);

 LeftScrollBar->Position=CentralScrollBar->Position-(RSpan()/2);
 RightScrollBar->Position=CentralScrollBar->Position+(RSpan()/2);

 RStartFreq(LeftScrollBar->Position);

 Unlock();

 CentralFreqEdit->Text=CentralScrollBar->Position*_ratio;
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::SpanScrollBarChange(TObject *Sender)
{
 if(Lock()) return;


 if(CentralScrollBar->Position-(SpanScrollBar->Position/2)<CentralScrollBar->Min)
  SpanScrollBar->Position=2*(CentralScrollBar->Position-CentralScrollBar->Min);
 if(CentralScrollBar->Position+(SpanScrollBar->Position/2)>CentralScrollBar->Max)
  SpanScrollBar->Position=2*(CentralScrollBar->Max-CentralScrollBar->Position);

 LeftScrollBar->Position=CentralScrollBar->Position-(SpanScrollBar->Position/2);
 RightScrollBar->Position=CentralScrollBar->Position+(SpanScrollBar->Position/2);
 RSpan(RightScrollBar->Position-LeftScrollBar->Position);
 RStartFreq(LeftScrollBar->Position);

 Unlock();     
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::LeftScrollBarChange(TObject *Sender)
{
 if(Lock()) return;

 if(LeftScrollBar->Position>(RightScrollBar->Position-2))
 {
  RightScrollBar->Position=LeftScrollBar->Position+2;
 }
 else
 {
  RSpan(RightScrollBar->Position-LeftScrollBar->Position);
  RStartFreq(LeftScrollBar->Position);
 }

 CentralScrollBar->Position=LeftScrollBar->Position+(RSpan()/2);
 SpanScrollBar->Position=RSpan();

 Unlock();

 LeftFreqEdit->Text=LeftScrollBar->Position*_ratio;

}
//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::RightScrollBarChange(TObject *Sender)
{
 if(Lock()) return;

 if(LeftScrollBar->Position>(RightScrollBar->Position-2))
 {
  LeftScrollBar->Position=RightScrollBar->Position-2;
 }
 else
 {
  RSpan(RightScrollBar->Position-LeftScrollBar->Position);
  RStartFreq(LeftScrollBar->Position);
 }

 SpanScrollBar->Position=RSpan();
 CentralScrollBar->Position=LeftScrollBar->Position+(RSpan()/2);

 Unlock();

 RightFreqEdit->Text=RightScrollBar->Position*_ratio;
}


//---------------------------------------------------------------------------
void TAnalyserBaseFrame::RSpan(unsigned long span)
{
 Span(MAX(1,span)*_ratio);
}

//---------------------------------------------------------------------------
void TAnalyserBaseFrame::Span(unsigned long span)
{
 _span=MAX(1,span);
 SpanEdit->Text=_span;

 OnChangeSpan();


}

//---------------------------------------------------------------------------
unsigned long TAnalyserBaseFrame::RSpan()
{
 return _span/_ratio;
}
//---------------------------------------------------------------------------
unsigned long TAnalyserBaseFrame::Span()
{
 return _span;
}
//---------------------------------------------------------------------------
void TAnalyserBaseFrame::RStartFreq(unsigned long freq)
{
 _startFreq=freq*_ratio;  

 Chart1->BottomAxis->Maximum=MAX(_startFreq+_span,Chart1->BottomAxis->Maximum);
 Chart1->BottomAxis->Minimum=_startFreq;
 Chart1->BottomAxis->Maximum=_startFreq+_span;

 //StartScrollBar->Max=span;
}
//---------------------------------------------------------------------------
unsigned long TAnalyserBaseFrame::RStartFreq()
{
 return _startFreq/_ratio;
}


//---------------------------------------------------------------------------
void TAnalyserBaseFrame::MiddleFreq(unsigned long freq)
{
 this->CentralScrollBar->Position=freq/_ratio;
}

//---------------------------------------------------------------------------













///////////////////// QUAL


//---------------------------------------------------------------------------
////////////////////////////// BEAM
//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::BeamWidthComboBoxChange(TObject *Sender)
{
 //int width=(1<<BeamWidthComboBox->ItemIndex);

 for(int i=0;i<16;i++)
 {
  _Series[i]->LinePen->Width=BeamWidthComboBox->ItemIndex;//width;
 }
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::BeamFadingEditChange(TObject *Sender)
{
 if(_Series[0]==NULL) return;

 int n=BeamFadingUpDown->Position;

 TColor color0=BeamColor();
 TColor color2=Chart1->Gradient->EndColor;

 if(FonColorComboBox->ItemIndex>4)        color2=Chart1->Gradient->StartColor;
 if(FonGradientCheckBox->Checked==true)
 {
  color2=((Chart1->Gradient->StartColor&0xFEFEFE)>>0x1)+((Chart1->Gradient->EndColor&0xFEFEFE)>>0x1);
 }
 if(BeamColorCheckBox->Checked==true)  color0=color2^0xFFFFFF;


 int colorR0=color0&0xFF;
 int colorG0=(color0&0xFF00)>>8;
 int colorB0=(color0&0xFF0000)>>16;

 int colorR2=color2&0xFF;
 int colorG2=(color2&0xFF00)>>8;
 int colorB2=(color2&0xFF0000)>>16;

 int colorR=colorR0;
 int colorG=colorG0;
 int colorB=colorB0;

 double incR=(colorR2-colorR0)/(double)n; // red increment
 double incG=(colorG2-colorG0)/(double)n;
 double incB=(colorB2-colorB0)/(double)n;

 TColor color=colorR+(colorG<<8)+(colorB<<16);

 _Series[0]->SeriesColor=color;

 for(int i=1;i<n;i++)
 {
  colorR=colorR+incR;
  //incR+=incR;
  colorG=colorG+incG;
  //incG+=incG;
  colorB=colorB+incB;
  //incB+=incB;

  _Series[i]->Active=true;

  color=colorR+(colorG<<8)+(colorB<<16);
  _Series[i]->SeriesColor=color;
  Image1->Canvas->Brush->Color=color;  
  Image1->Canvas->Pen->Color=color;
  Image1->Canvas->FillRect(Rect(1,i*8,120,(i+1)*8));
  //_Series[i]->SeriesColor=color-((i*(0xFF/BeamFadingUpDown->Position))<<8);
 }

 for(int i=n;i<16;i++)
  _Series[i]->Active=false;
}
//---------------------------------------------------------------------------


void __fastcall TAnalyserBaseFrame::Chart1Resize(TObject *Sender)
{
 OnChangeSpan();
// QualRadioGroupClick(this);
}

//---------------------------------------------------------------------------













/////////////////////////  WORK

//---------------------------------------------------------------------------


///////////////////////// FON


//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::FonRadioGroupClick(TObject *Sender)
{
 switch(FonColorComboBox->ItemIndex)
 {
  case 0 :
  Chart1->Gradient->EndColor=clBlack;
  Chart1->BottomAxis->LabelsFont->Color=clBlue;
  break;
  case 1 :
  Chart1->Gradient->EndColor=clGray;
  Chart1->BottomAxis->LabelsFont->Color=clSkyBlue;
  break;
  case 2 :
  Chart1->Gradient->EndColor=clMaroon;
  Chart1->BottomAxis->LabelsFont->Color=clSkyBlue;
  break;
  case 3 :
  Chart1->Gradient->EndColor=clNavy;
  Chart1->BottomAxis->LabelsFont->Color=clSkyBlue;
  break;
  case 4 :
  Chart1->Gradient->EndColor=clGreen;
  Chart1->BottomAxis->LabelsFont->Color=clSkyBlue;
  break;
  case 5 :
  Chart1->Gradient->StartColor=clWhite;
  Chart1->BottomAxis->LabelsFont->Color=clBlue;
  break;
  case 6 :
  Chart1->Gradient->StartColor=clSilver;
  Chart1->BottomAxis->LabelsFont->Color=clSkyBlue;
  break;
  case 7 :
  Chart1->Gradient->StartColor=clCream;
  Chart1->BottomAxis->LabelsFont->Color=clSkyBlue;
  break;
  case 8 :
  Chart1->Gradient->StartColor=clSkyBlue;
  Chart1->BottomAxis->LabelsFont->Color=clSkyBlue;
  break;
  case 9 :
  Chart1->Gradient->StartColor=clMoneyGreen;
  Chart1->BottomAxis->LabelsFont->Color=clSkyBlue;
  break;
 }
 if(FonGradientCheckBox->Checked==true)
  if(FonColorComboBox->ItemIndex<5)
   Chart1->Gradient->StartColor=clBlack;
  else
   Chart1->Gradient->EndColor=clWhite;
 else
  if(FonColorComboBox->ItemIndex<5)
   Chart1->Gradient->StartColor=Chart1->Gradient->EndColor;
  else
   Chart1->Gradient->EndColor=Chart1->Gradient->StartColor;

 BeamColorRadioGroupClick(Sender);
 GridColorAdaptCheckBoxClick(Sender);
 this->LegendColorCheckBoxClick(Sender);
 ShadowSeries->SeriesColor=Chart1->Gradient->StartColor;
 InfoPanel->Color=Chart1->Gradient->EndColor;
}
//---------------------------------------------------------------------------
TColor TAnalyserBaseFrame::BeamColor()
{
 switch(BeamColorComboBox->ItemIndex)
 {
  case 0 : return clWhite;
  case 1 : return clSilver;
  case 2 : return clRed;
  case 3 : return clYellow;
  case 4 : return clLime;
  case 5 : return clSkyBlue;
  case 6 : return clGray;
  case 7 : return clBlack;
 }
 return clLime;
}
//---------------------------------------------------------------------------
void __fastcall TAnalyserBaseFrame::BeamColorRadioGroupClick(TObject *Sender)
{
 BeamFadingEditChange(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TAnalyserBaseFrame::GridColorNoCheckBoxClick(TObject *Sender)
{
 Chart1->LeftAxis->Grid->Visible=1-GridColorNoCheckBox->Checked;
 Chart1->BottomAxis->Grid->Visible=1-GridColorNoCheckBox->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::GridColorSplashCheckBoxClick(TObject *Sender)
{
 if(GridColorSplashCheckBox->Checked==true) 
  Chart1->LeftAxis->Grid->Style=psSolid;
 else
  Chart1->LeftAxis->Grid->Style=psDot;
}
//---------------------------------------------------------------------------
void __fastcall TAnalyserBaseFrame::GridColorAdaptCheckBoxClick(TObject *Sender)
{
 TColor color=clGray;
 if(GridColorAdaptCheckBox->Checked==true)
 {
  if(this->FonColorComboBox->ItemIndex<5)
   color=clSilver;
 }
 else
 {
  switch(GridColorComboBox->ItemIndex)
  {
   case 0 : color=clBlack;break;  
   case 1 : color=clGray;break;
   case 2 : color=clRed;break;
   case 3 : color=clBlue;break;
   case 4 : color=clGreen;break;
   case 5 : color=clWhite;break;
   case 6 : color=clSilver;break;
   case 7 : color=clCream;break;
   case 8 : color=clSkyBlue;break;
   case 9 : color=clMoneyGreen;break;
  }
 }
 Chart1->LeftAxis->Grid->Color=color;
 Chart1->BottomAxis->Grid->Color=color;
 InfoPanel->Font->Color=Color;
}
//---------------------------------------------------------------------------
void __fastcall TAnalyserBaseFrame::LegendColorCheckBoxClick(TObject *Sender)
{
 TColor colorX=clAqua;
 TColor colorY=clRed;

 if(LegendColorCheckBox->Checked==true)
 {
  if(this->FonColorComboBox->ItemIndex>4)
  {
   colorX=clNavy;
   colorY=clMaroon;
  }
 }
 else
 {
  colorX=LegendXColorBox->Selected;
  colorY=LegendYColorBox->Selected;
 }
 Chart1->LeftAxis->LabelsFont->Color=colorY;
 DBLabel->Font->Color=colorY;
 Chart1->BottomAxis->LabelsFont->Color=colorX;
 FreqLabel->Font->Color=colorX;
} 
//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::BeamShadowCheckBoxClick(TObject *Sender)
{
 ShadowSeries->Active=BeamShadowCheckBox->Checked;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::OnBandChanged(TObject *Sender)
{
 _SeriesFP->Clear();
 PlanTitleSeries->Clear();

 if(PlanListBox->Count<1)  return;

 TBAND *band=(TBAND *)(PlanListBox->Items->Objects[PlanListBox->ItemIndex]);
 band->Set(FreqParamFrame1->_setts); //_setts.Assign(FreqParamFrame1->_setts);
 AllocStep=FreqParamFrame1->StepEdit->Text.ToInt();

 ASS name=band->BandName();// >_setts.Name;
 if(name.Length()<1) name=ASS(band->CarrierFreq()/1000)+ASS(" к√ц");
 PlanListBox->Items->Strings[PlanListBox->ItemIndex]=name;//_bands AddItem("FIRST",NULL);


 TColor color=_SeriesFP->SeriesColor;
 _SeriesFP->AddXY(MIN_FREQ,10,NULL,color);
 //TBAND *Band;
 unsigned long bandWidth;
 unsigned long freq=MAX_FREQ;
 unsigned long maxFreq=MIN_FREQ;
 for(int i=0;i<PlanListBox->Count;i++)
 {
  band=(TBAND *)(PlanListBox->Items->Objects[i]);
  bandWidth=band->AssignedBand()/1000; // band
  freq=band->CarrierFreq()/1000;
  ASS name=band->BandName();
  if(name.Length()<1) name=ASS(freq)+ASS(" к√ц");

  PlanTitleSeries->AddXY(freq,83+(i&0x3)*3,name,_SeriesFP->SeriesColor);


  _SeriesFP->AddXY(freq-bandWidth/2,10,"",color);
  _SeriesFP->AddXY(freq-bandWidth/4,78,"",color);
  _SeriesFP->AddXY(freq-bandWidth/8,80,"",color);
  _SeriesFP->AddXY(freq,81,"",color);
  _SeriesFP->AddXY(freq+bandWidth/8,80,"",color);
  _SeriesFP->AddXY(freq+bandWidth/4,78,"",color);
  _SeriesFP->AddXY(freq+bandWidth/2,10,"",color);
  maxFreq=freq+bandWidth/2+20000L;
 }
 //_SeriesFP->AddXY(freq+bandWidth,10,"",color);
 //_SeriesFP->AddXY(Chart1->BottomAxis->Maximum,10,"",color);
 //_SeriesFP->AddXY((double)754773L,10,"",color);
 _SeriesFP->AddXY(maxFreq,10,"",color);  // strange? but on any intervals nor drowed
}

//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::PlanListBoxClick(TObject *Sender)
{
 if(PlanListBox->ItemIndex>=0)
 {
  TBAND *band=(TBAND *)(PlanListBox->Items->Objects[PlanListBox->ItemIndex]);
  FreqParamFrame1->StepUpDown->Position=AllocStep;
  FreqParamFrame1->Set(band->GetSetts());// band->_setts);
  FreqParamFrame1->Visible=true;
  FreqParamFrame1->OnChanged=this->OnBandChanged;
 }
 else
  FreqParamFrame1->Visible=false;

}
//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::FreqPlanEditMenuItemClick(TObject *Sender)
{
 TMenuItem *menu=(TMenuItem *)Sender;
 TBAND *band;

 switch(menu->Tag)
 {
  case 0 :
  band=_bands->CreateBand(NULL);//(BAND_SETTS &)band->_setts);
 // band->_setts.Name="Unnamed";
  PlanListBox->AddItem("Unnamed",band);
  PlanListBox->ItemIndex=PlanListBox->Count-1;
  PlanListBox->OnClick(this);

  break;
  case 1 :
  if(PlanListBox->Count<1) break;
  band=(TBAND *)(PlanListBox->Items->Objects[PlanListBox->ItemIndex]);
  break;
  case 2 : 
  if(PlanListBox->Count<1) break;
  if(MessageDlg("”далить полосу?",mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0)!=mrYes) break;

  band=(TBAND *)(PlanListBox->Items->Objects[PlanListBox->ItemIndex]);
  _bands->RemoveBand(band);
  PlanListBox->DeleteSelected();

  break;
 }
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::FreqPlanMenuItemClick(TObject *Sender)
{
 TMenuItem *menu=(TMenuItem *)Sender;
//

 switch(menu->Tag)
 {
  case 0 :
  {
   TSaveDialog *SaveDialog1=new TSaveDialog(this);
   AnsiString dir=GetCurrentDir();
   SaveDialog1->InitialDir=GetCurrentUserPath("Personal");
   SaveDialog1->Title="—охранение";
   SaveDialog1->Filter="‘айл частотного плана|*.cfg";
   SaveDialog1->DefaultExt=".cfg";
   SaveDialog1->FileName=FreqPlanNameEdit->Caption;

   if(SaveDialog1->Execute()==true)
   {
    FreqPlanNameEdit->Caption=SaveDialog1->FileName;
    _bands->BandsSave(FreqPlanNameEdit->Caption);
   }
   delete SaveDialog1;
   SetCurrentDir(dir);
  }

  break;
  case 1 :
  {
   //if(_bands)
   if(MessageDlg("”далить текущий план?",mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0)!=mrYes) break;
   // clearing old
   ClearFreqPlan();
    // loadind
   TOpenDialog *SaveDialog1=new TOpenDialog(this);
   AnsiString dir=GetCurrentDir();
   SaveDialog1->InitialDir=GetCurrentUserPath("Personal");
   SaveDialog1->Title="ќткрытие";
   SaveDialog1->Filter="‘айл частотного плана|*.cfg";
   SaveDialog1->DefaultExt=".cfg";
   SaveDialog1->FileName=FreqPlanNameEdit->Caption;

   if(SaveDialog1->Execute()==true)
   {
    LoadFreqPlan(SaveDialog1->FileName);
   }
   delete SaveDialog1;
   SetCurrentDir(dir);
  }
  break;
  case 2 :
  if(MessageDlg("”далить все полосы?",mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0)!=mrYes) break;
  ClearFreqPlan();

  break; 
  case 3 :
  OnBandChanged(this);

  break;
 }
}
//---------------------------------------------------------------------------
void TAnalyserBaseFrame::ClearFreqPlan()
{
 TBAND *band;
 // clearing
  for(int i=0;i<PlanListBox->Count;i++)
  {
   band=(TBAND *)(PlanListBox->Items->Objects[i]);
   _bands->RemoveBand(band);
  }
  PlanListBox->Clear();
  FreqPlanNameEdit->Caption="";
  OnBandChanged(NULL);
}
//---------------------------------------------------------------------------
void TAnalyserBaseFrame::LoadFreqPlan(ASS fileName)
{
 ClearFreqPlan();

 TBAND *band;
 FreqPlanNameEdit->Caption=fileName;
 _bands->BandsLoad(FreqPlanNameEdit->Caption);
 band=_bands;
 for(int i=0;;i++)
 {
  band=band->NextBand();
  if(band==NULL) break;

  ASS name=band->BandName();// >_setts.Name;
  if(name.Length()<1) name=ASS(band->CarrierFreq()/1000)+ASS(" к√ц");
  PlanListBox->AddItem(name,band);
 }
 if(PlanListBox->Count>0)
 {
  PlanListBox->ItemIndex=0;
  PlanListBox->OnClick(PlanListBox);
  OnBandChanged(this);
 }
} 
//---------------------------------------------------------------------------
/*
TAnalyserFrame::SaveFreqPlan(ASS fileName)
{
}              */
//---------------------------------------------------------------------------


void __fastcall TAnalyserBaseFrame::FreqPlanLineWidthComboBoxChange(TObject *Sender)
{
// int width=(1<<BeamWidthComboBox->ItemIndex);

 _SeriesFP->LinePen->Width=FreqPlanLineWidthComboBox->ItemIndex;
 _SeriesFP->RefreshSeries();
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::FreqPlanLineColorBoxChange(TObject *Sender)
{
 _SeriesFP->SeriesColor=FreqPlanLineColorBox->Selected;
 OnBandChanged(this);
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::FreqPlanNameColorBoxChange(TObject *Sender)
{
 PlanTitleSeries->Marks->Font->Color=FreqPlanNameColorBox->Selected;
 PlanTitleSeries->RefreshSeries();
}
//---------------------------------------------------------------------------










//---------------------------------------------------------------------------


#include <Forms.hpp>

void __fastcall TAnalyserBaseFrame::SettsButtonClick(TObject *Sender)
{
 if(SettsPageControl->Visible==false)
 {
  SettsPageControl->Visible=true;
  CtrlPanel->Visible=false;
 }
 else
 {
  SettsPageControl->Visible=false;
 }
}
//---------------------------------------------------------------------------
void __fastcall TAnalyserBaseFrame::CtrlButtonClick(TObject *Sender)
{
 if(CtrlPanel->Visible==false)
 {
  SettsPageControl->Visible=false;
  CtrlPanel->Visible=true;
 }
 else
 {
  CtrlPanel->Visible=false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::FreqSetComboBoxChange(TObject *Sender)
{
 FreqSpanPanel->Align=alClient;
 FreqInterPanel->Align=alClient;
 
 if(FreqSetComboBox->ItemIndex==1)
 {
  FreqInterPanel->Visible=false;
  FreqSpanPanel->Visible=true;
 }
 else
 {
  FreqSpanPanel->Visible=false;
  FreqInterPanel->Visible=true;
 }


}
//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::SettsPageControlChanging(TObject *Sender,
      bool &AllowChange)
{
 //if(RecTimer->Enabled==true) AllowChange=false;
}
//---------------------------------------------------------------------------



void __fastcall TAnalyserBaseFrame::RecStartButtonClick(TObject *Sender)
{
/*
 if(RecStartButton->Tag==0)
 {

  LevelGroupBox->Enabled=false;
  APanel->Enabled=false;
  SettsButton->Enabled=false;
  FreqGroupBox->Enabled=false;
 // SettsPageControl->Enabled=false;
  RecStaticText->Visible=true;
  RecStartButton->Tag=1;
  RecTimer->Enabled=true;
  _recCount=0;
  _recStartTime=Now();
  RecTimerStart();
  RecStartButton->Caption="ќстановить запись";
  RecStaticText->Left=Width/2-RecStaticText->Width;
 }
 else
 {
  LevelGroupBox->Enabled=true;
  APanel->Enabled=true;
  SettsButton->Enabled=true;
  FreqGroupBox->Enabled=true;
 // SettsPageControl->Enabled=true;
  RecStaticText->Visible=false;
  RecStartButton->Tag=0;
  RecTimer->Enabled=false;
  RecStartButton->Caption="Ќачать запись";
 }
 */
 //TWinControl *form=GetTopParentControl(this);
 //stasrt
 

}

//---------------------------------------------------------------------------



void __fastcall TAnalyserBaseFrame::RecDivComboBoxChange(TObject *Sender)
{
// if(RecDivComboBox->ItemIndex==1)  _recDivValue=0;
}

//---------------------------------------------------------------------------

