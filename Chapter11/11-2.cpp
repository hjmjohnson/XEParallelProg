static void draw_task (void)
{
  // Start a parallel region
  #pragma omp parallel
  {
    // each thread will have its own copy of these variables
    int ison = 1;
    unsigned int serial = 1;
    unsigned int mboxsize = sizeof(unsigned int)*(max_objectid() + 20);
    unsigned int * local_mbox = (unsigned int *) alloca(mboxsize);
    memset(local_mbox, 0, mboxsize);
    // workshare the loops between the threads
    #pragma omp for
    for(int y = starty; y < stopy; y++) {
      if (ison) {
        drawing_area drawing(startx, totaly-y, stopx-startx, 1);
        for (int x = startx; x < stopx; x++) {
          color_t c = render_one_pixel (x, y, local_mbox, serial, startx,
                                                stopx, starty, stopy);
          drawing.put_pixel(c);
        }
        ison = (video->next_frame()? 1 : 0);
      }
    }
  }
  return;
}