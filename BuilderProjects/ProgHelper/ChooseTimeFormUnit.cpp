//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ChooseTimeFormUnit.h"
#include "Functions.h"   
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TChooseTimeForm *ChooseTimeForm;
//---------------------------------------------------------------------------
__fastcall TChooseTimeForm::TChooseTimeForm(TComponent* Owner)
        : TForm(Owner)
{
 Image1->Canvas->Pen->Color=clRed;
 Image1->Canvas->Pen->Width=2;
 Panel1->DoubleBuffered=true;
}    
//---------------------------------------------------------------------------
void TChooseTimeForm::SetTime(TDateTime t)
{
 unsigned short h,m,s,ms;
 t.DecodeTime(&h,&m,&s,&ms);
 HourUpDown->Position=h;
 MinUpDown->Position=m;
 SecUpDown->Position=s;
}
//---------------------------------------------------------------------------
TDateTime TChooseTimeForm::GetTime()
{
 TDateTime t=TDateTime(HourUpDown->Position,MinUpDown->Position,SecUpDown->Position,0);
 return t;
}
//---------------------------------------------------------------------------
void TChooseTimeForm::DrawClock()
{
 int angle=270-(HourUpDown->Position*360)/12;
 double rad=(M_PI *2 * angle)/(360);
 double c=cos(rad);
 double s=sin(rad);
 int r=Width/6;
 int b=r*cos(rad);
 int a=r*sin(rad);

 //
 //TColor color=Image1->Canvas->Pixels[Image1->Width/2][Image1->Height/2];
  // clear
 Image1->Canvas->Brush->Color=clBtnFace;//clWhite;
 //Image1->Canvas->FloodFill(Image1->Width/2, Image1->Height/2, clWhite, fsBorder);
 Image1->Canvas->FillRect(Image1->ClientRect);
 // hour
 Image1->Canvas->Pen->Width=6;
 Image1->Canvas->MoveTo(Image1->Width/2,(Image1->Height-4)/2);
 Image1->Canvas->LineTo(Image1->Width/2-b,(Image1->Height-4)/2+a);
 // min
 angle=270-(MinUpDown->Position*360)/60;
 rad=(M_PI *2 * angle)/(360);
 c=cos(rad);
 s=sin(rad);
 r=Width/4.5;
 b=r*cos(rad);
 a=r*sin(rad);
 Image1->Canvas->Pen->Width=4;
 Image1->Canvas->MoveTo(Image1->Width/2,(Image1->Height-4)/2);
 Image1->Canvas->LineTo(Image1->Width/2-b,(Image1->Height-4)/2+a);
 // sec
 angle=270-(SecUpDown->Position*360)/60;
 rad=(M_PI *2 * angle)/(360);
 c=cos(rad);
 s=sin(rad);
 r=Width/3.5;
 b=r*cos(rad);
 a=r*sin(rad);
 Image1->Canvas->Pen->Width=2;
 Image1->Canvas->MoveTo(Image1->Width/2,(Image1->Height-4)/2);
 Image1->Canvas->LineTo(Image1->Width/2-b,(Image1->Height-4)/2+a);
 // center
 int x=(Image1->Width/2);
 int y=(Image1->Height/2);
 Image1->Canvas->Brush->Color=Image1->Canvas->Pen->Color;
 Image1->Canvas->Ellipse(x-4,y-6,x+4,y+2);
}
//---------------------------------------------------------------------------
void __fastcall TChooseTimeForm::HourEditChange(TObject *Sender)
{
 char s[12];
 int v;

 strncpy(s,HourEdit->Text.c_str(),10);
 v=atoi(s);
 if(v==24) v=0; 
 if(v==-1) v=23;
 v=MIN(23,MAX(0,v));
 HourUpDown->Position=v;
 DrawClock();
}
//---------------------------------------------------------------------------
void __fastcall TChooseTimeForm::MinEditChange(TObject *Sender)
{
 char s[12];
 int v;

 strncpy(s,MinEdit->Text.c_str(),10);
 v=atoi(s);
 if(v==60) v=0;
 if(v==-1) v=59;
 v=MIN(59,MAX(0,v));
 MinUpDown->Position=v;
 DrawClock();
}
//---------------------------------------------------------------------------

void __fastcall TChooseTimeForm::SecEditChange(TObject *Sender)
{
 char s[12];
 int v;

 strncpy(s,SecEdit->Text.c_str(),10);
 v=atoi(s);
 if(v==60) v=0;
 if(v==-1) v=59;
 v=MIN(59,MAX(0,v));
 SecUpDown->Position=v;
 DrawClock();
}
//---------------------------------------------------------------------------

