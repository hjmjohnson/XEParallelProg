bool Solve(SUDOKU *pPuzzle,int PuzzleIdx,int NodeIdx,int &NumRecursions)
{
  NumRecursions ++;
  if (NodeIdx >= NUM_NODES)
    return true;

  if(!FillPossibilities(pPuzzle,NodeIdx))
    return false;

  NODE BackupNode;
  for(int i=1; i<=MAX_NUM; i++)
  {
    if(Allowed(pPuzzle,NodeIdx,i))
    {
      StoreNumber(pPuzzle,NodeIdx,BackupNode,NumRecursions,i);
      int NewIdx = GetNextIdx(pPuzzle, NodeIdx);

      if (!Solve(pPuzzle,PuzzleIdx,NewIdx,NumRecursions))
      ClearNumber(pPuzzle,NodeIdx,BackupNode,i);
    }
  }
 return false;
}