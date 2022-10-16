// 学习30天cpp服务器学习代码
// auther: SimpleAstronaut
// time: 2022-10-16

#include <sys/socket.h>
#include <arpa/inet.h>  //这个头文件包含了<netinet/in.h>，不用再次包含了

int main(){

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  // AF_INET:地址类型
  // SOCK_STREAM:数据传输方式，SOCK_STREAM表示流格式、面向连接，多用于TCP。SOCK_DGRAM表示数据报格式、无连接，多用于UDP。
  // 0:数据传输方式，SOCK_STREAM表示流格式、面向连接，多用于TCP。SOCK_DGRAM表示数据报格式、无连接，多用于UDP。

  struct sockaddr_in serv_addr;
  //对于客户端，服务器存在的唯一标识是一个IP地址和端口，这时候我们需要将这个套接字绑定到一个IP地址和端口上。首先创建一个sockaddr_in结构体
  bzero(&serv_addr, sizeof(serv_addr));
}
