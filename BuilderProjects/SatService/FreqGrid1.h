//---------------------------------------------------------------------------
#ifndef FreqGrid1H
#define FreqGrid1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
    TStringGrid *FGrid;
    TPrintDialog *PrintDialog1;
    TPrinterSetupDialog *PrinterSetupDialog1;
    TPanel *Panel1;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall PrinterSetupDialog1Close(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
