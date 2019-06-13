//---------------------------------------------------------------------------
#ifndef DoplerUnitH
#define DoplerUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TDoplerForm : public TForm
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
    TLabel *BUFFERLabel;
    TEdit *BUFFEREdit;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *RazmahLabel;
    TScrollBar *RAZMAHScrollBar;
    TEdit *RAZMAHEdit;
    TScrollBar *RAZMAHScrollBar1;
    TScrollBar *RAZMAHScrollBar2;
    TEdit *RAZMAHEdit1;
    TLabel *KZLabel;
    TScrollBar *KZScrollBar;
    TEdit *KZEdit;
    TLabel *TIMELabel;
    TEdit *TIMEEdit;
    TLabel *Label7;
    TEdit *BUFFEREdit1;
    TLabel *Label8;
    TEdit *RATEEdit;
    TScrollBar *RATEScrollBar;
    TEdit *BUFFERREdit;
    TEdit *BUFFERREdit1;
        TCheckBox *CheckBox1;
    void __fastcall ScrollBarChange(TObject *Sender);
    void __fastcall DOLScrollBar2Change(TObject *Sender);
    void __fastcall SHIRScrollBar2Change(TObject *Sender);
    void __fastcall DOLScrollBar1Change(TObject *Sender);
    void __fastcall SHIRScrollBar1Change(TObject *Sender);
   // void __fastcall Button1Click(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall RAZMAHScrollBar1Change(TObject *Sender);
    void __fastcall RAZMAHScrollBar2Change(TObject *Sender);
    
    
private:	// User declarations
public:		// User declarations
    __fastcall TDoplerForm(TComponent* Owner);
    double KA,SHIR,DOL,RAZMAH,AZ,UM,dDOL,dSHIR,dRAZMAH,KZ,BUFFER,DT,RATE;
    bool ChangeFlag;
    int PosFlag;
};
//---------------------------------------------------------------------------
extern PACKAGE TDoplerForm *DoplerForm;
//---------------------------------------------------------------------------
#endif
