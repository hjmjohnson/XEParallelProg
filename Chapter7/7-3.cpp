#include <tbb/tbb.h>
#include <vector>

void Work(int Val)
{ 
  // do some work here
}
void Func()
{
  std::vector<int> s;
  s.push_back(0);
  s.push_back(1);
  s.push_back(2);
  s.push_back(3);
  tbb::parallel_do(s.begin(), s.end(),
    [&](int Val) { Work(Val);});
}