#include "func.h"

void WideStrToAsciiStr(CHAR16 *w,CHAR8 *buffer)
{
  UnicodeStrToAsciiStrS(w,buffer,1024);
  Print(L"%a\n",buffer);
}

void AsciiStrToWideStr(CHAR8 *a,CHAR16 *buffer)
{
  AsciiStrToUnicodeStrS(a,buffer,1024);
  Print(L"%s\n",buffer);
}

void strrep(char *src,char* pattern,char* replace,char* dest) {
    char *ins;    // the next insert point
    char *tmp;    // varies
    char* result;
    int len_pattern;  // length of rep (the string to remove)
    int len_replace; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!src || !pattern)
        return;
    len_pattern = strlen(pattern);
    if (len_pattern == 0)
        return; // empty rep causes infinite loop during count
    if (!replace)
        replace = "";
    len_replace = strlen(replace);

    // count the number of replacements needed
    ins = src;
    for (count = 0; (tmp = strstr(ins, pattern)); ++count) {
        ins = tmp + len_pattern;
    }

    tmp = result = malloc(strlen(src) + (len_replace - len_pattern) * count + 1);

    if (!result)
        return ;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(src, pattern);
        len_front = ins - src;
        tmp = strncpy(tmp, src, len_front) + len_front;
        tmp = strcpy(tmp, replace) + len_replace;
        src += len_front + len_pattern; // move to next "end of rep"
    }
    strcpy(tmp, src);
    strcpy(dest,result);
}