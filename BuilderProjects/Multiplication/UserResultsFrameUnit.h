//---------------------------------------------------------------------------


#ifndef UserResultsFrameUnitH
#define UserResultsFrameUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TUserResultFrame : public TFrame
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TEdit *Edit1;
private:	// User declarations
public:		// User declarations
        __fastcall TUserResultFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TUserResultFrame *UserResultFrame;
//---------------------------------------------------------------------------
#endif
