//---------------------------------------------------------------------------

#ifndef AnalyserViewerFrameUnitH
#define AnalyserViewerFrameUnitH
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
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TAnalyserViewerFrame : public TAnalyserBaseFrame
{
__published:	// IDE-managed Components
        TPageControl *CtrlPageControl;
        TTabSheet *WorkTabSheet;
        TLabel *Label15;
        TEdit *PlayIntervalEdit;
        TUpDown *PlayIntervalUpDown;
        TButton *PlayButton;
        TTimer *PlayTimer;
        TLabel *Label37;
        TScrollBar *PlayScrollBar;
        TLabel *Label4;
        TEdit *FileNameEdit;
        TButton *FileChooseButton;
        TLabel *Label5;
        TEdit *PlayerFileInfEdit;
        void __fastcall PlayIntervalEditChange(TObject *Sender);
        void __fastcall PlayButtonClick(TObject *Sender);
        void __fastcall FileNameEditChange(TObject *Sender);
        void __fastcall FileChooseButtonClick(TObject *Sender);
        void __fastcall PlayTimerTimer(TObject *Sender);
        void __fastcall PlayScrollBarScroll(TObject *Sender,
          TScrollCode ScrollCode, int &ScrollPos);
private:	// User declarations
public:		// User declarations
 __fastcall TAnalyserViewerFrame(TComponent* Owner);
 void LoadInits(ASS fileName);
 void SaveInits(ASS fileName);
 
 void OnChangeSpan() { }   
 double GetBeamDrawInterval();

 unsigned long _index[100];
 int _indexCount;
 int _indexRank; // if file small <100 records - 1 index = 1 record< more: 1 index - 10 records
 FILE *_fd;

 long _posLast;
 long _posCount;

 void Open();
 void Close();
 void Play(bool flag);
 void ShowNext();



};
//---------------------------------------------------------------------------
extern PACKAGE TAnalyserViewerFrame *AnalyserViewerFrame;
//---------------------------------------------------------------------------
#endif
