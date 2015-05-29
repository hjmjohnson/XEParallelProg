#include <fstream>
#include "mandelbrot.h"

// write to a PPM file.
void WriteMandlebrot()
{
  std::ofstream ppm_file("default.ppm");
  ppm_file << "P6 " << maxI << " " << maxJ << " 255" << std::endl;
  unsigned char red, green, blue; 
  for (int i=0; i<maxI; i++) {
    for (int j=0; j<maxJ; j++) {
      float color = (float)zcolor[i][j] ;
      float temp = color;
      if (color >= .99999)
      {
        red = 255 ; green = 255; blue = 255;
      }
      else
      {
        red = 0 ; green = 0; blue = 0;
      }
      // write to PPM file
      ppm_file << red << green << blue;
    }
  }
}