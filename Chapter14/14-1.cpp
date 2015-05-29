// This code has known data race bugs and is used as an example
// to explain how to detect parallelization problems.
unsigned int stepcount;
void Step()
{
  // parallelize following loop using cilk_for in place of C for
  cilk_for(int i = 0; i < theTable.SortedList.Cursor; i++)
  {
    // declare and set hash table value
    unsigned int Hash = theTable.SortedList.List[i];
    if(Hash != 0)
    {
      // declare pointers to first & next nodes
      NODE *pNode = GetNode(Hash);
      NODE *pChain = pNode->pNext;
      // advance to next node and step count
      HashAdvance(pNode,GetNode(0));
      stepcount++;
      // while not end of list
      while(pChain)
      {
        // advance to next node
        HashAdvance(pChain, GetNode(0));
        pChain = pChain->pNext;
        stepcount++;
      }
    }
  }
}