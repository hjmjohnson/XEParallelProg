extern double AddY( double sumy, int k );

double Series1(int j)
{
  int k;
  double sumx = 0.0;
    for( k=0; k<j; k++ )
      sumx = sumx + (double)k;	
  return sumx;
}

double Series2(int j)
{
  int k;
  double sumy = 0.0;
  for( k=j; k>0; k--)
  {
    sumy++;  
    sumy = AddY(sumy, k);
  }
   return sumy;
}
