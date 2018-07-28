#include<stdio.h>
#include<iostream>

using namespace std;

int partion(int* a, int left, int right)
{
  int k = left;
  int begin = left;
  int end = right;
  while(begin < end)
  {
    while(begin < end && a[end] >= a[k])
      --end;
    while(begin < end && a[begin] <= a[k])
      ++begin;
    swap(a[begin], a[end]);
  }
  if(begin == end)
    swap(a[begin], a[k]);
  return begin;
}

void quick_sort(int *a, int begin, int end)
{
  if(end <= begin)
    return;
  int index = partion(a, begin, end);
  quick_sort(a, begin, index-1);
  quick_sort(a, index+1, end);
}

int main()
{
  int a[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  quick_sort(a, 0, 9);
  for(int i = 0; i < 10; ++i)
  {
    cout<<a[i]<<" ";
  }
  return 0;
}
