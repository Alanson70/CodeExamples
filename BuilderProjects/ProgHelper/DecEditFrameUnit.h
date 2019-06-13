//---------------------------------------------------------------------------


#ifndef DecEditFrameUnitH
#define DecEditFrameUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>   
#include "Functions.h"
//---------------------------------------------------------------------------
class TDecEditFrame : public TFrame
{
__published:	// IDE-managed Components
        TMemo *DecEdit;
        void __fastcall DecEditChange(TObject *Sender);
        void __fastcall DecEditKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall DecEditClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
 __fastcall TDecEditFrame(TComponent* Owner);
 
 unsigned long _maxValue;
 unsigned long _minValue;
 
 bool _locked;
 int _sign;
 void Sign(int sign);

 int _digits;
 void Digits(int digits);

 signed long _value;
 void Value(long value);
 void ShowValue();
 Callback OnValueChange;
 bool TestValue(double v);
                   
 void InsertText(char *buffer);
};
//---------------------------------------------------------------------------
extern PACKAGE TDecEditFrame *DecEditFrame;
//---------------------------------------------------------------------------
#endif
