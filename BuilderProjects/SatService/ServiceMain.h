//---------------------------------------------------------------------------
#ifndef ServiceMainH
#define ServiceMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TServiceForm : public TForm
{
__published:	// IDE-managed Components
    TImage *Image1;
    TPopupMenu *PopupMenu1;
    TMenuItem *dbItem;
    TMenuItem *toKAItem;
    TMenuItem *fpItem;
    TMenuItem *closeItem;
    TMenuItem *N1;
    TTimer *Timer1;
    TMenuItem *CallItem;
    TMenuItem *azumItem;
    TMenuItem *DopplerItem;
    TMenuItem *PXYItem;
    TTimer *Timer2;
    void __fastcall Image1DblClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall closeItemClick(TObject *Sender);
    void __fastcall dbItemClick(TObject *Sender);
    void __fastcall toKAItemClick(TObject *Sender);
    void __fastcall fpItemClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall OnTimerClick(TObject *Sender);

    void __fastcall CallItemClick(TObject *Sender);
    void __fastcall ESItemClick(TObject *Sender); 
    
    void __fastcall DopplerItemClick(TObject *Sender);
    void __fastcall PXYItemClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TServiceForm(TComponent* Owner);
    void __fastcall ApplicationIdle(TObject *Sender,bool &Done);

    bool DragStatus;
    int XStart;
    int YStart;
    int DX;
    int DY;
    int Count;
    unsigned int TitleCount;
};
//---------------------------------------------------------------------------
extern PACKAGE TServiceForm *ServiceForm;
//---------------------------------------------------------------------------
#endif
