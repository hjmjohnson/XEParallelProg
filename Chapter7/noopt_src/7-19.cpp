// linked list iteration
void RunThoughLinkedList()
{
  node *pHead = Head;
  while(pHead != NULL)
  {
    Work(pHead);
    pHead = pHead->next;
  }
}