//---------------------------------------------------------------------------
#ifndef UgolAzimutH
#define UgolAzimutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TUAForm : public TForm
{
__published:	// IDE-managed Components
    TScrollBar *KAScrollBar;
    TScrollBar *SHIRScrollBar;
    TScrollBar *DOLScrollBar;
    TLabel *KALabel;
    TLabel *LabelSHIR;
    TLabel *DOLLabel;
    TEdit *KAEdit;
    TEdit *SHIREdit;
    TEdit *DOLEdit;
    TEdit *AZEdit;
    TEdit *UMEdit;
    TLabel *AZLabel;
    TLabel *UMLabel;
    TScrollBar *SHIRScrollBar1;
    TScrollBar *DOLScrollBar1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TScrollBar *DOLScrollBar2;
    TScrollBar *SHIRScrollBar2;
    TEdit *DOLEdit1;
    TEdit *SHIREdit1;
    TButton *Button1;
    TLabel *NAMELabel;
    TLabel *COMMENTLabel;
    TEdit *NAMEEdit;
    TEdit *COMMENTEdit;
    TButton *Button2;
    TImage *Image1;
    void __fastcall ScrollBarChange(TObject *Sender);
    void __fastcall DOLScrollBar2Change(TObject *Sender);
    void __fastcall SHIRScrollBar2Change(TObject *Sender);
    void __fastcall DOLScrollBar1Change(TObject *Sender);
    void __fastcall SHIRScrollBar1Change(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TUAForm(TComponent* Owner);
    double KA,SHIR,DOL,AZ,UM,dDOL,dSHIR;
    bool ChangeFlag;
    int PosFlag;
};
//---------------------------------------------------------------------------
extern PACKAGE TUAForm *UAForm;
//---------------------------------------------------------------------------
#endif
