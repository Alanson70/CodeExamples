//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFormUnit.h"
#include <NMUDP.hpp>
#include "AboutFormUnit.h"
#include "Inifiles.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "TerminalFormUnit.h"
#include "ApiFunctionsUnit.h"
//#include "UTermSetFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
 _terminalsCount=1;

 if(InitSockets()==false)
  Application->Terminate();


}

//----
//---------------------------------------------------------------------------

bool TMainForm::InitSockets()
{
 WORD wVersionRequested;
 WSADATA wsaData;
 int err;
  
 wVersionRequested = MAKEWORD( 2, 0 );
 
 err = WSAStartup( wVersionRequested, &wsaData );
 if ( err != 0 )
 {
    /* Tell the user that we couldn't find a usable */
    /* WinSock DLL.                                  */
    return false;
 }

/* Confirm that the WinSock DLL supports 2.0.*/
/* Note that if the DLL supports versions greater    */
/* than 2.0 in addition to 2.0, it will still return */
/* 2.0 in wVersion since that is the version we      */

/* requested.                                        */

 if ( LOBYTE( wsaData.wVersion ) != 2 ||
        HIBYTE( wsaData.wVersion ) != 0 ) {
    /* Tell the user that we couldn't find a usable */
    /* WinSock DLL.                                  */
    WSACleanup( );
    return false;
 }
 return true;

}

//---------------------------------------------------------------------------


void __fastcall TMainForm::TerminalOpenMenuItemClick(TObject *Sender)
{
 /*ASS path;
 TRegistry *reg=new TRegistry;

 reg->RootKey = HKEY_CURRENT_USER;
 reg->OpenKeyReadOnly("\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
 path=reg->ReadString("personal");

 delete reg;

StaticText2.Caption :=
reg.ReadString('Shell Folders','cache','');
StaticText4.Caption :=
reg.ReadString('Shell Folders','cookies','');
StaticText6.Caption :=
reg.ReadString('Shell Folders','desktop','');
StaticText8.Caption :=
reg.ReadString('Shell Folders','favorites','');
StaticText10.Caption :=
reg.ReadString('Shell Folders','fonts','');
StaticText12.Caption :=
reg.ReadString('Shell Folders','personal','');
StaticText14.Caption :=
reg.ReadString('Shell Folders','programs','');
StaticText16.Caption :=
reg.ReadString('Shell Folders','recent','');
StaticText18.Caption :=
reg.ReadString('Shell Folders','sendto','');
StaticText20.Caption :=
reg.ReadString('Shell Folders','startup','');
reg.CloseKey;
reg.Free;
end;

                                                  */

 FileOpen("Noname");//ExtractFilePath(_argv[0])+ASS("Default.ini"));

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::TerminalCloseMenuItemClick(TObject *Sender)
{
 if(this->ActiveMDIChild==NULL) return;
 ((TTerminalForm *)(this->ActiveMDIChild))->Close();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::TerminalControlMenuItemClick(TObject *Sender)
{
 /*for(int i=0;i<this->ControlCount;i++)
 {
  if(c->InheritsFrom(__classid(TUTermForm)))
  if(Controls[i]->InheritsFrom()
 }
 */
 if(this->ActiveMDIChild==NULL) return;
 ((TTerminalForm*)(this->ActiveMDIChild))->ControlButtonClick(this);
}    
//---------------------------------------------------------------------------

void TMainForm::MenuUpdate(int minCount)
{
 if(MDIChildCount>=minCount)
 {
  TerminalCloseMenuItem->Enabled=true;
  TerminalControlMenuItem->Enabled=true;
  FileCloseMenuItem->Enabled=true; 
  FileSaveAsMenuItem->Enabled=true;
 }
 else
 {
  TerminalCloseMenuItem->Enabled=false;
  TerminalControlMenuItem->Enabled=false;
  FileCloseMenuItem->Enabled=false; 
  FileSaveAsMenuItem->Enabled=false;
 }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnTerminalClose(TObject *Sender)
{
 MenuUpdate(2);
} 
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnTerminalOpen(TObject *Sender)
{
 MenuUpdate(1);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AboutMenuItemClick(TObject *Sender)
{
 TAboutForm *form=new TAboutForm(this);

 try
 {
  form->ShowModal();
  delete form;
 }
 catch(...)
 {
  delete form;
 }              
}
//---------------------------------------------------------------------------

bool TMainForm::FileOpen()
{
 OpenDialog1->DefaultExt="*.utt";
 OpenDialog1->Filter="Файл ю-терминала|*.utt";
 if(OpenDialog1->Execute())
 {
  return FileOpen(OpenDialog1->FileName);
 }
 return false;
}
//---------------------------------------------------------------------------
bool TMainForm::FileOpen(ASS fileName)
{
 TTerminalForm *termForm;

 for(int i=0;i<MDIChildCount;i++)
 {
  termForm=(TTerminalForm *)this->MDIChildren[i];
  if(termForm->_profile==fileName)
  {
   termForm->BringToFront();
   if(termForm->WindowState==wsMinimized)
    termForm->WindowState=wsNormal;
   termForm->Show();
   return true;
  }
 }

 termForm=new TTerminalForm(this);
 termForm->OnTerminalCreate=OnTerminalOpen;
 termForm->OnTerminalDestroy=OnTerminalClose;

 if(FileExists(fileName)==false)
 {
  //fileName=GetCurrentDir()+ASS("\\Default.ini");
  //GetCurrentUserPath("Personal");
  termForm->LoadProfile(fileName);
  termForm->ControlButtonClick(this);

  /*
  if(termForm->ControlStart(0)==mrCancel)
  {
   delete termForm;
   return false;
  }
  */
 }
 else
 {
  termForm->LoadProfile(fileName);
  termForm->Connect();
  //ControlStart(1);
 }
 termForm->Show();
 //termForm->Caption=fileName;//AnsiString("Terminal ")+_terminalsCount;
 
 MenuUpdate(1);
 return true;

}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FileSaveAsMenuItemClick(TObject *Sender)
{
 TTerminalForm *termForm=(TTerminalForm *)MDIChildren[0];

 SaveDialog1->Title="Сохранение";
 SaveDialog1->DefaultExt="*.utt";
 SaveDialog1->Filter="Файл унитерминала|*.utt";
 SaveDialog1->FileName=termForm->_profile;// _setForm->_fileName;// OpenDialog1->FileName;

 if(termForm->Caption=="Default")
 {
  SaveDialog1->FileName="";
  SaveDialog1->InitialDir=GetCurrentUserPath("Personal");
 }

// ASS currDir=GetCurrentDir();

 if(SaveDialog1->Execute()==true)
 {
  OpenDialog1->FileName=SaveDialog1->FileName;
  FileSaveAsMenuItem->Enabled=true;
  //termForm->_setForm->_fileName=SaveDialog1->FileName;
  termForm->SaveProfileAs(SaveDialog1->FileName);// _setForm->SaveProfileAs(SaveDialog1->FileName);
 }
 //SetCurrentDir(currDir);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileNewMenuItemClick(TObject *Sender)
{

 SaveDialog1->Title="Новый";
 SaveDialog1->Filter="Файл унитерминала|*.utt";
 //SaveDialog1->FileName=OpenDialog1->FileName;
 //ASS currDir=GetCurrentDir();

 if(SaveDialog1->Execute()==true)
 {
  //FileOpen("Default.ini");
 // TTerminalForm *termForm=(TTerminalForm *)MDIChildren[0];
 // termForm->SaveProfileAs(SaveDialog1->FileName);
  FileOpen(SaveDialog1->FileName);
 }
 
 //SetCurrentDir(currDir);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileOpenMenuItemClick(TObject *Sender)
{            
 FileOpen();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FileCloseMenuItemClick(TObject *Sender)
{
 TerminalCloseMenuItemClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
 for(;;)
 {
  if(this->ActiveMDIChild!=NULL)
  {
   TForm *form=this->ActiveMDIChild;
   form->Close();
   delete form; 
  }
  else
   break; 
 }
}
//---------------------------------------------------------------------------


