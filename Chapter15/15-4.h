/! define stations (SOA)
// NOTE: See arbb_classes.h for complete listing.
// The listing here is not intended to be compiled.

template<typename U>
class StationsArBB
{
public:
  dense<U> z, thick, zhit, RL, RadThick, logRadThick, Sigma, Sigma2, Sy;
  dense<U, 2> mapX, mapY, mapZ; // polynomial coeff.
public:
  StationsArBB(){};
  void field( const usize &i, const dense<U> &x,
  const dense<U> &y, dense<U> H[3] )
  {
    dense<U> x2 = x*x;
    // etc ...
  }
};