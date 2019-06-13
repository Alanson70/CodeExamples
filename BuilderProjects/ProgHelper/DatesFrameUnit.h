//---------------------------------------------------------------------------


#ifndef DatesFrameUnitH
#define DatesFrameUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include "HexEditFrameUnit.h"
//---------------------------------------------------------------------------
class TDatesFrame : public TFrame
{
__published:	// IDE-managed Components
        TEdit *DateTimeStringEdit;
        TEdit *WindowsEdit;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TButton *NowButton;
        TButton *ChooseDateButton;
        TButton *ChooseTimeButton;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TPopupMenu *DatesPopupMenu;
        TMenuItem *CopyMenuItem;
        TMenuItem *PasteMenuItem;
        THexEditFrame *DosHexEditFrame;
        THexEditFrame *LinuxHexEditFrame;
        TEdit *WindowsHexEdit;
        TMemo *LinuxEdit;
        TMemo *DosEdit;
        void __fastcall NowButtonClick(TObject *Sender);
        void __fastcall WindowsEditChange(TObject *Sender);
        void __fastcall DosEditChange(TObject *Sender);
        void __fastcall LinuxEditChange(TObject *Sender);
        void __fastcall ChooseTimeButtonClick(TObject *Sender);
        void __fastcall ChooseDateButtonClick(TObject *Sender);
        void __fastcall DatesMenuItemClick(TObject *Sender);
        void __fastcall DatesPopupMenuPopup(TObject *Sender);
private:	// User declarations
public:		// User declarations
 __fastcall TDatesFrame(TComponent* Owner);
 TDateTime _dt;
 void ShowDateTime();


 void __fastcall OnWinHexChange(TObject *Sender);
 void __fastcall OnDosHexChange(TObject *Sender);
 void __fastcall OnLinuxHexChange(TObject *Sender);

};
//---------------------------------------------------------------------------
extern PACKAGE TDatesFrame *DatesFrame;
//---------------------------------------------------------------------------
#endif
