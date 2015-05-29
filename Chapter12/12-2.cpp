#include <ittnotify.h>
int main()
{
  __itt_domain* pD = __itt_domain_create( "Time" );
  pD->flags = 1; // enable domain

  for(int i = 0; i < 100000; i++)
  {
    // mark the beginning of the frame
    __itt_frame_begin_v3( pD,NULL);

    // simulate frames with different timings
    if(i%3)
      for(int j = 0; j < 30000; j++); // a delay
    else
      for(int j = 0; j < 11200; j++); // another delay

    // mark the end of the frame
    __itt_frame_end_v3( pD,NULL);
  }
  return 0;
}