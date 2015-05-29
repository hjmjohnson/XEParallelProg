#include <cilk/cilk.h>
// linked list iteration
void RunThoughLinkedList()
{
  node *pHead = Head;
  while(pHead != NULL)
  {
    cilk_spawn Work(pHead);
    pHead = pHead->next;
  }
}