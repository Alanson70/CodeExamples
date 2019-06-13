//---------------------------------------------------------------------------

#include <vcl.h>  
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#pragma hdrstop

#include "ColorsFrameUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TColorsFrame *ColorsFrame;
//---------------------------------------------------------------------------
__fastcall TColorsFrame::TColorsFrame(TComponent* Owner)
        : TFrame(Owner)
{  
 this->DoubleBuffered=true;
 StandartColorBox->DoubleBuffered=true;
}
//---------------------------------------------------------------------------
void TColorsFrame::EditsChange()
{
}

//---------------------------------------------------------------------------
void TColorsFrame::SummaryChange()
{

}
//---------------------------------------------------------------------------
void TColorsFrame::ScrollsChange()
{
}
//---------------------------------------------------------------------------
void __fastcall TColorsFrame::ScrollBarChange(TObject *Sender)
{
 char buffer[25];
 unsigned long color=0;
 unsigned long sumColor=0;

 TControl *control=(TControl *)Sender;
 if(control->Tag==1) return;
 control->Tag=1;

 color=RedScrollBar->Position;
 sumColor=sumColor|color;
 RedEdit->Text=RedScrollBar->Position;
 sprintf(buffer,"%2.2X",RedScrollBar->Position);
 RedHexEdit->Text=buffer;
 RedShape->Brush->Color=TColor(color);

 color=GreenScrollBar->Position<<8;
 sumColor=sumColor|color;
 GreenEdit->Text=GreenScrollBar->Position;
 sprintf(buffer,"%2.2X",GreenScrollBar->Position);
 GreenHexEdit->Text=buffer;
 GreenShape->Brush->Color=TColor(color);

 color=BlueScrollBar->Position<<16;
 sumColor=sumColor|color;
 BlueEdit->Text=BlueScrollBar->Position;
 sprintf(buffer,"%2.2X",BlueScrollBar->Position);
 BlueHexEdit->Text=buffer;
 BlueShape->Brush->Color=TColor(color);

 color=IntScrollBar->Position<<24;
 sumColor=sumColor|color;
 IntEdit->Text=IntScrollBar->Position;
 sprintf(buffer,"%2.2X",IntScrollBar->Position);
 IntHexEdit->Text=buffer;
 IntShape->Brush->Color=TColor(color);

 if(SummaryEdit->Tag==0)
 {
  SummaryEdit->Text=sumColor;
 }
 if(SummaryHexEdit->Tag==0)
 {
  sprintf(buffer,"%8.8X",sumColor);
  SummaryHexEdit->Text=buffer;
 }
 SummaryShape->Brush->Color=TColor(sumColor);
 if(StandartColorBox->Tag==0)
 {
  StandartColorBox->Selected=TColor(sumColor);
  StandartColorBox->Invalidate();
 }

 control->Tag=0;
}
//---------------------------------------------------------------------------
void __fastcall TColorsFrame::EditChange(TObject *Sender)
{
 TEdit *edit=(TEdit *)Sender;
 if(edit->Tag==1) return;
 edit->Tag=1;

 unsigned long color=0;

 char buffer[10];

 strncpy(buffer,edit->Text.c_str(),4);
 buffer[4]=0;
 int j=0;
 for(int i=0;i<strlen(buffer);i++)
 {
  if(isdigit(buffer[i])!=0) buffer[j++]=buffer[i];
 }
// if(j==0) buffer[j++]='0';
 buffer[j]=0;
 if(j!=0)
 {
  color=atol(buffer);
  if(color>255) color=255;

  TScrollBar *scrollBar=IntScrollBar;

  if(edit==RedEdit) scrollBar=RedScrollBar;
  else
  if(edit==GreenEdit) scrollBar=GreenScrollBar;
  else
  if(edit==BlueEdit) scrollBar=BlueScrollBar;

  scrollBar->Position=color;
   
  if(scrollBar->Tag==0)  scrollBar->Position=color;
 }
 edit->Text=buffer;
 edit->Tag=0;
}
//---------------------------------------------------------------------------
void __fastcall TColorsFrame::HexEditChange(TObject *Sender)
{  
 TEdit *edit=(TEdit *)Sender;
 if(edit->Tag==1) return;
 edit->Tag=1;

 int pos=edit->SelStart;

 unsigned long color=0;
 char buffer[10];

 strncpy(buffer,edit->Text.c_str(),3); 
 buffer[3]=0;
 int j=0;
 for(int i=0;i<strlen(buffer);i++)
 {
  if(isxdigit(buffer[i])!=0) buffer[j++]=buffer[i];
 }
// if(j==0) buffer[j++]='0';
 buffer[j]=0;
 if(j!=0)
 {
  sscanf(buffer,"%2X",&color);
  if(color>255) color=255;

  TScrollBar *scrollBar=BlueScrollBar;
  if(edit==RedHexEdit) scrollBar=RedScrollBar;
  else
  if(edit==GreenHexEdit) scrollBar=GreenScrollBar;

  if(scrollBar->Tag==0)  scrollBar->Position=color;

  sprintf(buffer,"%X",color);
 }
 edit->Text=buffer;
 if(pos>strlen(buffer)) pos=strlen(buffer);
 edit->SelStart=pos;

 edit->Tag=0;
}
//---------------------------------------------------------------------------
void __fastcall TColorsFrame::SummaryEditChange(TObject *Sender)
{   
 TEdit *edit=(TEdit *)Sender;
 if(edit->Tag==1) return;
 edit->Tag=1;

 unsigned long color=0;

 char buffer[15];

 strncpy(buffer,edit->Text.c_str(),10);
 buffer[11]=0;
 int j=0;
 for(int i=0;i<strlen(buffer);i++)
 {
  if(isdigit(buffer[i])!=0) buffer[j++]=buffer[i];
 }
// if(j==0) buffer[j++]='0';
 buffer[j]=0;
 if(j!=0)
 {
  color=atol(buffer);
  if(color>0xFFFFFFFF) color=0xFFFFFFFF;
  if(RedScrollBar->Tag==0)    RedScrollBar->Position=color&0xFF;
  if(GreenScrollBar->Tag==0)  GreenScrollBar->Position=(color>>8)&0xFF;
  if(BlueScrollBar->Tag==0)   BlueScrollBar->Position=(color>>16)&0xFF; 
  if(IntScrollBar->Tag==0)    IntScrollBar->Position=(color>>24)&0xFF;
 }
 edit->Text=buffer;
 edit->Tag=0;
}
//---------------------------------------------------------------------------
void __fastcall TColorsFrame::SummaryHexEditChange(TObject *Sender)
{
 TEdit *edit=(TEdit *)Sender;
 if(edit->Tag==1) return;
 edit->Tag=1;

 int pos=edit->SelStart;

 unsigned long color=0;
 char buffer[15];

 strncpy(buffer,edit->Text.c_str(),8);
 buffer[8]=0;
 int j=0;
 for(int i=0;i<strlen(buffer);i++)
 {
  if(isxdigit(buffer[i])!=0) buffer[j++]=buffer[i];
 }
// if(j==0) buffer[j++]='0';
 buffer[j]=0;
 if(j!=0)
 {
  long c=0;
  sscanf(buffer,"%X",&color); 
  if(color>0xFFFFFFFF) color=0xFFFFFFFF;
  //color=color<<((6-strlen(buffer))*4);
  c=color&0xFF;
  RedScrollBar->Position=c;
  c=(color>>8)&0xFF;
  GreenScrollBar->Position=c;
  c=(color>>16)&0xFF;
  BlueScrollBar->Position=c;
  c=(color>>24)&0xFF;
  IntScrollBar->Position=c;
  //sprintf(buffer,"%X",color);
 }
 edit->Text=buffer;
 if(pos>strlen(buffer)) pos=strlen(buffer);
 edit->SelStart=pos;

 edit->Tag=0;
}
//---------------------------------------------------------------------------
void __fastcall TColorsFrame::StandartColorBoxChange(TObject *Sender)
{
 TControl *control=(TControl *)Sender;
 if(control->Tag==1) return;
 control->Tag=1;

 SummaryEdit->Text=(unsigned long)StandartColorBox->Selected;

 control->Tag=0;
}
//---------------------------------------------------------------------------
#include <vcl\Clipbrd.hpp>
void __fastcall TColorsFrame::ColorsMenuItemClick(TObject *Sender)
{
 TMenuItem *item=(TMenuItem *)Sender;

 TControl *c=(TControl *)(((TPopupMenu *)(item->GetParentMenu()))->PopupComponent);
 TEdit *edit=NULL;
 if(c->InheritsFrom(__classid(TEdit))) edit=(TEdit *)c;

 else return;
 switch(item->Tag)
 {
  case 0 : // copy
  {
   char buffer[200];
   if(edit->SelLength>0) strncpy(buffer,edit->SelText.c_str(),199);
   else                  strncpy(buffer,edit->Text.c_str(),199);

   Clipboard()->SetTextBuf(buffer);
  }
  break;

  case 1 :  // paste
  {
   char buffer[100];
   strncpy(buffer,Clipboard()->AsText.c_str(),25);

   edit->Text=buffer;
  }
  break;

 }
}
//---------------------------------------------------------------------------

void __fastcall TColorsFrame::ColorsPopupMenuPopup(TObject *Sender)
{
 PasteMenuItem->Enabled=false;

 TControl *c=(TControl *)(((TPopupMenu *)Sender)->PopupComponent);
 TEdit *edit=NULL;
 if(c->InheritsFrom(__classid(TEdit))) edit=(TEdit *)c;
 else return;

 char buffer[100];
 strncpy(buffer,Clipboard()->AsText.c_str(),25);

 if(strlen(buffer)>edit->MaxLength) return;
 if(edit->MaxLength==2)
 for(int i=0;i<strlen(buffer);i++)
 {
  if(isxdigit(buffer[i])==0) return;
 }
 else
 for(int i=0;i<strlen(buffer);i++)
 {
  if(isdigit(buffer[i])==0) return;
 }

 PasteMenuItem->Enabled=true;
}
//---------------------------------------------------------------------------

