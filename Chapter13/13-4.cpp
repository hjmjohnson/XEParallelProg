SUDOKU Puzzles[NUM_NODES];

int Generate(SUDOKU *pPuzzle)
{
  #pragma omp parallel
  for(int i = 0 ; i < NUM_NODES -1; i++ )
  {
    #pragma omp single nowait
    {
      NODE Node1 = pPuzzle->Nodes[i];
      if(Node1.number > 0)
      {
        memcpy(&Puzzles[i],pPuzzle,sizeof(SUDOKU));
        #pragma omp task firstprivate(i)
        GenDoWork(&Puzzles[i],i);
      }
    }
  }
  return gNumCalls; //global incremented on each call to solver
}