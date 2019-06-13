//---------------------------------------------------------------------------

#ifndef UserEditUnitH
#define UserEditUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TUserEditForm : public TForm
{
__published:	// IDE-managed Components
    TButton *EditButton;
    TEdit *UserEdit;
    void __fastcall UserEditChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TUserEditForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TUserEditForm *UserEditForm;
//---------------------------------------------------------------------------
#endif
