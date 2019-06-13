//---------------------------------------------------------------------------
#ifndef ReportUnitH
#define ReportUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <quickrpt.hpp>
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TReportForm : public TForm
{
__published:	// IDE-managed Components
    TQuickRep *QuickRep1;
    TQRLabel *KALabel;
    TQRLabel *DOLLabel;
    TQRLabel *SHIRLabel;
    TQRLabel *AZLabel;
    TQRLabel *UMLabel;
    TQRDBText *QRDBText1;
    TQRDBText *QRDBText2;
    TQRDBText *QRDBText3;
    TQRDBText *QRDBText4;
    TQRDBText *QRDBText5;
    TQRDBText *QRDBText6;
    TQRDBText *QRDBText7 ;
    void __fastcall QuickRep1Preview(TObject *Sender);
    void __fastcall QuickRep1StartPage(TQuickRep *Sender);
    void __fastcall QuickRep1EndPage(TQuickRep *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TReportForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TReportForm *ReportForm;
//---------------------------------------------------------------------------
#endif
