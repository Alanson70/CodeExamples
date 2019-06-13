//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("AboutFormUnit.cpp", AboutForm);
USEFORM("FreqParamFrameUnit.cpp", FreqParamFrame); /* TFrame: File Type */
USEFORM("RecordingFormUnit.cpp", RecordingForm);
USEFORM("AnalyserBaseFrameUnit.cpp", AnalyserBaseFrame); /* TFrame: File Type */
USEFORM("AnalyserMeterFrameUnit.cpp", AnalyserMeterFrame); /* TFrame: File Type */
USEFORM("ConnectFrameUnit.cpp", ConnectFrame); /* TFrame: File Type */
USEFORM("MainFormUnit.cpp", MainForm);
USEFORM("AnalyserViewerFrameUnit.cpp", AnalyserViewerFrame); /* TFrame: File Type */
USEFORM("ProfileDialogFormUnit.cpp", ProfileDialogForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Спектроанализатор";
                 Application->CreateForm(__classid(TMainForm), &MainForm);
         Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
