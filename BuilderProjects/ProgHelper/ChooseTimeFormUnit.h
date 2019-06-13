//---------------------------------------------------------------------------

#ifndef ChooseTimeFormUnitH
#define ChooseTimeFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TChooseTimeForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TImage *ImageClock;
        TEdit *HourEdit;
        TUpDown *HourUpDown;
        TEdit *MinEdit;
        TUpDown *MinUpDown;
        TButton *OkButton;
        TButton *CancelButton;
        TEdit *SecEdit;
        TUpDown *SecUpDown;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TImage *Image1;
        void __fastcall HourEditChange(TObject *Sender);
        void __fastcall MinEditChange(TObject *Sender);
        void __fastcall SecEditChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TChooseTimeForm(TComponent* Owner);
        void SetTime(TDateTime t);
        TDateTime GetTime();
        void DrawClock();
};
//---------------------------------------------------------------------------
extern PACKAGE TChooseTimeForm *ChooseTimeForm;
//---------------------------------------------------------------------------
#endif
