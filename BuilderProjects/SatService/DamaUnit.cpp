//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DamaUnit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
TDama *Dama;
//---------------------------------------------------------------------------
__fastcall TDama::TDama(TComponent* Owner) : TComponent(Owner)
{
 for(int j=0;j<6;j++)
 {
  for(int i=0;i<3;i++)
  {
   FPS[j].B[i].Begin=90000;
   FPS[j].B[i].End=90000;
  }
  FPS[j].B[0].Begin=70000;
  FPS[j].B[0].End=73000;
 }

 for(int i=0;i<3;i++)
 {
  FP.B[i].Begin=90000;
  FP.B[i].End=90000;
 }
 FP.B[0].Begin=70000;
 FP.B[0].End=73000;
 FreqStep=1000;
 ChangeFlag=true;
}
//---------------------------------------------------------------------------
void __fastcall TDama::SetFPBegin(int n,int b,double f)
{
 FPS[n].B[b].Begin=f;
 ChangeFlag=true;
}
//---------------------------------------------------------------------------
void __fastcall TDama::SetFPEnd(int n,int b,double f)
{
 FPS[n].B[b].End=f;
 ChangeFlag=true;
}
//---------------------------------------------------------------------------
void __fastcall TDama::SetFreqStep(double f)
{
 ChangeFlag=true;
}
//---------------------------------------------------------------------------
void __fastcall TDama::SetCurrentFP(int n)
{
 memcpy(&FP,&FPS[n],sizeof(FreqPlan));
 ChangeFlag=true;
}
//---------------------------------------------------------------------------
double __fastcall TDama::GetFPSBegin(int fpsn,int row)
{
 return FPS[fpsn].B[row].Begin;
}
//---------------------------------------------------------------------------
double __fastcall TDama::GetFPSEnd(int fpsn,int row)
{ 
 return FPS[fpsn].B[row].End;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
