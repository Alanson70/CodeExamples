
//---------------------------------------------------------------------------
#include           <Jpeg.hpp>

void __fastcall TAnalyserBaseFrame::SaveImgMenuItemClick(TObject *Sender)
{
 AnsiString dir=GetCurrentDir();

 SaveDialog1->InitialDir=GetCurrentUserPath("Personal");
 SaveDialog1->DefaultExt = ".bmp";//GraphicExtension(__classid(Graphics::TBitmap));
 SaveDialog1->Filter ="JPEG Image File (*.jpg)|*.jpg|JPEG Image File (*.jpeg)|*.jpeg|Bitmaps (*.bmp)|*.bmp|Icons (*.ico)|*.ico|Enhanced Metafiles (*.emf)|*.emf|Metafiles (*.wmf)|*.wmf";

 GraphicFilter(__classid(Graphics::TBitmap));

 if(SaveDialog1->Execute()==true)
 {
  AnsiString fileName=SaveDialog1->FileName;
  //Chart1->SaveToBitmapFile(fileName);
  /*
  TImage *image=new TImage(this);
  image->Parent=this;
  image->BringToFront();
  image->Transparent=true;
  image->Left=ChartPanel->Left;
  image->Top=ChartPanel->Top;
  image->Width=ChartPanel->Width;
  image->Height=ChartPanel->Height;

  image->Picture->Bitmap->SaveToFile(fileName);

  delete image;
  */
  Application->ProcessMessages();

  SaveAsPicture(fileName);


  TForm* CurForm = CreateMessageDialog("���� ��������",mtWarning, mbYesNoCancel);
  CurForm->Width=400;
  ((TButton*)CurForm->Components[2])->Caption="������� � �������?";
  ((TButton*)CurForm->Components[2])->Width=120;
  ((TButton*)CurForm->Components[3])->Caption="������� ����?";
  ((TButton*)CurForm->Components[3])->Width=120;
  ((TButton*)CurForm->Components[3])->Left=140;
  ((TButton*)CurForm->Components[4])->Caption="�� ���������";
  ((TButton*)CurForm->Components[4])->Left=270;
  ((TButton*)CurForm->Components[4])->Width=120;

  switch(CurForm->ShowModal())
  {
   case mrYes :
   {
     //AnsiString com="/open, "+ExtractFileDir(fileName);
     AnsiString com=ExtractFileDir(fileName);
     ShellExecute(0,"open","Explorer.exe",com.c_str(),NULL,SW_SHOW);
   }
   break;
   case mrNo :
   {
    ShellExecute (Application->Handle, "open", fileName.c_str(), NULL, NULL , SW_SHOW);
   }
   break;
  } 
  delete CurForm;
 }
 SetCurrentDir(dir);
} 
//---------------------------------------------------------------------------

#include <windef.h>
//#include <stdargfx.h>
//#include <resource.h>
void TAnalyserBaseFrame::SaveAsPicture(ASS fileName)
{
 // work method first
 /*
  Graphics::TBitmap *Bitmap = new Graphics::TBitmap();
  Bitmap->Height=ChartPanel->Height;
  Bitmap->Width=ChartPanel->Width;
  BitBlt(Bitmap->Canvas->Handle,0,0,ChartPanel->Width,ChartPanel->Height,
  GetDC(Application->MainForm->Handle),ChartPanel->Left,ChartPanel->Top,SRCCOPY);
  Bitmap->SaveToFile(fileName);
  delete Bitmap;
  */
  /*
  // second (works in princip)
  //������� �����, ������� ����� ������������
 //��� ��������� �������� �����
 TCanvas* tCanvas = new TCanvas;
 //������ TBitmap ����� ����� �����
 Graphics::TBitmap*  gBitmap = new Graphics::TBitmap;
 //������� �������� ������ � ����
 TRect tRectFrom;
 TRect tRectTo;
 //�������� �����
 tRectFrom.Left=0;
 tRectFrom.Top=0;
 tRectTo.Left=0;
 tRectTo.Top=0;

 int pril=0;
 //������ ������ ������ ���� ����������
 if(pril==0)
 {
  tCanvas->Handle = GetDC(0);
  gBitmap->Width = Width;
  gBitmap->Height = Height;
  tRectFrom=BoundsRect;
  Caption=tRectFrom.Left;
  tRectTo.Right=Width;
  tRectTo.Bottom=Height;
 }
 else
 {
 //����� ���� ���������� ��� ���������
   //(���������� ������� ����
   tCanvas->Handle = GetDC(Handle);
   //������������� ������� TBitmap c��������������
   //������� ��������� ������� ����
  gBitmap->Width = ClientWidth;
  gBitmap->Height = ClientHeight;
  tRectFrom.Right=ClientWidth;
  tRectFrom.Bottom=ClientHeight;
  tRectTo.Right=ClientWidth;
  tRectTo.Bottom=ClientHeight;
 }
 gBitmap->Canvas->CopyRect(tRectTo,tCanvas,tRectFrom);
 gBitmap->SaveToFile(fileName);

 delete gBitmap;
 delete tCanvas;
 */


 // THE BEST METHOD!!!!
 // Before put follow strings in the beginning of file
 //#define _WIN32_WINNT    0x0501
//#define WINVER          0x0501
//#include <vcl.h>

 RECT rcSrc;
 HWND hSrcWnd;
 HDC hDC, hSrcDC;
 HBITMAP hBmp;
// HBITMAP tBmp;
 Graphics::TBitmap * tBmp = new Graphics:: TBitmap ;

 // tbmp:=TBitmap.Create;

 hSrcWnd=FindWindow(NULL, "SPECTROS"); // "*********" - ??? ??????? ????

 if(hSrcWnd==NULL)
  hSrcWnd=Application->MainForm->Handle;

 GetWindowRect(hSrcWnd, &rcSrc);

 hDC=GetDC(hSrcWnd);
 hSrcDC=CreateCompatibleDC(hDC);
 hBmp=CreateCompatibleBitmap(hDC, rcSrc.right - rcSrc.left, rcSrc.bottom - rcSrc.top);

 SelectObject(hSrcDC, hBmp);
 PrintWindow(hSrcWnd, hSrcDC, 0);
 BitBlt(
    hDC,
    0,
    0,
    rcSrc.right - rcSrc.left,
    rcSrc.bottom - rcSrc.top,
    hSrcDC,
    0,
    0,
    SRCCOPY);

 tBmp->Handle=hBmp;
 tBmp->SaveToFile(fileName);

 DeleteObject(hBmp);
 DeleteDC(hSrcDC);
 ReleaseDC(hSrcWnd, hDC);
 delete tBmp;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::CopyImageMenuItemClick(TObject *Sender)
{
 //Chart1->CopyToClipboardBitmap();
 Application->ProcessMessages();

  Graphics::TBitmap *Bitmap = new Graphics::TBitmap();
  Bitmap->Height=ChartPanel->Height;
  Bitmap->Width=ChartPanel->Width;
  BitBlt(Bitmap->Canvas->Handle,0,0,ChartPanel->Width,ChartPanel->Height,
  GetDC(Application->MainForm->Handle),ChartPanel->Left,ChartPanel->Top,SRCCOPY);

  Clipboard()->Assign(Bitmap);
           /*
  int DataHandle;
  HPALETTE APalette;
  unsigned short MyFormat;
  try
  {

   Bitmap->SaveToClipboardFormat(MyFormat,DataHandle,APalette);

    // save the data to the clipboard using that format and
    // the generated data
   Clipboard()->SetAsHandle(MyFormat,DataHandle);
  }
  catch (...)
  {
     ShowMessage("Failed to copy image to clipboard!");
  }
        */
 // Bitmap-> >SaveToClipboardFormat()) >SaveToFile(fileName);
  delete Bitmap;
}
//---------------------------------------------------------------------------

void __fastcall TAnalyserBaseFrame::SaveAsGridMenuItemClick(TObject *Sender)
{
 AnsiString dir=GetCurrentDir();
 ASS filter=SaveDialog1->Filter;

 SaveDialog1->InitialDir=GetCurrentUserPath("Personal");
 SaveDialog1->DefaultExt=".csv";
 SaveDialog1->Filter="���� ������ (*.csv)|*.csv";

 if(SaveDialog1->Execute()==true)
 {
  AnsiString fileName=SaveDialog1->FileName;
  SaveAsGrid(fileName);

  TForm* CurForm = CreateMessageDialog("���� ��������",mtWarning, mbOKCancel);
  CurForm->Width=280;
  ((TButton*)CurForm->Components[2])->Caption="������� � �������?";
  ((TButton*)CurForm->Components[2])->Width=120;
  ((TButton*)CurForm->Components[3])->Caption="�� ����������";
  ((TButton*)CurForm->Components[3])->Left=150;
  ((TButton*)CurForm->Components[3])->Width=120;

  switch(CurForm->ShowModal())
  {
   case mrOk :
   {
     AnsiString com=ExtractFileDir(fileName);
     //AnsiString com="/open, "+fileName;
     ShellExecute(0,"open","Explorer.exe",com.c_str(),NULL,SW_SHOW);
   }
   break;
   case mrNo :
   {
    ShellExecute (Application->Handle, "open", fileName.c_str(), NULL, NULL , SW_SHOW);
   }
   break;
  } 
  delete CurForm;
 }
}
//---------------------------------------------------------------------------

void TAnalyserBaseFrame::SaveAsGrid(ASS fileName)
{
 FILE *_fd=fopen(fileName.c_str(),"wt");

 if(_fd == NULL) return;

 fprintf(_fd,"n/n;frequency(kHz);level(dB)\n");

 for (int i=0; i<_Series[0]->Count(); i++)
 {
  fprintf(_fd, "%d;%lu;%lf\n",i,(unsigned long)(_Series[0]->XValue[i]),_Series[0]->YValue[i]);

 }
 fprintf(_fd,"\n");

 fclose(_fd);
}

//---------------------------------------------------------------------------
void __fastcall TAnalyserBaseFrame::SaveAsTextMenuItemClick(TObject *Sender)
{
 AnsiString dir=GetCurrentDir();
 ASS filter=SaveDialog1->Filter;

 SaveDialog1->InitialDir=GetCurrentUserPath("Personal");
 SaveDialog1->DefaultExt=".txt";
 SaveDialog1->Filter="��������� �������� (*.txt)|*.txt";

 if(SaveDialog1->Execute()==true)
 {
  AnsiString fileName=SaveDialog1->FileName;
  SaveAsText(fileName);

  TForm* CurForm = CreateMessageDialog("���� ��������",mtWarning, mbYesNoCancel);
  CurForm->Width=400;
  ((TButton*)CurForm->Components[2])->Caption="������� � �������?";
  ((TButton*)CurForm->Components[2])->Width=120;
  ((TButton*)CurForm->Components[3])->Caption="������� ����?";
  ((TButton*)CurForm->Components[3])->Width=120;
  ((TButton*)CurForm->Components[3])->Left=140;
  ((TButton*)CurForm->Components[4])->Caption="�� ���������";
  ((TButton*)CurForm->Components[4])->Left=270;
  ((TButton*)CurForm->Components[4])->Width=120;

  switch(CurForm->ShowModal())
  {
   case mrYes :
   {
    // AnsiString com="/open, "+fileName;
     AnsiString com=ExtractFileDir(fileName);
     ShellExecute(0,"open","Explorer.exe",com.c_str(),NULL,SW_SHOW);
   }
   break;
   case mrNo :
   {
    ShellExecute (Application->Handle, "open", fileName.c_str(), NULL, NULL , SW_SHOW);
   }
   break;
  }
  delete CurForm;
 }
}
//---------------------------------------------------------------------------

void TAnalyserBaseFrame::SaveAsText(ASS fileName)
{
 FILE *_fd=fopen(fileName.c_str(),"wt");

 if(_fd == NULL) return;

 fprintf(_fd," n/n | Freq.(kHz) |  Level(dB)\n");

 for (int i=0; i<_Series[0]->Count(); i++)
 {
  fprintf(_fd, "%4.3d |    %7lu | %6.2lf\n",i,(unsigned long)(_Series[0]->XValue[i]),_Series[0]->YValue[i]);

 }
 fprintf(_fd,"\n");

 fclose(_fd);
}

//---------------------------------------------------------------------------

void TAnalyserBaseFrame::SaveAsSA4(ASS fileName)
{
 FILE *_fd=fopen(fileName.c_str(),"at");

 if(_fd == NULL) return;

// fprintf(_fd,"frequency(kHz);level(dB)\n");
// time start freq step count
 fprintf(_fd,"%lf;%lu;%d;%d;",Now().operator double(),_lastStartFreq,_lastStep,_lastCount);

 for (int i=0; i<_lastCount; i++)
 {
//  fprintf(_fd, "%d;%lu;%lf\n",i,_Series[0]->YValue[i]);
  fprintf(_fd, "%d;",(int)(GetLevel(i)*(-1)));
 }
 fprintf(_fd,"\n");

 fclose(_fd);
}
//---------------------------------------------------------------------------

