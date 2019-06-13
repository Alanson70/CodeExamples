//---------------------------------------------------------------------------


#ifndef BinEditFrameUnitH
#define BinEditFrameUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp> 
#include "Functions.h"
//---------------------------------------------------------------------------
class TBinEditFrame : public TFrame
{
__published:	// IDE-managed Components
        TMemo *BinEdit;
        void __fastcall BinEditKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall BinEditChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
 __fastcall TBinEditFrame(TComponent* Owner);
 
 bool _locked;
 int _sign; 
 void Sign(int sign);

 int _pos;
 char _valueArray[32];
 int _arrayMax;

 //void Type(int type);
 int _digits;
 void Digits(int digits);



 long _value;
 void Value(long value);
 void ShowValue();
 Callback OnValueChange;

 void InsertText(char *buffer);
};
//---------------------------------------------------------------------------
extern PACKAGE TBinEditFrame *BinEditFrame;
//---------------------------------------------------------------------------
#endif
