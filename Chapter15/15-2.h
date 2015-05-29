// NOTE: See class.h for complete listing.
// The listing here is not intended to be compiled.
class Tracks
{
public:
  unsigned int nStations;
  unsigned int nTracks;
  
  ftype *MC_x, *MC_y, *MC_z, *MC_px, *MC_py, *MC_pz, *MC_q;
  int *nHits, *NDF;
  ftype **hitsX, **hitsY;
  ftype *hitsX2, *hitsY2;
  int **hitsIsta;

  void init( int ns, int nt )
  {
    nTracks = nt;
    MC_x = ( ftype* ) malloc( sizeof( ftype ) * nt );

    // repeat for : MC_y MC_z MC_px MC_py MC_pz MC_q nHits
    // NDF hitsX hitsY hitsIsta

    memXPool = ( ftype* ) malloc( sizeof( ftype ) * nt * nStations );
    // repeat for : memYPool memIstaPool hitsX2 hitsY2
  }

  ~Tracks() {}

  void setHits( int i, int *iSta, ftype *hx, ftype *hy )
  {
    // record hits
  }

private:
  ftype *memXPool, *memYPool;
  int *memIstaPool;
};