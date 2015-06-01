#include <iostream>
#include "StopWatch.h"
#include <omp.h>

/*IGNORE THIS BLOCK******************************/

class LLNode{
 public:
  LLNode(): payload(321),next(NULL) {}
  int payload;
  LLNode * next;
} ;

static void PrintLL(LLNode *currNode)
 {
 unsigned char count=1;
 while(currNode != NULL)
   {
   if( count%10  == 0 )
     {
     std::cout << std::flush << std::endl;
     count=1;
     }
   std::cout << currNode->payload << "\t";
   currNode=currNode->next;
   count++;
  }
  std::cout << std::flush << std::endl;

 return;
}

/*IGNORE THIS BLOCK*******************************/

//Relevant code starts here
static void Work(LLNode * thisNode)
{
  const int tid = omp_get_thread_num();
  thisNode->payload=tid;
}

// linked list iteration
static void RunThoughLinkedList( LLNode *Head)
{
  #pragma omp parallel default(none) shared(Head)
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

int main()
{
  LLNode * myLLHead=new LLNode();
  LLNode * currNode=myLLHead;

  for( int i = 0 ; i < 30; ++i )
  {
  currNode->next=new LLNode();
  currNode=currNode->next;
  }

  PrintLL(myLLHead);

  StopWatch TotalTimer;
  TotalTimer.StartTimer();

  RunThoughLinkedList(myLLHead);

  TotalTimer.StopTimer();

  PrintLL(myLLHead);

  std::cout << "Time_Total: " << TotalTimer.GetElapsedSeconds() << std::flush << std::endl;

  return EXIT_SUCCESS;
}
