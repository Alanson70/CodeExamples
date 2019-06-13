//---------------------------------------------------------------------------
#ifndef DamaUnitH
#define DamaUnitH


typedef struct
{
 struct
 {
  double Begin;
  double End;
 }B[3];
}FreqPlan;

class TDama : public TComponent
{
 protected :
  FreqPlan FPS[6];
  FreqPlan FP;
  double FreqStep;
 public :
  bool ChangeFlag;
  __fastcall TDama(TComponent* Owner);
  void __fastcall SetFPBegin(int,int,double f);
  void __fastcall SetFPEnd(int,int,double f);
  double __fastcall GetFPSBegin(int,int);  
  double __fastcall GetFPSEnd(int,int);
  void __fastcall SetCurrentFP(int);
  void __fastcall SetFreqStep(double f);
};
extern PACKAGE TDama *Dama;

//---------------------------------------------------------------------------
#endif
