#include <stdio.h>
#include <stdlib.h>
#include <tbb/tbb.h>
#define LINE_LENGTH 8000
#define NUM_LINES 100
#define NUM_ENTRIES LINE_LENGTH * NUM_LINES

float sqroot(int n)  
{  
  float i = 0;  
  float x1, x2;  
  while( i*i<= n )  
    i+=0.1;  
  x1 = i;  
  for(int j=0; j<10; j++)  
  {  
     x2 = n;  
     x2 = x2/x1;  
     x2 = x2+x1;  
     x2 = x2/2;  
     x1 = x2;  
  }  
  return x2;  
}  

int LineIn[NUM_LINES][LINE_LENGTH];
float LineOut[NUM_LINES][LINE_LENGTH];

using namespace tbb;

int main()
{
  int i = 0;
  int ntokens = 24;
  FILE *pFile = fopen(".\\Test.Data","r");
  if(!pFile){ printf("Couldn’t open Test.Data");exit(999);}

  FILE *pOutputFile = fopen("TBB_Squared.Data","w");
  if(!pOutputFile){ printf("Couldn’t open OpenMP_Squared.Data");exit(999);}

  parallel_pipeline(
    ntokens,
    tbb::make_filter<void,int>(
      filter::serial_in_order, [&i,&pFile](flow_control& fc)->int {
        if (i < NUM_LINES)
        {
          for (int j = 0; j < LINE_LENGTH; j++)
            fscanf( pFile,"%d ",&LineIn[i][j]);
          return i++;
        }
        else
          fc.stop();
      return -1;
    }) &

  tbb::make_filter<int,int>(
    filter::serial_in_order, [](int i)->int {
    parallel_for (size_t(0), (size_t)LINE_LENGTH,[&](size_t j){
      LineOut[i][j]=sqroot((float)LineIn[i][j]);
    });
    return i;
  }) &

  tbb::make_filter<int,void>(
    filter::serial_in_order, [&pOutputFile](int i) {
      for (int j = 0; j < LINE_LENGTH; j++)
      fprintf(pOutputFile,"%f ",LineOut[i][j]);
    fprintf(pOutputFile,"\n");
    })
  );
}