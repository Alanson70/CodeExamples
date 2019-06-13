//---------------------------------------------------------------------------

#ifndef FunctionsH
#define FunctionsH


#include <stdio.h>
#include <stdlib.h>                       
#include <Classes.hpp>	// Pascal unit 
#include "Inifiles.hpp"

#define Closure(a) a 
typedef void __fastcall (__closure *Callback)(TObject *Sender);

//--------------------------------------------------------------

char *StrSearch(char *sourceStr,char *searchStr,bool wholeWord);

void DateFromString(char *eventText,int &day,int &mon,int &year);
void TimeFromString(char *eventText,int &hour,int &min);
void ValuesFromString(char *eventText,int &day,int &mon,int &year);
void ValuesFromString(char *eventText,int &hour,int &min);
void DateTimeFromString(char *eventText,int &day,int &mon,int &year,int &hour,int &min,int &sec);

//#define MAX(a,b) (a>=b?a:b)
//#define MIN(a,b) (b>=a?a:b)
#define ASS AnsiString
//-----------------------------------------------------------------------
#define MAX(value1,value2)  ((value1>value2)?value1:value2)
#define MIN(value1,value2)  ((value1<value2)?value1:value2)
#define EQUAL(value1,value2)  ((value1==value2)?value1:value2)


#define max(value1,value2)    ((value1>value2)?value1:value2)
#define min(value1,value2)    ((value1<value2)?value1:value2)
#define equal(value1,value2)  ((value1==value2)?value1:value2)

// for TApplication and not classes
#define IFMAX(a,b,n) if((a!=0)&&(b!=0)&&(0==strncasecmp(a,b,max(n,strlen(b)))))
// for classes
#define IF(a,b,n) if((a!=0)&&(b!=0)&&(b[0]!=0)&&(0==strnicmp(a,b,min(n,strlen(b)))))
//-----------------------------------------------------------------------
#define commbracketOpen '\"'
#define commbracketClose '\"'

int SplitBuffer(char *buffer,char **argv,int argcMax,char *delimeters=";\n");
int SplitBuffer(char *buffer,unsigned int count,char **argv,int argcMax,char *delimeters=";\n");

int SplitCommand(char *buffer,int count,char **argv,int argcMax); 
int SplitCommand(char *buffer,char **argv,int argcMax); 

int SplitPath(char *path,char **argv,int argcMax);
ASS MergePath(ASS sPath,ASS addPath);
ASS MergePath(ASS sPath,ASS addPath,ASS addPath1);

int StringFromStruct(char *string,int stringSize,char *structure);
int StringToStruct(char *string,char *structure,int structSize);
int Memcpy(char *dest,char *src,int count);
int IntFromDouble(double v);

int StringFromStruct(char *string,int stringSize,char *structure);
int StringToStruct(char *string,char *structure,int structSize);
int Memcpy(char *dest,char *src,int count);
int IntFromDouble(double v);


//char *Strupr(char *s);
//char *Strlwr(char *s);
int  Strlen(char *s);
int  Strncpy(char *dest,char *src,int len);
int  Strnbackcpy(char *dest,char *src,int len);
int Strback(char *str);
int Strcat(char *str1,char *str2);
int Strncat(char *str,char *str2,int n);


char *TimeToAscii(long t,char *buffer); 
double TimeFromAscii(char *buffer);
unsigned long DateTimeFromAscii(char *buffer,int yearFrom);



//---------------------------------------------------------------------------
#endif
 