// Function that will call IPP FFT
int FFT(float in[], const float out[], int len)
{
  int power = 12;
  Ipp32fc* pFilterCCS;
  IppsFFTSpec_R_32f *pFFTSpec;

  // allocate space for FFT
  pFilterCCS = (Ipp32fc*)ippsMalloc_32f(len+2);

  // FFT configure
  Ipp32fc one = {1.0, 0.0};

  // zero initialize the FFT space
  ippsZero_32fc( pFilterCCS, len/2+1 );

  //initialize the FFT
  ippsFFTInitAlloc_R_32f( &pFFTSpec,
                 power, IPP_FFT_DIV_BY_SQRTN, ippAlgHintFast );

  // do the FFT
  ippsFFTFwd_RToPerm_32f(in, (Ipp32f*)out, pFFTSpec, 0 );

  // free up the FFT space
  ippsFree(pFFTSpec);
  return 0;
}