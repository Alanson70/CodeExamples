//---------------------------------------------------------------------------


#pragma hdrstop

#include "Functions.h"
#include <string.h>
#include <mbstring.h>
#include <stdlib.h> 
#include <stdio.h>
#include <time.h>
#include <stdio.h>



#define ASS AnsiString





//------------------------------------------------------------
char *StrSearch(char *sourceStr,char *fStr,bool wholeWord)
{
 //const char *ds=" /\?.,<>@!~`$%^&*()_+|{}[]\"=-";
 int j=0;
 int fCount=Strlen(fStr);
 bool isStr=false;
 int first=0;

// bool firstSym=false;
 //char lastSym=0;

 for(int i=0;i<(Strlen(sourceStr)-fCount);i++)
 {
  isStr=0;
  //firstSym=true;

  if(sourceStr[i]==fStr[0])
  {
   first=i;
   for(int j=0;j<fCount;j++,i++)
   {
    if(sourceStr[i]==fStr[j])
    {
     if(j==(fCount-1))
     {
      isStr=true;
      break;// return sourceStr+i;
     }
    }
    else break;
   }

   if(isStr==true)
   {
    if(wholeWord==true)
    {
     // firstSym
     isStr=false;
     if(first>0)
     {
      //for(int d=0;d<strlen(ds);d++) if(ds[d]==sourceStr[i-1]) { firstSym=true;break; }
      wchar_t wc;
      //int Key=sourceStr[first-1];
      MultiByteToWideChar(CP_ACP,0,sourceStr+(first-1),1,&wc,1);


      if((iswalpha(wc)==false) & (isdigit(wc)==false)) isStr=true;
     }
     else
      isStr=true;

      // last Sym
     if(isStr==true)
     {    
      isStr=false;
      if(sourceStr[first+fCount]!=0)
      {
       //Key=sourceStr[first+fCount1];
       wchar_t wc;
       MultiByteToWideChar(CP_ACP,0,sourceStr+(first+fCount),1,&wc,1);

       if((iswalpha(wc)==false) & (isdigit(wc)==false)) isStr=true;
      }
      else
       isStr=true;
     }
    }

    if(isStr==true) return sourceStr+first;

   }

  }
 }
 return NULL;
}
//---------------------------------------------------------------------------
void ValuesFromString(char *eventText,int &day,int &mon,int &year)
{
 DateFromString(eventText,day,mon,year);
}

void DateFromString(char *eventText,int &day,int &mon,int &year)
{
 unsigned i;
 for(i=0;i<strlen(eventText);i++) if(isdigit(eventText[i])) { day=atoi(eventText+i);break; }
 for(;i<strlen(eventText);i++) if(!isdigit(eventText[i])) { break; }
 for(;i<strlen(eventText);i++) if(isdigit(eventText[i])) { mon=atoi(eventText+i);break; }
 for(;i<strlen(eventText);i++) if(!isdigit(eventText[i])) { break; }
 for(;i<strlen(eventText);i++) if(isdigit(eventText[i])) { year=atoi(eventText+i);break; }
}
//---------------------------------------------------------------------------
void ValuesFromString(char *eventText,int &hour,int &min)
{
 TimeFromString(eventText,hour,min);
}

void TimeFromString(char *eventText,int &hour,int &min)
{
 unsigned i;
 for(i=0;i<strlen(eventText);i++) if(isdigit(eventText[i])) { hour=atoi(eventText+i);break; }
 for(;i<strlen(eventText);i++) if(!isdigit(eventText[i])) { break; }
 for(;i<strlen(eventText);i++) if(isdigit(eventText[i])) { min=atoi(eventText+i);break; }
}

//---------------------------------------------------------------------------
void DateTimeFromString(char *eventText,int &day,int &mon,int &year,int &hour,int &min,int &sec)
{
 unsigned i;
 for(i=0;i<strlen(eventText);i++) if(isdigit(eventText[i])) break;
 day=atoi(eventText+i);
 for(;i<strlen(eventText);i++) if(!isdigit(eventText[i])) break;
 for(;i<strlen(eventText);i++) if(isdigit(eventText[i]))  break;
 mon=atoi(eventText+i);                                     
 for(;i<strlen(eventText);i++) if(!isdigit(eventText[i])) break;
 for(;i<strlen(eventText);i++) if(isdigit(eventText[i]))  break;
 year=atoi(eventText+i);                                      
 for(;i<strlen(eventText);i++) if(!isdigit(eventText[i])) break;
 for(;i<strlen(eventText);i++) if(isdigit(eventText[i]))  break;
 hour=atoi(eventText+i);                                      
 for(;i<strlen(eventText);i++) if(!isdigit(eventText[i])) break;
 for(;i<strlen(eventText);i++) if(isdigit(eventText[i]))  break;
 min=atoi(eventText+i);                                     
 for(;i<strlen(eventText);i++) if(!isdigit(eventText[i])) break;
 for(;i<strlen(eventText);i++) if(isdigit(eventText[i])) break;
 sec=atoi(eventText+i);
}

//-----------------------------------------------------------------------
int SplitCommand(char *buffer,char **argv,int argcMax)
{
 return SplitCommand(buffer,strlen(buffer)+1,argv,argcMax);
}
//-----------------------------------------------------------------------
/*
int SplitCommand(char *buffer,int count,char **argv,int argcMax)
{ 
 unsigned char b;
 int argc=0;
 int j;
 int bracket=0;
 
 for(int i=0;i<count;i++)
 {   
  b=buffer[i];  if((b<0x20)&&(b!=0x0A)) buffer[i]=0; 
 
  if((buffer[i]!='\n')&&(buffer[i]!=' ')&&(buffer[i]!=0)) // it's symbol
  {
   j=i;
   argv[argc]=buffer+j;
   argc++; 
   if(argc==argcMax) break;

   if(buffer[i]==commbracketOpen) { bracket=1;j++; }

   for(;i<count;i++)
   {
    if(argc==argcMax) break;    
    if((buffer[i]=='\n')||(buffer[i]==' ')||(buffer[i]==0)) // it's end of word
    {     
     if((bracket==0)||(buffer[i-1]==commbracketClose))
     {
      buffer[i]=0;
      if(bracket) buffer[i-1]=0;
      bracket=0;
      break;
     }
    }
   }
  }
 }
 for(int k=argc;k<argcMax;k++) argv[k]=NULL;

 return argc;
}
*/

//-----------------------------------------------------------------------
int SplitCommand(char *buffer,int count,char **argv,int argcMax)
{ 
 unsigned char b;
 int argc=0;
 int j;
 int bracket=0;
 
 for(int i=0;i<count;i++)
 {   
  b=buffer[i];  if((b<0x20)&&(b!=0x0A)) buffer[i]=0; 

  if((buffer[i]!='\n')&&(buffer[i]!=' ')&&(buffer[i]!='\\')&&(buffer[i]!=0)) // it's symbol
  {
   j=i;

   if(buffer[i]==commbracketOpen) { bracket=1;j++; }

   argv[argc]=buffer+j;
   argc++; 
   if(argc==argcMax) break;
   
   for(;i<(count+1);i++)
   {
    if(argc==argcMax) break;    
    if((buffer[i]=='\n')||(buffer[i]==' ')||(buffer[i]=='\\')||(buffer[i]==0)) // it's end of word
    {     
     if((bracket==0)||(buffer[i-1]==commbracketClose))     
     {
      buffer[i]=0;
      if(bracket) buffer[i-1]=0;
      bracket=0;
      break;
     } 
    }
   }
  }
 }
 for(int k=argc;k<argcMax;k++) argv[k]=NULL;
 
 return argc;
}
//-----------------------------------------------------------------------
int SplitPath(char *buffer,char **argv,int argcMax)
{ 
 unsigned char b;
 int argc=0;
 int j;
 int bracket=0;
 int count=Strlen(buffer);

 for(int i=0;i<count;i++)
 {
  b=buffer[i];

  if((b<0x20)&&(b!=0x0A)) buffer[i]=0;

  if((buffer[i]!='\n')&&(buffer[i]!=' ')&&(buffer[i]!='\\')&&(buffer[i]!=0)) // it's symbol
  {
   j=i;

   if(buffer[i]==commbracketOpen) { bracket=1;j++; }

   argv[argc]=buffer+j;
   argc++;
   if(argc==argcMax) break;

   for(;i<(count+1);i++)
   {
    if(argc==argcMax) break;
    if((buffer[i]=='\n')||(buffer[i]=='\\')||(buffer[i]==0)) // it's end of word
    {
     if((bracket==0)||(buffer[i-1]==commbracketClose))
     {
      buffer[i]=0;
      if(bracket) buffer[i-1]=0;
      bracket=0;
      break;
     }
    }
   }
  }
 }
 for(int k=argc;k<argcMax;k++) argv[k]=NULL;

 return argc;
}

//-----------------------------------------------------------------------
int SplitBuffer(char *buffer,char **argv,int argcMax,char *delimeters)
{
 return SplitBuffer(buffer,strlen(buffer)+1,argv,argcMax,delimeters);
}
//-----------------------------------------------------------------------
int SplitBuffer(char *buffer,unsigned int count,char **argv,int argcMax,char *delimeters)
{
 unsigned char b;
 int argc=0;
 int j;
 int bracket=0;

 for(int i=0;i<count;i++)
 {
  b=buffer[i];  if((b<0x20)&&(b!=0x0A)) buffer[i]=0;

  bool isSym=true;
  for(int c=0;c<=Strlen(delimeters);c++)
   if(buffer[i]==delimeters[c])
   {
    isSym=false;
    break;
   }
  //if((buffer[i]!='\n')&&(buffer[i]!=' ')&&(buffer[i]!=delim)&&(buffer[i]!=0)) // it's symbol
  if(isSym==true)
  {
   j=i;

   if(buffer[i]==commbracketOpen) { bracket=1;j++; }

   argv[argc]=buffer+j;
   argc++; 
   if(argc==argcMax) break;
   
   for(;i<(count+1);i++)
   {
    if(argc==argcMax) break;

    for(int c=0;c<=Strlen(delimeters);c++)
    if(buffer[i]==delimeters[c])
    {
     isSym=false;
     break;
    }

   // if((buffer[i]=='\n')||(buffer[i]==' ')||(buffer[i]=='\\')||(buffer[i]==0)) // it's end of word
    if(isSym==false)
    {     
     if((bracket==0)||(buffer[i-1]==commbracketClose))     
     {
      buffer[i]=0;
      if(bracket) buffer[i-1]=0;
      bracket=0;
      break;
     } 
    }
   }
  }
 }
 for(int k=argc;k<argcMax;k++) argv[k]=NULL;
 
 return argc;
}
//-----------------------------------------------------------------------
ASS MergePath(ASS sPath,ASS addPath)
{
 ASS newPath;

 if(sPath.Length()<1) return addPath;
 if(addPath.Length()<1) return sPath;
 if(addPath.operator [](1)=='\\')
  newPath=sPath+addPath;
 else
 if(sPath.operator [](sPath.Length())=='\\')
  newPath=sPath+addPath;
 else
  newPath=sPath+ASS("\\")+addPath;
 return newPath;
}

//-----------------------------------------------------------------------
ASS MergePath(ASS sPath,ASS addPath,ASS addPath1)
{
 ASS newPath=MergePath(sPath,addPath);
 return MergePath(newPath,addPath1);
}
//-----------------------------------------------------------------------

//char *Strupr(char *s) { if(s) for(unsigned int i=0;i<strlen(s);i++) s[i]=toupper(s[i]);return s; }
//char *Strlwr(char *s) { if(s) for(unsigned int i=0;i<strlen(s);i++) s[i]=tolower(s[i]);return s; }
//---------------------------------------------------------------------------
int  Strlen(char *s) { if(s) return strlen(s);return 0; }
//---------------------------------------------------------------------------
int  Strncpy(char *dest,char *src,int len)
{
 if(!dest) return 0;
 if(!src)  { dest[0]=0;return 0; }
 if(len<0) { dest[0]=0;return 0; }
 for(int i=0;i<len;i++)
 {
  if(src[i]==0) { dest[i]=0;return i; }
  dest[i]=src[i];
 }
 dest[len]=0;
 return len;
}
/*
int  Strnbackcat(char *dest,char *src,int len)
{
 int pos=Strlen(dest);
 for(int i=0;i<Strlen(src);i++)
 dest
}

int Strback(char *str)
{
 char c;
 int len=Strlen(str);
 int n=len-1;
 
 for(int i=0;i<len;i++,n--)
 {
  c=str[n];
  str[n]=str[0];
  str[0]=c;  
 }
}
*/ 
//---------------------------------------------------------------------------
int Strcat(char *str1,char *str2)
{
 if(!str1) return 0;
 if(!str2) return Strlen(str1);
 return Strlen(strcat(str1,str2));
}
//---------------------------------------------------------------------------
int Strncat(char *str1,char *str2,int n)
{
 if(!str1) return 0;
 if(!str2) return Strlen(str1);
 return Strlen(strncat(str1,str2,n));
}

//---------------------------------------------------------------------------
int IntFromDouble(double v)
{ 
 return (int)v;
}

//---------------------------------------------------------------------------
int StringFromStruct(char *string,int stringSize,char *structure)
{
 for(int i=0,j=0;j<stringSize;i++,j+=2) sprintf(string+j,"%2.2X",(unsigned char)structure[i]);
 return strlen(string);
}

//---------------------------------------------------------------------------
int StringToStruct(char *string,char *structure,int structSize)
{
 int D,i,j;
 for(i=0,j=0;i<structSize;i++,j+=2) { sscanf(string+j,"%2X",&D);structure[i]=D; }
 return i;
}

//---------------------------------------------------------------------------
int Memcpy(char *dest,char *src,int count)
{
 int i;
 if(count<=0)   return 0;
 if(dest==NULL) return 0;
 if(src==NULL)  return 0;
 for(i=0;i<count;i++) dest[i]=src[i];
 return count;
}

//---------------------------------------------------------------------------
char TimeAsciiBuffer[25];

char *TimeToAscii(long t,char *buffer)
{
 struct tm *lt;

 if(t==0) t=time(NULL);
 lt=localtime(&t);

 char *buf=TimeAsciiBuffer;

 if(buffer!=NULL) buf=buffer;

 if(lt==0) sprintf(buf,"N/A");
 else
 {
  sprintf(buf,"%2.2d.%2.2d.%4.4d-%2.2d:%2.2d:%2.2d",lt->tm_mday,
                                                      lt->tm_mon+1,
						      lt->tm_year+1900,
						      lt->tm_hour,
						      lt->tm_min,
						      lt->tm_sec);
 }
 return buf;
}

double TimeFromAscii(char *buffer)
{
 double dt=0;
 if(buffer==NULL) return 0.0;
 if(strlen(buffer)<19) return 0.0;
                                /*
 time_t t;
 struct tm lt;
 if((buffer+0)!=NULL)  lt.tm_mday=atoi(buffer+0);
 if((buffer+3)!=NULL)  lt.tm_mon=atoi(buffer+3)-1;
 if((buffer+6)!=NULL)  lt.tm_year=atoi(buffer+6)-1900;
 if((buffer+11)!=NULL) lt.tm_hour=atoi(buffer+11);
 if((buffer+14)!=NULL) lt.tm_min=atoi(buffer+14);
 if((buffer+17)!=NULL) lt.tm_sec=atoi(buffer+17);

 t=mktime(&lt);
 */

 dt=TDateTime(atoi(buffer+6),atoi(buffer+3),atoi(buffer+0))+TDateTime(atoi(buffer+11),atoi(buffer+14),atoi(buffer+17),0);
 return dt;
}
//-----------------------------------------------------
unsigned long DateTimeFromAscii(char *buffer,int yearFrom)
{
 time_t t;
// struct tm lt;
 int day=0;
 int mon=0;
 int year=0;
 int hour=0;
 int min=0;
 int sec=0;

 DateTimeFromString(buffer,day,mon,year,hour,min,sec);

 if(year<yearFrom) return 0L;

 long secCurr=(double)TDateTime(year,mon,day);
 long sec1970=(double)TDateTime(yearFrom,1,1); // days from 1970 //12/30/1899

 unsigned long dt=secCurr-sec1970;

 dt=dt*24*3600+sec+min*60+hour*3600;

 //t=dt;

// t=mktime(&lt);
 //if(t==-1) t=time(NULL);
 return dt;
}
//---------------------------------------------------------------------------




#pragma package(smart_init)
