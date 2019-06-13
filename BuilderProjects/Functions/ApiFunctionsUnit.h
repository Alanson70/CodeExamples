//---------------------------------------------------------------------------

#ifndef ApiFunctionsUnitH
#define ApiFunctionsUnitH
 
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#define ASS AnsiString
//-------------------------- //

bool ConfirmDialog(AnsiString title,AnsiString text);
void ShowSystemErrorMessage(int err);


AnsiString GetCurrentUserPath(AnsiString param);
///////////////////////////////////////////////////////////////////
TWinControl *GetTopParentControl(TWinControl *control);
int CalculateAbsoluteLeft(TWinControl *control);
int CalculateAbsoluteTop(TWinControl *control);


void TextMenuItemClickFunc(TObject *Sender);
void TextPopupMenuPopupFunc(TObject *Sender);

AnsiString GetApplicationDataPath(char *productName,char *folder);


// not use it anymore - threads not released
// try SelectDirectory
AnsiString SelectFolder(TObject *object,AnsiString dir,AnsiString title);

AnsiString ImproveFileName(AnsiString name);
bool TestFileName(AnsiString name);
////////////////////////////////////////////
// single starting
void SingleStartingFunc(TForm* form);
void CheckRunning(TForm *form,AnsiString paramMessage);

/////////////////////////////////////////////////
void __fastcall AddExtensionToRegistry(char *ext,char *extDescription,char *applicationDesription,char *command="");
void AddProgramToRegistry(char *SoftwareName);
AnsiString GetExePath();

//void __fastcall AddExtensionToRegistry(char *ext,char *command);
bool __fastcall IsExtensionInRegistry(char *ext,char *command);
void __fastcall RemoveExtensionFromRegistry(char *ext,char *command);

AnsiString GetVersionInfo(char *ident,int num);

///////////////////////////////////////////////////////////////////
void AnsiToClipboard(AnsiString s);
AnsiString  AnsiFromClipboard();
void AnsiClearClipboard();
///////////////////////////////////////////////////////////////////

           
bool CheckAppInstance();
bool TestFileInstance(char *fileName);
bool CreateFileInstance(char *fileName);
bool CloseFileInstance();

//---------------------------------------------------------------------------
#endif
