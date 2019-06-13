//---------------------------------------------------------------------------
#ifndef FreqPrint1H
#define FreqPrint1H
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
//---------------------------------------------------------------------------
class TFreqPrintForm : public TForm
{
__published:	// IDE-managed Components
    TChart *Chart1;
    TLineSeries *Series1;
    TLineSeries *Series2;
    TLineSeries *Series3;
    TLineSeries *Series4;
    TLineSeries *Series5;
    TLineSeries *Series6;
    TLineSeries *Series7;
    TLineSeries *Series8;
    TLineSeries *Series9;
    TLineSeries *Series10;
    TButton *Button2;
    TButton *Button3;
    TPrintDialog *PrintDialog1;
    TPrinterSetupDialog *PrinterSetupDialog1;
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall ScrollBar1Change(TObject *Sender);
    
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
    __fastcall TFreqPrintForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFreqPrintForm *FreqPrintForm;
//---------------------------------------------------------------------------
#endif
