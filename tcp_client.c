
// Nawaf
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
// Find Header Files and Put them here
// For example, #include <stdio.h>
// Please Add your remark at the ends of lines, line by line
#define BUF_SIZE 1024
int main(int argc, char *argv[])
{
    int sock;
    char message[BUF_SIZE];
    int str_len;
    struct sockaddr_in serv_adr;
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("failed socket");
    }
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
    {
        printf("failed to connect");
    }
    else
        printf("Message from server: Hello\n");

    while (1)
    {
        fputs("\nInput message: ", stdout);
        fgets(message, BUF_SIZE, stdin);
        write(sock, message, strlen(message));
        str_len = read(sock, message, BUF_SIZE - 1);
        message[str_len] = 0;
        printf("\nMessage from server: %s", message);
    }

    close(sock);
    return 0;
}
