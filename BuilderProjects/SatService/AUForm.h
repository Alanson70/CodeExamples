//---------------------------------------------------------------------------
#ifndef AUFormH
#define AUFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TAUGridForm : public TForm
{
__published:	// IDE-managed Components
    TStringGrid *Grid1;
    TPopupMenu *PopupMenu1;
    TMenuItem *AddItem;
    TMenuItem *ChangeItem;
    TMenuItem *DeleteItem;
    TMenuItem *PrintItem;
    TMenuItem *N1;
    TMenuItem *CloseItem;
    void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TAUGridForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAUGridForm *AUGridForm;
//---------------------------------------------------------------------------
#endif
