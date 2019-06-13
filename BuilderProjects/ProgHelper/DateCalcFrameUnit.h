//---------------------------------------------------------------------------


#ifndef DateCalcFrameUnitH
#define DateCalcFrameUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TDateCalcFrame : public TFrame
{
__published:	// IDE-managed Components
        TEdit *DateTimeStringEdit1;
        TEdit *DateTimeStringEdit2;
        TEdit *DateTimeStringEdit3;
        TButton *SumButton;
        TButton *DiffButton;
        TPopupMenu *PopupMenu1;
        TMenuItem *CutMenuItem;
        TMenuItem *CopyMenuItem;
        TMenuItem *PasteMenuItem;
        void __fastcall PopupMenuItemClick(TObject *Sender);
        void __fastcall DateTimeStringEditChange(TObject *Sender);
        void __fastcall SumButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TDateCalcFrame(TComponent* Owner);
        TDateTime _date1;
        TDateTime _date2;
        TDateTime DateTimeFromString(char *text);
};
//---------------------------------------------------------------------------
extern PACKAGE TDateCalcFrame *DateCalcFrame;
//---------------------------------------------------------------------------
#endif
