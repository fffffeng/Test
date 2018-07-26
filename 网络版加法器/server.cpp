#include"com.h"

//*****服务器模块：利用TCP多线程计算客户端发过来的数****

struct net_info_t
{
    int sock;
    char ip[24];
    int port;
};

void service(int sock, char* ip, int port)
{
  while(1)
  {
    request r;
    ssize_t s  = read(sock, &r, sizeof(r));

    response p;
    p.sum = r.num1 + r.num2;
    write(sock, &p, sizeof(p));
  }
}

void* thread_server(void* arg)
{
  net_info_t* p = (net_info_t*)arg;
  service(p->sock, p->ip, p->port);

  close(p->sock);
  free(p);
}

int startup(int port,char* ip)
{
  //创建套接字
  int sock = socket(AF_INET,SOCK_STREAM,0);
  if(sock < 0)
  {
    perror("socket");
    exit(2);
  }


  //绑定
  struct sockaddr_in local;
  local.sin_family = AF_INET;
  local.sin_port = htons(port);
  local.sin_addr.s_addr = inet_addr(ip);

  if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0)
  {
    perror("bind");
    exit(3);
  }

  //监听
  if(listen(sock,10) < 0)  //最多有5个连接
  {
    perror("listen");
    exit(4);
  }
  return sock;
}


int main(int argc,char* argv[])
{
  if(argc != 3)
  {
    usage(argv[0]);
    exit(1);
  }
  //准备工作（创建套接字，监听，绑定）
  int listen_sock = startup(atoi(argv[2]),argv[1]);

  struct sockaddr_in peer;
  char ipbuf[24];
  while(1)
  {
    ipbuf[0] = 0;
    socklen_t len = sizeof(peer);

    //从监听套接字中取连接
    int new_sock = accept(listen_sock, (struct sockaddr*)&peer, &len);
    if(new_sock < 0)
    {
      cout<<"accept failed"<<endl;
      continue;
    }

    //到此处就获得了一个新连接
    inet_ntop(AF_INET, (const void*)&peer.sin_addr, ipbuf, sizeof(ipbuf));//将四字节ip转为点分十进制
    int port =ntohs(peer.sin_port);//获得端口号；网络字节序转为主机字节序
    cout<<"获取新连接："<<"ip:"<<ipbuf<<"port:"<<port<<endl;

    net_info_t* info = new net_info_t;
    info->sock = new_sock;
    strcpy(info->ip, ipbuf);
    info->port = port;

    pthread_t tid;
    pthread_create(&tid, NULL, thread_server, (void*)info);
    pthread_detach(tid);

  }
  return 0;
}
