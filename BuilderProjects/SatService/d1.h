//---------------------------------------------------------------------------
#ifndef d1H
#define d1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TtosputnikForm : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TEdit *Edit1;
    TUpDown *UpDown1;
    TEdit *Edit2;
    TUpDown *UpDown2;
    TEdit *Edit3;
    TUpDown *UpDown3;
    TLabel *Label4;
    TEdit *Edit4;
    TLabel *Label5;
    TLabel *Label6;
    TEdit *Edit5;
    TUpDown *UpDown4;
    TEdit *Edit6;
    TUpDown *UpDown5;
    TEdit *Edit7;
    TUpDown *UpDown6;
    TBitBtn *BitBtn1;
    void __fastcall Edit1Change(TObject *Sender);
    
    void __fastcall BitBtn1Click(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
    __fastcall TtosputnikForm(TComponent* Owner);
    double d;
    double A,B,G;
};
//---------------------------------------------------------------------------
extern PACKAGE TtosputnikForm *tosputnikForm;
//---------------------------------------------------------------------------
#endif
