//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "PG_MainUnit.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPGForm *PGForm;
//---------------------------------------------------------------------------
__fastcall TPGForm::TPGForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPGForm::FormShow(TObject *Sender)
{
 ChangeFlag=true;

 KB=-228.6;
 D=40000000;
 TNKA=26.3;
 TNZS=20;
 EKA=36.7;
 GTKA=0.2;
 GKA=26.5;
 GTZS=38.3;
 GRZS=43.4;
 PXY=0.5;
 PAF=0.5;
 PSN=7.6;
 FTM=6400;
 FRM=4075;
 LT=0.05;
 LR=0.08;
 PLZSKA=2;
 PLKAZS=1;
 PKZSKA=6;
 PKKAZS=6;
 RINF=64000;
 B=76800;
 FEC=0.5;
 W=-34.6;
 KU=110;

 ScrollBar1->Position=TNKA*10;
 ScrollBar2->Position=TNZS*10;
 ScrollBar3->Position=EKA*10;
 ScrollBar4->Position=GTKA*10;
 ScrollBar5->Position=GKA*10;
 ScrollBar6->Position=GTZS*10;
 ScrollBar7->Position=GRZS*10;
 ScrollBar8->Position=PXY*10;
 ScrollBar9->Position=PAF*10;
 ScrollBar10->Position=PSN*10;
 ScrollBar11->Position=FTM;
 ScrollBar12->Position=FRM;
 ScrollBar13->Position=LT*100;
 ScrollBar14->Position=LR*100;
 ScrollBar15->Position=PLZSKA*10;
 ScrollBar16->Position=PLKAZS*10;
 ScrollBar17->Position=PKZSKA*10;
 ScrollBar18->Position=PKKAZS*10;
 ScrollBar19->Position=RINF/1000;

 ComboBox21->ItemIndex=0;
 //ScrollBar1->Position=;
 //ScrollBar1->Position=;
 ScrollBar22->Position=W*(-10.0);
 ScrollBar23->Position=KU*10;

 ChangeFlag=false;
 OnChange(Sender);
}

double FEC_Struct[4]=
{
 1.0/2,
 2.0/3,
 3.0/4,
 7.0/8,
};

void __fastcall TPGForm::OnChange(TObject *Sender)
{
 if(ChangeFlag==true) return;
 ChangeFlag=true;

 TNKA=ScrollBar1->Position/10.0;
 TNZS=ScrollBar2->Position/10.0;
 EKA=ScrollBar3->Position/10.0;
 GTKA=ScrollBar4->Position/10.0;
 GKA=ScrollBar5->Position/10.0;
 GTZS=ScrollBar6->Position/10.0;
 GRZS=ScrollBar7->Position/10.0;
 PXY=ScrollBar8->Position/10.0;
 PAF=ScrollBar9->Position/10.0;
 PSN=ScrollBar10->Position/10.0;
 FTM=ScrollBar11->Position;
 FRM=ScrollBar12->Position;
 LT=ScrollBar13->Position/100.0;
 LR=ScrollBar14->Position/100.0;
 PLZSKA=ScrollBar15->Position/10.0;
 PLKAZS=ScrollBar16->Position/10.0;
 PKZSKA=ScrollBar17->Position/10.0;
 PKKAZS=ScrollBar18->Position/10.0;
 RINF=ScrollBar19->Position*1000;
 FEC=FEC_Struct[ComboBox21->ItemIndex];
 B=10*log10(RINF*1.2/(2*FEC));
 W=ScrollBar22->Position/(-10.0);
 KU=ScrollBar23->Position/10.0;


 Edit1->Text=TNKA;
 Edit2->Text=TNZS;
 Edit3->Text=EKA;
 Edit4->Text=GTKA;
 Edit5->Text=GKA;
 Edit6->Text=GTZS;
 Edit7->Text=GRZS;
 Edit8->Text=PXY;
 Edit9->Text=PAF;
 Edit10->Text=PSN;
 Edit11->Text=FTM;
 Edit12->Text=FRM;
 Edit13->Text=LT;
 Edit14->Text=LR;
 Edit15->Text=PLZSKA;
 Edit16->Text=PLKAZS;
 Edit17->Text=PKZSKA;
 Edit18->Text=PKKAZS;
 Edit19->Text=RINF;
 Edit20->Text=pow(10,B/10);
 Edit20db->Text=B;
 Edit21->Text=FEC;
 Edit22->Text=W;
 Edit23->Text=KU;

 Recount(Sender);
 Edit24->Text=KB;
 Edit25->Text=D;
 Edit26->Text=L0;
 Edit26a->Text=L0a;
 Edit27->Text=PZS;
 Edit28->Text=EZS;
 Edit29->Text=PINKA;
 Edit30->Text=PINNKA;
 Edit31->Text=PSNKA;
 Edit32->Text=POUTKA;
 Edit33->Text=POUTNKA;
 Edit34->Text=EPKA;
 Edit35->Text=PINZS;
 Edit36->Text=PNZS;
 Edit37->Text=PSNZS;
 Edit38->Text=PINNZS;
 Edit39->Text=PNCZS;
 Edit40->Text=SNNC;
 ChangeFlag=false;
}

void __fastcall TPGForm::Recount(TObject *Sender)
{
 L0=10*log10(16*M_PI*M_PI*D*D/(LT*LT));
 L0a=10*log10(16*M_PI*M_PI*D*D/(LR*LR));
 PZS=W+B;
 EZS=PZS+GTZS;
 PINKA=EZS-L0-PLZSKA-PKZSKA+GKA;
 PINNKA=KB+TNKA+B;
 PSNKA=PINKA-PINNKA;
 POUTKA=PINKA+KU;
 POUTNKA=PINNKA+KU;
 EPKA=PINKA+KU+GKA;
 PINZS=EPKA-L0a-PLKAZS-PKKAZS+GRZS;
 PNZS=KB+TNZS+B;
 PSNZS=PINZS-PNZS;
 PINNZS=POUTNKA+GKA-L0a-PLKAZS-PKKAZS+GRZS;
 PNCZS=10*log10(pow(10,PINNZS/10)+pow(10,PNZS/10));
 SNNC=PINZS-PNCZS;
}
//---------------------------------------------------------------------------
