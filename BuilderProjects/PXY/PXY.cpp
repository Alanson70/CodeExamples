//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USEFORM("PXYFormUnit.cpp", PXYForm);
USEFORM("SensUnit.cpp", SensForm);
USEFORM("AboutFormUnit.cpp", AboutForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->Title = "Шаг наведения";
                 Application->CreateForm(__classid(TPXYForm), &PXYForm);
         Application->CreateForm(__classid(TAboutForm), &AboutForm);
         Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
