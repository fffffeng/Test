#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<iostream>
using namespace std;

//实现一个简易版本的shell,支持重定向功能

char* argv[8];
int argc = 0;

void do_parse(char* buf)
{
  int i = 0;
  int status = 0;
  for(argc = i = 0; buf[i]; ++i)
  {
    if( !isspace(buf[i]) && status == 0)
    {
      argv[argc++] = buf + i;
      status = 1; 
    }
    else if(isspace(buf[i]))
    {
      status = 0;
      buf[i] = 0;
    }
  }
    argv[argc] = NULL;
}
void do_exec(void)
{
  pid_t pid = fork();
  switch(pid)
  {
    case -1:
      perror("fork");
      exit(EXIT_FAILURE);//程序异常退出
      break;
    case 0:
      //寻找重定向>符号
      for(int i = 0; argv[i]!=NULL; ++i)
      {
        if(strcmp(argv[i],">") == 0)
        {
          if(i+1<8 && argv[i+1] == NULL) //检查重定向>后面是否有文件名
          {
            perror("command '>' [option]?");
            exit(1);
          }
          argv[i] = NULL;//将 > 符号换位空字符创
          int fd = open(argv[i+1], O_RDWR | O_CREAT | O_TRUNC, 0664);
          if(fd < 0)
          {
            perror("open");
            exit(1);
          }
          dup2(fd, 1);//将本应写到stdout的文件写到文件描述符为fd的文件里
          close(fd);
        }
      }
      execvp(argv[0],argv);//成功没有返回值，失败返回-1
      perror("execvp");
      exit(EXIT_FAILURE);
    default:
      {
        int st;
        while(wait(&st) != pid)
        {}
      }
  }
}

int main()
{

  char buf[1024];
  while(1)
  {
    cout<<"myshell >";
    scanf("%[^\n]%*c",buf);
    do_parse(buf);
    do_exec();
  }
    return 0;
}
