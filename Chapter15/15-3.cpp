#include <arbb.hpp>
#include <cstdlib>

void sum_of_differences(dense<f32> a, dense<f32> b, f64& result)
{
  result = add_reduce((a – b) * (a - b));
}

int main()
{
  std::size_t size = 1024;
  dense<f32> a(size), b(size);
  f64 result;
  range<f32> data_a = a.read_write_range();
  range<f32> data_b = a.read_write_range();

  for (std::size_t i = 0; i != size; ++i) {
    data_a[i] = static_cast<float>(i);
    data_b[i] = static_cast<float>(i + 1);
    call(&sum_of_differences)(a, b, result);
    std::cout << “Result: ” << value(result) << ‘\n’;
  }
  return 0;
}