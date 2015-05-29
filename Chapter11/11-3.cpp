// This code fixes some of the data races but not all of them!
// WARNING: THERE ARE STILL SOME DATA RACES IN HERE
static void draw_task (void)
{
  unsigned int serial = 1;
  int ison=1;
  unsigned int mboxsize = sizeof(unsigned int)*(max_objectid() + 20);
  unsigned int * local_mbox = (unsigned int *) alloca(mboxsize);
  memset(local_mbox,0,mboxsize);

  // Each thread has its own initialized copy of serial and ison
  #pragma omp parallel for firstprivate(serial, ison)
  for(int y = starty; y < stopy; y++) {
    if(ison) {
      drawing_area drawing(startx, totaly-y, stopx-startx, 1);
      for (int x = startx; x < stopx; x++) {
        color_t c = render_one_pixel (x, y, local_mbox, serial,
                                 startx, stopx, starty, stopy);
        drawing.put_pixel(c);
      }
      ison = video->next_frame();
    }
  }
return;
}