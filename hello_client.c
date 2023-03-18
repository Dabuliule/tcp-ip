#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message); // 函数声明：用于打印错误信息并退出程序

int main(int argc, char *argv[])
{
    int sock; // 定义socket描述符

    struct sockaddr_in serv_addr; // 定义服务器地址结构体
    char message[30];             // 定义用于存放接收消息的缓冲区
    int str_len;                  // 定义用于存放接收消息的长度

    if (argc != 3) // 检查参数个数是否正确
    {
        printf("Usage: %s <IP> <port>\n", argv[0]); // 打印使用说明
        exit(1);                                    // 退出程序
    }

    sock = socket(PF_INET, SOCK_STREAM, 0); // 创建socket
    if (sock == -1)                         // 如果创建失败
        error_handling("socket() error");   // 打印错误信息并退出程序

    memset(&serv_addr, 0, sizeof(serv_addr));   // 将服务器地址结构体清零
    serv_addr.sin_family = AF_INET;             // 设置地址族为IPv4
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // 将IP地址设为用户指定的IP
    serv_addr.sin_port = htons(atoi(argv[2]));  // 设置端口号，将用户指定的字符串转换为整数

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) // 连接到指定的服务器
        error_handling("connect() error"); // 打印错误信息并退出程序

    str_len = read(sock, message, sizeof(message) - 1); // 从服务器接收消息
    if (str_len == -1)                                   // 如果接收失败
        error_handling("read() error");                  // 打印错误信息并退出程序

    message[str_len] = 0; // 在消息末尾添加空字符
    printf("Message from server: %s \n", message); // 打印接收到的消息
    close(sock); // 关闭socket

    return 0; // 退出程序
}

void error_handling(char *message)
{
    fputs(message, stderr); // 打印错误信息到标准错误输出
    fputc('\n', stderr);    // 换行
    exit(1);                // 退出程序
}
