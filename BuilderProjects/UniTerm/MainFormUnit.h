//---------------------------------------------------------------------------

#ifndef MainFormUnitH
#define MainFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>  
#include "Functions.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu;
        TMenuItem *TermMenuItem;
        TMenuItem *TerminalOpenMenuItem;
        TMenuItem *TerminalCloseMenuItem;
        TMenuItem *AboutMenuItem;
        TMenuItem *ProfileMenuItem;
        TMenuItem *FileOpenMenuItem;
        TMenuItem *FileCloseMenuItem;
        TMenuItem *FileSaveAsMenuItem;
        TMenuItem *N1;
        TMenuItem *ExitMenuItem;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TMenuItem *FileNewMenuItem;
        TMenuItem *N2;
        TMenuItem *TerminalControlMenuItem;
        void __fastcall TerminalOpenMenuItemClick(TObject *Sender);
        void __fastcall TerminalControlMenuItemClick(TObject *Sender);
        void __fastcall TerminalCloseMenuItemClick(TObject *Sender);
        void __fastcall AboutMenuItemClick(TObject *Sender);
        void __fastcall FileSaveAsMenuItemClick(TObject *Sender);
        void __fastcall FileNewMenuItemClick(TObject *Sender);
        void __fastcall FileOpenMenuItemClick(TObject *Sender);
        void __fastcall FileCloseMenuItemClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
 __fastcall TMainForm(TComponent* Owner);
 int _terminalsCount;

  void __fastcall OnTerminalOpen(TObject *Sender);
  void __fastcall OnTerminalClose(TObject *Sender);
  bool InitSockets();

 bool FileOpen(void);
 bool FileOpen(ASS fileName);
 bool FileSave();
 bool FileSaveAs();

 void MenuUpdate(int minCount);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
