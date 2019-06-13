//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("MainFormUnit.cpp", MainForm);
USEFORM("ColorsFrameUnit.cpp", ColorsFrame); /* TFrame: File Type */
USEFORM("DatesFrameUnit.cpp", DatesFrame); /* TFrame: File Type */
USEFORM("ChooseTimeFormUnit.cpp", ChooseTimeForm);
USEFORM("ChooseDateFormUnit.cpp", ChooseDateForm);
USEFORM("ValueEditFrameUnit.cpp", ValueEditFrame); /* TFrame: File Type */
USEFORM("BinEditFrameUnit.cpp", BinEditFrame); /* TFrame: File Type */
USEFORM("ValuesFrameUnit.cpp", ValuesFrame); /* TFrame: File Type */
USEFORM("DecEditFrameUnit.cpp", DecEditFrame); /* TFrame: File Type */
USEFORM("HexEditFrameUnit.cpp", HexEditFrame); /* TFrame: File Type */
USEFORM("AboutFormUnit.cpp", AboutForm);
USEFORM("SymbolsFrameUnit.cpp", SymbolsFrame); /* TFrame: File Type */
USEFORM("DateCalcFrameUnit.cpp", DateCalcFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Помошник программиста";
                 Application->CreateForm(__classid(TMainForm), &MainForm);
         Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
