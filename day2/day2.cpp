// 学习30天cpp服务器学习代码
// day2
// auther: SimpleAstronaut
// time: 2022-10-16

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "util.h"

int main(){

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  errif(sockfd == -1, "socket create error");
  //调用封装的异常处理函数
  //与day1的代码相同

  struct sockaddr_in serv_addr;
  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serv_addr.sin_port = htons(8888);

  errif(bind(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) == -1, "socket bind error");

  errif(listen(sockfd, SOMAXCONN) == -1, "socket listen error");

  struct sockaddr_in clnt_addr;
  socklen_t clnt_addr_len = sizeof(clnt_addr);
  bzero(&clnt_addr, sizeof(clnt_addr));

  int clnt_sockfd = accept(sockfd, (sockaddr*)&clnt_addr, &clnt_addr_len);
  errif(clnt_sockfd == -1, "socket accept error");

  printf("new client fd %d! IP: %s Port: %d\n", clnt_sockfd, inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));

  //作者注释:当我们建立一个socket连接后，就可以使用<unistd.h>头文件中read和write来进行网络接口的数据读写操作了。
  //这两个函数用于TCP连接。如果是UDP，需要使用sendto和recvfrom，这些函数的详细用法可以参考游双《Linux高性能服务器编程》第五章第八节。
  while (true) {
      char buf[1024];
      bzero(&buf, sizeof(buf));
      //定义信息缓冲区
      //使用bzero初始化缓冲区

      ssize_t read_bytes = read(clnt_sockfd, buf, sizeof(buf));
      //客户端socket读取到缓冲区，并获取信息长度

      if(read_bytes > 0){
          printf("message from client fd %d: %s\n", clnt_sockfd, buf);
          write(clnt_sockfd, buf, sizeof(buf));
          //调用write函数向客户端发送信息

      } else if(read_bytes == 0){
          //read返回0表示EOF
          printf("client fd %d disconnected\n", clnt_sockfd);
          close(clnt_sockfd);
          break;

      } else if(read_bytes == -1){
        //read返回-1，表示发生错误，按照上文方法进行错误处理
          close(clnt_sockfd);
          errif(true, "socket read error");
      }
  }
  close(sockfd);
  return 0;

}
