//---------------------------------------------------------------------------

#ifndef MainFormUnitH
#define MainFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>   
#include "Functions.h"
#include <Dialogs.hpp>  
#include "AnalyserBaseFrameUnit.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *RecMenuItem;
        TMenuItem *ViewerMenuItem;
        TMenuItem *ProfileOpenMenuItem;
        TMenuItem *ProfileSaveAsMenuItem;
        TMenuItem *N7;
        TMenuItem *ProfileAutoSaveMenuItem;
        TMenuItem *N9;
        TMenuItem *ExitMenuItem;
        TMenuItem *ProfileNewMenuItem;
        TMenuItem *ProfileCloseMenuItem;
        TMenuItem *ProfileSaveMenuItem;
        TMenuItem *ProfileAutoLoadMenuItem;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ProfileOpenMenuItemClick(TObject *Sender);
        void __fastcall ExitMenuItemClick(TObject *Sender);
        void __fastcall ProfileNewMenuItemClick(TObject *Sender);
        void __fastcall ProfileSaveAsMenuItemClick(TObject *Sender);
        void __fastcall ProfileCloseMenuItemClick(TObject *Sender);
        void __fastcall ProfileSaveMenuItemClick(TObject *Sender);
        void __fastcall RecMenuItemClick(TObject *Sender);
        void __fastcall ViewerMenuItemClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
 __fastcall TMainForm(TComponent* Owner);
 
 bool __fastcall ApplicationHookProc(TMessage &Message);

 ASS _fileName;
 void OpenSA(ASS fileName); 
 void SaveSA(ASS fileName);
 void CloseSA();
 TAnalyserBaseFrame *_frame;
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
