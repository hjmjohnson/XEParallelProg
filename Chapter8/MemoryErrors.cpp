#include <stdio.h>
#include <stdlib.h>
#ifdef __WINDOWS__
#include <windows.h>
#endif
#include <omp.h>

#define STORESIZE 1000
int main( void )
{
  int i, j;
  int * ptr_begin_space;
  int * ptr_another_space;
  int * ptr = NULL;
  #ifdef __WINDOWS__
  HGDIOBJ hDefpen;
  #endif

  printf( "Detecting Memory Errors >\n\n" );
  for( i=0; i<1; i++ )
  {
    #ifdef __WINDOWS__
    hDefpen = CreatePen( PS_SOLID, 1, RGB( 255, 255, 255 ) );
    #endif

    ptr_begin_space = (int *)calloc( STORESIZE, sizeof(int) );
    if( ptr_begin_space == NULL )
      printf( "Unable to allocate space on iteration %d\n", i );
    else
    {
      for( j=0; j<STORESIZE; j++ )
        *(ptr_begin_space+j) = j;
    }

    ptr_another_space = (int *)calloc( STORESIZE, sizeof(int) );
    if( ptr_begin_space == NULL )
      printf( "Unable to allocate space on iteration %d\n", i );
    else
    {
      for( j=0; j<STORESIZE+1; j++ )
      {
        ptr_another_space[j] = j;
      }
    }
    free( ptr_another_space );
    *ptr_another_space = 7;
    free( ptr_another_space );
    *ptr = 5;
  }
  return 0;
}