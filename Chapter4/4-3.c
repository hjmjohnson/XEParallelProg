// ORIGINAL VERSION
void MatrixMul(double a[N][N], double b[N][N],double c[N][N])
{
  int i,j,k;
  for (i=0; i<N; i++) {
    for (j=0; j<N; j++) {
      for (k=0; k<N; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

// VERSION USING ARRAY NOTATION
void MatrixMul(double a[N][N], double b[N][N],double c[N][N])
{
  int i,j;
  for (i=0; i<N; i++) {
    for (j=0; j<N; j++) {
      c[i][j] += a[j][:] * b[:][j];
    }
  }
}