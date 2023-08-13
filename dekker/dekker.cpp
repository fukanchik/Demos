/* Store buffering affects https://en.wikipedia.org/wiki/Dekker%27s_algorithm 
TODO: lfence, sfence, memory_order_acq_rel, memory_order_seq_cst, memory_order_relaxed
https://stackoverflow.com/questions/27595595/when-are-x86-lfence-sfence-and-mfence-instructions-required
*/
#include <iostream>
#include <atomic>
#include <thread>

/*
1 - atomic
2 - volatile
3 - mfence
4 - none
*/
#define CODE 4

int
main(int argc, char *argv[])
{
  int violations = 0;

  for(int i=0; i < 200000; ++i)
    {
#if CODE==1
      std::atomic_int x{0};
      std::atomic_int y{0};
#elif CODE==2
      volatile int x{0};
      volatile int y{0};
#else
      int x{0};
      int y{0};
#endif

      std::thread g1([&]{
                       x=1;
#if CODE==3
asm volatile("mfence":::"memory");
#endif
                       if(y==0)x=2;
                     });
      std::thread g2([&]{
                       y=1;
#if CODE==3
asm volatile("mfence":::"memory");
#endif
                       if(x==0)y=2;
                     });
      g1.join();
      g2.join();
      if(x==2 && y==2) ++violations;
    }
  std::cout << "N="<< violations << std::endl;
  return 0;
}

