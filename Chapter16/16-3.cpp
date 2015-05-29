// int Arr_1_Glob [50];
array_holder<int,50> Arr_1_Glob;
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