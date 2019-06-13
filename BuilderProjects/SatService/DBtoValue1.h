//---------------------------------------------------------------------------
#ifndef DBtoValue1H
#define DBtoValue1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TdbForm : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TBitBtn *BitBtn1;
    TScrollBar *ScrollBarD;
    TEdit *EditD;
    TScrollBar *ScrollBarOUT;
    TEdit *EditOUT;
    TScrollBar *ScrollBarIN;
    TEdit *EditIN;
    TScrollBar *ScrollBarR;
    TEdit *EditR;
    TLabel *LabelIN;
    TLabel *LabelOUT;
    TLabel *LabelDB;
    void __fastcall BitBtn1Click(TObject *Sender);
    void __fastcall ScrollBarDChange(TObject *Sender);
    void __fastcall ScrollBarRChange(TObject *Sender);
    void __fastcall ScrollBarINChange(TObject *Sender);
    void __fastcall ScrollBarOUTChange(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    
private:	// User declarations
public:		// User declarations
    __fastcall TdbForm(TComponent* Owner);
    double DB,R,VOUT,VIN;
    bool ChangeFlag;
    char FS[25];
};
//---------------------------------------------------------------------------
extern PACKAGE TdbForm *dbForm;
//---------------------------------------------------------------------------
#endif
