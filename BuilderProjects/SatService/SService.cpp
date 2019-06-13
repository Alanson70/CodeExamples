//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("SService.res");
USEFORM("ServiceMain.cpp", ServiceForm);
USEFORM("d1.cpp", tosputnikForm);
USEUNIT("DBtoValue.cpp");
USEFORM("DBtoValue1.cpp", dbForm);
USEUNIT("FreqPlan.cpp");
USEFORM("FreqPlan1.cpp", FreqForm);
USEFORM("FreqPrint1.cpp", FreqPrintForm);
USEUNIT("fromZStoKA.cpp");
USEFORM("UgolAzimut.cpp", UAForm);
USEUNIT("AzUm1.cpp");
USEFORM("QR2Unit.cpp", RForm2);
USEFORM("AUGridUnit.cpp", AUGridForm);
USEFORM("CloseUnit.cpp", CloseForm);
USEFORM("DoplerUnit.cpp", DoplerForm);
USEFORM("PXY.cpp", PXYForm);
USEFORM("SensUnit.cpp", SensForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->Title = "SatServ";
        Application->CreateForm(__classid(TServiceForm), &ServiceForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
