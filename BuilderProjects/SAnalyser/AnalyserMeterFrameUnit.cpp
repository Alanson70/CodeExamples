//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AnalyserMeterFrameUnit.h"  
#include <Math.h>             
#include "RecordingFormUnit.h" 
#include "ApiFunctionsUnit.h"  
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AnalyserBaseFrameUnit"
#pragma link "ConnectFrameUnit"
#pragma resource "*.dfm"
TAnalyserMeterFrame *AnalyserMeterFrame;
//---------------------------------------------------------------------------
__fastcall TAnalyserMeterFrame::TAnalyserMeterFrame(TComponent* Owner)
        : TAnalyserBaseFrame(Owner)
{ 
 _step=1;
 _count=20;
 _id=time(NULL);  
 _timeAscing0=1;
 this->ConnectFrame1->DisconnectButtonClick(this);
}
//---------------------------------------------------------------------------
void TAnalyserMeterFrame::LoadInits(ASS fileName)
{
 TIniFile *iniFile=new TIniFile(fileName);

 _userQualStep=iniFile->ReadInteger("Qual","Step",20);
 _userQualCount=iniFile->ReadInteger("Qual","Count",20);
 QualRadioGroup->ItemIndex=iniFile->ReadInteger("Qual","Index",2);
 this->QualRadioGroupClick(QualRadioGroup);

 WorkContRadioButton->Checked=iniFile->ReadBool("Work","Cont",true);
 WorkIntervalRadioButton->Checked=iniFile->ReadBool("Work","Int",true);
 WorkOnceRadioButton->Checked=iniFile->ReadBool("Work","Once",false);
 WorkIntervalUpDown->Position=iniFile->ReadInteger("Work","Interval",1);
 WorkIntervalEditChange(this);
 
  // Recording
 RecIntervalCheckBox->Checked=iniFile->ReadBool("Recording","IntervalCheck",RecIntervalCheckBox->Checked);
 RecDivCheckBox->Checked=iniFile->ReadBool("Recording","DivCheck",RecDivCheckBox->Checked);
 RecIntervalUpDown->Position=iniFile->ReadInteger("Recording","Interval",RecIntervalUpDown->Position);
 RecDivUpDown->Position=iniFile->ReadInteger("Recording","Div",RecDivUpDown->Position);
 RecIntervalComboBox->ItemIndex=iniFile->ReadInteger("Recording","IntervalFactor",RecIntervalComboBox->ItemIndex);
 RecDivComboBox->ItemIndex=iniFile->ReadInteger("Recording","DivFactor",RecDivComboBox->ItemIndex);
 RecMaxCountEdit->Text=iniFile->ReadString("Recording","MaxCount",RecMaxCountEdit->Text);
 RecToCSVCheckBox->Checked=iniFile->ReadBool("Recording","ToCSV",RecToCSVCheckBox->Checked);
 RecToSA4CheckBox->Checked=iniFile->ReadBool("Recording","ToSA4",RecToSA4CheckBox->Checked);
 RecToJPEGCheckBox->Checked=iniFile->ReadBool("Recording","ToJPEG",RecToJPEGCheckBox->Checked);
 RecDivEdit->Text=RecDivUpDown->Position/10.0;
 RecPathEdit->Text=iniFile->ReadString("Recording","Path","");
 RecMaxCountEditChange(this);

 delete iniFile;

 this->ConnectFrame1->LoadInits(fileName);


}
//---------------------------------------------------------------------------
void TAnalyserMeterFrame::SaveInits(ASS fileName)
{
 TIniFile *iniFile=new TIniFile(fileName);

 iniFile->WriteInteger("Qual","Step",_userQualStep);
 iniFile->WriteInteger("Qual","Count",_userQualCount);
 iniFile->WriteInteger("Qual","Index", QualRadioGroup->ItemIndex);
 iniFile->WriteInteger("Qual","Step",StepScrollBar->Position);

 iniFile->WriteBool("Work","Cont",WorkContRadioButton->Checked);
 iniFile->WriteBool("Work","Int",WorkIntervalRadioButton->Checked);
 iniFile->WriteBool("Work","Once",WorkOnceRadioButton->Checked);
 iniFile->WriteInteger("Work","Interval",WorkIntervalUpDown->Position);
  // Recording
 iniFile->WriteBool("Recording","IntervalCheck",RecIntervalCheckBox->Checked);
 iniFile->WriteBool("Recording","DivCheck",RecDivCheckBox->Checked);
 iniFile->WriteInteger("Recording","Interval",RecIntervalUpDown->Position);
 iniFile->WriteInteger("Recording","Div",RecDivUpDown->Position);
 iniFile->WriteInteger("Recording","IntervalFactor",RecIntervalComboBox->ItemIndex);
 iniFile->WriteInteger("Recording","DivFactor",RecDivComboBox->ItemIndex);
 iniFile->WriteString("Recording","MaxCount",RecMaxCountEdit->Text);
 iniFile->WriteBool("Recording","ToCSV",RecToCSVCheckBox->Checked);
 iniFile->WriteBool("Recording","ToSA4",RecToSA4CheckBox->Checked);
 iniFile->WriteBool("Recording","ToJPEG",RecToJPEGCheckBox->Checked);
 iniFile->WriteString("Recording","Path",RecPathEdit->Text);

 delete iniFile;

 this->ConnectFrame1->SaveInits(fileName);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TAnalyserMeterFrame::QualRadioGroupClick(TObject *Sender)
{
 StepScrollBar->Enabled=false;
 CountScrollBar->Enabled=false;
 switch(QualRadioGroup->ItemIndex)
 {
  case 2 :
  _count=20;
  _step=ceil((1.0*Span())/_count);
  break;

  case 1 :
  _count=(((Chart1->Width-40)/10)*10)/2;
  _step=ceil((1.0*Span())/_count);
  break;

  case 0 :
  _step=MAX(1,Span()/1000);
  _count=MIN(1000,ceil((1.0*Span())/(_step) ) );
  if(_count==1000)
   _step=ceil((1.0*Span())/_count);
  break;

  case 3 :
  StepScrollBar->Enabled=true;
  CountScrollBar->Enabled=true;
  if(Sender==QualRadioGroup)
  {
   _step=_userQualStep;
   _count=_userQualCount;
  }
  else
   _step=ceil((1.0*Span())/_count);
  break;
 }
 CountScrollBar->Position=_count;
 StepScrollBar->Position=_step;       
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserMeterFrame::StepScrollBarChange(TObject *Sender)
{
 if(Lock()) return;
 if(QualRadioGroup->ItemIndex==3)
 {
  _step=StepScrollBar->Position;
  _count=MIN(1000,ceil((1.0*Span())/(_step) ) );
  if(_count==1000)
   _step=ceil((1.0*Span())/_count);
  CountScrollBar->Position=_count;
  CountEdit->Text=_count;
  _userQualStep=_step;
  _userQualCount=_count;
 }
 StepScrollBar->Position=_step;
 Unlock();
 StepEdit->Text=_step;       
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserMeterFrame::CountScrollBarChange(TObject *Sender)
{
 if(Lock()) return;
 if(QualRadioGroup->ItemIndex==3)
 {
  _count=CountScrollBar->Position;
  _step=ceil((1.0*Span())/_count);
  StepScrollBar->Position=_step;
  StepEdit->Text=_step;
  _userQualStep=_step;
  _userQualCount=_count;
 }
 CountScrollBar->Position=_count;
 Unlock();
 CountEdit->Text=_count;
}  
//---------------------------------------------------------------------------
void TAnalyserMeterFrame::OnChangeSpan()
{
 StepScrollBar->Position=MIN(StepScrollBar->Position,Span());
 StepScrollBar->Max=Span();

 QualRadioGroupClick(this);
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserMeterFrame::WorkRadioButtonClick(TObject *Sender)
{
 TComponent *c=(TComponent *)Sender;

 switch(c->Tag)
 {
  case 0 :
   WorkIntervalTimer->Enabled=true;
   WorkIntervalTimer->Interval=100;
   _timeAscing0=(clock()/CLK_TCK);
  break;
  case 1 :
   WorkIntervalTimer->Enabled=true;
   WorkIntervalTimer->Interval=1000L*(WorkIntervalUpDown->Position);
   _timeAscing0=(clock()/CLK_TCK);
  break;
  case 2 :
   WorkIntervalTimer->Enabled=false;
   _timeAscing0=0;
  break;
 }       
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserMeterFrame::WorkIntervalEditChange(TObject *Sender)
{
 WorkIntervalTimer->Interval=1000*(WorkIntervalUpDown->Position);       
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserMeterFrame::RunButtonClick(TObject *Sender)
{
 //OnCanSend(this);
 this->ConnectFrame1->OnCanSend(this);
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserMeterFrame::WorkIntervalTimerTimer(
      TObject *Sender)
{        
 this->ConnectFrame1->OnCanSend(this);
 //OnCanSend(this);
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserMeterFrame::RecMaxCountEditChange(TObject *Sender)
{
 char s[10];
 int v;

 sprintf(s,"%s",RecMaxCountEdit->Text.c_str());
 v=atoi(s);

 if(v<1) v=1;
 else
 if(v>10000) v=10000;
 else
 return;

 RecMaxCountEdit->Text=s;
} 
//---------------------------------------------------------------------------
#include <FileCtrl.hpp>
const SELDIRHELP = 1000;

void __fastcall TAnalyserMeterFrame::RecPathButtonClick(TObject *Sender)
{
 ASS path=(RecPathEdit->Text);
 if(SelectDirectory(ASS("Выберите каталог"), "",path))   //Path - ?????
 {
  RecPathEdit->Text=path;
 }
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserMeterFrame::RecFileNameEditChange(TObject *Sender)
{
  if(RecFileNameEdit->Text.Length()<1)
  RecStartButton->Enabled=false;
 else
  RecStartButton->Enabled=true;       
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserMeterFrame::RecDivUpDownChangingEx(
      TObject *Sender, bool &AllowChange, short NewValue,
      TUpDownDirection Direction)
{   
 RecDivEdit->Text=NewValue/10.0;
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserMeterFrame::RecStartButtonClick(TObject *Sender)
{
 int l=ChartPanel->Left;
 int t=ChartPanel->Top;
 int w=ChartPanel->Width;
 int h=ChartPanel->Height;

 ChartPanel->Align=alClient;
 ChartPanel->BringToFront();

 CtrlPanel->Visible=false;
 LevelGroupBox->Enabled=false;
 APanel->Enabled=false;
 //SettsButton->Enabled=false;
 ButtonsPanel->Enabled=false;
 FreqGroupBox->Enabled=false;
 RecTimer->Enabled=true;
  _recCount=0;
  _recStartTime=Now();
  RecTimerStart();

 TRecordingForm *form=new TRecordingForm(this);
 form->_srcFrame=this;
 form->ShowModal();
 // stop

 ChartPanel->Align=alNone;

 ChartPanel->Left=l;
 ChartPanel->Top=t;
 ChartPanel->Width=w;
 ChartPanel->Height=h;

 CtrlPanel->Visible=true;
 LevelGroupBox->Enabled=true;
 APanel->Enabled=true;  
 ButtonsPanel->Enabled=true;
 //SettsButton->Enabled=true;
 FreqGroupBox->Enabled=true;
 RecTimer->Enabled=false;
}  
//-----------------------------------------------
void TAnalyserMeterFrame::RecTimerStart()
{
 int n=1;
 switch(RecIntervalComboBox->ItemIndex)
 {
  case 1 : n=60;break;
  case 2 : n=3600;break;
 }
 RecTimer->Tag=n*RecIntervalUpDown->Position;
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserMeterFrame::RecTimerTimer(TObject *Sender)
{
 TDateTime dt=Now();
 dt=dt-_recStartTime;
 if(((double)dt)>(0.0))
  RecTimeEdit->Text=ASS((int )dt)+ASS(". ")+TDateTime(dt-(int)dt);
 else
  RecTimeEdit->Text=TDateTime(dt-(int)dt);

 RecCountEdit->Text=_recCount;

 if(RecTimer->Tag!=0) RecTimer->Tag--;
 else
  if(RecIntervalCheckBox->Checked==true)
  {
   DoRecord();
   RecTimerStart();
  }       
} 
//---------------------------------------------------------------------------
void TAnalyserMeterFrame::TestForRecord()
{
 if(RecTimer->Enabled==false) return;

 bool mustRec=false;
 double div=RecDivUpDown->Position/10.0;

 if(RecDivComboBox->ItemIndex==0)
 {
  for(int i=0;i<_lastCount;i++)
  {
   if(abs( (_oldLevel[i]-GetLevel(i))/
     (_oldLevel[i]==0?-0.01:_oldLevel[i]*0.01) ) >div)
   {
    mustRec=true;
    break;
   }
  }
 }
 else
 {
  div=div*10;

  for(int i=0;i<_lastCount;i++)
  {
   if(abs(_oldLevel[i]-GetLevel(i))>div)
   {
    mustRec=true;
    break;
   }
  }
 }

 if(mustRec)
 {
  for(int i=0;i<_lastCount;i++)   _oldLevel[i]=GetLevel(i);
  DoRecord();
 }
}
//---------------------------------------------------------------------------

void TAnalyserMeterFrame::DoRecord()
{
 _recCount++;

 char add[20];
 int len=RecMaxCountEdit->Text.Length();

 sprintf(add,"%*.*d",len,len,_recCount);

 //ASS dir=GetCurrentUserPath("Personal")+ASS("\\");
 ASS dir=RecPathEdit->Text;//+ASS("\\");
 if(dir.Length()<1)
  dir=dir=GetCurrentUserPath("Personal");
 dir=dir+ASS("\\")+RecFileNameEdit->Text;

 if(RecToJPEGCheckBox->Checked==true)
 {
  ASS fileName=dir+ASS("-")+ASS(add)+ASS(".jpg");
  SaveAsPicture(fileName);
 }
 if(RecToCSVCheckBox->Checked==true)
 {
  ASS fileName=dir+ASS("-")+ASS(add)+ASS(".csv");
  SaveAsGrid(fileName);
 }
 if(RecToSA4CheckBox->Checked==true)
 {
  ASS fileName=dir+ASS(".csv");
  SaveAsSA4(fileName);
 }
}

//---------------------------------------------------------------------------


#include <Math.h>

//extern int _lastReceived;
//extern int _lastSended;

void TAnalyserMeterFrame::Translate(char *buffer,int count)
{
 char *argv[25];
 int argc;

 argc=SplitCommand(buffer,count,argv,24);
    /*
 IF(argv[0],"LAST",4)
 {
  _lastReceived=atol(argv[1]);
  if(_lastReceived!=_lastSended)
   _lastReceived=0;
 }
 else     */
 IF(argv[0],"GET",3)
 {
  if(argc<6) return;
  else
  {
   DrawSignalEnds();

   IF(argv[1],"0",1)
   {
    _lastCount=atoi(argv[2]);
    _lastStartFreq=atol(argv[3]);
    _lastStep=atoi(argv[4]);

    if(_count!=(Strlen(argv[5])/4)) return;

    int x;
    char *b;

    for(int i=0;i<_lastCount;i++)
    {
     b=argv[5]+(i*4);
     sscanf(b,"%4X",&x);
     SetLevel(i,x);
    }
   }
  }
 }
 else
 IF(argv[0],"SES",3)
 {
  if(argc<7) return;

  TimeTransferCalculate();

  count=atoi(argv[5]);
  _lastStartFreq=atol(argv[3]);
  _lastStep=atoi(argv[4]);

  IF(argv[2],"0",1)
  {
   if(count!=(Strlen(argv[6])/4)) return;

   if(_lastCount==1) return;

   DrawSignalEnds();
   _lastCount=count;

   int x;
   char *b;

   for(int i=0;i<_lastCount;i++)
   {
    b=argv[6]+(i*4);
    sscanf(b,"%4X",&x);
    SetLevel(i,x);
   }
  }
  else
  IF(argv[2],"1",1)
  {
   if((count)!=((Strlen(argv[6])-2)/2)) return;
    
   if(_lastCount==1) return;  
   DrawSignalEnds();
   _lastCount=count;
   
   signed char c;
   int x;
   int x0;
   char *b;

   b=argv[6];
   sscanf(b,"%4X",&x); 
   SetLevel(0,x);
   x0=x;

   for(int i=1;i<_lastCount;i++)
   {
    b=argv[6]+2+(i*2);
    sscanf(b,"%2hhX",&c);
    x=c;
    if((x&0x1)>0)
     x=((x-1)/2)*10;
    else x=x/2;
    x0=x0+x;    
    SetLevel(i,x0);
   }
  }
  
  else
  IF(argv[2],"2",1)
  {
   _timeOfMeasuring=atol(argv[6]);

   if(_timeOfMeasuring!=_timeOfLastMeasuring) // new data
   {
    if((count)!=((Strlen(argv[7])-2)/2)) return;

    if(count==1) return;

    DrawSignalEnds();

    _lastCount=count;

  //  if(_lastCount==1 | _lastStep==1)
  //   _lastCount=0;

    signed char c;
    int x;
    signed short int x0;
    char *b;

    b=argv[7];
    sscanf(b,"%4X",&x);

    SetLevel(0,(-1)*x);
    x0=x;

    for(int i=1;i<_lastCount;i++)
    {
     b=argv[7]+2+(i*2);
     sscanf(b,"%2hhX",&c);
     x=c;
     if((x&0x1)>0)
      x=((x-1)/2)*10;
     else x=x/2;
      x0=x0+x;
     
     SetLevel(i,(-1)*(signed int)x0);
    }

    TestForRecord();

   }
  }
 }
 else  return;

 if((_timeOfMeasuring!=_timeOfLastMeasuring)|(BeamRefreshCheckBox->Checked==false))
 {
  _lastMeasuringTime=Now();
 // _timeOfMeasuringLocal=time(NULL);

  

  if(_timeAscing0==0)
  _timeAscingAveraged=0;
  else
  {
   _timeAscing0=(clock()/CLK_TCK)-_timeAscing0;
   _timeAscingAveraged=_timeAscingAveraged*0.9+_timeAscing0*0.1;
   _timeAscing0=(clock()/CLK_TCK);
  }

  
  DrawSignal();

  _timeOfLastMeasuring=_timeOfMeasuring;
 }
 else return;


}
//---------------------------------------------------------------------------
ASS TAnalyserMeterFrame::GetCommand()
{
 _timeTransfer0=(clock()/CLK_TCK);

 ASS com="SES "+ASS(_id)+ASS(" 2 ")+ASS(StartFreq())+ASS(" ")+ASS(_step)+ASS(" ")+ASS(_count);

 return com;
}

//---------------------------------------------------------------------------
void TAnalyserMeterFrame::TimeTransferCalculate()
{
 _timeTransfer0=(clock()/CLK_TCK)-_timeTransfer0;
 _timeTransferAveraged=_timeTransferAveraged*0.9+_timeTransfer0*0.1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TAnalyserMeterFrame::InfoTimerTimer(TObject *Sender)
{
 char s[25];
 ASS text;
 text=Now().DateTimeString();

 sprintf(s,"   T обмена %.4lf сек",_timeTransferAveraged);
 text=text+s;
 sprintf(s,"   T опроса %.4lf сек",_timeAscingAveraged);
 text=text+s;

 AscingInfoLabel->Text=text;       
}

//---------------------------------------------------------------------------
double TAnalyserMeterFrame::GetBeamDrawInterval()
{
 return _timeAscingAveraged;
}
//---------------------------------------------------------------------------


