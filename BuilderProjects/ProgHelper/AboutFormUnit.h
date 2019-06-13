//----------------------------------------------------------------------------
#ifndef AboutFormUnitH
#define AboutFormUnitH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
//----------------------------------------------------------------------------
class TAboutForm : public TForm
{
__published:
	TPanel *Panel1;
	TImage *ProgramIcon;
	TButton *OKButton;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
private:
public:
	virtual __fastcall TAboutForm(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TAboutForm *AboutForm;
//----------------------------------------------------------------------------
#endif    
