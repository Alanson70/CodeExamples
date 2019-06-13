
#include "WinTtyDefs.hpp"

#pragma package(smart_init)

 
DWORD BaudRates[16]=
{
 CBR_110,
 CBR_300,
 CBR_600,
 CBR_1200,
 CBR_2400,
 CBR_4800,
 CBR_9600,
 CBR_14400,
 CBR_19200,
 CBR_38400,
 CBR_56000,
 CBR_57600,
 CBR_115200,
 CBR_128000,
 CBR_256000
};

long BaudRatesReal[16]=
{
 110,
 300,
 600,
 1200,
 2400,
 4800,
 9600,
 14400,
 19200,
 38400,
 56000,
 57600,
 115200,
 128000,
 256000
};

BYTE Paritets[4]=
{
 EVENPARITY,	//Even
 MARKPARITY,	//Mark
 NOPARITY,   	//No parity
 ODDPARITY,	    //Odd
};

BYTE StopBitss[3]=
{
 ONESTOPBIT,	//1 stop bit
 ONE5STOPBITS,	//1.5 stop bits
 TWOSTOPBITS,	//2 stop bits
};

BYTE ByteSizes[5]=
{
 4,
 5,
 6,
 7,
 8
};

 