//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("FreqPlan.res");
USEFORM("FreqPlan1.cpp", FreqForm);
USEFORM("..\..\..\Рабочий стол\WORKS\Formuls\FreqPrint1.cpp", FreqPrintForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TFreqForm), &FreqForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
