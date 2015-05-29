int node;
#pragma omp parallel shared(omp_log, node)
{
  #pragma omp single nowait
  {
    for(node = 0; node < Num_SudokuNode ; node++)
    {
      #pragma omp task firstprivate(omp_log, node)
      {
        int result = AddClues(SudokuNode[node], omp_log);
      }
    }
  }
}