//---------------------------------------------------------------------------


#ifndef ValueEditFrameUnitH
#define ValueEditFrameUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TValueEditFrame : public TFrame
{
__published:	// IDE-managed Components
        TMemo *Edit;
        void __fastcall EditChange(TObject *Sender);
        void __fastcall EditKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
 unsigned long _value;
 unsigned int _type;
 unsigned long _maxValue;
 unsigned int _digits;
 unsigned int _maxPos;
 int _pos;
 char _buffer[25];
public:		// User declarations
 __fastcall TValueEditFrame(TComponent* Owner);

 void Value(unsigned long value);
 unsigned long Value();

 void Digits(unsigned int value);
 unsigned long MaxValue();

 void Type(int type);
 int Type();

 void DecEdit();
 void HexEdit();
 void BinEdit();

 void ShowValue();
};
//---------------------------------------------------------------------------
extern PACKAGE TValueEditFrame *ValueEditFrame;
//---------------------------------------------------------------------------
#endif
