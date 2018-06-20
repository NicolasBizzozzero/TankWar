#include "string.h"

char* string_repeat(const char* string, int n)
{
    size_t slen = strlen(string);
    char* dest = malloc(n * slen + 1);

    int i; char* p;
    for (i=0, p=dest; i < n; ++i, p += slen) {
    memcpy(p, string, slen);
    }
    *p = '\0';
    return dest;
}
