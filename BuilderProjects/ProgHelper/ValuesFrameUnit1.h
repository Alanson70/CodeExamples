//---------------------------------------------------------------------------


#ifndef ValuesFrameUnit1H
#define ValuesFrameUnit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "ValueEditFrameUnit.h"
//---------------------------------------------------------------------------
class TValuesFrame1 : public TFrame
{
__published:	// IDE-managed Components
        TEdit *HexEdit;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *BinEdit;
        TLabel *Label1;
        TComboBox *FormatComboBox;
        TEdit *DigitsEdit;
        TUpDown *DigitsUpDown;
        TComboBox *ComboBox1;
        TEdit *Edit1;
        TMemo *DecEdit;
        TValueEditFrame *ValueEditFrame1;
        void __fastcall DecEditChange(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall FormatComboBoxChange(TObject *Sender);
        void __fastcall HexEditChange(TObject *Sender);
        void __fastcall DigitsEditChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
 __fastcall TValuesFrame1(TComponent* Owner);
 void ShowValues();
 unsigned long _value;
};
//---------------------------------------------------------------------------
extern PACKAGE TValuesFrame1 *ValuesFrame1;
//---------------------------------------------------------------------------
#endif
