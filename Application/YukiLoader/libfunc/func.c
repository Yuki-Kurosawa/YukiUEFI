#include "func.h"

void WideStrToAsciiStr(CHAR16 *w,CHAR8 *buffer)
{
  UnicodeStrToAsciiStrS(w,buffer,1024);
  Print(L"%a\n",buffer);
}