//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AnalyserViewerFrameUnit.h"
#include <Math.h>             
#include "RecordingFormUnit.h"  
#include "ApiFunctionsUnit.h"  
#include "Functions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AnalyserBaseFrameUnit"
#pragma resource "*.dfm"
TAnalyserViewerFrame *AnalyserViewerFrame;
//---------------------------------------------------------------------------
__fastcall TAnalyserViewerFrame::TAnalyserViewerFrame(TComponent* Owner)
        : TAnalyserBaseFrame(Owner)
{ 
 //_step=1;
 //_count=20;
// _id=time(NULL);
// _timeAscing0=1;
 this->DoubleBuffered=true;
}
//---------------------------------------------------------------------------
void TAnalyserViewerFrame::LoadInits(ASS fileName)
{
 TIniFile *iniFile=new TIniFile(fileName);
/*

 WorkContRadioButton->Checked=iniFile->ReadBool("Work","Cont",true);
 WorkIntervalRadioButton->Checked=iniFile->ReadBool("Work","Int",true);
 WorkOnceRadioButton->Checked=iniFile->ReadBool("Work","Once",true);
 WorkIntervalUpDown->Position=iniFile->ReadInteger("Work","Interval",1);
 IntervalEditChange(this);
  */
 delete iniFile;


}
//---------------------------------------------------------------------------
void TAnalyserViewerFrame::SaveInits(ASS fileName)
{   
 Close();
 TIniFile *iniFile=new TIniFile(fileName);

/*

 iniFile->WriteBool("Work","Cont",WorkContRadioButton->Checked);
 iniFile->WriteBool("Work","Int",WorkIntervalRadioButton->Checked);
 iniFile->WriteBool("Work","Once",WorkOnceRadioButton->Checked);
 iniFile->WriteInteger("Work","Interval",WorkIntervalUpDown->Position);
  */
 delete iniFile;   
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

/*
void TAnalyserViewerFrame::OnChangeSpan()
{

}   */
//---------------------------------------------------------------------------


void __fastcall TAnalyserViewerFrame::PlayIntervalEditChange(TObject *Sender)
{
 PlayTimer->Interval=1000*(PlayIntervalUpDown->Position);
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserViewerFrame::PlayButtonClick(TObject *Sender)
{
 Play(1-PlayTimer->Enabled);
}
//---------------------------------------------------------------------------
void TAnalyserViewerFrame::Play(bool flag)
{
 if(flag==false)
 {
  PlayTimer->Enabled=false;
  PlayButton->Caption="Запустить"; 
  PlayScrollBar->Enabled=true;
 }
 else
 {
  PlayTimer->Enabled=true;
  PlayButton->Caption="Остановить";
  PlayScrollBar->Enabled=false;
 }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <Math.h>
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

double TAnalyserViewerFrame::GetBeamDrawInterval()
{
 if(PlayTimer->Enabled==true)
  return PlayTimer->Interval/1000;
 else
  return 0.1;
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserViewerFrame::FileNameEditChange(TObject *Sender)
{
 if(FileNameEdit->Text.Length()<1)
  PlayButton->Enabled=false;
 else
  PlayButton->Enabled=true;
 PlayScrollBar->Enabled=PlayButton->Enabled;
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserViewerFrame::FileChooseButtonClick(
      TObject *Sender)
{
 TOpenDialog *dialog=new TOpenDialog(this);
 AnsiString dir=GetCurrentDir();
 dialog->InitialDir=GetCurrentUserPath("Personal");
 dialog->Title="Открытие";
 dialog->Filter="Файл записанных спектрограмм|*.csv";
 dialog->DefaultExt=".csv";
 dialog->FileName=FileNameEdit->Text;

 if(dialog->Execute()==true)
 {
  FileNameEdit->Text=dialog->FileName;
  Open();
 }
 delete dialog;
 SetCurrentDir(dir);
}
//---------------------------------------------------------------------------



void TAnalyserViewerFrame::Close()
{
 if(_fd!=NULL) fclose(_fd);
 _fd=NULL;
}

//---------------------------------------------------------------------------
void TAnalyserViewerFrame::Open()
{
 TDateTime dt1,dt2;
 _indexCount=0;
 _indexRank=1; // if file small <100 records - 1 index = 1 record< more: 1 index - 10 records
 _fd=NULL;

 _posLast=0;
 _posCount=0;

 char buf[8000];

 Close();
 _fd=fopen(FileNameEdit->Text.c_str(),"rt");

 if(_fd == NULL) return;

 int n=0;

 int i;

 for(i=0;;i++)
 {
  if(fgets(buf,8000,_fd)==NULL) break;
  if(i==0) dt1=atof(buf);
  if(i>((100*_indexRank)-1))
  {
   _indexRank*=10;
   for(int j=0;j<10;j++)
    _index[j]=_index[j*10];
   n=10;
  }

  if(i==(n*_indexRank))
  {
   _index[n]=ftell(_fd);
   n++;
  }
 } 
 dt2=atof(buf);

 _posCount=i;
 _indexCount=n;
 PlayScrollBar->Max=_posCount;

 fseek(_fd,0,SEEK_SET);
 _posLast=-1;
 ShowNext();

 PlayerFileInfEdit->Text=
  ASS("Записей: ")+ASS(_posCount)+
  ASS(", Точек: ")+ASS(_lastCount)+
  ASS(", Интервал: ")+ASS(_lastStep)+ASS(" кГц,")+
  ASS("Частоты: ")+ASS(_lastStartFreq)+ASS("...")+ASS(_lastStartFreq+_lastStep*_lastCount)+ASS(" кГц,")+
  ASS("Продолжительность: ");

 TDateTime dt=dt2-dt1;
 ASS st;
 if(((int)dt)>0)
  st=ASS((int )dt)+ASS(". ")+TDateTime(dt-(int)dt);
 else
  st=TDateTime(dt-(int)dt);

 PlayerFileInfEdit->Text=PlayerFileInfEdit->Text+st;

}
//---------------------------------------------------------------------------
void __fastcall TAnalyserViewerFrame::PlayTimerTimer(TObject *Sender)
{
 ShowNext();
}

//---------------------------------------------------------------------------
void TAnalyserViewerFrame::ShowNext()
{
 this->DrawSignalEnds();

 char buf[8000];

 if(fgets(buf,8000,_fd)==NULL) return;

 _posLast++;
 PlayScrollBar->Position=_posLast;

 char *argv[1000];
 int argc=5;
 argc=SplitBuffer(buf,argv,argc,";\n");

 _lastMeasuringTime=atof(argv[0]);

 _lastStartFreq=atol(argv[1]);
 _lastStep=atol(argv[2]);
 _lastCount=atol(argv[3]);

 argc=SplitBuffer(argv[4],argv,1000,";\n");
 for(int i=0;i<argc;i++)
 {
  SetLevel(i,atol(argv[i])*(-1));
 }

 DrawSignal();
}
//---------------------------------------------------------------------------
void __fastcall TAnalyserViewerFrame::PlayScrollBarScroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
 switch(ScrollCode)
 {
  case scPosition:
   _posLast=ScrollPos;
  break;
  case scLineUp:
   _posLast--;
  break; 
  case scLineDown:
   _posLast++;
  break;
  case scPageUp:
   _posLast-=_indexRank;
  break;
  case scPageDown:
   _posLast+=_indexRank;
  break;
  default:  ScrollPos=_posLast;
   return;
 }
 if(_posLast>=_posCount)  _posLast=_posCount-1;
 if(_posLast<0) _posLast=0;
 ScrollPos=_posLast;

 long indexPos=(_posLast/_indexRank);
 int posMin=_posLast-(indexPos*_indexRank);

 fseek(_fd,_index[indexPos],SEEK_SET);

 char buf[8000];
 for(int i=0;i<(posMin-1);i++)
  if(fgets(buf,8000,_fd)==NULL) return;

 _posLast--;
 ShowNext(); 
}
//---------------------------------------------------------------------------

