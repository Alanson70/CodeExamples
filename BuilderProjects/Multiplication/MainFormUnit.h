//---------------------------------------------------------------------------

#ifndef MainFormUnitH
#define MainFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "UserResultsFrameUnit.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TEdit *ResultEdit;
        TEdit *Value1Edit;
        TEdit *Value2Edit;
        TLabel *Label3;
        TLabel *Label4;
        TButton *StartButton;
        TGroupBox *SourceGroupBox;
        TEdit *FromEdit;
        TUpDown *FromUpDown;
        TEdit *ToEdit;
        TUpDown *ToUpDown;
        TCheckBox *RandomCheckBox;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *ResumeEdit;
        TEdit *PointsEdit;
        TEdit *TimeEdit;
        TTimer *Timer1;
        TComboBox *ComboBox1;
    TButton *AddUserButton;
    TButton *DelButton;
    TLabel *UserLabel;
    TGroupBox *GroupBox1;
    TUserResultFrame *UserResultFrame1;
        void __fastcall ToEditChange(TObject *Sender);
        void __fastcall FromEditChange(TObject *Sender);
        void __fastcall StartButtonClick(TObject *Sender);
        void __fastcall ResultEditKeyPress(TObject *Sender, char &Key);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall RandomCheckBoxClick(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
    void __fastcall AddUserButtonClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall DelButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
 __fastcall TMainForm(TComponent* Owner);

 void FirstExpression();
 void NextExpression();

 void TestResult();

 void LoadUsers();
 void SaveUsers();
 void LoadBestResults();
 void SaveResult(TDateTime t);

 TUserResultFrame *_userResult[8];

};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
