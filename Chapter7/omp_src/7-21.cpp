// linked list iteration
void RunThoughLinkedList()
{
  #pragma omp parallel
  {
    #pragma omp single
    {
      node *pHead = Head;
      while(pHead != NULL)
      {
        #pragma omp task firstprivate(pHead)
        {
          Work(pHead);
        }
        pHead = pHead->next;
      }
    }
  }
}