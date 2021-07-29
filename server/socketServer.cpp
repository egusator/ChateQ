#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
int main()
{
    int sock, listener;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }

    int optval = 1;

    if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (void*)&optval, sizeof(int)) < 0){
        perror("setsockopt(SO_REUSEADDR) failed");
        exit(3);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    listen(listener, 1);


    while(1)
    {
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }

        while(1)
        {
            bytes_read = recv(sock, buf, 1024, 0);
            if(bytes_read <= 0) break;
            buf[bytes_read] = '\0';
            char sBuff[10240];
            sprintf(sBuff, "ECHO: %s", buf);
            printf("Recieved message: %s", buf);
            send(sock, sBuff, strlen(sBuff), 0);
            sleep(1);
        }

        close(sock);
    }

    return 0;
}
