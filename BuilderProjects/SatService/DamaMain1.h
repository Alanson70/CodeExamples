//---------------------------------------------------------------------------
#ifndef DamaMain1H
#define DamaMain1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
//--------------------------------------------------------------------------
#define MAX_FREQS 10
typedef struct
{
 double FC;
 double DR;
 bool FO;
 bool FRS;
 int FEC;
 int CM;
 double IR;
 double SR;
 double DI;
 double LB;
 double RB;
 double AN;
 double Band;
 char Name[25];
 bool Enabled;


}FreqStruct;

class TFreqForm : public TForm
{
__published:	// IDE-managed Components
    TChart *Chart1;
    TLineSeries *Series1;
    TScrollBar *FCScrollBar;
    TLineSeries *FPSeries;
    TLabel *FCLabel;
    TLabel *DRLabel;
    TLabel *FOLabel;
    TLabel *FRSLabel;
    TLabel *FECLabel;
    TLabel *CMLabel;
    TEdit *FCEdit;
    TScrollBar *DRScrollBar;
    TEdit *DREdit;
    TComboBox *FOComboBox;
    TComboBox *RSComboBox;
    TComboBox *CMComboBox;
    TComboBox *FECComboBox;
    TLabel *IRLabel;
    TLabel *BandLabel;
    TLabel *DILabel;
    TEdit *IREdit;
    TEdit *SREdit;
    TEdit *DIEdit;
    TLineSeries *BandSeries;
    TRadioGroup *RadioGroup1;
    TEdit *Edit1;
    TEdit *Edit2;
    TEdit *Edit3;
    TEdit *Edit4;
    TEdit *Edit5;
    TEdit *Edit6;
    TEdit *Edit7;
    TEdit *Edit8;
    TEdit *Edit9;
    TEdit *Edit10;
    TBevel *Bevel1;
    TLabel *LBLabel;
    TLabel *RBLabel;
    TEdit *LBEdit;
    TEdit *RBEdit;
    TMainMenu *MainMenu1;
    TMenuItem *FileItem;
    TMenuItem *OpenItem;
    TMenuItem *SaveItem;
    TMenuItem *ExitItem;
    TOpenDialog *OpenDialog1;
    TSaveDialog *SaveDialog1;
    TCheckBox *CheckBox1;
    TCheckBox *CheckBox2;
    TCheckBox *CheckBox3;
    TCheckBox *CheckBox4;
    TCheckBox *CheckBox5;
    TCheckBox *CheckBox6;
    TCheckBox *CheckBox7;
    TCheckBox *CheckBox8;
    TCheckBox *CheckBox9;
    TCheckBox *CheckBox10;
    TMenuItem *N1;
    TLabel *SRLabel;
    TEdit *BandEdit;
    TBevel *Bevel2;
    TLabel *FreqStepLabel;
    TEdit *FreqStepEdit;
    TScrollBar *FreqStepScrollBar;
    TEdit *Edit11;
    TEdit *Edit12;
    TEdit *Edit13;
    TEdit *Edit14;
    TRadioGroup *FPRadioGroup;
    TButton *FPEditButton;
    TStringGrid *StringGrid1;
    void __fastcall FCScrollBarChange(TObject *Sender);
    void __fastcall DRScrollBarChange(TObject *Sender);
    void __fastcall AnyChange(TObject *Sender);
    void __fastcall AnyChoose(TObject *Sender);
    void __fastcall FOComboBoxChange(TObject *Sender);
    void __fastcall RSComboBoxChange(TObject *Sender);
    void __fastcall CMComboBoxChange(TObject *Sender);
    void __fastcall FECComboBoxChange(TObject *Sender);
    void __fastcall ExitItemClick(TObject *Sender);
    void __fastcall OpenItemClick(TObject *Sender);
    void __fastcall SaveItemClick(TObject *Sender);
    void __fastcall Edit1Change(TObject *Sender);
    void __fastcall Edit2Change(TObject *Sender);
    void __fastcall Edit3Change(TObject *Sender);
    void __fastcall Edit4Change(TObject *Sender);
    void __fastcall Edit5Change(TObject *Sender);
    void __fastcall Edit6Change(TObject *Sender);
    void __fastcall Edit7Change(TObject *Sender);
    void __fastcall Edit8Change(TObject *Sender);
    void __fastcall Edit9Change(TObject *Sender);
    void __fastcall Edit10Change(TObject *Sender);
    void __fastcall Edit1Click(TObject *Sender);
    void __fastcall CheckBox1Click(TObject *Sender);
    
    void __fastcall ANEdit1Change(TObject *Sender);
    void __fastcall ANEditChange(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FreqScroolBarChange(TObject *Sender);
    void __fastcall FPEditButtonClick(TObject *Sender);
    void __fastcall FPRadioGroupClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFreqForm(TComponent* Owner);
    void LoadOnStart();
 // FreqStruct FS[MAX_FREQS];


  int CurrentFreq;
};
//---------------------------------------------------------------------------
extern PACKAGE TFreqForm *FreqForm;
//---------------------------------------------------------------------------
#endif
 