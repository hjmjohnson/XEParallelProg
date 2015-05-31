#include <iostream>
#include <omp.h>

/* IGNORE THIS */class LLNode{
/* IGNORE THIS */ public:
/* IGNORE THIS */  LLNode(): payload(321),next(NULL) {}
/* IGNORE THIS */  int payload;
/* IGNORE THIS */  LLNode * next;
/* IGNORE THIS */} ;
/* IGNORE THIS */static void PrintLL(const LLNode *currNode)
/* IGNORE THIS */ {
/* IGNORE THIS */ unsigned char count=1;
/* IGNORE THIS */ while(currNode != NULL)
/* IGNORE THIS */   {
/* IGNORE THIS */   if( count%10  == 0 )
/* IGNORE THIS */     {
/* IGNORE THIS */     std::cout << std::flush << std::endl;
/* IGNORE THIS */     count=1;
/* IGNORE THIS */     }
/* IGNORE THIS */   std::cout << currNode->payload << "\t";
/* IGNORE THIS */   currNode=currNode->next;
/* IGNORE THIS */   count++;
/* IGNORE THIS */  }
/* IGNORE THIS */  std::cout << std::flush << std::endl;
/* IGNORE THIS */
/* IGNORE THIS */ return;
/* IGNORE THIS */}


    /////////////////////////////////////////
    //////// PAY ATTENTION TO CODE BELOW HERE
static void Work(LLNode * thisNode)
{
  const int tid=omp_get_thread_num(); // <---------------------------- Fill in LL with current thread number
  thisNode->payload=tid;
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
#pragma omp task firstprivate(pHead) // <----------------------------
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
  RunThoughLinkedList(myLLHead);
  PrintLL(myLLHead);

  return EXIT_SUCCESS;
}
