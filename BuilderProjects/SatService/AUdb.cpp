//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("AUdb.res");
USEFORM("..\..\..\Рабочий стол\WORKS\Formuls\UgolAzimut.cpp", UAForm);
USEFORM("..\..\..\Рабочий стол\WORKS\Formuls\AUGridUnit.cpp", AUGridForm);
USEFORM("..\..\..\Рабочий стол\WORKS\Formuls\QR2Unit.cpp", RForm2);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TAUGridForm), &AUGridForm);
        Application->CreateForm(__classid(TUAForm), &UAForm);
        Application->CreateForm(__classid(TRForm2), &RForm2);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
