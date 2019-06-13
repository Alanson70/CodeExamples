//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("PG1_Project.res");
USEFORM("PG1_Unit.cpp", PG1Form);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TPG1Form), &PG1Form);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
