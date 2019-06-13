//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "PG1_Unit.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPG1Form *PG1Form;
//---------------------------------------------------------------------------
__fastcall TPG1Form::TPG1Form(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPG1Form::FormShow(TObject *Sender)
{
 ScrollBarChange(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TPG1Form::ScrollBarChange(TObject *Sender){
 double PM=0;
 KUTZSEdit->Text=ZS.KUT=KUTZSScrollBar->Position/10.0;
 KURZSEdit->Text=ZS.KUR=KURZSScrollBar->Position/10.0;
 QZSEdit->Text=ZS.Q=QZSScrollBar->Position/10.0;
 LSNEdit->Text=ZS.LSN=LSNScrollBar->Position/10.0;
 LAFUEdit->Text=ZS.LAFU=LAFUScrollBar->Position/10.0;
 SSEdit->Text=ZS.SS=SSScrollBar->Position/10.0;
 POUTEdit->Text=ZS.P=POUTScrollBar->Position/10.0;
 BEdit->Text=ZS.B=BScrollBar->Position/10.0;

 KUKAEdit->Text=KA.KU=KUKAScrollBar->Position/10.0;
 EKAEdit->Text=KA.E=EKAScrollBar->Position/10.0;
 QKAEdit->Text=KA.Q=QKAScrollBar->Position/10.0;
 FUPEdit->Text=KA.FUP=FUPScrollBar->Position;
 FDNEdit->Text=KA.FDN=FDNScrollBar->Position;
 SSKAEdit->Text=KA.SS=SSKAScrollBar->Position/10.0;
 dEdit->Text=KA.d=dScrollBar->Position;
 KBEdit->Text=KA.KB=-228.6;
 LZSKAEdit->Text=KA.LZSKA=LZSKAScrollBar->Position/10.0;
 LKAZSEdit->Text=KA.LKAZS=LKAZSScrollBar->Position/10.0;
 //WZSKAEdit->Text=KA.WZSKA=10*log10(pow(300.0/KA.FUP,2)); //WZSKAScrollBar->Position/(-10.0);
 //WKAZSEdit->Text=KA.WKAZS=10*log10(pow(300.0/KA.FDN,2));  //WKAZSScrollBar->Position/(-10.0);
 KA.WZSKA=10*log10(pow(300.0/KA.FUP,2));
 KA.WKAZS=10*log10(pow(300.0/KA.FDN,2));
 KA.KB1=1.38*pow(10,-23);
 PM=10*log10(pow(4*M_PI*KA.d*1000,2));

 EZSEdit->Text=ZS.E=    PM+KA.KB+ZS.B+KA.LZSKA-KA.Q-KA.WZSKA+KA.SS;
 PPKAEdit->Text=KA.PP=  PM+KA.KB+ZS.B+KA.LKAZS-ZS.Q-KA.WKAZS+ZS.SS;

 EZSEditM->Text=ZS.EM=  PM+KA.KB+ZS.B+KA.LZSKA-KA.Q-KA.WZSKA+7+ZS.SS;
 PPKAEditM->Text=KA.PPM=PM+KA.KB+ZS.B+KA.LKAZS-ZS.Q-KA.WKAZS+1+ZS.SS;

 EMZSEdit->Text=pow(10,(ZS.E-ZS.KUT)/10.0);
 PPMKAEdit->Text=pow(10,(KA.PP-KA.KU)/10.0);
 EMZSEditM->Text=pow(10,(ZS.EM-ZS.KUT)/10.0);
 PPMKAEditM->Text=pow(10,(KA.PPM-KA.KU)/10.0);

 EZSEditS->Text=pow(10,(ZS.P)/10.0);
 PPKAEditS->Text=pow(10,(KA.E-KA.KU)/10.0);
}
//---------------------------------------------------------------------------


