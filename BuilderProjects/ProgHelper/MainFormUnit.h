//---------------------------------------------------------------------------

#ifndef MainFormUnitH
#define MainFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "ColorsFrameUnit.h"
#include "DatesFrameUnit.h"
#include "ValuesFrameUnit.h"
#include <Menus.hpp>
#include "SymbolsFrameUnit.h"
#include "DateCalcFrameUnit.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControl1;
        TTabSheet *ColorsTabSheet;
        TTabSheet *DatesTabSheet;
        TTabSheet *ValuesTabSheet;
        TDatesFrame *DatesFrame1;
        TValuesFrame *ValuesFrame1;
        TMainMenu *MainMenu1;
        TMenuItem *AboutMenuItem;
        TColorsFrame *ColorsFrame1;
        TTabSheet *SymbolsTabSheet;
        TSymbolsFrame *SymbolsFrame1;
        TTabSheet *DateCalcTabSheet;
        TDateCalcFrame *DateCalcFrame1;
        void __fastcall AboutMenuItemClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
