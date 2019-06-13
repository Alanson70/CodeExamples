//---------------------------------------------------------------------------

#ifndef AnalyserMeterFrameUnitH
#define AnalyserMeterFrameUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AnalyserBaseFrameUnit.h"
#include "FreqParamFrameUnit.h"
#include <Chart.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include "ConnectFrameUnit.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TAnalyserMeterFrame : public TAnalyserBaseFrame
{
__published:	// IDE-managed Components
        TPageControl *CtrlPageControl;
        TTabSheet *QualTabSheet;
        TRadioGroup *QualRadioGroup;
        TPanel *StepPanel;
        TLabel *Label5;
        TLabel *Label4;
        TEdit *CountEdit;
        TEdit *StepEdit;
        TScrollBar *CountScrollBar;
        TScrollBar *StepScrollBar;
        TTabSheet *WorkTabSheet;
        TRadioButton *WorkContRadioButton;
        TRadioButton *WorkIntervalRadioButton;
        TRadioButton *WorkOnceRadioButton;
        TLabel *Label15;
        TEdit *WorkIntervalEdit;
        TUpDown *WorkIntervalUpDown;
        TButton *RunButton;
        TTimer *WorkIntervalTimer;
        TTabSheet *RecTabSheet;
        TTimer *RecTimer;
        TLabel *Label37;
        TTimer *InfoTimer;
        TTabSheet *ConnectTabSheet;
        TConnectFrame *ConnectFrame1;
        TEdit *AscingInfoLabel;
        TCheckBox *RecIntervalCheckBox;
        TCheckBox *RecDivCheckBox;
        TLabel *Label36;
        TLabel *Label38;
        TEdit *RecIntervalEdit;
        TUpDown *RecIntervalUpDown;
        TEdit *RecDivEdit;
        TUpDown *RecDivUpDown;
        TComboBox *RecIntervalComboBox;
        TComboBox *RecDivComboBox;
        TEdit *RecMaxCountEdit;
        TLabel *Label35;
        TLabel *Label32;
        TEdit *RecPathEdit;
        TEdit *RecFileNameEdit;
        TButton *RecStartButton;
        TButton *RecPathButton;
        TPanel *Panel1;
        TLabel *Label39;
        TLabel *Label33;
        TLabel *Label34;
        TEdit *RecTimeEdit;
        TEdit *RecCountEdit;
        TLabel *Label31;
        TCheckBox *RecToCSVCheckBox;
        TCheckBox *RecToSA4CheckBox;
        TCheckBox *RecToJPEGCheckBox;
        void __fastcall QualRadioGroupClick(TObject *Sender);
        void __fastcall StepScrollBarChange(TObject *Sender);
        void __fastcall CountScrollBarChange(TObject *Sender);
        void __fastcall WorkRadioButtonClick(TObject *Sender);
        void __fastcall WorkIntervalEditChange(TObject *Sender);
        void __fastcall RunButtonClick(TObject *Sender);
        void __fastcall WorkIntervalTimerTimer(TObject *Sender);
        void __fastcall RecMaxCountEditChange(TObject *Sender);
        void __fastcall RecFileNameEditChange(TObject *Sender);
        void __fastcall RecDivUpDownChangingEx(TObject *Sender,
          bool &AllowChange, short NewValue, TUpDownDirection Direction);
        void __fastcall RecStartButtonClick(TObject *Sender);
        void __fastcall RecTimerTimer(TObject *Sender);
        void __fastcall InfoTimerTimer(TObject *Sender);
        void __fastcall RecPathButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
 __fastcall TAnalyserMeterFrame(TComponent* Owner);  
 void LoadInits(ASS fileName);
 void SaveInits(ASS fileName);

 // qual  
 void OnChangeSpan();
 int _step;
 int _count;

 int _userQualStep;
 int _userQualCount;
// rec
 signed short int _oldLevel[MAX_COUNT];
 double _recStartTime;
 int _recCount;
 int _recDivValue;
 void RecTimerStart();

 void DoRecord();
 void TestForRecord();
 int _fileNumber;

 // transfer

 double _timeTransfer0;
 double _timeTransferAveraged;
 void TimeTransferCalculate();

 double _timeAscing0;
 double _timeAscingAveraged;


 unsigned long _id;
 Callback OnCanSend;
 void Translate(char *recBuffer,int count);
 ASS GetCommand();
 
 unsigned long _timeOfLastMeasuring;
 unsigned long _timeOfMeasuring;

 double GetBeamDrawInterval();

 ////
 void OnDoConnect();
 void OnDisconnect();
};
//---------------------------------------------------------------------------
extern PACKAGE TAnalyserMeterFrame *AnalyserMeterFrame;
//---------------------------------------------------------------------------
#endif
