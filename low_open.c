#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;
    char buf[] = "Let' go!\n";

    fd = open("data.txt", O_CREAT | O_WRONLY | O_TRUNC);
    if (fd == -1)
    {
        perror("open()");
        exit(EXIT_FAILURE);
    }

    printf("file descriptor: %d\n", fd);

    if (write(fd, buf, sizeof(buf)) == -1)
    {
        perror("write()");
        exit(EXIT_FAILURE);
    }

    close(fd);
    return 0;
}