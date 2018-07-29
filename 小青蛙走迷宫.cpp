#include<stdio.h>
#include<vector>

#include<iostream>
using namespace std;


struct Node
{
  int x;
  int y;
};

int n,m,p,step = 999999;
vector<Node> res;//保存最优路径
int a[10][10];
bool is_visit[10][10] = { false };//标记走过的位置（true:已经走过；false:还没走过）

void findpath(vector<Node>& tmp, int energy, int i, int j)
{
  if(i == 0 && j == m-1)//走到了出口处
  {
    if(energy < p && energy < step)//判断改路径是否比上条路径更好（即比较消耗的能量）
    {
      step = energy;
      res = tmp;
    }
    return;
  }
  //上 
  if(i-1 >= 0 && a[i-1][j]== 1 && is_visit[i-1][j]==false)
  {
    energy += 3;
    Node node;
    node.x = i-1;
    node.y = j;
    tmp.push_back(node);
    is_visit[i-1][j] = true;
    findpath(tmp, energy, i-1, j);
    energy -= 3;
    tmp.pop_back();
    is_visit[i-1][j] =false;
  }
  //右
  if(j+1 < m && a[i][j+1] == 1 && is_visit[i][j+1] == false)
  {
    energy += 1;
    Node node;
    node.x = i;
    node.y = j+1;
    tmp.push_back(node);
    is_visit[i][j+1] = true;
    findpath(tmp, energy, i, j+1);
    energy -= 1;
    tmp.pop_back();
    is_visit[i][j+1] =false;
  }
  //下
  if(i+1 < n && a[i+1][j] == 1 && is_visit[i+1][j] == false)
  {
    energy += 0;
    Node node;
    node.x = i+1;
    node.y = j;
    tmp.push_back(node);
    is_visit[i+1][j] = true;
    findpath(tmp, energy, i+1, j);
    energy -= 0;
    tmp.pop_back();
    is_visit[i+1][j] = false;
  }
  //左
  if(j-1 >= 0 && a[i][j-1] == 1 && is_visit[i][j-1] == false)
  {
    energy += 1;
    Node node;
    node.x = i;
    node.y = j-1;
    tmp.push_back(node);
    is_visit[i][j-1] = true;
    findpath(tmp, energy, i, j-1);
    energy -= 1;
    tmp.pop_back();
    is_visit[i][j-1] = false;
  }
}

int main()
{

  cin>>n>>m>>p;
  for(int i = 0; i < n; ++i)
  {
    for(int j = 0; j < m; ++j)
      cin>>a[i][j];
  }

  vector<Node> tmp;
  int energy = 0;
  Node node;
  node.x = 0;
  node.y = 0;
  tmp.push_back(node);//将起点保存
  is_visit[0][0] = true;

  findpath(tmp, energy, 0, 0);

  if(step == 999999)
    cout<<"没有出路！";
  else 
  {
    int i = 0;
    for(i = 0; i < res.size()-1; ++i)
    {
      cout<<"["<<res[i].x<<","<<res[i].y<<"]"<<",";
    }
    cout<<"["<<res[i].x<<","<<res[i].y<<"]";
    cout<<endl;
  }

  return 0;
}

