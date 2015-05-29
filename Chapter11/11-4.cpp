// A new class used to hold the former stack variables
class ParameterForRendering {
public:
  int _ison;
  unsigned int _serial;
  unsigned int _mboxsize;
  unsigned int *_local_mbox;
public:
  // constructor
  ParameterForRendering(unsigned int box_size) :
    _ison(1),
    _serial(1),
    _mboxsize(box_size),
    _local_mbox(NULL) {
      _local_mbox = (unsigned int *) malloc(_mboxsize);
      memset(_local_mbox, 0, _mboxsize);
    }

    // copy constructor
    ParameterForRendering(const ParameterForRendering &input) :
      _ison(input._ison),
      _serial(input._serial),
      _mboxsize(input._mboxsize),
      _local_mbox(NULL) {
      _local_mbox = (unsigned int *) malloc(_mboxsize);
      memset(_local_mbox, 0, _mboxsize);
    }

  // destructor
  ~ParameterForRendering() {
    free (_local_mbox);
  }
};

static void draw_task (void)
{
  unsigned int mboxsize = sizeof(unsigned int)*(max_objectid() + 20);

  // instantiate class object
  ParameterForRendering pars(mboxsize);

  // share loop iterations between threads
  // each thread gets its own initialized copy of ‘pars’
  #pragma omp parallel for firstprivate (pars) schedule (dynamic)
  for(int y = starty; y < stopy; y++) {
    if (pars._ison) {
      drawing_area drawing(startx, totaly-y, stopx-startx, 1);
      for (int x = startx; x < stopx; x++) {
        color_t c = render_one_pixel (x, y, pars._local_mbox, pars._serial,
                                 startx, stopx, starty, stopy);
        drawing.put_pixel(c);
      }
      pars._ison = (video->next_frame()? 1 : 0);
    }
  }
return;
}