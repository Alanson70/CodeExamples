//---------------------------------------------------------------------------


#ifndef ColorsFrameUnitH
#define ColorsFrameUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TColorsFrame : public TFrame
{
__published:	// IDE-managed Components
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *SummaryEdit;
        TEdit *SummaryHexEdit;
        TShape *SummaryShape;
        TShape *RedShape;
        TScrollBar *RedScrollBar;
        TScrollBar *GreenScrollBar;
        TScrollBar *BlueScrollBar;
        TShape *GreenShape;
        TShape *BlueShape;
        TEdit *BlueHexEdit;
        TEdit *GreenHexEdit;
        TEdit *RedHexEdit;
        TEdit *RedEdit;
        TEdit *GreenEdit;
        TEdit *BlueEdit;
        TLabel *Label3;
        TLabel *Label2;
        TLabel *Label1;
        TColorBox *StandartColorBox;
        TPopupMenu *ColorsPopupMenu;
        TMenuItem *CopyMenuItem;
        TMenuItem *PasteMenuItem;
        TLabel *Label4;
        TEdit *IntEdit;
        TEdit *IntHexEdit;
        TShape *IntShape;
        TScrollBar *IntScrollBar;
        void __fastcall ScrollBarChange(TObject *Sender);
        void __fastcall EditChange(TObject *Sender);
        void __fastcall HexEditChange(TObject *Sender);
        void __fastcall SummaryEditChange(TObject *Sender);
        void __fastcall SummaryHexEditChange(TObject *Sender);
        void __fastcall StandartColorBoxChange(TObject *Sender);
        void __fastcall ColorsMenuItemClick(TObject *Sender);
        void __fastcall ColorsPopupMenuPopup(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TColorsFrame(TComponent* Owner);
 void EditsChange();
 void SummaryChange();
 void ScrollsChange();
};
//---------------------------------------------------------------------------
extern PACKAGE TColorsFrame *ColorsFrame;
//---------------------------------------------------------------------------
#endif
