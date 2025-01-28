#include <stdio.h>

bool isleap_fast(int year) {
    if (year %4 == 0) {
        if (year %100 == 0) {
            if (year %400 == 0) {
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
}

int isleap_branchless(int year)
{
    int div4 = !(year % 4);
    int div100 = !(year % 100);
    int div400 = !(year % 400);
    
    return (div4 & !div100) | div400;
}

int main()
{
    for(int i=1000;i<=2100;++i)
    {
        printf("%d %d\n", i, isleap_fast(i));
    }
    return 0;
}
