//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("AzUm1.res");
USEFORM("UgolAzimut.cpp", UAForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TUAForm), &UAForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
