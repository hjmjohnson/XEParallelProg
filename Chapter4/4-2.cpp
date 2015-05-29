void f(int n, float *x, float *y, float *z, float *d1, float *d2)
{
  for (int i = 0; i < n; i++)
  z[i] = x[i] + y[i] – (d1[i]*d2[i]);
}