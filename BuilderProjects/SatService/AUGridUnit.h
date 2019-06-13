//---------------------------------------------------------------------------
#ifndef AUGridUnitH
#define AUGridUnitH
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
    TMenuItem *SaveItem;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall AddItemClick(TObject *Sender);
    void __fastcall ChangeItemClick(TObject *Sender);
    void __fastcall DeleteItemClick(TObject *Sender);
    void __fastcall PrintItemClick(TObject *Sender);
    void __fastcall CloseItemClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall SaveItemClick(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
    __fastcall TAUGridForm(TComponent* Owner);
    void __fastcall FormChange();
    void __fastcall LoadFromIniFile();
    void __fastcall SaveToIniFile();
    bool ChangeFlag;
    bool CloseFlag;
    AnsiString FileName;
};
//---------------------------------------------------------------------------
extern PACKAGE TAUGridForm *AUGridForm;
//---------------------------------------------------------------------------
#endif
