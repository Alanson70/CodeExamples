//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FreqGrid1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
#include "FreqPlan1.h"

void __fastcall TForm3::FormShow(TObject *Sender)
{
 int Col=0;
 FreqStruct *F;
 char *OnText[2]={"Ќет","≈сть"};
 char *MText[4]={"BPSK","QPSK","8PSK","16PSK"};
 char *FECText[3]={"1/2","3/4","7/8"};

 FGrid->Cells[0][1]="„астота несущей,к√ц";
 FGrid->Cells[0][2]="—корость данных,кЅит/с";
 FGrid->Cells[0][3]="ћодул€ци€";
 FGrid->Cells[0][4]=" одирование";
 FGrid->Cells[0][5]="–ид-—оломон";
 FGrid->Cells[0][6]="ќверхед";
 FGrid->Cells[0][7]="»нформационна€ скорость,кЅит/с";
 FGrid->Cells[0][8]="Ћева€ граница,к√ц";
 FGrid->Cells[0][9]="ѕрава€ граница,к√ц";

 FGrid->ColCount=1;
 TitleEdit->Text=Form1->TitleEdit->Text;
 for(int i=0;i<MAX_FREQS;i++)
 {
  F=&Form1->FS[i];
  if(F->Enabled==true)
  {
   FGrid->ColCount++;
  }
 }
 for(int i=0;i<MAX_FREQS;i++)
 {
  F=&Form1->FS[i];
  if(F->Enabled==true)
  {
   Col++;
   FGrid->ColWidths[Col]=80;
   FGrid->Cells[Col][0]=F->Name;
   FGrid->Cells[Col][1]=F->FC;
   FGrid->Cells[Col][2]=F->DR;
   FGrid->Cells[Col][3]=MText[F->CM];
   FGrid->Cells[Col][4]=FECText[F->FEC];
   FGrid->Cells[Col][5]=OnText[F->FRS];
   FGrid->Cells[Col][6]=OnText[F->FO];
   FGrid->Cells[Col][7]=F->IR;
   FGrid->Cells[Col][8]=F->LB;
   FGrid->Cells[Col][9]=F->RB;
  }
 }
// FGrid->Cells[1][0]="";
// FGrid->Cells[1][0]="";


}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button3Click(TObject *Sender)
{
 PrinterSetupDialog1->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button1Click(TObject *Sender)
{
 //Chart1->PrintMargins.Left=0;
 //Chart1->PrintMargins.Right=0;
 //Chart1->PrintMargins.Top=0;
 //Chart1->PrintMargins.Bottom=0;
 Form1->PrintScale = poPrintToFit	;//poProportional;
 //Form3->Print();
 if(PrintDialog1->Execute()==true)
 {
  Form1->PrintScale = poNone;//poPrintToFit	;//poProportional;
  Form3->Print();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button2Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::PrinterSetupDialog1Close(TObject *Sender)
{
 Form1->PrintScale = poPrintToFit	;//poProportional;
 Form3->Print();
}
//---------------------------------------------------------------------------

