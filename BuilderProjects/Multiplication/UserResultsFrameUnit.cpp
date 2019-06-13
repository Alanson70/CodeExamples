//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UserResultsFrameUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TUserResultFrame *UserResultFrame;
//---------------------------------------------------------------------------
__fastcall TUserResultFrame::TUserResultFrame(TComponent* Owner)
        : TFrame(Owner)
{
}
//---------------------------------------------------------------------------
