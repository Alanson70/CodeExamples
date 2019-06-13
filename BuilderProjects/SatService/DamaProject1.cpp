//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USEFORM("DamaMain1.cpp", FreqForm);
USEFORM("FPEditUnit.cpp", FPForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TFreqForm), &FreqForm);
                 Application->CreateForm(__classid(TFPForm), &FPForm);
                 Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
