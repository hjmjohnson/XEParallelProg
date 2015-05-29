#include <cilk/cilk.h>
#include <cilk/holder.h>

cilk::holder<int> g;

// code that uses Cilk Plus holder
void test1()
{
  int i;
  g() = 8;
  cilk_spawn[&]
  {
    g()=100;
    i = g();
  }();
  g()= 37;
  cilk_sync;
  }

 // template for wrapper
 template <typename T>
 class myholder
 {
   private:
     cilk::holder<T> m_holder;
   public:
     myholder<T> & operator=(const T &rhs)
     {
       m_holder() = rhs;return *this;
     }
   operator T &(){return m_holder();}
 };

 // code that uses the wrapper
 myholder<int> h;
 void test2()
 {
   int i;
   h = 8;
   cilk_spawn[&]
   {
     h=100;
     i = h;
   }();
   h = 37;
   cilk_sync;
 }