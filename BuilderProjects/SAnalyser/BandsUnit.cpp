//---------------------------------------------------------------------------
                                                                                          

#pragma hdrstop

#include "BandsUnit.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


double AssFactor=1.2;
double OcpFactor=1.4;

unsigned long AllocStep=1;

//unsigned long FreqRxCenter=3890;
//unsigned long FreqTxCenter=6215;



//unsigned long MIN_FREQ=50000;
//unsigned long MAX_FREQ=90000;

//----------------------------------------------------------
void BAND_SETTS::Calculate()
{
 unsigned long value=InfRate;
 unsigned long band=BandHand;

 if(Overhead==true)  value=value*(OverheadFactor/(OverheadDivisor*1.0));
 if(RS==true)        value=value*(RSFactor/(RSDivisor*1.0));
 if(Coding)   value=value/(CodingFactor/(CodingDivisor*1.0));
 value=value/(Modulation+1);

 BandCalc=value;

 if(BandHandSet==false)
  band=BandCalc;

 BandOccupied=band*OcpFactor;
 BandAssigned=band*AssFactor;


 {
  double ba=(BandAssigned*1.0)/AllocStep;
  long b=(long)(ba);
  if(b<ba) b++;
  if((b&0x1)==0) b++;
  BandAssigned=b*AllocStep;
  BandOccupied=MAX(BandOccupied,BandAssigned);

  LeftFreq=Freq-BandAssigned/2;
  RightFreq=Freq+BandAssigned/2;
 }
}

//----------------------------------------------------------
BAND_SETTS::BAND_SETTS()
{
 InfRate=128000;
 Freq=70000000;
 Overhead=true;
 OverheadFactor=16;
 OverheadDivisor=15;
 RS=false;
 RSFactor=128;
 RSDivisor=126;

 Coding=true;
 CodingFactor=1;
 CodingDivisor=2;

 Modulation=1;

 
 LeftFreq=70000000;
 RightFreq=80000000;
 BandHand=128000;
 BandCalc=128000;
 BandHandSet=false;

 Name="";
}

//----------------------------------------------------------
void BAND_SETTS::Assign(BAND_SETTS &s)
{
 InfRate=s.InfRate;

 Overhead=s.Overhead;
 OverheadFactor=s.OverheadFactor;
 OverheadDivisor=s.OverheadDivisor;

 RS=s.RS;
 RSFactor=s.RSFactor;
 RSDivisor=s.RSDivisor;

 Coding=s.Coding;
 CodingFactor=s.CodingFactor;
 CodingDivisor=s.CodingDivisor;

 Modulation=s.Modulation;

 Freq=s.Freq;
 BandOccupied=s.BandOccupied;
 BandAssigned=s.BandAssigned;

 LeftFreq=s.LeftFreq;
 RightFreq=s.RightFreq;

 BandHand=s.BandHand;
 BandCalc=s.BandCalc;
 BandHandSet=s.BandHandSet;

 Name=s.Name;
}

//----------------------------------------------------------










//TBAND *_firstBand=NULL;

__fastcall TBAND::TBAND(TComponent* owner) : TComponent(owner)
{
 /*if(_firstBand==NULL) _firstBand=this;
 else
  _firstBand->NextBand(this);
   */
 _next=NULL;
 OnInserted=NULL;
 OnChanged=NULL;
 
}

//---------------------------------------------------------------------------
TBAND *TBAND::NextBand()
{
 return _next;
}

//---------------------------------------------------------------------------
void TBAND::InsertToList(TBAND *band)
{
 if(_next==NULL) _next=band;
 else _next->InsertToList(band);
}
 /*
 if(_firstBand==NULL)
 {
  _firstBand=this;
 }
 else
 */


/*
  sort

 if(this->LeftFreq()<_firstBand->LeftFreq())   // insert
 {
  this->_next=_firstBand;
  _firstBand=this;
 }
 else
  _firstBand->NextBand(this);

// RecountTitleLevel();
 TBAND *band=_firstBand;

 for(;;)
 {
  if(band==NULL) break;
  band=band->_next;
 }
 if(OnInserted) OnInserted(this);
}
*/
//---------------------------------------------------------------------------
void TBAND::NextBand(TBAND *band)
{
/*
 if(!_next) _next=band;
 else
 {
  if(band->LeftFreq()<_next->LeftFreq())
  {
   band->_next=this->_next;
   this->_next=band;
  }
  else
   _next->NextBand(band);
 }
 */
}
//---------------------------------------------------------------------------
void TBAND::RemoveFromList(TBAND *band)
{
 if(_next==NULL) return;
 if(_next==band)
  _next=band->NextBand();
 else
  _next->RemoveFromList(band);
 /*
 TBAND *band;
 if(_firstBand==this) _firstBand=this->_next;
 else
 {
  band=_firstBand;
  for(;;)
  {
   if(band==NULL) break;

   if(band->_next==this)
   {
    band->_next=this->_next;
    this->_next=NULL;
    break;
   }
   band=band->_next;
  }
 }
 */


 //if(OnInserted) OnInserted(this);
}
//---------------------------------------------------------------------------
void TBAND::Sort()
{
 TBAND *newList=NULL;
 TBAND *band;
 TBAND *leftBand;

 for(;;)
 {
  leftBand=_next;

  if(_next==NULL) break;
  band=leftBand->_next;

  for(;;)
  {
   if(band==NULL) break;

   if(band->LeftFreq()<_next->LeftFreq())
    leftBand=band;

   band=band->_next;
  }
  if(leftBand)
  {
   this->RemoveFromList(leftBand);
   this->_next=leftBand;
   if(newList) newList->InsertToList(leftBand);
   else newList=leftBand;
  }
 }
 _next=newList;
} 
//---------------------------------------------------------------------------
void TBAND::Realign(TBAND *band)
{
 TBAND *curr=this;

 if(band==NULL) return;

 this->RemoveFromList(band);

 for(;;)
 {
  if(curr->_next==NULL) break;

  if(band->LeftFreq()<curr->_next->LeftFreq())
  {
   band->_next=curr->_next;
   break;
  }
  curr=curr->NextBand();
 }
 curr->_next=band;
}
//---------------------------------------------------------------------------
void TBAND::Set(BAND_SETTS &s)
{
 _setts.Assign(s);

 ((TBAND *)(this->Owner))->Realign(this);

 if(OnChanged) OnChanged(this);
}
//---------------------------------------------------------------------------
void TBAND::Get(BAND_SETTS &s)
{
 s.Assign(_setts);
}
//---------------------------------------------------------------------------
void TBAND::AssignBand(TBAND *band)
{
 _setts.Assign(band->_setts);
 this->OnInserted=band->OnInserted;
 this->OnChanged=band->OnChanged;
}
//---------------------------------------------------------------------------
unsigned long TBAND::CarrierFreq()
{
 return _setts.Freq;
}

unsigned long TBAND::LeftFreq()
{
 return _setts.LeftFreq;
}

unsigned long TBAND::RightFreq()
{
 return _setts.RightFreq;
}

unsigned long TBAND::OccupiedBand()
{
 return _setts.BandOccupied;
}

unsigned long TBAND::AssignedBand()
{
 return _setts.BandAssigned;
}

AnsiString TBAND::BandName()
{
 return _setts.Name;
}


//---------------------------------------------------------------------------
bool TBAND::BandsSave(ASS fileName)
{
 TIniFile *iniFile;
 char Section[10];

 try
 {
  if(DirectoryExists(ExtractFilePath(fileName))==false)
   fileName="DefaultFreqPlan.cfg";
  iniFile=new TIniFile(fileName);

  int count=0;

  BAND_SETTS s;
  ASS section="Common";
  TBAND *band=this;


  iniFile->WriteFloat(section,"OcpFactor",OcpFactor);
  iniFile->WriteFloat(section,"AssFactor",AssFactor);
  iniFile->WriteInteger(section,"AllocStep",AllocStep);  // transponder

  for(int i=0;;i++)
  {      
   band=band->NextBand();
   if(band==NULL) break;
   band->Get(s);

   section=(i+1);
   iniFile->WriteInteger(section,"CarrierFreq",s.Freq);
   iniFile->WriteInteger(section,"OccupiedBand",s.BandOccupied);
   iniFile->WriteInteger(section,"AssignedBand",s.BandAssigned);
   iniFile->WriteInteger(section,"LeftFreq",s.LeftFreq);
   iniFile->WriteInteger(section,"RightFreq",s.RightFreq);

   iniFile->WriteInteger(section,"InfRate",s.InfRate);
   iniFile->WriteInteger(section,"BandCalc",s.BandCalc);
   iniFile->WriteInteger(section,"BandHand",s.BandHand);
   iniFile->WriteBool(section,"BandHandSet",s.BandHandSet);

   iniFile->WriteInteger(section,"Modulation",s.Modulation);

   iniFile->WriteBool(section,"Coding",s.Coding);
   iniFile->WriteInteger(section,"CodingDivisor",s.CodingDivisor);
   iniFile->WriteInteger(section,"CodingFactor",s.CodingFactor);

   iniFile->WriteBool(section,"RS",s.RS);
   iniFile->WriteInteger(section,"RSDivisor",s.RSDivisor);
   iniFile->WriteInteger(section,"RSFactor",s.RSFactor);

   iniFile->WriteBool(section,"Overhead",s.Overhead);
   iniFile->WriteInteger(section,"OverheadDivisor",s.OverheadDivisor);
   iniFile->WriteInteger(section,"OverheadFactor",s.OverheadFactor);
   iniFile->WriteString(section,"BandName",s.Name);

   count++;
  }
  iniFile->WriteInteger("Common","Count",count); 
  //iniFile->WriteBool("Common","NoCross",EditForm->NoCrossCheckBox->Checked);
  delete iniFile;
 // _wasChanges=false;
  return true;
 }
 catch(...)
 {
  delete iniFile;
  return false;
 }
}

//---------------------------------------------------------------------------
bool TBAND::BandsLoad(ASS fileName)
{
 ASS path=ExtractFileDir(fileName);
 if(path.Length()<1)
  path=GetCurrentDir();
 fileName=path+ASS("\\")+ExtractFileName(fileName);
 if(FileExists(fileName)==true)
 {
 }
 else
  fileName="DefaultFreqPlan.cfg";

 TIniFile *iniFile;


 char Section[10];

 iniFile=new TIniFile(fileName);

 int count=iniFile->ReadInteger("Common","Count",0);
 BAND_SETTS s;
 TBAND *band;
 ASS section="Common";

 OcpFactor=iniFile->ReadFloat(section,"OcpFactor",1.2);
 AssFactor=iniFile->ReadFloat(section,"AssFactor",1.4);
 AllocStep=iniFile->ReadInteger(section,"AllocStep",AllocStep);

 for(int i=0;i<count;i++)
 {
  section=(i+1);

  s.Freq=iniFile->ReadInteger(section,"CarrierFreq",50000000);
  s.BandOccupied=iniFile->ReadInteger(section,"OccupiedBand",0);
  s.BandAssigned=iniFile->ReadInteger(section,"AssignedBand",0);
  s.LeftFreq=iniFile->ReadInteger(section,"LeftFreq",0);
  s.RightFreq=iniFile->ReadInteger(section,"RightFreq",0);

  s.InfRate=iniFile->ReadInteger(section,"InfRate",0);
  s.BandCalc=iniFile->ReadInteger(section,"BandCalc",0); 
  s.BandHand=iniFile->ReadInteger(section,"BandHand",0);
  s.BandHandSet=iniFile->ReadBool(section,"BandHandSet",0);
  s.Modulation=iniFile->ReadInteger(section,"Modulation",0);

  s.Coding=iniFile->ReadBool(section,"Coding",0);
  s.CodingDivisor=iniFile->ReadInteger(section,"CodingDivisor",0);
  s.CodingFactor=iniFile->ReadInteger(section,"CodingFactor",0);

  s.RS=iniFile->ReadBool(section,"RS",0);
  s.RSDivisor=iniFile->ReadInteger(section,"RSDivisor",0);
  s.RSFactor=iniFile->ReadInteger(section,"RSFactor",0);

  s.Overhead=iniFile->ReadBool(section,"Overhead",0);
  s.OverheadDivisor=iniFile->ReadInteger(section,"OverheadDivisor",0);
  s.OverheadFactor=iniFile->ReadInteger(section,"OverheadFactor",0);
  s.Name=iniFile->ReadString(section,"BandName","");

  s.Calculate();

  band=this->CreateBand(&s);
//  band->Set(s);
 }

 delete iniFile;

// Sort();

 return true;
}
 
//---------------------------------------------------------------------------
TBAND *TBAND::CreateBand(BAND_SETTS *s)
{
 TBAND *band;
 band=new TBAND(this);
// band->OnInserted=OnChangedBand;
// band->OnChanged=OnChangedBand;
 if(s!=NULL)  band->Set(*s);
 //this->InsertToList(band);
 //this->Realign(band);
 return band;
}  
//---------------------------------------------------------------------------
void TBAND::RemoveBand(TBAND *band)
{
 this->RemoveFromList(band);
 //if(_firstBand==band) _firstBand=NULL;
 delete band;
}
//---------------------------------------------------------------------------



