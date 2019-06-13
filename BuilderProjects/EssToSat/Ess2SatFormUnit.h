//---------------------------------------------------------------------------

#ifndef Ess2SatFormUnitH
#define Ess2SatFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TAzEl2SatForm : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *EsBox;
        TLabel *DOLLabel;
        TEdit *DOLEdit;
        TEdit *DOLEdit1;
        TScrollBar *DOLScrollBar;
        TScrollBar *DOLScrollBar1;
        TScrollBar *DOLScrollBar2;
        TLabel *LabelSHIR;
        TEdit *SHIREdit;
        TEdit *SHIREdit1;
        TScrollBar *SHIRScrollBar;
        TScrollBar *SHIRScrollBar1;
        TScrollBar *SHIRScrollBar2;
        TGroupBox *SatBox;
        TScrollBar *KAScrollBar;
        TEdit *KAEdit;
        TLabel *KALabel;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TPanel *MapPanel;
        TImage *MapImage;
        TImage *SatImage;
        TImage *AntImage;
        TBitBtn *InfoBtn;
        TBitBtn *CloseBtn;
        TLabel *Label4;
        TEdit *AzEdit;
        TLabel *Label5;
        TEdit *ElEdit;
        TLabel *Label9;
        TEdit *DistanceEdit;
        void __fastcall SatScrollChange(TObject *Sender);
        void __fastcall LongScrollChange(TObject *Sender);
        void __fastcall LatScrollChange(TObject *Sender);
        void __fastcall ScrollBarChange(TObject *Sender);
        void __fastcall DOLScrollBar1Change(TObject *Sender);
        void __fastcall DOLScrollBar2Change(TObject *Sender);
        void __fastcall SHIRScrollBar1Change(TObject *Sender);
        void __fastcall SHIRScrollBar2Change(TObject *Sender);
        void __fastcall InfoBtnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TAzEl2SatForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAzEl2SatForm *AzEl2SatForm;
//---------------------------------------------------------------------------
#endif
