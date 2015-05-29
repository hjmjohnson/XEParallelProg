tbb::make_filter<int,int>(
  filter::parallel, [](int i)->int {
  {
    for (int j = 0; j < LINE_LENGTH; j++)
    LineOut[i][j]=sqroot((float)LineIn[i][j]);
    return i;
  }
}) &