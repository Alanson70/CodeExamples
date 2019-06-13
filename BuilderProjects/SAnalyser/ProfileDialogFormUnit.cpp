//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProfileDialogFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProfileDialogForm *ProfileDialogForm;
//---------------------------------------------------------------------------
__fastcall TProfileDialogForm::TProfileDialogForm(TComponent* Owner)
        : TForm(Owner)
{
} 
//---------------------------------------------------------------------------
void TProfileDialogForm::Mode(int mode)
{
 _mode=mode;
 switch(mode)
 {
  case 0 :
  Caption="Новый";
  Edit1->ReadOnly=false;
  break;
  case 1 :
  Caption="Открыть";
  Edit1->ReadOnly=true;
  break;
  case 2 :
  Caption="Сохранить как"; 
  Edit1->ReadOnly=false;
  break;
 }
 Edit1Change(this);
}
//---------------------------------------------------------------------------
void __fastcall TProfileDialogForm::Edit1Change(TObject *Sender)
{
 bool ok=true;
 char *z="\\\/:*?\"<>|+";
 char *s=Edit1->Text.c_str();


 if(ChangeFileExt(Edit1->Text,"")<1) ok=false;

 for(int i=0;i<Strlen(s);i++)
  for(int j=0;j<strlen(z);j++)
   if(s[i]==z[j])
   {
    ok=false;
    break;
   }

 OkButton->Enabled=ok;
} 
//---------------------------------------------------------------------------
bool TProfileDialogForm::Execute()
{          
 ASS curDir=GetCurrentDir();
 ForceDirectories(InitialDir);//GetCurrentDir()+"\\Profiles");
 this->FileListBox1->Directory=InitialDir;

 if(ShowModal()==mrOk)
 {
  this->FileName=InitialDir+ASS("\\")+ChangeFileExt(Edit1->Text,".sa3");
  SetCurrentDir(curDir);

  if(_mode==2)
   if(FileExists(FileName)==true)
    if(Application->MessageBox(ASS("Файл " + ChangeFileExt(Edit1->Text,".sa3") + " существует. Перезаписать?").c_str(),
               "Внимание!",  mbYes | mbNo | mbCancel)!=mrYes) return false;
  return true;
 }
 SetCurrentDir(curDir);
 return false;
}
//---------------------------------------------------------------------------
