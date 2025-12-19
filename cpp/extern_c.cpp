/* extern "C" only applies to name mangling, not the language */
extern "C" {
    static inline int foo(void *ptr)
    {
        /* Even though we are in extern "C" this is still invalid. */
        int *i=ptr;
        return *i;
    }
}

int
main()
{
}

