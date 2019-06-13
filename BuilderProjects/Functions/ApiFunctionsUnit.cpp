//---------------------------------------------------------------------------


#pragma hdrstop

#include "ApiFunctionsUnit.h"

#include <Registry.hpp>
   
#include "Dialogs.hpp"

//#include <shlobj.h>
//---------------------------------------------------------------------------
AnsiString GetCurrentUserPath(ASS param)
{
 AnsiString path;
 TRegistry *reg=new TRegistry;

 reg->RootKey = HKEY_CURRENT_USER;
 reg->OpenKeyReadOnly("\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
 path=reg->ReadString(param);//"personal");

 delete reg;
 return path;
}

 /*
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

}
  */ 
//---------------------------------------------------------------------------
TWinControl *GetTopParentControl(TWinControl *control)
{
 //TWinControl *parent=control;

 for(;;)
 {
  if(control==NULL) break;
  if(control->Parent==NULL)
   return control;
  control=control->Parent;
 }
 return control;
}
//---------------------------------------------------------------------------
int CalculateAbsoluteLeft(TWinControl *control)
{
 int left=0;

 for(;;)
 {
  if(control==NULL) break;
  //if(control->Name.Length());
  left=left+control->Left;
  control=control->Parent;
 }
 return left;
}

//---------------------------------------------------------------------------
int CalculateAbsoluteTop(TWinControl *control)
{
 int top=0;

 for(;;)
 {
  if(control==NULL) break;
  top=top+control->Top;
  control=control->Parent;
 }
 return top;
}
//----------------------------------------------------------------------

//Windows Folder Dialog
// Perhaps it;ll be necessary to ad to Projects->Directories->Conditions string
// NO_WIN32_LEAN_AND_MEAN


AnsiString GetApplicationDataPath(char *productName,char *folderName)
{
 HKEY hKey;
 long lerr;
 char buffer[1000];
 unsigned long count=1000;

 lerr=RegOpenKeyEx (HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders", 0, KEY_QUERY_VALUE, &hKey);

 if (lerr!=ERROR_SUCCESS) return NULL;
 lerr=RegQueryValueEx (hKey, "Common AppData", NULL, NULL, buffer, &count);
 RegCloseKey(hKey);
 if (lerr!=ERROR_SUCCESS)  return NULL;

 AnsiString path=buffer+AnsiString("\\Shaposhnikov\\")+AnsiString(productName)+AnsiString("\\")+AnsiString(folderName)+AnsiString("\\");

 return path;
              
}
/////////////////////////

void ShowSystemErrorMessage(int err)
{
 ShowMessage(SysErrorMessage(err));
}

//////////

bool ConfirmDialog(AnsiString title,AnsiString text)
{
 if(Application->MessageBox(text.c_str(),title.c_str(),MB_YESNO)==IDYES) return true;
 return false;
 //return MessageDlg(text,mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
}

// switch(MessageBox(((TForm *)(this))-> Handle,"Удалить?","Параметры проверки",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON1))


/*********************************************/

   /*
AnsiString selectFolderInitDir;

int __stdcall SelectFolderCallbackFunc(HWND hwnd,UINT uMsg, LPARAM lParam, LPARAM lpData )
{
    char szDir[MAX_PATH];

    switch(uMsg)
    {
        case BFFM_INITIALIZED:
            SendMessage(hwnd, BFFM_SETSTATUSTEXT,0, (LPARAM)"Greetings");

            // Set the initial directory. If WPARAM is TRUE, then LPARAM is a
            // string that contains the path. If WPARAM is FALSE, then LPARAM
            // should be a lovely PIDL
            SendMessage(hwnd, BFFM_SETSELECTION, TRUE,(LPARAM)selectFolderInitDir.c_str());


            break;
        case BFFM_SELCHANGED:
            if(SHGetPathFromIDList((LPITEMIDLIST)lParam, szDir));
   //             MainForm->Label3->Caption = szDir;
            break;

        case BFFM_SETSELECTION :
        break;
    }
    return 0;
}
     */
//---------------------------------------------------------------------------

// not use it anymore - threads not released
// try SelectDirectory
        /*
AnsiString SelectFolder(TObject *object,AnsiString dir,AnsiString title)
{
// AnsiString dir;
 //selectFolderInitDir=dir;

 BROWSEINFO    info;
 char          szDir[MAX_PATH];
 char          szDisplayName[MAX_PATH];
 LPITEMIDLIST  pidl=NULL;
 LPMALLOC      pShellMalloc;

 if(SHGetMalloc(&pShellMalloc) == NO_ERROR)
 {
  memset(&info, 0x00, sizeof(info));
  info.hwndOwner=((TForm *)object)->Handle;
  info.pidlRoot=NULL;//;
  info.pszDisplayName = szDisplayName;
  info.lParam=LPARAM(dir.c_str());
  info.lpszTitle=title.c_str();// "Browse Title";

  info.ulFlags   = BIF_RETURNONLYFSDIRS|0x0040|BIF_STATUSTEXT ;
  info.lpfn      = NULL;//SelectFolderCallbackFunc;//BrowseProc;//NULL;          // callback function

  pidl = SHBrowseForFolder(&info);

  if(pidl)
  {
   if(SHGetPathFromIDList(pidl,szDir))
    dir=szDir;
   else
    dir="";
  }
  else
   dir="";
  pShellMalloc->Free(pidl);
  pShellMalloc->Release();
 }
 return dir;
}
*/





char *UnAllowedSymbols="/\\:*?«<>|.";
//---------------------------------------------------------------------------
AnsiString ImproveFileName(AnsiString name)
{
 //char buffer[2000];
 char *buffer=name.c_str();

// strncpy(buffer,name.c_str(),2000);
 for(int i=0;i<strlen(buffer);i++)
 {
  for(int si=0;si<strlen(UnAllowedSymbols);si++)
  {
   if(buffer[i]==UnAllowedSymbols[si]) buffer[i]='_';
  }
 }
 AnsiString s=buffer;
 return s;
}
//---------------------------------------------------------------------------
bool TestFileName(AnsiString name)
{
// char buffer[2000];
 char *buffer=name.c_str();
// strncpy(buffer,name.c_str(),2000);
 for(int i=0;i<strlen(buffer);i++)
 {
  for(int si=0;si<strlen(UnAllowedSymbols);si++)
  {
   if(buffer[i]==UnAllowedSymbols[si]) return false;
  }
 }
 return true;
}


//---------------------------------------------------------------------------

// Defending from double-starting of programm

#include <process.h>    /* _beginthread, _endthread */

bool _singleStartingShowFlag=false;
HANDLE _singleStartingSemaphor;

void SingleStartingThreadFunc(void *param)
{
 TForm *form=(TForm *)param;

 HANDLE hSemaphore=_singleStartingSemaphor;
 for(;;)
 {
  DWORD dwWaitResult;
  dwWaitResult=WaitForSingleObject(hSemaphore,10000);
  switch(dwWaitResult)
  {
   case WAIT_TIMEOUT  :
   break;

   case WAIT_OBJECT_0	:
    _singleStartingShowFlag=true;
    Application->Restore();
    /*
    if (IsIconic(hWnd))
     ShowWindow(hWnd,SW_RESTORE);
    SetForegroundWindow(hWnd);
    */
   break;
  }
 }
}

//-----------

void SingleStartingFunc(TForm* form)
{
 AnsiString name=ExtractFileName(Application->ExeName)+AnsiString("_Semaphor");// "Shaposhnikov's ApplicationName Semafor";

 _singleStartingShowFlag=false;

 _singleStartingSemaphor=OpenSemaphore(SEMAPHORE_ALL_ACCESS,true,name.c_str());
 if(_singleStartingSemaphor!=NULL)
 {
  ReleaseSemaphore(_singleStartingSemaphor,1,NULL);
  Application->Terminate();
  form->Visible=false;
  return;
 }
 _singleStartingSemaphor=CreateSemaphore(NULL,0,1,name.c_str());

 //TTimer *timer=new TTimer(form);
 //timer->OnTimer=Single

 int err=_beginthread(SingleStartingThreadFunc,1024,form);
}

//-------------------------------------------------------------

//AnotherMethod
void CheckRunning(TForm *form,AnsiString paramMessage)
{
 AnsiString className=form->ClassName();
 AnsiString formName=form->Caption;
 AnsiString appName=Application->Title;

 Application->Title="Temporary Application Title";

 //HWND hWnd=FindWindow(AnsiString(Application->ClassName()).c_str(),appName.c_str());
 
 HWND hWndf=FindWindow(className.c_str(),formName.c_str());
 if(hWndf)
 {
  if(IsWindowVisible(hWndf)==true)
 // form->Caption="123";
  //Sleep(2000);
  //Application->ProcessMessages();
  //HWND hWndf=GetNextWindow(hWnd,GW_HWNDPREV);
 // HWND hWndf=FindWindow(className.c_str(),formName.c_str());
  //HWND hWndf=FindWindow(className.c_str(),formName.c_str());
//  if(hWndf)
  {
   char buffer[100];
   int count=GetWindowText(hWndf,buffer,99);
  // if(hWnd==form->Handle);// return;
  //if(hWnd==Application->MainForm->Handle) return;
   if(IsIconic(hWndf))
    ShowWindow(hWndf,SW_RESTORE);
   SetForegroundWindow(hWndf);

   if(paramMessage.Length()>0)
   {
    TCopyDataStruct ParamCmd;

    ParamCmd.dwData=0;
    ParamCmd.cbData = paramMessage.Length();
    ParamCmd.lpData = paramMessage.c_str();
    SendMessage(hWndf, WM_COPYDATA,  0,Longint(paramMessage.c_str()));
//            Longint(Application->Handle),
   }
   Application->Terminate();
  } 
 }
 form->Caption=formName;
 Application->Title=appName;
}


//-----------------------
         /*
void FirstForm::TimerFunc(TObject *Sender)
{
 if(_mustShow)
 {
  ShowWindow(Application->Handle, SW_SHOW);
 }
}          */
//------------------



 ///// Attempt to change class  name
 /*
 
 //LPTSTR szKey;             // строка с путем к ключу, например "Software\\Microsoft\\Windows\\CurrentVersion\\Run"
 char chBuffer[255];     // имя параметра
 char chType[255];      // тип ключа: REG_SZ, ... в строке
 BYTE chData[255];     // значение параметра
 unsigned long lBufLen = sizeof(chBuffer);
 unsigned long lDataLen = sizeof(chData);
 DWORD dwType;        // тип ключа, число
 unsigned long numItems;

 LPTSTR szKey="Software\\Microsoft\\Windows\\ShellNoRoam\\MUICache";
 _argv[0];
 //lerr = RegOpenKeyEx(HKEY_CURRENT_USER, (LPCTSTR)szKey, 0, KEY_ALL_ACCESS, &hKey);
 lerr = RegOpenKey(HKEY_CURRENT_USER,(LPCTSTR)szKey,&hKey);
 if (lerr!=ERROR_SUCCESS)  return;

 lerr = RegQueryInfoKey(hKey, NULL, NULL, NULL, NULL, NULL, NULL, &numItems, NULL, NULL, NULL, NULL);
 for (unsigned int j = 0; j < numItems; j++)
 {
  lBufLen = sizeof(chBuffer);//эти 2-е строчки перемести перед вызовом
  lDataLen = sizeof(chData);//функции RegEnumValue

  lerr = RegEnumValue(hKey, j, chBuffer, &lBufLen, 0, &dwType, (LPBYTE)chData, &lDataLen);
  if (lerr == ERROR_SUCCESS)
  {
   switch(dwType)
   {
    case REG_DWORD:
    //sprintf(chType, "REG_DWORD");
    break;
    case REG_MULTI_SZ:
    //sprintf(chType, "REG_MULTI_SZ");
    break;
    case REG_SZ:
    if(stricmp(chBuffer,_argv[0])==0)
    {
     / *HKEY hKey1;
     AnsiString key1=chBuffer+AnsiString("\\");
//     char buff[200];
     lerr = RegOpenKey(hKey,(LPCTSTR)key1.c_str(),&hKey1);
     if(lerr== ERROR_SUCCESS)
     {
      AnsiString buf="GenDrevo2";
     //strncpy(chData,buf.c_str(),buf.Length());
      //AnsiString kk=szKey+AnsiString("\\")+AnsiString(chBuffer);
      lerr=RegSetValue(hKey1, chBuffer,REG_SZ,buf.c_str(),buf.Length());
      RegCloseKey(hKey1);
      * /
      //AnsiString buf="GenDrevo2";
      char *buf="GDR";
//      lerr=RegDeleteValue(hKey, chBuffer);
  //    lerr=RegFlushKey(hKey);
    //  lerr = RegCreateKey(hKey, , &hKey);
      lerr=RegSetValue(hKey, chBuffer,REG_SZ,buf,4);
      lerr=RegFlushKey(hKey);

      //RegCloseKey(hKey);

     lerr=1;
    }
   // sprintf(chType, "REG_SZ");
    break;                   // ...
   }
  }
  if(lerr==1) break;
 }
 RegCloseKey(hKey);



 */


  ///////////////// REGISTRATING EXTENSION ////////////////////
//---------------------------------------------------------------------------

// Example of ext : ".mp3"
// Example of command : "Rename vs TAG"

#include <Registry.hpp>


//---------------------------------------------------------------------------
AnsiString GetExePath()
{
 return AnsiString(ExtractFilePath(ParamStr(0)));
}
//---------------------------------------------------------------------------


void AddProgramToRegistry(char *SoftwareName)
{
 TRegistry *Reg;
 Reg=NULL;
 HKEY hKey;

 try
 {
  Reg=new  TRegistry;
  Reg->RootKey=HKEY_LOCAL_MACHINE;
  AnsiString keyString;
  keyString="SOFTWARE";
  keyString=keyString+AnsiString("\\Shaposhnikoff");

  if(Reg->OpenKey(keyString,true)==true)
  {
   Reg->CloseKey();
   keyString=keyString+AnsiString("\\")+AnsiString(SoftwareName);
   if(Reg->OpenKey(keyString,true)==true)
   {
    Reg->CloseKey();
    keyString=keyString+AnsiString("\\ExePath");
    if(Reg->OpenKey(keyString,true)==true)
    {
     Reg->WriteString("",ExtractFilePath(ParamStr(0)));
     Reg->CloseKey();
    }
   }
  }
 }
 __finally
 {
  if  (Reg!=NULL)
   delete Reg;
 }
 return;
}

//---------------------------------------------------------------------------
void __fastcall AddExtensionToRegistry(char *ext,char *extDescription,char *appDescription,char *commandString)
{
 TRegistry *Reg;
 Reg=NULL;
 AnsiString  keyString=appDescription+AnsiString(".")+AnsiString(ext);
 bool add=false;
 try
 {
  Reg=new  TRegistry;
  Reg->RootKey=HKEY_CLASSES_ROOT;
  AnsiString dscr;

  if((commandString!=NULL) & (strlen(commandString)>0)) add=true;

  // Open(create) ext key   // ".ext"
  if(Reg->OpenKey(AnsiString(".")+AnsiString(ext),true)==true)
  {
   // Write Description      // "SoftwareName.ext"
   Reg->WriteString("",keyString);
   Reg->CloseKey();

   // Open(Create) file descr key // "SoftwareName.ext"
   if(Reg->OpenKey(keyString,true)==true)
   {
    Reg->WriteString("",extDescription); // "SoftwareName.ext=(By Default) File Description
    Reg->CloseKey();
    // Open (Create) icon key of descr key and write exe-file path
    if(Reg->OpenKey(keyString+"\\DefaultIcon",true)==true)
    {
     Reg->WriteString("",ParamStr(0)+AnsiString(",0"));
     Reg->CloseKey();
    }
    // Open command key if necessary and set it
    if(add==true)
    {
     if(Reg->OpenKey(keyString+AnsiString("\\shell\\")+AnsiString(commandString)+AnsiString("\\command"),true)==true)
     {
       //create value where exefile is stored --> c:\project1.exe "%1"
      Reg->WriteString("",ParamStr(0)+" \"%1\"");
     }
     Reg->CloseKey();
    }
   }
  }
 }
 __finally
 {
  if  (Reg!=NULL)
   delete Reg;
 }

 try
 {
  Reg=new  TRegistry;
  Reg->RootKey=HKEY_CURRENT_USER;
  if(Reg->OpenKey("\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\."+AnsiString(ext),false))
  {
   Reg->WriteString("",extDescription);
   Reg->WriteString("Progid",keyString);
   Reg->CloseKey();
  }
 } 
 __finally
 {
  if  (Reg!=NULL)
   delete Reg;
 }
 return;
   /*
  keyString="\\"+AnsiString(applicationDesription)+AnsiString("\\Shell\\");
  if(add==true) keyString=keyString+AnsiString(commandString);
  else          keyString=keyString+AnsiString("Open");
  keyString=keyString+AnsiString("\\Command");

  Reg->OpenKey(keyString,true);
  try
  {
   Reg->WriteString("",ParamStr(0)+"  \"%1\"");
   Reg->CloseKey();
   if(add==false)
   {
    keyString="\\"+AnsiString(applicationDesription)+AnsiString("\\DefaultIcon");
    Reg->OpenKey(keyString,true);
    Reg->WriteString("",ParamStr(0)+",  1");
    Reg->CloseKey();
   }
  }
  catch(...)
  {   
   Reg->CloseKey();
  }
 }

 */
}
//---------------------------------------------------------------------------
/*
void __fastcall AddExtensionToRegistry(char *ext,char *command)  // old version
{
 HKEY hKey;
 long lerr;
 char buffer[1000];
 long count=1000;

 AnsiString dscr=GetVersionInfo("FileDescription",-1);

 // find  extention type

 lerr = RegOpenKey(HKEY_CLASSES_ROOT,ext , &hKey);
 if (lerr!=ERROR_SUCCESS)
 {
  lerr = RegCreateKey(HKEY_CLASSES_ROOT,ext , &hKey);
  if (lerr!=ERROR_SUCCESS)  return;
 }
 lerr=RegQueryValue(HKEY_CLASSES_ROOT,ext,buffer,&count);
 RegCloseKey(hKey);
 if (lerr!=ERROR_SUCCESS)  return;

 AnsiString SubKey1=buffer+AnsiString("\\shell\\")+AnsiString(command);
 AnsiString SubKey=SubKey1+AnsiString("\\command\\");

 / *
 // find key
 lerr = RegOpenKey(HKEY_CLASSES_ROOT, SubKey.c_str(), &hKey);
 if (lerr!=ERROR_SUCCESS) return;
  // show key
 lerr=RegQueryValue(HKEY_CLASSES_ROOT,SubKey.c_str(),buffer,&count);
   * /
 // create key
 lerr = RegCreateKey(HKEY_CLASSES_ROOT, SubKey.c_str(), &hKey);
 if (lerr==ERROR_SUCCESS)
 {                                                   
  AnsiString buf=AnsiString("\"")+GetVersionInfo("FileDescription",-1)+AnsiString("\" \"%1\"");
  //AnsiString buf=AnsiString("\"")+Application->ExeName+AnsiString("\" \"%1\"");
  lerr=RegSetValue(HKEY_CLASSES_ROOT, SubKey.c_str(),REG_SZ,buf.c_str(),buf.Length());
  if (lerr==ERROR_SUCCESS);
  RegCloseKey(hKey);
 }   
 //RegistryMenuItem->Checked=IsInRegistry(); ///????????????????????
}
*/
//---------------------------------------------------------------------------

bool __fastcall IsExtensionInRegistry(char *ext,char *command)
{
 HKEY hKey;
 long lerr;
 char buffer[1000];
 long count=1000;

 // find mp3 extention type

 lerr = RegOpenKey(HKEY_CLASSES_ROOT, ext, &hKey);
 if (lerr!=ERROR_SUCCESS) return false;
 lerr=RegQueryValue(HKEY_CLASSES_ROOT,ext,buffer,&count);
 RegCloseKey(hKey);
 if (lerr!=ERROR_SUCCESS)  return false;

 AnsiString SubKey1=buffer+AnsiString("\\shell\\")+AnsiString(command);
 AnsiString SubKey=SubKey1+AnsiString("\\command\\");

 // find key
 lerr = RegOpenKey(HKEY_CLASSES_ROOT, SubKey.c_str(), &hKey);
 if (lerr!=ERROR_SUCCESS) return false;
  // read key value
 count=1000;
 lerr=RegQueryValue(HKEY_CLASSES_ROOT,SubKey.c_str(),(char *)buffer,&count);
 RegCloseKey(hKey);
 if (lerr!=ERROR_SUCCESS) return false;

 AnsiString buf=(AnsiString("\"")+Application->ExeName+AnsiString("\" \"%1\"")).c_str();
 if(AnsiString(buffer)==buf) return true;

 return false;
}
//---------------------------------------------------------------------------

void __fastcall RemoveExtensionFromRegistry(char *ext,char *command)
{
 HKEY hKey;
 long lerr;
 char buffer[1000];
 long count=1000;

  // find mp3 extention type

 lerr = RegOpenKey(HKEY_CLASSES_ROOT,ext, &hKey);
 if (lerr!=ERROR_SUCCESS) return;
 lerr=RegQueryValue(HKEY_CLASSES_ROOT,ext,buffer,&count);
 RegCloseKey(hKey);
 if (lerr!=ERROR_SUCCESS)  return;

 AnsiString SubKey1=buffer+AnsiString("\\shell\\")+AnsiString(command);
 AnsiString SubKey=SubKey1+AnsiString("\\command\\");

 // find key
 lerr = RegOpenKey(HKEY_CLASSES_ROOT, SubKey.c_str(), &hKey);
 if (lerr!=ERROR_SUCCESS) return;

 // deleting of key
 RegCloseKey(hKey);
 lerr = RegDeleteKey(HKEY_CLASSES_ROOT, SubKey.c_str());
 lerr = RegDeleteKey(HKEY_CLASSES_ROOT, SubKey1.c_str());

 
 ///// RegistryMenuItem->Checked=IsInRegistry(); // ??????????????
}


//---------------------------------------------------------------------------
AnsiString VersionInfoValue;

AnsiString GetVersionInfo(char *ident,int num)
{
 char *VersionInfoBuffer=NULL;
 const char *noInfo="";
 const AnsiString InfoStr[10] =
  {"CompanyName", "FileDescription", "FileVersion", "InternalName", "LegalCopyright", "LegalTradeMarks", "OriginalFileName", "ProductName", "ProductVersion", "Comments"};
 char *ExeName = Application->ExeName.c_str();
 DWORD n=0;
 ExeName[strlen(ExeName)-1]=0;

 VersionInfoValue=noInfo;

 n=GetFileVersionInfoSize(ExeName, &n);
 if(n>0)
 {
  VersionInfoBuffer= (char *) malloc(n);
  GetFileVersionInfo(ExeName, 0, n, VersionInfoBuffer);
 }
 else return VersionInfoValue;

 n=-1;

 if(ident!=NULL)
 {
  for (int i = 0; i < 10; i++)
  {
   if(!strcmp(ident,InfoStr[i].c_str())) { n=i;break;}
  }
 }
 else n=num;
 if(n>=0 & n<10)
 {
  char *pValue;
  unsigned int Len;

  VerQueryValue(VersionInfoBuffer, "\\VarFileInfo\\Translation", &(void *)pValue,&Len);
  if(Len>=4) 
  {
   AnsiString CharSet=IntToHex((int )MAKELONG(*(int *)(pValue + 2),*(int *)pValue), 8);

   AnsiString temp = "StringFileInfo\\"+CharSet+AnsiString("\\")+AnsiString(InfoStr[n]);
//   temp = temp ;
   if (VerQueryValue(VersionInfoBuffer, temp.c_str(),&(void *)pValue, &Len))
    VersionInfoValue=pValue;
  }
 }
 free(VersionInfoBuffer);


 return VersionInfoValue;
}

//---------------------------------------------------------------------------
#include <Clipbrd.hpp>

void AnsiClearClipboard()
{
 Clipboard()->Clear();
}
//---------------------------------------------------------------------------
void AnsiToClipboard(AnsiString s)
{
 int len = (s.Length() + 1) * 2;
 HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE,len);
 if(hGlobal != NULL)
 {
  void *lpText = GlobalLock(hGlobal);
  Move(WideString(s).c_bstr(), lpText, len);
//   Clipboard()->Clear();
  GlobalUnlock(hGlobal);
  Clipboard()->SetAsHandle(CF_UNICODETEXT,(int)hGlobal);
 }
}

//---------------------------------------------------------------------------


AnsiString AnsiFromClipboard()
{
 AnsiString s;
 int WTextHandle = Clipboard()->GetAsHandle ( CF_UNICODETEXT );
 wchar_t * wpText = (wchar_t *)GlobalLock ( (HGLOBAL)WTextHandle );

 s= wpText;
 GlobalUnlock ( (HGLOBAL)WTextHandle );

 return s;

}




              // Test On Exclusuve copy of running programm
              // function must be inserted in ~ as

              /*
               #include "../Functions/AppMutexFile.h"

              WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
              {
               if(CheckAppInstance()==true)
               {
                */

bool CheckAppInstance() // Test if this class application is running and fix up id it's not true
{
 HANDLE AppMutex;
 HWND P;

 AppMutex=CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE,
   0, 1024, Application->Title.c_str());
        //0, 1024, (ExtractFileName(Application->ExeName)).c_str());

 bool result=true;
 if(GetLastError()==ERROR_ALREADY_EXISTS) result=false;  // application is already run
 P=MapViewOfFile(AppMutex, FILE_MAP_WRITE, 0, 0, 0);
 if(P==NULL) result=false;
 else
 {
  if(result) // remember our description
  {
   //P=Application->Handle;
   memcpy(P,(char *)&(Application->Handle),sizeof(Application->Handle));
  }
  else
  {
   HANDLE h;
   memcpy((char *)&h,P,sizeof(Application->Handle));

   if(IsIconic(h))
    ShowWindow(h,SW_RESTORE);
   SetForegroundWindow(h);

   if(_argc>1)
   {
    TCopyDataStruct ParamCmd={0};
    ParamCmd.dwData=Longint(Application->Handle);
    ParamCmd.cbData =strlen(_argv[1])+1;
    ParamCmd.lpData =_argv[1];

    SendMessage(h, WM_COPYDATA,(WPARAM)Application->Handle,(LPARAM)&ParamCmd);
   }
  }


  if(P!=NULL)
   UnmapViewOfFile(P);
  if(result==false)
   CloseHandle(AppMutex);

 }
 return result;
}
//---------------------------------------------
          // test if file in argv is running by this class of application
          // another application must CreateFileInstance
bool TestFileInstance(char *fileName)
{

 bool result=CreateFileInstance(fileName);

 CloseFileInstance();

 return result;
}

//-----------------

HANDLE _AppMutex=NULL;
          // fix up that file is running by this class of application
          // In Form Create
bool CreateFileInstance(char *fileName)
{
 if(fileName==NULL) return true;

 AnsiString title=fileName;

 for(int i=0;i<title.Length();i++)
  if(title.operator [](i+1)=='\\') title.operator [](i+1)=':';

 if(FileExists(fileName))
 {
  HWND P;

  _AppMutex=CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE,0, 1024,title.c_str());

  if(GetLastError()==ERROR_ALREADY_EXISTS)
  {
   P=MapViewOfFile(_AppMutex, FILE_MAP_WRITE, 0, 0, 0);
   if(P!=NULL)
   {
    HANDLE h;
    memcpy((char *)&h,P,sizeof(Application->Handle));

    if(IsIconic(h))
     ShowWindow(h,SW_RESTORE);
    SetForegroundWindow(h);
    UnmapViewOfFile(P);
   }
   CloseHandle(_AppMutex);
   _AppMutex=NULL;
   return false;  // application is already run
  }

  int err=GetLastError();
  char buffer[1024];
  FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,GetLastError(),0,buffer,1024,NULL);

  P=MapViewOfFile(_AppMutex, FILE_MAP_WRITE, 0, 0, 0);
  if(P==NULL)
  {
   CloseHandle(_AppMutex);
   _AppMutex=NULL;
   return false;
  }
   // remember our description
  memcpy(P,(char *)&(Application->Handle),sizeof(Application->Handle));
  if(P!=NULL)
   UnmapViewOfFile(P);
 }
 else return false;

 return true;
}

//-----------------
bool CloseFileInstance()
{
 if(_AppMutex)  CloseHandle(_AppMutex);
 _AppMutex=NULL;
 return true;
}

//////////////// Hook Messages
   // hook of messages - starting keys sending by function OneInstnse
   // set this string in FormCreate:
   //
   //    Application->HookMainWindow(ApplicationHookProc);
   //


// Declair this function and redifine of reset MessageProceesFunc(text);
/*
//---------------------------------------------------------------------------
bool __fastcall TMainForm::ApplicationHookProc(TMessage &Message)
{
 switch (Message.Msg)
 {
  case WM_COPYDATA :
  {
   TCopyDataStruct *ParamCmd=(TCopyDataStruct *)Message.LParam;
   char *text=(char *)(ParamCmd->lpData);

   //AddNewFile(text);
   MessageProceesFunc(text);
  }
  return true; //true - запрещаем другую обработку

  default: break;
 }
 return false; //false - разрешаем обработку этого сообщения
}
*/

#include <Clipbrd.hpp>

void TextPopupMenuPopupFunc(TObject *Sender)
{
 TPopupMenu *menu=(TPopupMenu *)Sender;

 if(menu->PopupComponent->InheritsFrom(__classid(TCustomEdit)))
 {
  TCustomEdit *edit=(TCustomEdit *)(menu->PopupComponent);
  if(edit->SelText.Length()>0)
   menu->Items->Items[1]->Enabled=true;//   TextCopyMenuItem->Enabled=true;
  else
   menu->Items->Items[1]->Enabled=false;//TextCopyMenuItem->Enabled=false;
 }
 else
 if(menu->PopupComponent->InheritsFrom(__classid(TCustomComboBox)))
 {
  TCustomComboBox *edit=(TCustomComboBox *)(menu->PopupComponent);
  if(edit->SelText.Length()>0)
   menu->Items->Items[1]->Enabled=true;//TextCopyMenuItem->Enabled=true;
  else
   menu->Items->Items[1]->Enabled=false;//TextCopyMenuItem->Enabled=false;
 }
 else return;

 menu->Items->Items[0]->Enabled=true;//=TextCopyMenuItem->Enabled;

 if(Clipboard()->HasFormat(CF_TEXT))
  menu->Items->Items[2]->Enabled=true;//TextPasteMenuItem->Enabled=true;
 else
  menu->Items->Items[2]->Enabled=false;//TextPasteMenuItem->Enabled=false;

}

//--------------------------------------------------------

void TextMenuItemClickFunc(TObject *Sender)
{
 TMenuItem *item=(TMenuItem *)Sender;
 TPopupMenu *menu=(TPopupMenu *)item->GetParentMenu();

 if(menu->PopupComponent->InheritsFrom(__classid(TCustomEdit)))
 {
  TCustomEdit *edit=(TCustomEdit *)(menu->PopupComponent);
  switch(item->Tag)
  {
   case 0 :  
   if(edit->SelText.Length()>0)
   {
    AnsiToClipboard(edit->SelText);
    edit->ClearSelection();
   } 
   break;
   case 1 :
   if(edit->SelText.Length()>0)
    AnsiToClipboard(edit->SelText);
   break;
   case 2 :
   if(Clipboard()->HasFormat(CF_TEXT))
    edit->SetSelTextBuf(AnsiFromClipboard().c_str());
   break;
  }
 }
 else 
 if(menu->PopupComponent->InheritsFrom(__classid(TCustomComboBox)))
 {
  TCustomComboBox *edit=(TCustomComboBox *)(menu->PopupComponent);
  switch(item->Tag)
  {
   case 0 :
   AnsiToClipboard(edit->SelText);
   edit->ClearSelection();
   break;
   case 1 :
   AnsiToClipboard(edit->SelText);
   break;
   case 2 :
   if(Clipboard()->HasFormat(CF_TEXT))
   {
    if(edit->Items->Count<3)
     edit->Items->Add(AnsiFromClipboard().c_str());
    else
     edit->Items->Strings[2]=AnsiFromClipboard().c_str();
    edit->ItemIndex=2;
   }
   break;
  }
 }
}
//----------------------------------------------------------------------------
















///------------------------------------

#pragma package(smart_init)
