#include <cilk/cilk.h>
__declspec (vector) double ef_add (double x, double y){
  return x + y;
}
int main()
{
  double a[5];
  double b[] = {1,2,3,4,5};
  double c[] = {6,7,8,9,10};

  // apply function to whole array
  a[:] = ef_add(b[:],c[:]);

  a[:] = 0;
  int n = 2;
  int s = 1;
  // apply function to a sub range
  a[0:n:s] = ef_add(b[0:n:s],c[0:n:s]);

  a[:] = 0;
  // apply function in parallel
  cilk_for (int j = 0; j < n; ++j)
  {
    a[j] = ef_add(b[j],c[j]);
  }
}