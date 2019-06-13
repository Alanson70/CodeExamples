//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFormUnit.h"
#include "AnalyserMeterFrameUnit.h"
#include "ProfileDialogFormUnit.h"
#include "AnalyserViewerFrameUnit.h"
#include "ApiFunctionsUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
 Caption="СПЕКТРОС";

 SetCurrentDir(ExtractFilePath(_argv[0]));

 if(_argc>6)
 {
  IF(_argv[2],"TCP",3)
  {

  }
 }

 

 //AnalyserMeterFrame->ConnectFrame1->ConnectButtonClick(this);
}

//---------------------------------------------------------------------------
char *FirmwareName="Shaposhnikov A.A.";
char *SoftwareName="SPECTROS";
char *Extensions[]={"sa3",NULL};
char *ExtensionDescription="Spectrum Analyser Profile";

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
 AddExtensionToRegistry(Extensions[0],ExtensionDescription,SoftwareName,"Open By");

 Application->ShowHint=true;
 Application->HintHidePause=20000;
 Application->HookMainWindow(ApplicationHookProc); 
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormShow(TObject *Sender)
{
 ASS fileName=GetCurrentDir()+ASS("\\Default.ini");
 TIniFile *iniFile=new TIniFile(fileName);
 ProfileAutoSaveMenuItem->Checked=iniFile->ReadBool("Main","ProfileAutoSave",true);
 ProfileAutoLoadMenuItem->Checked=iniFile->ReadBool("Main","ProfileAutoLoad",true);
 fileName=iniFile->ReadString("Main","ProfileLastFile","");
 RecMenuItem->Checked=1-iniFile->ReadBool("Main","ViewerMode",false);
 ViewerMenuItem->Checked=iniFile->ReadBool("Main","ViewerMode",false);

 delete iniFile;

 if(_argc>1)
 {
  char fullPath[2000];
  char *bufFile;
  GetLongPathName(_argv[1],fullPath,1900);
  OpenSA(fullPath);
 }
 else
 if(this->ProfileAutoLoadMenuItem->Checked==true)
 {
  OpenSA(fileName);
 }
}

//---------------------------------------------------------------------------
bool __fastcall TMainForm::ApplicationHookProc(TMessage &Message)
{
 switch (Message.Msg)
 {
  case WM_COPYDATA :
  {
   TCopyDataStruct *ParamCmd=(TCopyDataStruct *)Message.LParam;
   char *text=(char *)(ParamCmd->lpData);

   char fullPath[2000];
   char *bufFile;
   GetLongPathName(text,fullPath,1900);

   OpenSA(fullPath);

  }
  return true; //true - запрещаем другую обработку

  default:
  //Memo1->Lines->Add(ASS(Message.Msg));
  break;
 }
 return false; //false - разрешаем обработку этого сообщения
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 ASS fileName=GetCurrentDir()+ASS("\\Default.ini");

 TIniFile *iniFile=new TIniFile(fileName);

 iniFile->WriteBool("Main","ProfileAutoSave",ProfileAutoSaveMenuItem->Checked);
 iniFile->WriteBool("Main","ProfileAutoLoad",ProfileAutoLoadMenuItem->Checked);
 iniFile->WriteString("Main","ProfileLastFile",_fileName);
 iniFile->WriteBool("Main","ViewerMode",ViewerMenuItem->Checked);

 delete iniFile;

 CloseSA();
}
//---------------------------------------------------------------------------
void TMainForm::OpenSA(ASS fileName)
{
 CloseSA();

 if(FileExists(fileName)==false) return;

 _fileName=fileName;

 Caption="СПЕКТРОС."+ChangeFileExt(ExtractFileName(fileName),"");
 TIniFile *iniFile=new TIniFile(fileName);//GetCurrentDir()+AnsiString("\\UniTerm.ini"));

 Left=iniFile->ReadInteger("Defaults","Left",Left);
 Top=iniFile->ReadInteger("Defaults","Top",Top);
 Width=iniFile->ReadInteger("Defaults","Width",Width);
 Height=iniFile->ReadInteger("Defaults","Height",Height);

 delete iniFile;

 if(RecMenuItem->Checked==true)
  _frame=new TAnalyserMeterFrame(this);
 else
  _frame=new TAnalyserViewerFrame(this);

 _frame->Parent=this;
 _frame->Align=alClient;
 _frame->LoadBaseInits(fileName);
 _frame->SettsButtonClick(this);

 ProfileSaveAsMenuItem->Enabled=true;
 ProfileSaveMenuItem->Enabled=true;
 ProfileCloseMenuItem->Enabled=true;
}
//---------------------------------------------------------------------------
void TMainForm::CloseSA()
{
 ASS fileName=_fileName;

 if(FileExists(fileName)==true)
 {
  if(this->ProfileAutoSaveMenuItem->Checked==true)
  {
   SaveSA(fileName);
  }
  else
  {
   if(Application->MessageBox(ASS("Профиль " + fileName + " будет закрыт. Сохранить?").c_str(),
               "Внимание!",  mbYes | mbNo | mbCancel)==mrYes)

   SaveSA(fileName);
  }
 }

 //_fileName="";
 Caption="СПЕКТРОС";
 ProfileSaveAsMenuItem->Enabled=false;
 ProfileSaveMenuItem->Enabled=false;
 ProfileCloseMenuItem->Enabled=false;

 if(_frame==NULL) return;
 delete _frame;
 _frame=NULL;
} 
//---------------------------------------------------------------------------
void TMainForm::SaveSA(ASS fileName)
{
 if(fileName.Length()<1) return;

 _fileName=fileName;

 _frame->SaveBaseInits(fileName);

 TIniFile *iniFile=new TIniFile(fileName);//GetCurrentDir()+AnsiString("\\UniTerm.ini"));

 iniFile->WriteInteger("Defaults","Left",Left);
 iniFile->WriteInteger("Defaults","Top",Top);
 iniFile->WriteInteger("Defaults","Width",Width);
 iniFile->WriteInteger("Defaults","Height",Height);

 delete iniFile;
 Caption="СПЕКТРОС."+ChangeFileExt(ExtractFileName(_fileName),"");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ExitMenuItemClick(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ProfileOpenMenuItemClick(TObject *Sender)
{
 TOpenDialog *dialog=new TOpenDialog(this); //
 dialog->Mode(1);
 dialog->Title="Открытие профиля";
 dialog->DefaultExt=".sa3";
 dialog->Filter="Профиль спектроанализатора|*.sa3";
 dialog->FileName=_fileName;
 dialog->InitialDir=GetCurrentDir()+"\\Profiles";//
 if(dialog->Execute()==true)
 {
  ASS fileName=dialog->FileName;
  OpenSA(fileName);
 }
 delete dialog;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ProfileNewMenuItemClick(TObject *Sender)
{
 CloseSA();
 ForceDirectories(GetCurrentDir()+"\\Profiles");

 TSaveDialog *dialog=new TSaveDialog(this); // SaveDialog1;//
 dialog->Mode(0);
 dialog->Title="Создание профиля";
 dialog->DefaultExt=".sa3";
 dialog->Filter="Профиль спектроанализатора|*.sa3";
 dialog->FileName=_fileName;
 dialog->InitialDir=GetCurrentDir()+"\\Profiles";//
 if(dialog->Execute()==true)
 {
  ASS fileName=dialog->FileName;
  OpenSA(fileName);
  SaveSA(fileName);
 }
 delete dialog;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ProfileSaveAsMenuItemClick(TObject *Sender)
{
 ForceDirectories(GetCurrentDir()+"\\Profiles");

 TSaveDialog *dialog=new TSaveDialog(this);
 dialog->Mode(2);
 dialog->Title="Переименование профиля";
 dialog->DefaultExt=".sa3";
 dialog->Filter="Профиль спектроанализатора|*.sa3";
 dialog->FileName=_fileName;
 dialog->InitialDir=GetCurrentDir()+"\\Profiles";//
 if(dialog->Execute()==true)
 {
  ASS fileName=dialog->FileName;
  SaveSA(fileName);
 }
 delete dialog;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ProfileCloseMenuItemClick(TObject *Sender)
{
 CloseSA();

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ProfileSaveMenuItemClick(TObject *Sender)
{
 SaveSA(_fileName);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::RecMenuItemClick(TObject *Sender)
{
 RecMenuItem->Checked=true;
 if(_frame==NULL) return;

 if(_frame->InheritsFrom(__classid(TAnalyserViewerFrame)))
 {
  OpenSA(_fileName);
 }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ViewerMenuItemClick(TObject *Sender)
{             
 ViewerMenuItem->Checked=true;
 if(_frame==NULL) return;

 if(_frame->InheritsFrom(__classid(TAnalyserMeterFrame)))
 {
  OpenSA(_fileName);
 }
}

//---------------------------------------------------------------------------

