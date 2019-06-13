//---------------------------------------------------------------------------
#ifndef AUdb1H
#define AUdb1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TUADBForm : public TForm
{
__published:	// IDE-managed Components
    TPopupMenu *PopupMenu1;
    TMenuItem *AddItem;
    TMenuItem *ChangeItem;
    TMenuItem *DeleteItem;
    TDBGrid *DBGrid1;
    TMenuItem *N1;

    TMenuItem *PrintItem;
    TMenuItem *CloseItem;
    void __fastcall AddItemClick(TObject *Sender);
    void __fastcall ChangeItemClick(TObject *Sender);
    void __fastcall DeleteItemClick(TObject *Sender);
    void __fastcall FormChange();
    void __fastcall FormShow(TObject *Sender);
    void __fastcall PrintItemClick(TObject *Sender);
    void __fastcall CloseItemClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TUADBForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TUADBForm *UADBForm;
//---------------------------------------------------------------------------
#endif
 