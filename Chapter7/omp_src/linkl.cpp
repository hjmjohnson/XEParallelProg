#include <iostream>

class LLNode{
 public:
  LLNode(): payload(321),next(NULL) {}
  int payload;
  LLNode * next;
} ;


static void Work(LLNode * thisNode)
{
  thisNode->payload=1;
}

// linked list iteration
static void RunThoughLinkedList( LLNode *Head)
{
  #pragma omp parallel
  {
    #pragma omp single
    {
      LLNode *pHead = Head;
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

static void PrintLL(LLNode *currNode)
 {
 unsigned char count=0;
 while(currNode != NULL)
   {
   if( count%10  == 0 )
     {
     std::cout << std::flush << std::endl;
     }
   std::cout << currNode->payload << " ";
  }
  std::cout << std::flush << std::endl;

 return;
}

int main()
{
  LLNode * myLLHead=new LLNode();
  LLNode * currNode=myLLHead;

  for( int i = 0 ; i < 30; ++i )
  {
  currNode->next=new LLNode();
  currNode=currNode->next;
  }

  RunThoughLinkedList(myLLHead);

 return EXIT_SUCCESS;
}
