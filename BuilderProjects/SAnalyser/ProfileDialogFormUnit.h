//---------------------------------------------------------------------------

#ifndef ProfileDialogFormUnitH
#define ProfileDialogFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <FileCtrl.hpp> 
#include "Functions.h"
//---------------------------------------------------------------------------
class TProfileDialogForm : public TForm
{
__published:	// IDE-managed Components
        TFileListBox *FileListBox1;
        TEdit *Edit1;
        TButton *OkButton;
        TButton *CancelButton;
        void __fastcall Edit1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
 __fastcall TProfileDialogForm(TComponent* Owner);
 int _mode;
 void Mode(int mode);
 ASS Filter;
 ASS Title;
 ASS DefaultExt;
 ASS FileName;
 ASS InitialDir;

 bool Execute();
};

#define TFileDialog TProfileDialogForm  
#define TSaveDialog TProfileDialogForm
#define TOpenDialog TProfileDialogForm
//---------------------------------------------------------------------------
extern PACKAGE TProfileDialogForm *ProfileDialogForm;
//---------------------------------------------------------------------------
#endif
