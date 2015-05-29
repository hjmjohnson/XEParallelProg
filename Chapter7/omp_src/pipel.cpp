#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
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

int main()
{
  FILE *pFile = fopen(".\\Test.Data","r");
  if(!pFile){ printf("Couldn’t open Test.Data");exit(999);}
  
  FILE *pOutputFile = fopen("OpenMP_Squared.Data","w");
  if(!pOutputFile){ printf("Couldn’t open OpenMP_Squared.Data");exit(999);}

  // preload line 0
  for (int j = 0; j < LINE_LENGTH; j++)
    fscanf( pFile,"%d ",&LineIn[0][j]);

  #pragma omp parallel
  {
    for (int i = 0; i < NUM_LINES; i++)
    {
      // Pipeline STAGE 1
      #pragma omp single nowait
      {
        // start reading the next line
        // Don’t read beyond end
        if(i < NUM_LINES-1);
        {
          for (int j = 0; j < LINE_LENGTH; j++)
            fscanf( pFile,"%d ",&LineIn[i+1][j]);
        }
      }

      // Pipeline STAGE 2
      #pragma omp for schedule(dynamic)
      for (int j = 0; j < LINE_LENGTH; j++)
        LineOut[i][j]=sqroot((float)LineIn[i][j]);

      // Pipeline STAGE 3
      #pragma omp single nowait
      {
        for (int j = 0; j < LINE_LENGTH; j++)
          fprintf(pOutputFile,"%f ",LineOut[i][j]);
        fprintf(pOutputFile,"\n");
      }
    }
  }
  
  fclose(pFile);
  fclose(pOutputFile);
  return 0;
}