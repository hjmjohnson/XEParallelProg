#pragma once
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


// --------------- to hold arrays --------------------------
template <typename T, int SZ>
struct CArrayOneDimension
{
  T Data[SZ];
};


template <typename T, int SZ>
  class array_holder
  {
    private:
      cilk::holder<CArrayOneDimension<T,SZ>> m_holder;
    public:
        operator T* (){return m_holder().Data;} 
  };
// ------------------------------------------------------------------------------------  
  
template <typename T, int SZ1, int SZ2>
struct CArrayTwoDimension
{
  T Data[SZ1][SZ2];
};


template <typename T, int SZ1,int SZ2>
  class array_2_holder
  {
    private:
      cilk::holder<CArrayTwoDimension<T,SZ1,SZ2>> m_holder;
    public:
    operator Arr_2_Dim &(){return m_holder().Data;}   
    T* operator[](const T x){return m_holder().Data[x];}
  };


