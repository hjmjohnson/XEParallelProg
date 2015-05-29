void RunThoughLinkedList()
{
  tbb::task_group g;
  node *pHead = Head;
  printf("Starting Linked List\n");
  while(pHead != NULL)
  {
    g.run([=]{Work(pHead);});
    pHead = pHead->next;
  }
  g.wait();
}