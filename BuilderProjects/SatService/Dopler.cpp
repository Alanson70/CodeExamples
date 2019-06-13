//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("Dopler.res");
USEFORM("DoplerUnit.cpp", DoplerForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TDoplerForm), &DoplerForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
