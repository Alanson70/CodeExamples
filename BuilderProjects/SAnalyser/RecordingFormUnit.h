//---------------------------------------------------------------------------

#ifndef RecordingFormUnitH
#define RecordingFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TRecordingForm : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TTimer *RecTimer;
        TStaticText *RecStaticText;
        TLabel *Label33;
        TEdit *RecTimeEdit;
        TLabel *Label34;
        TEdit *RecCountEdit;
        void __fastcall RecTimerTimer(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
 __fastcall TRecordingForm(TComponent* Owner);
 TFrame *_srcFrame;
};
//---------------------------------------------------------------------------
extern PACKAGE TRecordingForm *RecordingForm;
//---------------------------------------------------------------------------
#endif
