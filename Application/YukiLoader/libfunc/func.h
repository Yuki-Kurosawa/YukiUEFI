#include <Uefi.h>
#include <Library/UefiLib.h>
#include <string.h>
#include <stdlib.h>

void WideStrToAsciiStr(CHAR16 *w,CHAR8 *buffer);
void AsciiStrToWideStr(CHAR8 *a,CHAR16 *buffer);

void strrep(char *src,char* pattern,char* replace,char* dest);