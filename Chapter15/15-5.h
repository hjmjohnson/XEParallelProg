// NOTE THIS CODE IS INCOMPLETE AND WILL NOT COMPILE!
// IT IS INCLUDED HERE FOR COMPARISON PURPOSES ONLY
// SERIAL VERSION
for( --i; i>=0; i-- ){
  // h = &t.vHits[i];
  z0 = vStations.z[i];
  dz = (z1-z0);
  vStations.field(i,T[0]-T[2]*dz,T[1]-T[3]*dz,H0);
  vStations.field(i,vTracks.hitsX[iTrack][i],vTracks.hitsY[iTrack][i], HH);
  combine( HH, h_w, H0 );
  f.set( H0, z0, H1, z1, H2, z2);
  extrapolateALight( T, C, vStations.zhit[i], qp0, f );
  addMaterial( iTrack, i, qp0, T, C );
  filter( iTrack, xInfo, vTracks.hitsX[iTrack][i], h_w, T, C );
  filter( iTrack, yInfo, vTracks.hitsY[iTrack][i], h_w, T, C );
  memcpy( H2, H1, sizeof(ftype) * 3 );
  memcpy( H1, H0, sizeof(ftype) * 3 );
  z2 = z1;
  z1 = z0;
}

// ARBB VERSION
// Note 'U' is a template parameter and becomes an ArBB floating point type
_for( i -= 1, i >= 0, i-- ){
  U z0 = ss.z[i];
  dz = z1 - z0;
  ss.field( i, T[0] - T[2] * dz, T[1] - T[3] * dz, H0 );
  ss.field( i, ts.hitsX2.row( i ), ts.hitsY2.row( i ), HH );
  combineArBB<U>( HH, w, H0 );

  //! note: FieldRegionArBB f sets values here, needn‘t pass parameters
  f.set( H0, z0, H1, z1, H2, z2);

  extrapolateALightArBB2<U>( T, C, ss.zhit[i], qp0, f );
  addMaterialArBB( ts, ss, i, qp0, T, C );
  filterArBB( ts, ss, xInfo, ts.hitsX2.row( i ), w, T, C );
  filterArBB( ts, ss, yInfo, ts.hitsY2.row( i ), w, T, C );
  for( int j = 0; j < 3; j ++ ){
    H2[j] = H1[j];
    H1[j] = H0[j];
  }
  z2 = z1;
  z1 = z0;
}_end_for;