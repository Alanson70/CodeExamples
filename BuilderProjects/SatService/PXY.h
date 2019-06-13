//---------------------------------------------------------------------------
#ifndef PXYH
#define PXYH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TPXYForm : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TEdit *LEdit;
    TEdit *DEdit;
    TEdit *PEdit;
    TEdit *SEdit;
    TEdit *PXYEdit;
    TEdit *PTEdit;
    TEdit *StepEdit1;
    TScrollBar *LScrollBar;
    TScrollBar *DScrollBar;
    TScrollBar *PScrollBar;
    TScrollBar *SScrollBar;
    TEdit *StepEdit2;
    TButton *Button1;
    TScrollBar *TScrollBar;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall LScrollBarChange(TObject *Sender);
    void __fastcall DScrollBarChange(TObject *Sender);
    void __fastcall PScrollBarChange(TObject *Sender);
    void __fastcall SScrollBarChange(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall TScrollBarChange(TObject *Sender);
    
private:	// User declarations
public:		// User declarations
    __fastcall TPXYForm(TComponent* Owner);
    void __fastcall Change();
  double L,D,P,S,PXY,PT;
};
//---------------------------------------------------------------------------
extern PACKAGE TPXYForm *PXYForm;
//---------------------------------------------------------------------------
#endif
