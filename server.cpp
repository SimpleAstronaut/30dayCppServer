// 学习30天cpp服务器学习代码
// auther: SimpleAstronaut
// time: 2022-10-16

#include <sys/socket.h>
#include <arpa/inet.h>  //这个头文件包含了<netinet/in.h>，不用再次包含了
#include <string.h>

int main(){

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  // AF_INET:地址类型
  // SOCK_STREAM:数据传输方式，SOCK_STREAM表示流格式、面向连接，多用于TCP。SOCK_DGRAM表示数据报格式、无连接，多用于UDP。
  // 0:数据传输方式，SOCK_STREAM表示流格式、面向连接，多用于TCP。SOCK_DGRAM表示数据报格式、无连接，多用于UDP。

  struct sockaddr_in serv_addr;
  //对于客户端，服务器存在的唯一标识是一个IP地址和端口，这时候我们需要将这个套接字绑定到一个IP地址和端口上。首先创建一个sockaddr_in结构体
  bzero(&serv_addr, sizeof(serv_addr));
  //bzero初始化这个结构体,需要引用头文件<string.h>或<cstring>

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serv_addr.sin_port = htons(8888);
  //设置servaddr中的地址族、IP地址和端口
  //sin_family:地址类型
  //inet_addr:主机地址
  //htons:端口

  bind(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr));
  //绑定嵌套字
  //引用原作者文字: 为什么定义的时候使用专用socket地址（sockaddr_in）而绑定的时候要转化为通用socket地址（sockaddr），以及转化IP地址和端口号为网络字节序的inet_addr和htons等函数及其必要性，在游双《Linux高性能服务器编程》第五章第一节：socket地址API中有详细讨论。

  listen(sockfd, SOMAXCONN);
  //监听嵌套字
  //SOMAXCONN:最大监听队列长度，系统建议的最大值SOMAXCONN被定义为128

  struct sockaddr_in clnt_addr;
  socklen_t clnt_addr_len = sizeof(clnt_addr);
  bzero(&clnt_addr, sizeof(clnt_addr));
  //同理定义客户端对象
  //原作者注释:要注意和accept和bind的第三个参数有一点区别，对于bind只需要传入serv_addr的大小即可，而accept需要写入客户端socket长度，所以需要定义一个类型为socklen_t的变量，并传入这个变量的地址。另外，accept函数会阻塞当前程序，直到有一个客户端socket被接受后程序才会往下运行。

  int clnt_sockfd = accept(sockfd, (sockaddr*)&clnt_addr, &clnt_addr_len);
  printf("new client fd %d! IP: %s Port: %d\n", clnt_sockfd, inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));
  //要接受一个客户端连接，需要使用accept函数。对于每一个客户端，我们在接受连接时也需要保存客户端的socket地址信息

}
