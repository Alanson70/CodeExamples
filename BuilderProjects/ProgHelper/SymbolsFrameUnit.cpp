//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SymbolsFrameUnit.h" 
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DecEditFrameUnit"
#pragma link "HexEditFrameUnit"
#pragma resource "*.dfm"

TSymbolsFrame *SymbolsFrame;
//---------------------------------------------------------------------------
__fastcall TSymbolsFrame::TSymbolsFrame(TComponent* Owner) : TFrame(Owner)
{
 HexEditFrame1->Digits(8);
 DecEditFrame1->Digits(8);

 DecEditFrame1->Value('A');
 HexEditFrame1->Value('A');

 DecEditFrame1->OnValueChange=OnValue1Change;
 HexEditFrame1->OnValueChange=OnValue1Change;
 //AnsiToHex
 //AnsiToUtf8
} 
//---------------------------------------------------------------------------
void __fastcall TSymbolsFrame::OnValue1Change(TObject *Sender)
{
 if(Sender->InheritsFrom(__classid(TDecEditFrame)))
  _value1=(char)((TDecEditFrame *)Sender)->_value;
 else
 if(Sender->InheritsFrom(__classid(THexEditFrame)))
  _value1=(char)((THexEditFrame *)Sender)->_value;
 else
 if(Sender->InheritsFrom(__classid(TEdit)))
  _value1=LetterEdit->Text.operator[](1);
 else
 return;

 DecEditFrame1->Value(_value1);
 HexEditFrame1->Value(_value1);
 LetterEdit->Text=(char)_value1;
}
//---------------------------------------------------------------------------
void __fastcall TSymbolsFrame::LetterEditChange(TObject *Sender)
{
 if(LetterEdit->Tag!=0) return;
 LetterEdit->Tag=1;
 OnValue1Change(Sender); 
 LetterEdit->Tag=0;
}
//---------------------------------------------------------------------------
void __fastcall TSymbolsFrame::Edit2Change(TObject *Sender)
{
 char buffer[100];

 buffer[0]=0;
 for(int i=0;i<Edit2->Text.Length();i++)
  sprintf(buffer+strlen(buffer),"%2.2X ",(unsigned char)Edit2->Text[i+1]);
 Edit1->Text=buffer;
}
//---------------------------------------------------------------------------

#include <vcl\Clipbrd.hpp>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
void __fastcall TSymbolsFrame::PasteMenuItemClick(TObject *Sender)
{
 //TControl *c=(TControl *)(((TPopupMenu *)Sender)->PopupComponent);
 TEdit *edit=NULL;
 //if(c->InheritsFrom(__classid(TEdit)))

 edit=Edit2;//(TEdit *)c;
 //else return;

 char buffer[100];

 //AnsiToUtf8
 strncpy(buffer,(char *)(Clipboard()->AsText.data()),25);

 edit->Text=buffer;
}
//---------------------------------------------------------------------------

void __fastcall TSymbolsFrame::CopyMenuItemClick(TObject *Sender)
{
 //
}
//---------------------------------------------------------------------------

