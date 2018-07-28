#include<stdio.h>
#include<iostream>

using namespace std;

void selection_sort(int *a, int left, int right)
{
  if(right <= left)
    return;
  int begin = left;
  int end = right-1;
  
  while(begin < end)
  {
    int max = a[begin];
    int min = a[end];
    for(int i = begin; i <= end; ++i)
    {
      if(a[i] > a[max])
        max = i;
      if(a[i] < a[min])
        min = i;
    }
    swap(a[min], a[begin]);
    if(max == begin)//如果最大值是begin这个位置，上面交换后，最小值到begin位置，而最大值换到了min的位置
      max = min;
    swap(a[max], a[end]);

    ++begin;
    --end;
  }

}

int main()
{
  int a[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  selection_sort(a, 0, 10);
  for(int i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
  {
    cout<<a[i]<<" ";
  }
  cout<<endl;
  return 0;
}
