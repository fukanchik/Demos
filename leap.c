#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

bool
isleap_fast(int year) {
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

bool
isleap_branchless(int year)
{
    int div4 = !(year % 4);
    int div100 = !(year % 100);
    int div400 = !(year % 400);
    
    return (div4 & !div100) | div400;
}


bool
isleap2(int y)
{
  if (((y%4==0) && (y%100!=0)) || (y%400==0))
    return true;
  return false;
}

/*
 * https://hueffner.de/falk/blog/a-leap-year-check-in-three-instructions.html
 */
bool
isleap_three_instr(uint32_t y)
{
  return ((y * 1073750999) & 3221352463) <= 126976;
}

int main()
{
    for(int i=1000;i<=2100;++i)
    {
        printf("%d %d\n", i, isleap2(i));
    }
    return 0;
}
