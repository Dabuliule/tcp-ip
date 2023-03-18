#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message); // 函数声明：用于打印错误信息并退出程序

int main(int argc, char *argv[])
{
    int serv_sock; // 服务器socket文件描述符
    int clnt_sock; // 客户端socket文件描述符

    struct sockaddr_in serv_addr; // 服务器地址结构体
    struct sockaddr_in clnt_addr; // 客户端地址结构体
    socklen_t clnt_addr_size;     // 客户端地址结构体大小

    char message[] = "hello world!"; // 消息字符串

    if (argc != 2) // 检查参数个数是否正确
    {
        printf("Usage: %s <port>\n", argv[0]); // 打印使用说明
        exit(1);                               // 退出程序
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // 创建socket
    if (serv_sock == -1)                         // 如果创建失败
        error_handling("socket() error");        // 打印错误信息并退出程序

    memset(&serv_addr, 0, sizeof(serv_addr));      // 将服务器地址结构体清零
    serv_addr.sin_family = AF_INET;                // 设置地址族为IPv4
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 将IP地址设为INADDR_ANY，表示接受来自任何IP的连接
    serv_addr.sin_port = htons(atoi(argv[1]));     // 设置端口号

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) // 将socket与地址绑定
        error_handling("bind() error");                                    // 打印错误信息并退出程序

    if (listen(serv_sock, 5) == -1)       // 开始监听连接请求
        error_handling("listen() error"); // 打印错误信息并退出程序

    clnt_addr_size = sizeof(clnt_addr);                                            // 获取客户端地址结构体大小
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size); // 接受连接请求
    if (clnt_sock == -1)                                                           // 如果接受失败
        error_handling("accept() error");                                          // 打印错误信息并退出程序

    write(clnt_sock, message, sizeof(message)); // 向客户端发送消息
    close(clnt_sock);                           // 关闭客户端socket
    close(serv_sock);                           // 关闭服务器socket

    return 0; // 退出程序
}

void error_handling(char *message)
{
    fputs(message, stderr); // 打印错误信息到标准错误输出
    fputc('\n', stderr);    // 换行
    exit(1);                // 退出程序
}
