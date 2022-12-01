
// Nawaf
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>
// Find Header Files and Put them here
// For example, #include <stdio.h>
// Please Add your remark at the ends of lines, line by line
#define BUF_SIZE 1024
void make_upper(char *message)
{
    int length = strlen(message);
    for (int i = 0; i < length; i++)
        message[i] = toupper(message[i]);
}
int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    char message[BUF_SIZE];
    int str_len, i;
    struct sockaddr_in serv_adr;
    struct sockaddr_in clnt_adr;
    socklen_t clnt_adr_sz;
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
    {
        printf("socket error");
    }
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
    {
        printf("bind error");
    }
    if (listen(serv_sock, 5) == -1)
    {
        printf("listen error");
    }
    clnt_adr_sz = sizeof(clnt_adr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &clnt_adr_sz);
    if (clnt_sock == -1)
    {
        printf("accept error");
    }
    else
        printf("client connected\n");

    str_len = read(clnt_sock, message, BUF_SIZE);
    while (1)
    {
        fputs("\nInput message: ", stdout);
        fgets(message, BUF_SIZE, stdin);
        write(clnt_sock, message, strlen(message));
        str_len = read(clnt_sock, message, BUF_SIZE - 1);
        message[str_len] = 0;
        make_upper(message);
        printf("\nMessage from client: %s", message);
    }

    close(serv_sock);
    return 0;
}
