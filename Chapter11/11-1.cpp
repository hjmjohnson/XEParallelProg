static void draw_task (void)
{
  unsigned int serial = 1;
  int ison=1;
  unsigned int mboxsize = sizeof(unsigned int)*(max_objectid() + 20);
  unsigned int * local_mbox = (unsigned int *) alloca(mboxsize);
  memset(local_mbox,0,mboxsize);

  // Add parallelism - NOTE THIS WILL INTRODUCE DATA RACES!
  #pragma omp parallel for

  // each iteration will draw a raster
  for(int y = starty; y < stopy; y++) {
    if (ison) {
      drawing_area drawing(startx, totaly-y, stopx-startx, 1);

      // draw the individual line
      for (int x = startx; x < stopx; x++) {
        // work out the right color
        color_t c = render_one_pixel (x, y, local_mbox, serial,
        startx, stopx, starty, stopy);
 
        // draw the pixel
        drawing.put_pixel(c);
      }
      ison = video->next_frame();
    }
  }
}