#include <cilk/holder.h>
#include "dhry.h"
template <typename T>
class myholder
{
  private:
    cilk::holder<T> m_holder;
  public:
    T & operator->(){return m_holder();}
    myholder<T> & operator=(const T &rhs ){m_holder()=rhs;return *this;}
    myholder<T> & operator +=(const T &rhs ){m_holder()+=rhs;return *this;}
    T * operator &(){return &(m_holder());}
    operator T (){return m_holder();}
    void operator ++(){m_holder()++;}
};