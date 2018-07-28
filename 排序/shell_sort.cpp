#include<stdio.h>
#include<iostream>

using namespace std;

void shell_sort(int* arr, int n)
{
  int gap = n;
  while(gap > 1)
  {
    gap = gap/3+1;
    for(int i = 0; i < n-gap; ++i)
    {
      int end = i;
      int tmp = arr[end+gap];
      while(end >= 0 && tmp < arr[end])
      {
        arr[end+gap] = arr[end];
        end = end-gap;
      }
      arr[end+gap] = tmp;
    }
  }
}
int main()
{
  int a[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  shell_sort(a,sizeof(a)/sizeof(a[0]));
  for(int i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
  {
    cout<<a[i]<<" ";
  }
  return 0;
}
