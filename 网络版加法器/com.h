# pragma once 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<pthread.h>
#include<unistd.h>

#define MAXSIZE 128

using namespace std;

struct request
{
    int num1;
    int num2;
};

struct response
{
    int sum;
};

static void usage(const char* proc)
{
  cout<<"Usage: "<<proc<<"[local_ip] [local_port] "<<endl;
}

