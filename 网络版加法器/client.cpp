#include"com.h"

int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    usage(argv[0]);
    exit(1);
  }

  //创建套接字
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock < 0)
  {
    perror("socket");
    exit(2);
  }

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(argv[1]);
  server.sin_port = htons(atoi(argv[2]));

  if(connect(sock,(struct sockaddr*)&server, sizeof(server)) < 0)
  {
    perror("connect");
    return 3;
  }
  
  cout<<"连接成功"<<endl;

  char buf[MAXSIZE];
  request r;
  response q;
  while(1)
  {
    //cout<<"请输入两个数："<<endl;
    printf("请输入两个数：");
    fflush(stdout);
    //cin>>r.num1>>r.num2;
    scanf("%d%d",&r.num1,&r.num2);
    write(sock,(void*)&r, sizeof(r));

    read(sock, &q, sizeof(q));
    cout<<r.num1<<"+"<<r.num2<<"="<<q.sum<<endl;

  }
  close(sock);
  return 0;
}
