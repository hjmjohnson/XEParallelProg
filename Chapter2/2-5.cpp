 #include "tbb/tbb.h"
 #include <stdio.h>
 using namespace tbb;

 int main()
 {
   parallel_for( size_t(0),size_t(20),size_t(1),
   [=](size_t n) {
     std::printf("%d ",n);
   }
 );
 return 0;
}