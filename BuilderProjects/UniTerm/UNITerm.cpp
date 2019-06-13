//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("ControlFormUnit.cpp", ControlForm);
USEFORM("MainFormUnit.cpp", MainForm);
USEFORM("TerminalFormUnit.cpp", TerminalForm);
USEFORM("AboutFormUnit.cpp", AboutForm);
USEFORM("ParamsFormUnit.cpp", ParamsForm);
USEFORM("..\Connections\ControlClientFormUnit.cpp", ControlClientForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Терминал";
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
