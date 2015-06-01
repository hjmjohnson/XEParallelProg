#include <stdio.h>
#include <stdlib.h>

#define LINE_LENGTH 8000
#define NUM_LINES 100
#define NUM_ENTRIES LINE_LENGTH * NUM_LINES

int LineIn[LINE_LENGTH];
float LineOut[LINE_LENGTH];

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

int main()
{
  FILE *pFile = fopen("../src/Test.Data","r");
  if(!pFile){ printf("Couldn't open Test.Data");exit(999);}

  FILE *pOutputFile = fopen("Squared.Data","w");
  if(!pOutputFile){ printf("Couldn't open Squared.Data");exit(999);}

  // for every line in file ...
  for (int i = 0; i < NUM_LINES; i++)
  {
    // Pipeline STAGE 1
    for (int j = 0; j < LINE_LENGTH; j++)
    fscanf( pFile,"%d ",&LineIn[j]);

    // Pipeline STAGE 2
    for (int j = 0; j < LINE_LENGTH; j++)
    LineOut[j]=sqroot((float)LineIn[j]);

    // Pipeline STAGE 3
    for (int j = 0; j < LINE_LENGTH; j++)
    fprintf(pOutputFile,"%f ",LineOut[j]);
    fprintf(pOutputFile,"\n");
  }

  fclose(pFile);
  fclose(pOutputFile);
  return 0;
}
