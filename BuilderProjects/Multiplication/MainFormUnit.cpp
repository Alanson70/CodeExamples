//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFormUnit.h"

#include <stdio.h>
#include <math.h>
#include "UserResultsFrameUnit.h"
#include "UserEditUnit.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "UserResultsFrameUnit"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
 _userResult[0]=UserResultFrame1;

 for(int i=1;i<8;i++)
 {
  _userResult[i]=new TUserResultFrame(this);
  _userResult[i]->Top=10;
  _userResult[i]->Visible=false;
  _userResult[i]->Align=alTop;
  _userResult[i]->Name=AnsiString("UserResult")+AnsiString(i);
  _userResult[i]->Parent=GroupBox1;
 }
 LoadUsers();
}

//---------------------------------------------------------------------------
TDateTime _lastTime;
TDateTime _startTime;

void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{
 _lastTime=Time();
 TimeEdit->Text=(_lastTime-_startTime).TimeString();
}
//---------------------------------------------------------------------------

int _toValue=10;
int _fromValue=1;
bool _run=false;


void __fastcall TMainForm::ToEditChange(TObject *Sender)
{
 _toValue=ToEdit->Text.ToInt();
 if(_toValue<_fromValue)
 {
  _fromValue=_toValue;
  FromUpDown->Position=_fromValue;
 }
 LoadBestResults();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FromEditChange(TObject *Sender)
{
 _fromValue=FromEdit->Text.ToInt();
 if(_toValue<_fromValue)
 {
  _toValue=_fromValue;
  ToUpDown->Position=_toValue;
 }  
 LoadBestResults();
} 
//---------------------------------------------------------------------------

void __fastcall TMainForm::RandomCheckBoxClick(TObject *Sender)
{

 LoadBestResults();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::StartButtonClick(TObject *Sender)
{
 _run=1-_run;
 if(_run)
 {
  SourceGroupBox->Enabled=false;
  StartButton->Caption="Îñòàíîâèòü?";
  FirstExpression();
  //StartButton->Focused=false;// Default=false;
  this->ActiveControl=NULL; 
  _startTime=Time();
  Timer1->Enabled=true;
  Timer1Timer(this);

  Value1Edit->Color=clWindow;
  Value2Edit->Color=clWindow;
  ResultEdit->Color=clWindow;

 }
 else
 {
  SourceGroupBox->Enabled=true;
  StartButton->Caption="ÍÀ×ÀÒÜ!!!";
  Timer1->Enabled=false;

  Value1Edit->Color=clBtnFace;
  Value2Edit->Color=clBtnFace;
  ResultEdit->Color=clBtnFace;
 }
}
//---------------------------------------------------------------------------

int _values[10];
int _factors[10]={1,2,3,4,5,6,7,8,9,10};
int _order[100];
//int _value=0;
int _steps=10;
int _step=0;
int _value1=0;
//int _value2=0;
int _factor=0;
int _result=0;
int _resultFlag=0; // 0 - no answer, 1 - right, -1 - error
int _maxPoints;
int _points;

int _leg=0; // 0 - waiting for decision, 1 - is decision, - 1 - no start

char _buf[90];

void TMainForm::FirstExpression()
{
 _steps=(1+(_toValue-_fromValue));
 // set data to values from _from to _to
 for(int i=0;i<_steps;i++)
 {
  _values[i]=i+_fromValue;
 }
 for(int j=0;j<100;j++)
  _order[j]=j;
 // set steps
 _steps=_steps*10;
 _step=0;
 _leg=0;


 _points=0;
 _maxPoints=_steps;

 // dismiss values if necessary
 if(RandomCheckBox->Checked==true)
 {
  int tmp=0;
  int n=0;
  randomize();
  for(int i=0;i<_steps;i++)
  {
   tmp=_order[i];
   n=random(_steps);
   _order[i]=_order[n];
   _order[n]=tmp;
  } 
 }

 NextExpression();
}
//---------------------------------------------------------------------------
void TMainForm::NextExpression()
{
 int num=_order[_step];
 _value1=_values[num/10];
 _factor=_factors[num-((num/10)*10)];
 Value1Edit->Text=_value1;
 Value2Edit->Text=_factor;

 _result=_value1*_factor;
 _resultFlag=0;
 ResultEdit->Text=""; 
 ResultEdit->Font->Style =TFontStyles()<<fsBold;
 ResumeEdit->Font->Size=28;
 _buf[0]=0;
 TestResult();

 _step++;
 _leg=0;

 if(_step>_steps)
 {
  StartButtonClick(this);
  _leg=-1;
  if(_points==_maxPoints)
   SaveResult(_lastTime-_startTime);
 }
}
//---------------------------------------------------------------------------
char *_errorText[]=
{"ÍÅ ÏÐÀÂÈËÜÍÎ!!!",
"ÎØÈÁÊÀ!!!",
"ÍÅ ÒÎ!!!",
"ÍÅ ÒÀÊ!!!",
"ÆÀËÜ...",
"ÌÈÌÎ!!!",
"ÎÉ!!!",
"ÎÉ-ÎÉ-ÎÉ!!!",
"ÍÅÒ!!!",
"ÍÅ ÑÕÎÄÈÒÑß!!!",
"ÍÅÒ-ÍÅÒ!!!",NULL};
int _errorTextLeg=0;
//---------------------------------------------------------------------------
void TMainForm::TestResult()
{
 if(_buf[0]==0)
 {
  ResumeEdit->Text="";
  _resultFlag=0;
 }
 else
 {
  char rbuf[10];
  sprintf(rbuf,"%d",_result);

  for(int i=0;i<strlen(_buf);i++)
  {
   if((_buf[i]==0) |(rbuf[i]==_buf[i]));
   else
   { // error
    ResultEdit->Font->Style =TFontStyles()<<fsBold<<fsStrikeOut;

    ResumeEdit->Font->Color=clRed;
    ResumeEdit->Font->Size=16;
    ResumeEdit->Text=_errorText[_errorTextLeg]+AnsiString("  Áóäåò ")+AnsiString(_result);
    _errorTextLeg++;
    if(_errorText[_errorTextLeg]==NULL) _errorTextLeg=0;
    _resultFlag=-1;
    _leg=1;
    return;
   }
  }
  if(_result!=atoi(_buf))
  {                              
   ResumeEdit->Font->Color=clGreen;
   ResumeEdit->Text="Ïîêà ïðàâèëüíî";
   _resultFlag=0;
  }
  else
  {
   ResumeEdit->Font->Color=clGreen;
   ResumeEdit->Text="ÏÐÀÂÈËÜÍÎ!!!";
   _resultFlag=1;
   _leg=1;
   _points++;
  }
 } 
 PointsEdit->Text=AnsiString(_points)+AnsiString(" èç ")+AnsiString(_maxPoints);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ResultEditKeyPress(TObject *Sender, char &Key)
{
 if(_leg==-1) return;

 if(_leg==1)
 {
  Key=0;
  NextExpression();
  return;
 }

 int c='9';
 int len=strlen(_buf);


 switch(Key)
 {
  //case VK_OK:  // next
  //break;

  case VK_SPACE:  //  prompting
  break;

  case VK_BACK:
  {
    if(len<0) len=0;
    else   _buf[len-1]=0;

   int v=atoi(_buf);
   ResultEdit->Text=_buf;

   TestResult();

   return;
  }
  break;

  case '0' :
  case VK_NUMPAD0 :
   c='0';
  break;

  case '1' :
  case VK_NUMPAD1 :
   c='1';
  break;

  case '2' :
  case VK_NUMPAD2 :
   c='2';
  break;

  case '3' :
  case VK_NUMPAD3 :
   c='3';
  break;

  case '4' :
  case VK_NUMPAD4 :
   c='4';
  break;

  case '5' :
  case VK_NUMPAD5 :
   c='5';
  break;

  case '6' :
  case VK_NUMPAD6 :
   c='6';
  break;

  case '7' :
  case VK_NUMPAD7 :
   c='7';
  break;

  case '8' :
  case VK_NUMPAD8 :
   c='8';
  break;

  case '9' :
  case VK_NUMPAD9 :
   c='9';
  break;

  default : return;
 }

 if(len>2) return;

 _buf[len]=c;
 _buf[len+1]=0;

 ResultEdit->Text=_buf;

 TestResult();

}
//---------------------------------------------------------------------------
#include "inifiles.hpp"

struct
{
 TDateTime t;
}BestResults[8];

int _currUser=0;

//---------------------------------------------
void TMainForm::LoadUsers()
{
 TIniFile *iniFile=new TIniFile(GetCurrentDir()+"\\BestMultipliers.ini");
 AnsiString item;


 ComboBox1->AddItem("Anonym",NULL);

 int usersCount = iniFile->ReadInteger("Users","Count",0);

 for(int i=0;i<usersCount;i++)
 {
  item=AnsiString(i+1);

  item=iniFile->ReadString("Users",item,0);
  if(item.Length()>0)
  {
   _userResult[i]->Label1->Caption=item;
   ComboBox1->AddItem(item,NULL);
  }
 }

 delete iniFile;
}


//---------------------------------------------
void TMainForm::SaveUsers()
{
 TIniFile *iniFile=new TIniFile(GetCurrentDir()+"\\BestMultipliers.ini");

 AnsiString item;

 iniFile->WriteInteger("Users","Count",ComboBox1->Items->Count-1);

 for(int i=1;i<ComboBox1->Items->Count;i++)
 {
  item=AnsiString(i);

  iniFile->WriteString("Users",item,ComboBox1->Items->Strings[i]);
 }

 delete iniFile;
}
//---------------------------------------------
void TMainForm::LoadBestResults()
{
 AnsiString section=AnsiString(_toValue)+AnsiString("-")+AnsiString(_fromValue)+
      AnsiString("-")+AnsiString((int)(RandomCheckBox->Checked));

 TIniFile *iniFile=new TIniFile(GetCurrentDir()+"\\BestMultipliers.ini");
 AnsiString item;

 for(int i=0;i<8;i++)
 {
  item=AnsiString(i);

  BestResults[i].t=iniFile->ReadTime(section,item,0);
  _userResult[i]->Edit1->Text=BestResults[i].t.TimeString();
  if(BestResults[i].t.operator double()==0)
   _userResult[i]->Visible=false;
  else
   _userResult[i]->Visible=true;
 }

 delete iniFile;
}

//---------------------------------------------------------------------------
void TMainForm::SaveResult(TDateTime t)
{
 if(t<BestResults[_currUser].t  | (BestResults[_currUser].t.operator double()==0))
  BestResults[_currUser].t=t;
 else return;

 AnsiString section=AnsiString(_toValue)+AnsiString("-")+AnsiString(_fromValue)+
      AnsiString("-")+AnsiString((int)(RandomCheckBox->Checked));

 TIniFile *iniFile=new TIniFile(GetCurrentDir()+"\\BestMultipliers.ini");
 AnsiString item;

 item=AnsiString(_currUser);

 iniFile->WriteTime(section,item,BestResults[_currUser].t);


 delete iniFile;

 LoadBestResults();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ComboBox1Change(TObject *Sender)
{
 _currUser=ComboBox1->ItemIndex;
 if(0 == _currUser)
    DelButton->Enabled = false;
 else
    DelButton->Enabled = true;
 //LoadResult(ComboBox1->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AddUserButtonClick(TObject *Sender)
{
      TUserEditForm *form=new TUserEditForm(this);

      try
      {
          if(form->ShowModal()==mrOk)
          {
              ComboBox1->AddItem(form->UserEdit->Text,NULL);
              ComboBox1->ItemIndex = ComboBox1->Items->Count-1;
              ComboBox1Change(Sender);
          }
          delete form;
      }
      catch(...)
      {
          delete form;
      }
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    SaveUsers();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DelButtonClick(TObject *Sender)
{
     TUserEditForm *form=new TUserEditForm(this);
     form->UserEdit->ReadOnly=true;
     form->EditButton->Caption = "Óäàëèòü";
     form->UserEdit->Text = ComboBox1->Text;

      try
      {
          if(form->ShowModal()==mrOk)
          {
              ComboBox1->DeleteSelected();
              ComboBox1Change(Sender);
          }
          delete form;
      }
      catch(...)
      {
          delete form;
      }
}
//---------------------------------------------------------------------------

