//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("PG_Project.res");
USEFORM("PG_MainUnit.cpp", PGForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TPGForm), &PGForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
