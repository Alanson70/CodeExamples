//---------------------------------------------------------------------------


#ifndef SymbolsFrameUnitH
#define SymbolsFrameUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DecEditFrameUnit.h"
#include "HexEditFrameUnit.h"
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TSymbolsFrame : public TFrame
{
__published:	// IDE-managed Components
        TEdit *Edit2;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        THexEditFrame *HexEditFrame1;
        TDecEditFrame *DecEditFrame1;
        TPanel *Panel1;
        TEdit *LetterEdit;
        TEdit *Edit1;
        TPopupMenu *SymbolsPopupMenu;
        TMenuItem *CopyMenuItem;
        TMenuItem *PasteMenuItem;
        void __fastcall LetterEditChange(TObject *Sender);
        void __fastcall Edit2Change(TObject *Sender);
        void __fastcall PasteMenuItemClick(TObject *Sender);
        void __fastcall CopyMenuItemClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
 __fastcall TSymbolsFrame(TComponent* Owner);

 char _value1;
 void __fastcall OnValue1Change(TObject *Sender);
};
//---------------------------------------------------------------------------
extern PACKAGE TSymbolsFrame *SymbolsFrame;
//---------------------------------------------------------------------------
#endif
