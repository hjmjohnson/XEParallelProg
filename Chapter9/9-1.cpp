// Display progress
void PrintProgress(int Range )
{
  int Percent = 0;
  static int lastPercentile = 0;
  #pragma omp atomic
  gProgress++;
  Percent = (int)((float)gProgress/(float)Range *200.0f + 0.5f);  
  if( Percent % 10 == 0 )
  {
    // we should only call this if the value is new!
    if(lastPercentile < Percent / 10)
    {
      printf("%s%3d%%", CursorBack,Percent);
      lastPercentile++;
    }
  }
}