//---------------------------------------------------------------------------


#ifndef FreqParamFrameUnitH
#define FreqParamFrameUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>

#include "BandsUnit.h"
//---------------------------------------------------------------------------
class TFreqParamFrame : public TFrame
{
__published:	// IDE-managed Components
        TPanel *PlanParamsPanel;
        TLabel *Label24;
        TLabel *StepLabel;
        TLabel *Label1;
        TEdit *FreqEdit;
        TEdit *StepEdit;
        TUpDown *StepUpDown;
        TScrollBar *FreqScrollBar;
        TScrollBar *FreqScrollBarKHZ;
        TEdit *NameEdit;
        TPanel *ParamPanel;
        TLabel *DataRateLabel;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label22;
        TLabel *Label23;
        TLabel *Label25;
        TLabel *Label26;
        TLabel *Label27;
        TCheckBox *CodingCheck;
        TCheckBox *RSCheck;
        TCheckBox *OverheadCheck;
        TEdit *InfRateEdit;
        TUpDown *InfRateUpDown;
        TUpDown *InfRateUpDownKHZ;
        TEdit *OverheadFactorEdit;
        TUpDown *OverheadFactorUpDown;
        TEdit *OverheadDivisorEdit;
        TEdit *RSFactorEdit;
        TUpDown *RSFactorUpDown;
        TEdit *RSDivisorEdit;
        TUpDown *OverheadDivisorUpDown;
        TUpDown *RSDivisorUpDown;
        TUpDown *CodingDivisorUpDown;
        TEdit *CodingDivisorEdit;
        TUpDown *CodingFactorUpDown;
        TEdit *CodingFactorEdit;
        TComboBox *ModulationCombo;
        TLabel *Label2;
        TEdit *BandEdit;
        TScrollBar *BandScrollBar;
        TScrollBar *BandScrollBarKHZ;
        TCheckBox *BandHandSetCheckBox;
        TBevel *Bevel1;
        void __fastcall InfRateEditChange(TObject *Sender);
        void __fastcall InfRateUpDownKHZChangingEx(TObject *Sender,
          bool &AllowChange, short NewValue, TUpDownDirection Direction);
        void __fastcall OverheadChange(TObject *Sender);
        void __fastcall RSCheckClick(TObject *Sender);
        void __fastcall CodingCheckClick(TObject *Sender);
        void __fastcall ModulationComboChange(TObject *Sender);
        void __fastcall FreqEditChange(TObject *Sender);
        void __fastcall StepEditChange(TObject *Sender);
        void __fastcall FreqScrollBarChange(TObject *Sender);
        void __fastcall NameEditChange(TObject *Sender);
        void __fastcall InfRateUpDownClick(TObject *Sender,
          TUDBtnType Button);
        void __fastcall BandEditChange(TObject *Sender);
        void __fastcall BandHandSetCheckBoxClick(TObject *Sender);
        void __fastcall BandScrollBarChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFreqParamFrame(TComponent* Owner);

 void Recalc();
 bool _changing;
 bool Lock() { if(_changing==true) return true; else _changing=true; return false; }
 void Unlock() { _changing=false; }

// double _overheadK;
// double _rsK;
// double _codingK;
// double _modeK;

 BAND_SETTS _setts;
 void Set(BAND_SETTS &setts);

 //unsigned long _bandOccupated; 
  Callback OnChanged;
 //unsigned long _bandAssigned;

};
//---------------------------------------------------------------------------
extern PACKAGE TFreqParamFrame *FreqParamFrame;
//---------------------------------------------------------------------------
#endif
