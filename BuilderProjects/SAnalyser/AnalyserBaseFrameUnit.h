//---------------------------------------------------------------------------


#ifndef AnalyserBaseFrameUnitH
#define AnalyserBaseFrameUnitH
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
#include "Functions.h"
#include <ComCtrls.hpp>
#include <CheckLst.hpp>
#include <Mask.hpp>

#include <time.h>
#include <stdio.h>
#include <dos.h>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <Menus.hpp>  
#include "BandsUnit.h"
#include "FreqParamFrameUnit.h"
#include <Graphics.hpp>
#include <Buttons.hpp>


#define MAX_FREQ 8000000L
#define MIN_FREQ 50000
#define MAX_COUNT 1000
//---------------------------------------------------------------------------
class TAnalyserBaseFrame : public TFrame
{
__published:	// IDE-managed Components
        TPanel *APanel;
        TGroupBox *LevelGroupBox;
        TCheckBox *LevelAutoFitCheckBox;
        TPanel *LevelHandsPanel;
        TLabel *Label1;
        TLabel *Label2;
        TTimer *BeamTimer;
        TPopupMenu *ChartPopupMenu;
        TMenuItem *SaveImgMenuItem;
        TSaveDialog *SaveDialog1;
        TMenuItem *CopyImageMenuItem;
        TMenuItem *SaveAsGridMenuItem;
        TMenuItem *SaveAsTextMenuItem;
        TPopupMenu *FreqPlanPopupMenu;
        TMenuItem *FreqPlanAddMenuItem;
        TMenuItem *FreqPlanEditMenuItem;
        TMenuItem *FreqPlanDeleteMenuItem;
        TMenuItem *N1;
        TMenuItem *FreqPlanSaveMenuItem;
        TMenuItem *FreqPlanLoadMenuItem;
        TMenuItem *FreqPlanClearMenuItem;
        TMenuItem *N2;
        TMenuItem *FreqPlanAutoSaveMenuItem;
        TMenuItem *FreqPlanAutoLoadMenuItem;
        TPanel *ChartPanel;
        TChart *Chart1;
        TLabel *DBLabel;
        TLabel *FreqLabel;
        TLineSeries *MainSeries1;
        TLineSeries *PlanLineSeries;
        TLineSeries *PlanTitleSeries;
        TAreaSeries *ShadowSeries;
        TPanel *InfoPanel;
        TLabel *SignalInfoLabel;
        TGroupBox *FreqGroupBox;
        TPanel *FreqSpanPanel;
        TLabel *Label9;
        TLabel *Label10;
        TEdit *CentralFreqEdit;
        TEdit *SpanEdit;
        TScrollBar *CentralScrollBar;
        TScrollBar *SpanScrollBar;
        TPanel *FreqInterPanel;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *LeftFreqEdit;
        TEdit *RightFreqEdit;
        TScrollBar *LeftScrollBar;
        TScrollBar *RightScrollBar;
        TPageControl *SettsPageControl;
        TTabSheet *PlanTabSheet;
        TPageControl *PageControl2;
        TTabSheet *TabSheet7;
        TListBox *PlanListBox;
        TStaticText *FreqPlanNameEdit;
        TFreqParamFrame *FreqParamFrame1;
        TTabSheet *TabSheet8;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label22;
        TCheckBox *CheckBox1;
        TComboBox *FreqPlanLineWidthComboBox;
        TColorBox *FreqPlanLineColorBox;
        TColorBox *FreqPlanNameColorBox;
        TTabSheet *TabSheet1;
        TRadioGroup *BandsRadioGroup;
        TPanel *BandPanel;
        TLabel *Label13;
        TLabel *Label14;
        TEdit *UserMinFreqEdit;
        TEdit *UserMaxFreqEdit;
        TButton *BandEditButton;
        TButton *BandCancelButton;
        TTabSheet *TabSheet2;
        TLabel *Label19;
        TLabel *Label29;
        TComboBox *RatioComboBox;
        TComboBox *FreqSetComboBox;
        TTabSheet *TabSheet5;
        TLabel *Label3;
        TLabel *Label8;
        TImage *Image1;
        TComboBox *BeamWidthComboBox;
        TEdit *BeamFadingEdit;
        TUpDown *BeamFadingUpDown;
        TCheckBox *BeamCheckBox;
        TCheckBox *BeamShadowCheckBox;
        TGroupBox *BeamColorsGroupBox;
        TLabel *Label17;
        TCheckBox *BeamColorCheckBox;
        TComboBox *BeamColorComboBox;
        TCheckBox *BeamRefreshCheckBox;
        TTabSheet *TabSheet6;
        TGroupBox *FonGroupBox;
        TLabel *Label16;
        TComboBox *FonColorComboBox;
        TCheckBox *FonGradientCheckBox;
        TGroupBox *LegendGroupBox;
        TLabel *Label20;
        TLabel *Label21;
        TColorBox *LegendYColorBox;
        TColorBox *LegendXColorBox;
        TCheckBox *LegendColorCheckBox;
        TGroupBox *GridGroupBox;
        TLabel *Label18;
        TComboBox *GridColorComboBox;
        TCheckBox *GridColorAdaptCheckBox;
        TCheckBox *GridColorNoCheckBox;
        TCheckBox *GridColorSplashCheckBox;
        TTabSheet *AboutTabSheet;
        TScrollBox *ScrollBox1;
        TImage *ProgramIcon;
        TLabel *Label30;
        TLabel *Label28;
        TLabel *Label27;
        TLabel *Label26;
        TLabel *Label25;
        TLabel *Label24;
        TLabel *Label23;
        TScrollBar *LevelAmpScrollBar;
        TScrollBar *LevelCenterScrollBar;
        TPanel *CtrlPanel;
        TPanel *ButtonsPanel;
        TSpeedButton *SettsButton;
        TSpeedButton *CtrlButton;
        TMenuItem *FreqPlanRedrawMenuItem;
        void __fastcall CentralScrollBarChange(TObject *Sender);
        void __fastcall SpanScrollBarChange(TObject *Sender);
        void __fastcall LeftScrollBarChange(TObject *Sender);
        void __fastcall RightScrollBarChange(TObject *Sender);
        void __fastcall BeamWidthComboBoxChange(TObject *Sender);
        void __fastcall BeamFadingEditChange(TObject *Sender);
        void __fastcall UserMinFreqEditChange(TObject *Sender);
        void __fastcall BandsRadioGroupClick(TObject *Sender);
        void __fastcall BandEditButtonClick(TObject *Sender);
        void __fastcall BandCancelButtonClick(TObject *Sender);
        void __fastcall RatioComboBoxChange(TObject *Sender);
        void __fastcall Chart1Resize(TObject *Sender);
        void __fastcall LevelCenterScrollBarChange(TObject *Sender);
        void __fastcall LevelAmpScrollBarChange(TObject *Sender);
        void __fastcall LevelAutoFitCheckBoxClick(TObject *Sender);
        void __fastcall BeamTimerTimer(TObject *Sender);
        void __fastcall FonRadioGroupClick(TObject *Sender);
        void __fastcall BeamColorRadioGroupClick(TObject *Sender);
        void __fastcall GridColorNoCheckBoxClick(TObject *Sender);
        void __fastcall GridColorAdaptCheckBoxClick(TObject *Sender);
        void __fastcall LegendColorCheckBoxClick(TObject *Sender);
        void __fastcall BeamShadowCheckBoxClick(TObject *Sender);
        void __fastcall SaveImgMenuItemClick(TObject *Sender);
        void __fastcall CopyImageMenuItemClick(TObject *Sender);
        void __fastcall SaveAsGridMenuItemClick(TObject *Sender);
        void __fastcall SaveAsTextMenuItemClick(TObject *Sender);
        void __fastcall GridColorSplashCheckBoxClick(TObject *Sender);
        void __fastcall PlanListBoxClick(TObject *Sender);
        void __fastcall FreqPlanEditMenuItemClick(TObject *Sender);
        void __fastcall FreqPlanMenuItemClick(TObject *Sender);
        void __fastcall FreqPlanLineWidthComboBoxChange(TObject *Sender);
        void __fastcall FreqPlanNameColorBoxChange(TObject *Sender);
        void __fastcall FreqPlanLineColorBoxChange(TObject *Sender);
        void __fastcall SettsButtonClick(TObject *Sender);
        void __fastcall FreqSetComboBoxChange(TObject *Sender);
        void __fastcall RecStartButtonClick(TObject *Sender);
        void __fastcall SettsPageControlChanging(TObject *Sender,
          bool &AllowChange);
        void __fastcall RecDivComboBoxChange(TObject *Sender);
        void __fastcall CtrlButtonClick(TObject *Sender);
private:	// User declarations
  unsigned long _startFreq;
  unsigned long _span;
public:		// User declarations
  __fastcall TAnalyserBaseFrame(TComponent* Owner);
 
 TLineSeries *_Series[16];

 void LoadParameters(ASS fileName);
 void SaveParameters(ASS fileName);

 void MiddleFreq(unsigned long freq);


 // info

 //unsigned long _timeOfMeasuringLocal;

 
 virtual double GetBeamDrawInterval()=0;
 void DrawSignal();
 void DrawSignalEnds();

 // freq
private:
 bool _changing; 
 int _ratio;
public:
 bool Lock() { if(_changing==true) return true; else _changing=true; return false; }
 void Unlock() { _changing=false; }

 unsigned long _userMinFreq;
 unsigned long _userMaxFreq;
 void Span(unsigned long span);
 unsigned long Span();
 void RSpan(unsigned long span);
 unsigned long RSpan();

 void RStartFreq(unsigned long freq);
 unsigned long RStartFreq();

 unsigned long StartFreq() { return _startFreq; }

 void RecalcBand();

 virtual void OnChangeSpan()=0;



  /////// draw single beam
private:
 signed short int _Levels[MAX_COUNT];
public:         
 TDateTime _lastMeasuringTime;
 int _lastStartFreq;
 int _lastStep;
 int _lastCount;

 void SetLevel(int n,int level); 
 int GetLevel(int n);

 int _printedLast;
 int _printQuota;

 //////
 TColor BeamColor();
                              
  void SaveAsPicture(ASS fileName);
  void SaveAsGrid(ASS fileName);
  void SaveAsSA4(ASS fileName);
  void SaveAsText(ASS fileName);

 TLineSeries *_SeriesFP;
 
 TBAND *_bands;
 void __fastcall OnBandChanged(TObject *Sender); 
 void LoadFreqPlan(ASS fileName);
 void ClearFreqPlan();

// void Decode();
 virtual void LoadInits(ASS fileName)=0;
 void LoadBaseInits(ASS fileName); 
 virtual void SaveInits(ASS fileName)=0;
 void SaveBaseInits(ASS fileName);


};
//---------------------------------------------------------------------------
extern PACKAGE TAnalyserBaseFrame *AnalyserFrame1;
//---------------------------------------------------------------------------
#endif
