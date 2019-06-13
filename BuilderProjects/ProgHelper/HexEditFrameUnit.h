//---------------------------------------------------------------------------


#ifndef HexEditFrameUnitH
#define HexEditFrameUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>   
#include "Functions.h"
//---------------------------------------------------------------------------
class THexEditFrame : public TFrame
{
__published:	// IDE-managed Components
        TMemo *HexEdit;
        void __fastcall HexEditChange(TObject *Sender);
        void __fastcall HexEditKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
 __fastcall THexEditFrame(TComponent* Owner);

 unsigned long _maxValue;
 unsigned long _minValue;

 int _sign; 
 void Sign(int sign);

 int _digits;
 void Digits(int digits);

 long _value;
 void Value(long value);
 void ShowValue();
 Callback OnValueChange;
 
 void InsertText(char *buffer);

 bool _locked;
};
//---------------------------------------------------------------------------
extern PACKAGE THexEditFrame *HexEditFrame;
//---------------------------------------------------------------------------
#endif
