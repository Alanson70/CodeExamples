//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USEFORM("PXY.cpp", PXYForm);
USEFORM("SensUnit.cpp", SensForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TPXYForm), &PXYForm);
                 Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
