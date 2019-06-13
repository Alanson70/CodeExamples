//---------------------------------------------------------------------------
#ifndef FPEditUnitH
#define FPEditUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFPForm : public TForm
{
__published:	// IDE-managed Components
    TLabel *FreqBeginLabel;
    TLabel *FreqEndLabel;
    TEdit *FreqBeginEdit1;
    TEdit *FreqEndEdit1;
    TScrollBar *FreqBeginScrollBar1;
    TScrollBar *FreqEndScrollBar1;
    TEdit *FreqBeginEdit2;
    TEdit *FreqEndEdit2;
    TScrollBar *FreqBeginScrollBar2;
    TScrollBar *FreqEndScrollBar2;
    TEdit *FreqBeginEdit3;
    TEdit *FreqEndEdit3;
    TScrollBar *FreqBeginScrollBar3;
    TScrollBar *FreqEndScrollBar3;
    TButton *Button1;
    TButton *Button2;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FreqBeginScrollBarChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFPForm(TComponent* Owner); 
int fpsn;
};
//---------------------------------------------------------------------------
extern PACKAGE TFPForm *FPForm;
//---------------------------------------------------------------------------
#endif
