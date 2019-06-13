//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("DBtoValue.res");
USEFORM("DBtoValue1.cpp", dbForm);
USELIB("..\..\..\..\Program Files\BORLAND\CBuilder3\Lib\dxextra.lib");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TdbForm), &dbForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
