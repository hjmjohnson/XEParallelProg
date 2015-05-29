// NOTE: See class.h for complete listing.
// The listing here is not intended to be compiled.
class Stations{
public:
  int nStations;

  ftype *z, *thick, *zhit, *RL, *RadThick,*logRadThick,*Sigma,*Sigma2,*Sy;
  ftype (**mapX), (**mapY), (**mapZ); // polinom coeff.

  void initMap( int i, ftype *x, ftype *y, ftype *z){// init code }
  Stations( int ns ) {init( ns );}
  void init( int ns )
  {
    // allocate memory all 7 stations are together
    nStations = ns;
    z = (ftype*)malloc(ns*sizeof(ftype));
    // ... repeat for thick zhit RL RadThick logRadThick Sigma
    // Sigma2 Sy mapX mapY mapZ mapXPool mapYPool mapZPool
  }

  ~Stations() {// free dynamically allocated memory}

private:
  // pointers to private pool
  ftype *mapXPool, *mapYPool, *mapZPool;
};