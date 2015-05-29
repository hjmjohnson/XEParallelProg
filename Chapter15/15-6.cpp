#include <math.h>
#include "fit_util.h" // set of constants
#include "classes.h" // Main Kalman filter classes

typedef float ftype; // set ftype to be single precision data

using namespace std;
extern FieldRegion magField;
extern Stations vStations;
extern Tracks vTracks;

// -------------------------- Prototypes
void fit( int iTrack, ftype T[6], ftype C[15] );
void extrapolateALight( ftype T[], ftype C[], const ftype zOut, ftype qp0,
                                    FieldRegion &F );

// ***** Driver of Serial Version of Kalman Filter Track Fitter *****
void fitTracks( ftype (*T)[6], ftype (*C)[15], int nT, int nS )
{
  // Repeat the Kalman filtering 100 times
  for( int times=0; times<Ntimes; times++)
  {
    // take each track in turn and process
    for( unsigned int i=0; i<nT; i++ )
    {
      // apply Kalman filter to track
      fit( i, T[i], C[i], nT, nS );
    }
  }

  // extrapolate all tracks back to start
  for( unsigned int i=0; i<nT; i++ )
  {
    extrapolateALight( T[i], C[i], vTracks.MC_z[i], T[i][4], magField );
  }
}