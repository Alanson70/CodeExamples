//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Ess2SatFormUnit.h"
#include "AboutFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAzEl2SatForm *AzEl2SatForm;

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI M_PI
#define RadToDeg  (180.0/PI)
#define DegToRad  (M_PI/180.0)

double KA,SHIR,DOL,AZ,UM,dDOL,dSHIR;
double _distance;
bool ChangeFlag;
int PosFlag;




//---------------------------------------------------------------------------
__fastcall TAzEl2SatForm::TAzEl2SatForm(TComponent* Owner)
        : TForm(Owner)
{
 PosFlag=-1; 
 DOLScrollBar1Change(NULL);
 SHIRScrollBar1Change(NULL);
 MapPanel->DoubleBuffered=true;
}
//---------------------------------------------------------------------------
void __fastcall TAzEl2SatForm::SatScrollChange(TObject *Sender)
{
 //SatImage->Left=MapImage->Left+SatScroll->Position*((MapImage->Width-SatImage->Width)/180.0);
}
//---------------------------------------------------------------------------
void __fastcall TAzEl2SatForm::LongScrollChange(TObject *Sender)
{
 //AntImage->Left=MapImage->Left+LongScroll->Position*((MapImage->Width-AntImage->Width)/180.0);
}
//---------------------------------------------------------------------------
void __fastcall TAzEl2SatForm::LatScrollChange(TObject *Sender)
{
 //AntImage->Top=MapImage->Top+LatScroll->Position*((LatScroll->Height-AntImage->Height)/90.0);
}
//---------------------------------------------------------------------------
void __fastcall TAzEl2SatForm::ScrollBarChange(TObject *Sender)
{
 char s[20];
 double R=6371.0;
 double H=42170.0;

 DOL=DegToRad*(DOLScrollBar->Position+dDOL);
 sprintf(s,"%3.1d°%2.2d'",DOLScrollBar->Position,DOLScrollBar1->Position);
 DOLEdit->Text=AnsiString(s);
 sprintf(s,"%3.1d,%2.2d",DOLScrollBar->Position,DOLScrollBar2->Position);
 DOLEdit1->Text=AnsiString(s);

 SHIR=DegToRad*(SHIRScrollBar->Position+dSHIR);
 sprintf(s,"%3.1d°%2.2d'",SHIRScrollBar->Position,SHIRScrollBar1->Position);
 SHIREdit->Text=AnsiString(s);
 sprintf(s,"%3.1d,%2.2d",SHIRScrollBar->Position,SHIRScrollBar2->Position);
 SHIREdit1->Text=AnsiString(s);

 KA=DegToRad*(KAScrollBar->Position/10.0);
 sprintf(s,"%5.1lf°",KAScrollBar->Position/10.0);
 KAEdit->Text=AnsiString(s);

 if(SHIR<0)
  if(DOL>KA) AZ=RadToDeg*(atan(sin(KA-DOL)/(-1*sin(SHIR)*cos(KA-DOL)))+2*PI);
  else       AZ=RadToDeg*(atan(sin(KA-DOL)/(-1*sin(SHIR)*cos(KA-DOL))));
 if(SHIR>0)  AZ=RadToDeg*(atan(sin(KA-DOL)/(-1*sin(SHIR)*cos(KA-DOL)))+1*PI);
 if(SHIR==0)
  if(DOL>KA) AZ=90;
  else AZ=270;

 UM=RadToDeg*asin((H*cos(SHIR)*cos(KA-DOL)-R)/
    sqrt(R*R+H*H-2*R*H*cos(SHIR)*cos(KA-DOL)));

 
 _distance=42644.0 * sqrt (1.0-0.2954*cos((SHIR*2*M_PI)/360)*cos(2*M_PI*fabs(DOL-KA)/360));

 sprintf(s,"%3.1d°%2.2d'",(int)AZ,abs((int)((AZ-(int)AZ)*60)));
 AzEdit->Text=AnsiString(s);
 sprintf(s,"%3.1d°%2.2d'",(int)UM,abs((int)((UM-(int)UM)*60)));
 ElEdit->Text=AnsiString(s);
 DistanceEdit->Text=_distance;


 SatImage->Left=MapImage->Left-SatImage->Width/2+(KAScrollBar->Position/10.0)*((MapImage->Width)/((KAScrollBar->Max-KAScrollBar->Min)/10.0));
 //AntImage->Left=(MapImage->Left+(120+DOLScrollBar->Position)*(MapImage->Width-AntImage->Width))/((DOLScrollBar->Max-DOLScrollBar->Min));
 AntImage->Left=(MapImage->Left-AntImage->Width/2+(0+DOLScrollBar->Position)*(MapImage->Width-AntImage->Width))/((DOLScrollBar->Max-DOLScrollBar->Min));
 AntImage->Top=(MapImage->Top+(90-SHIRScrollBar->Position)*(MapImage->Height*0.75-AntImage->Height))/((SHIRScrollBar->Max-SHIRScrollBar->Min));

}
//---------------------------------------------------------------------------

void __fastcall TAzEl2SatForm::DOLScrollBar1Change(TObject *Sender)
{
  if(ChangeFlag==true) return;
 ChangeFlag=true;
 dDOL=DOLScrollBar1->Position/60.0;
 DOLScrollBar2->Position=DOLScrollBar1->Position/0.6;
 ScrollBarChange(Sender);
 ChangeFlag=false;       
}
//---------------------------------------------------------------------------

void __fastcall TAzEl2SatForm::DOLScrollBar2Change(TObject *Sender)
{
  if(ChangeFlag==true) return;
 ChangeFlag=true;
 dSHIR=SHIRScrollBar2->Position/100.0;
 SHIRScrollBar1->Position=SHIRScrollBar2->Position*0.6;
 ScrollBarChange(Sender);
 ChangeFlag=false;       
}
//---------------------------------------------------------------------------

void __fastcall TAzEl2SatForm::SHIRScrollBar1Change(TObject *Sender)
{
  if(ChangeFlag==true) return;
 ChangeFlag=true;
 dSHIR=SHIRScrollBar1->Position/60.0;
 SHIRScrollBar2->Position=SHIRScrollBar1->Position/0.6;
 ScrollBarChange(Sender);
 ChangeFlag=false;
}
//---------------------------------------------------------------------------

void __fastcall TAzEl2SatForm::SHIRScrollBar2Change(TObject *Sender)
{
 if(ChangeFlag==true) return;
 ChangeFlag=true;
 dSHIR=SHIRScrollBar2->Position/100.0;
 SHIRScrollBar1->Position=SHIRScrollBar2->Position*0.6;
 ScrollBarChange(Sender);
 ChangeFlag=false;
}
//---------------------------------------------------------------------------


void __fastcall TAzEl2SatForm::InfoBtnClick(TObject *Sender)
{
 TAboutForm *form=new TAboutForm(this);
 try
 {
  form->ShowModal();
  delete form;
 }
 catch(...)
 {
  delete form;
 }

}
//---------------------------------------------------------------------------

