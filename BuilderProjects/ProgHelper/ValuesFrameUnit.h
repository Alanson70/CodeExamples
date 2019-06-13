//---------------------------------------------------------------------------


#ifndef ValuesFrameUnitH
#define ValuesFrameUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "ValueEditFrameUnit.h"
#include "BinEditFrameUnit.h"
#include "DecEditFrameUnit.h"
#include "HexEditFrameUnit.h"
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TValuesFrame : public TFrame
{
__published:	// IDE-managed Components
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label1;
        TEdit *DigitsEdit;
        TUpDown *DigitsUpDown;
        TComboBox *SignComboBox;
        TBinEditFrame *BinFrame1;
        THexEditFrame *HexFrame1;
        TDecEditFrame *DecFrame1;
        TBinEditFrame *BinFrame2;
        THexEditFrame *HexFrame2;
        TDecEditFrame *DecFrame2;
        TBinEditFrame *BinFrame3;
        THexEditFrame *HexFrame3;
        TDecEditFrame *DecFrame3;
        TButton *SumButton;
        TButton *DiffButton;
        TButton *AndButton;
        TButton *OrButton;
        TButton *XorButton;
        TButton *MultButton;
        TButton *DivButton;
        TButton *SqrtButton;
        TButton *SqwButton;
        TButton *LeftButton;
        TButton *RightButton;
        TButton *InvButton;
        TLabel *Label2;
        TLabel *Label3;
        TPopupMenu *PopupMenu1;
        TMenuItem *CutMenuItem;
        TMenuItem *CopyMenuItem;
        TMenuItem *PasteMenuItem;
        void __fastcall FormatComboBoxChange(TObject *Sender);
        void __fastcall DigitsEditChange(TObject *Sender);
        void __fastcall OperationButtonClick(TObject *Sender);
        void __fastcall SignComboBoxChange(TObject *Sender);
        void __fastcall ResultButtonClick(TObject *Sender);
        void __fastcall PopupMenuItemClick(TObject *Sender);
        void __fastcall PopupMenu1Popup(TObject *Sender);
private:	// User declarations
public:		// User declarations
 __fastcall TValuesFrame(TComponent* Owner);
 void ShowValues();

 unsigned long _value1;
 void __fastcall OnValue1Change(TObject *Sender); 
 unsigned long _value2;
 void __fastcall OnValue2Change(TObject *Sender);
 unsigned long _value3;
 void __fastcall OnValue3Change(TObject *Sender);

 int _digits;
};
//---------------------------------------------------------------------------
extern PACKAGE TValuesFrame *ValuesFrame;
//---------------------------------------------------------------------------
#endif
