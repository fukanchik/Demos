#include <stdio.h>
#include <string.h>

static const char buf[]="a b c d e f g";
int
main(int c, char *v[])
{
    char *p=strpbrk(buf, " ");
    printf("...%s\n", p);
    *p='\0';
    return 0;
}

