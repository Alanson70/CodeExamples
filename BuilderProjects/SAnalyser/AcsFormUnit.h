//---------------------------------------------------------------------------

#ifndef AcsFormUnitH
#define AcsFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>     
#include "AnalyserBaseFrameUnit.h"
//---------------------------------------------------------------------------
class TAcsForm : public TForm
{
__published:	// IDE-managed Components
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
 __fastcall TAcsForm(TComponent* Owner);
 
 TAnalyserBaseFrame *_frame;
 AnsiString _fileName; 
};
//---------------------------------------------------------------------------
extern PACKAGE TAcsForm *AcsForm;
//---------------------------------------------------------------------------
#endif
