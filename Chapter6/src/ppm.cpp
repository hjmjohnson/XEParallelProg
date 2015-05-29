#include <fstream>
#include "mandelbrot.h"

// write to a PPM file.
void WriteMandlebrot()
{
  std::ofstream ppm_file("default.ppm");

  ppm_file << "P6 " << maxI << " " << maxJ << " 255" << std::endl;
  for( int i = 0; i < maxI; ++i )
    {
    for( int j = 0; j < maxJ; ++j )
      {
      const float color = (float)zcolor[i][j];
      const bool isWhite = ( color >= .99999 );
      const unsigned char red = (isWhite) ? 255 : 0 ;
      const unsigned char green = (isWhite) ? 255 : 0 ;
      const unsigned char blue = (isWhite) ? 255 : 0 ;
      // write to PPM file
      ppm_file << red << green << blue;
      }
    }
}
