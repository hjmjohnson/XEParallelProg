#include "fit_util.h"         // a set of constants
#include "classes.h"          // Main Kalman filter classes
#include "arbb_classes.h"     // Added classes for parallel driver
#include "arbb.hpp"           // added for arbb namespace data

typedef float ftype;
typedef f32 FTYPE;            // Added for parallel driver

using namespace std;
using namespace arbb;        // Access to arbb 

// ---------------------------------- Prototypes


void fitTracksArBBEntry( i32 vSize, TracksArBB<FTYPE> vTracksArBB,
                         StationsArBB<FTYPE> vStationsArBB,
                         dense< array<FTYPE, 6> > &vtT,
                         dense< array<FTYPE, 15> > &vtC    );

void fitArBB( TracksArBB<FTYPE> &ts, StationsArBB<FTYPE> &ss,
              FieldRegionArBB<FTYPE> &f,
              dense< array<FTYPE, 6> > &vtT,
            dense< array<FTYPE, 15> > &vtC   );

void extrapolateALightArBB( dense<FTYPE> *T, dense<FTYPE> *C, 
                            dense<FTYPE> &zOut,
                            dense<FTYPE>& qp0, 
                            FieldRegionArBB<FTYPE> &F);

// ------------------------- Global data, instances of classes

extern FieldRegion     magField;
extern Stations        vStations;
extern Tracks          vTracks;

// *** Driving ArBB Parallel Version of Kalman Filter Track Fitter ***

void fitTracksArBB( ftype (*T)[6], ftype (*C)[15], int nT, int nS )
{
  int ix, jx;

  // -----------------------------------------------------------------
  // Create new arrays to hold track hits and load with track hit data. 
  // The new data is transposed so the last index is track number, 
  // rather than first
  // Create two pointers for track hit data
  ARBB_CPP_ALIGN(ftype * X2hits);
  ARBB_CPP_ALIGN(ftype * Y2hits);
  // reserve array space 
  X2hits = ( ftype * ) arbb::aligned_malloc( sizeof(ftype) * nS * nT  );
  Y2hits = ( ftype * ) arbb::aligned_malloc( sizeof(ftype) * nS * nT  );
  // load hit data in reverse order
  for(ix = 0; ix < nT; ix ++)
  {
    for(jx = 0; jx < nS; jx ++)
    {
      X2hits[jx * nT + ix] = vTracks.hitsX[ix][jx];
      Y2hits[jx * nT + ix] = vTracks.hitsY[ix][jx];
    }
  }

  // ---------------------------------------------------------------
  // Create new temporary set of arrays for state 
  // and covariance matrix data.
  // The passed T & C matricies are 2D in the wrong order, 
  // with track number as the first index.
  // Define a state array of 6 pointers
  ARBB_CPP_ALIGN(ftype *TBuf[6]);
  // reserve array space for each, size number of tracks
  for( int i = 0; i < 6; i ++ )
  {
    TBuf[i] = ( ftype * ) arbb::aligned_malloc( sizeof( ftype ) * nT );
  }
  // define a covariance array of 15 pointers
  ARBB_CPP_ALIGN(ftype *CBuf[15]);
  // reserve array space for each
  for( int i = 0; i < 15; i ++ )
  {
    CBuf[i] = ( ftype * ) arbb::aligned_malloc( sizeof( ftype ) * nT );
  }
  // define array of 6 dense containers for state matrix
  dense< array<FTYPE, 6>  >  vtT;
  // bind to state matrix
  bind(vtT, nT, TBuf[0], TBuf[1], TBuf[2], TBuf[3], TBuf[4], TBuf[5]);
  // define array of 15 dense containers for covariance matrix
  dense< array<FTYPE, 15> >  vtC;
  // bind to covariance matrix
  bind(vtC, nT, CBuf[0], CBuf[1], CBuf[2], CBuf[3], CBuf[4], CBuf[5],
  CBuf[6], CBuf[7], CBuf[8], CBuf[9], CBuf[10], CBuf[11],
  CBuf[12], CBuf[13], CBuf[14]);
  // ---------------------------------------------------------------
  // Create and bind new instances of TrackArBB and StationArBB data
  // create new instance of new class
  TracksArBB<FTYPE> vTracksArBB;
  // bind with existing information from
  // instance of old class Tracks
  bind(vTracksArBB.MC_x, vTracks.MC_x, nT );
  bind(vTracksArBB.MC_y, vTracks.MC_y, nT );
  bind(vTracksArBB.MC_z, vTracks.MC_z, nT );
  bind(vTracksArBB.MC_px, vTracks.MC_px, nT );
  bind(vTracksArBB.MC_py, vTracks.MC_py, nT );
  bind(vTracksArBB.MC_pz, vTracks.MC_pz, nT );
  bind(vTracksArBB.MC_q, vTracks.MC_q, nT );
  bind(vTracksArBB.nHits, vTracks.nHits, nT );
  bind(vTracksArBB.NDF, vTracks.NDF, nT ); 
  bind(vTracksArBB.hitsX, vTracks.hitsX[0], nS, nT );
  bind(vTracksArBB.hitsY, vTracks.hitsY[0], nS, nT );
  bind(vTracksArBB.hitsX2, X2hits, nT, nS);
  bind(vTracksArBB.hitsY2, Y2hits, nT, nS);
  bind(vTracksArBB.hitsIsta, vTracks.hitsIsta[0], nS, nT );
  // create new instance of new class
  StationsArBB<FTYPE> vStationsArBB;
  // bind with existing information from
  // instance of old class Stations
  bind(vStationsArBB.z, vStations.z, nS );  
  bind(vStationsArBB.thick, vStations.thick, nS );
  bind(vStationsArBB.zhit, vStations.zhit, nS ); 
  bind(vStationsArBB.RL, vStations.RL, nS );
  bind(vStationsArBB.RadThick, vStations.RadThick, nS );
  bind(vStationsArBB.logRadThick, vStations.logRadThick, nS );
  bind(vStationsArBB.Sigma, vStations.Sigma, nS );
  bind(vStationsArBB.Sigma2, vStations.Sigma2, nS );
  bind(vStationsArBB.Sy, vStations.Sy, nS );
  bind(vStationsArBB.mapX, vStations.mapX[0], 10, nS );
  bind(vStationsArBB.mapY, vStations.mapY[0], 10, nS );
  bind(vStationsArBB.mapZ, vStations.mapZ[0], 10, nS );
  // ---------------------------------------------------------------
  // Invoke call to track fitter by a call operation
  // set number of tracks in ArBB data type
  i32 vSize = nT;
  // Invoke Kalman filter track fitter by call operator
  call(fitTracksArBBEntry)(vSize,vTracksArBB,vStationsArBB,vtT,vtC);

  // copy container to C buffers
  vtT.read_only_range();
  vtC.read_only_range();

  // --------------------------------------------------------------
  // Pack temporary array data back into T & C arrays, transposing
  // order of storage back to the original with track number being the   
  // first index
  for( int i = 0; i < nT; i ++ )
  {
    for( int j = 0; j < 6; j ++ )
    {
      T[i][j] = TBuf[j][i];
    }
    for( int j = 0; j < 15; j ++ )
    {
      C[i][j] = CBuf[j][i];
    }
  }
  // --------------------------------------------------------------
  // Release memory of TBuf and CBuf matrices
  for( int i = 0; i < 6; i ++ )
  {
    arbb::aligned_free( TBuf[i] );
  }
  for( int i = 0; i < 15; i ++ )
  {
    arbb::aligned_free( CBuf[i] );
  }

  arbb::aligned_free( X2hits );
  arbb::aligned_free( Y2hits );
}

//******************************************************************
void fitTracksArBBEntry( i32 vSize, TracksArBB<FTYPE> vTracksArBB,
                                    StationsArBB<FTYPE> vStationsArBB,
                                    dense< array<FTYPE, 6> > &vtT,
                                    dense< array<FTYPE, 15> > &vtC   )
{
  // create a FieldRegion class instance
  FieldRegionArBB<FTYPE> magFieldArBB(vSize);
  // create an ArBB index type 
  usize j;

  // -------------------------------------------------------------
  // Repeat 100 times the call to the
  // Kalman filter Track fitter
  // Using ArBB type for loop
  _for( j = (usize)0, j < Ntimes, j ++ )
  {
    fitArBB( vTracksArBB, vStationsArBB, magFieldArBB, vtT, vtC );
  }_end_for;

  // -------------------------------------------------------------
  // Extrapolate to start of tracks as in serial version
  // define local matrices of dense containers 
  dense<FTYPE> T[6];
  dense<FTYPE> C[15];
  // load T with contents of vtT
  T[0] = vtT.get<FTYPE, 0>();
  T[1] = vtT.get<FTYPE, 1>();
  T[2] = vtT.get<FTYPE, 2>();
  T[3] = vtT.get<FTYPE, 3>();
  T[4] = vtT.get<FTYPE, 4>();
  T[5] = vtT.get<FTYPE, 5>();

  // load C with contents of vtC
  C[0] = vtC.get<FTYPE, 0>();
  C[1] = vtC.get<FTYPE, 1>();
  C[2] = vtC.get<FTYPE, 2>();
  C[3] = vtC.get<FTYPE, 3>();
  C[4] = vtC.get<FTYPE, 4>();
  C[5] = vtC.get<FTYPE, 5>();
  C[6] = vtC.get<FTYPE, 6>();
  C[7] = vtC.get<FTYPE, 7>();
  C[8] = vtC.get<FTYPE, 8>();
  C[9] = vtC.get<FTYPE, 9>();
  C[10] = vtC.get<FTYPE, 10>();
  C[11] = vtC.get<FTYPE, 11>();
  C[12] = vtC.get<FTYPE, 12>();
  C[13] = vtC.get<FTYPE, 13>();
  C[14] = vtC.get<FTYPE, 14>();

  // Call extrapolation function within the filter
  extrapolateALightArBB( T, C, vTracksArBB.MC_x, T[4], magFieldArBB );

  // Reload vtT with new contents of T
  vtT.set<0>(T[0]);
  vtT.set<1>(T[1]);
  vtT.set<2>(T[2]);
  vtT.set<3>(T[3]);
  vtT.set<4>(T[4]);
  vtT.set<5>(T[5]);

  // Reload vtC with new contents of C
  vtC.set<0>(C[0]);
  vtC.set<1>(C[1]);
  vtC.set<2>(C[2]);
  vtC.set<3>(C[3]);
  vtC.set<4>(C[4]);
  vtC.set<5>(C[5]);
  vtC.set<6>(C[6]);
  vtC.set<7>(C[7]);
  vtC.set<8>(C[8]);
  vtC.set<9>(C[9]);
  vtC.set<10>(C[10]);
  vtC.set<11>(C[11]);
  vtC.set<12>(C[12]);
  vtC.set<13>(C[13]);
  vtC.set<14>(C[14])
}
