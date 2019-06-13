//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("fromZStoKA.res");
USEFORM("d1.cpp", tosputnikForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TtosputnikForm), &tosputnikForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
