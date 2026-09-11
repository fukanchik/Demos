/* Ok in C (tentative definition), bad in c++.
 *
 * - same translation unit
 * - outside of a function
 * - types match
 * - no initializers
 * - only `static' specifier is accepted
 */
int i;
int i;

static int a;
static int a;

int c = 12;
int c;

int
main()
{
    return 0;
}
