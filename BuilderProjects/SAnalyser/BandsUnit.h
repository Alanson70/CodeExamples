//---------------------------------------------------------------------------

#ifndef BandsUnitH
#define BandsUnitH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp> 
#include "Functions.h"

#define FREQ_HZ_MAX 8000000000L
#define FREQ_HZ_MIN 50000000L  
#define BAND_HZ_MAX 64000000L
#define BAND_HZ_MIN 1000L

struct BAND_SETTS
{
 unsigned long Freq;
 unsigned long InfRate;

 bool Overhead;
 unsigned int OverheadFactor;
 unsigned int OverheadDivisor;

 bool RS;
 unsigned int RSFactor;
 unsigned int RSDivisor;

 bool Coding;
 unsigned int CodingFactor;
 unsigned int CodingDivisor;

 unsigned int Modulation;

 unsigned long BandCalc;
 unsigned long BandHand;

 bool BandHandSet;

 unsigned long BandOccupied;
 unsigned long BandAssigned;

 unsigned long LeftFreq;
 unsigned long RightFreq;

 AnsiString Name;

 BAND_SETTS();
 void Assign(BAND_SETTS &s);
 void Calculate();

 
};

extern double AssFactor;
extern double OcpFactor;

extern unsigned long AllocStep;

//-------------------------------------
#include <Series.hpp>

//class TBAND;

//static TBAND _firstBand;

class TBAND : public TComponent
{
 public :
  __fastcall TBAND(TComponent* owner);

  TBAND *NextBand();
  void NextBand(TBAND *);
  void InsertToList(TBAND *band);
  void RemoveFromList(TBAND *band);
  void Realign(TBAND *band);
  void Sort();

  void Set(BAND_SETTS &s);
  void Get(BAND_SETTS &s);
  BAND_SETTS &GetSetts()     { return _setts; }

  unsigned long CarrierFreq();
  unsigned long LeftFreq();
  unsigned long RightFreq();
  unsigned long OccupiedBand();
  unsigned long AssignedBand();

  AnsiString BandName();

  TLineSeries *_line;
  void AssignBand(TBAND *band);
  Callback OnInserted;
  Callback OnChanged;
 protected :
  TBAND *_next;
  BAND_SETTS _setts;
 public :
  bool BandsLoad(ASS fileName);
  bool BandsSave(ASS fileName);
  TBAND *CreateBand(BAND_SETTS *s);
  void RemoveBand(TBAND *band);

};

//extern TBAND *_firstBand;



//---------------------------------------------------------------------------
#endif
