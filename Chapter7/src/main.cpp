#include <stdio.h>
#include <memory.h>
extern int Prime(int end);
extern int PrimeRecursive(int end);
#include "wtime.h"

#define PRIME_NUMS 1000000
#define PRIME_NUMS_RECURSE 20000
#define NUM_NODES 5

enum Op { OpPrime,OpPrimeRecursive};
struct node
{
  int ValueIn;
  Op Operation;
  int NumPrimes;
  double Start; // time
  double End; // time
  node *next; // the reference to the next node
  void Init(int v,Op o,node* n){ValueIn = v;Operation=o;next=n;}
  node(){Start=0;End=0;next=NULL;};
};

node List[NUM_NODES];
node * Head;

void Init()
{
  memset(List,'\0',sizeof(List));
  // set up the link
  List[0].Init(PRIME_NUMS,OpPrime,&List[4]);
  List[1].Init(PRIME_NUMS_RECURSE,OpPrimeRecursive,&List[2]);
  List[2].Init(PRIME_NUMS,OpPrime,NULL);
  List[3].Init(PRIME_NUMS_RECURSE,OpPrimeRecursive,&List[1]);
  List[4].Init(PRIME_NUMS,OpPrime,&List[3]);
  Head = &List[0];
}

void Work( node * pHead )
{
  pHead->Start = wtime();
  switch(pHead->Operation)
  {
    case OpPrime:
      pHead->NumPrimes=Prime(pHead->ValueIn);
      break;
    case OpPrimeRecursive:
      pHead->NumPrimes=PrimeRecursive(pHead->ValueIn);
      break;
  };
  pHead->End = wtime();
  printf("Work Time %7.2f\n",pHead->End-pHead->Start);
}

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

// manual iterations
void RunExplicit()
{
  Work(&List[0]);
  Work(&List[1]);
  Work(&List[2]);
  Work(&List[3]);
  Work(&List[4]);
}

int main()
{
  Init();
  double start = wtime();
  double start_linked_list = wtime();
  RunThoughLinkedList();
  double end_linked_list = wtime();
  double start_explicit = wtime();
  RunExplicit();
  double end_explicit = wtime();
  double end = wtime();

  printf("Time through Linked List %7.2f\n"
    "Time through explicit %7.2f\n"
    "Total Time taken %7.2f\n",
    end_linked_list-start_linked_list,
    end_explicit-start_explicit,
    end-start
  );
}
