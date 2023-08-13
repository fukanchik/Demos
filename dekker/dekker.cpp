/* Store buffering affects https://en.wikipedia.org/wiki/Dekker%27s_algorithm */
#include <iostream>
#include <atomic>
#include <thread>

int
main(int argc, char *argv[])
{
  int violations = 0;

  for(int i=0; i < 200000; ++i)
    {
      //std::atomic_int x{0};
      //std::atomic_int y{0};
      int x{0};
      int y{0};

      std::thread g1([&]{
                       x=1;
                       if(y==0)x=2;
                     });
      std::thread g2([&]{
                       y=1;
                       if(x==0)y=2;
                     });
      g1.join();
      g2.join();
      if(x==2 && y==2) ++viol;
    }
  std::cout << "N="<< viol<< std::endl;
  return 0;
}

