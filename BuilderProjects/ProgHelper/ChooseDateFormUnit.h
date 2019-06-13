//---------------------------------------------------------------------------

#ifndef ChooseDateFormUnitH
#define ChooseDateFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CCALENDR.h"
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TChooseDateForm : public TForm
{
__published:	// IDE-managed Components
        TCCalendar *Calendar;
        TButton *OkButton;
        TButton *CancelButton;
        TButton *LeftButton;
        TButton *RightButton;
        TComboBox *MonthComboBox;
        TEdit *YearEdit;
        void __fastcall CalendarChange(TObject *Sender);
        void __fastcall LeftButtonClick(TObject *Sender);
        void __fastcall RightButtonClick(TObject *Sender);
        void __fastcall YearEditChange(TObject *Sender);
        void __fastcall MonthComboBoxChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TChooseDateForm(TComponent* Owner);
        void SetDate(TDateTime date);
        TDateTime  GetDate();
        TDateTime _minDate;
        TDateTime _maxDate;
        void SetCurrentYearLimits(TDateTime date);
};
//---------------------------------------------------------------------------
extern PACKAGE TChooseDateForm *ChooseDateForm;
//---------------------------------------------------------------------------
#endif
