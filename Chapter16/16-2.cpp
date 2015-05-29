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