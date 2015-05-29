int main()
{
  int a[] = {1,2,3,4};
  int b[] = {2,4,6,8};
  int c[] = {0,0,0,0};
  
  c[:]=a[0:4] + b[0:4]; // 3,6,9,12
  int sum = __sec_reduce_add(c[:]); // 30

  return sum;
}