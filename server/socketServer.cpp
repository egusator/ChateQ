#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

    char sendBuff[1025];
    time_t ticks; 
	

    if(argc != 2)
    {
        printf("\n Usage: %s <port>\n", argv[0]);
        return 1;
    }
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1])); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 

    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
	int i = 0; char c; 

        while(i < strlen(sendBuff) && (c=getchar()) != '\n' && c != EOF)
		sendBuff[i++] = c;  
	for(;i<strlen(sendBuff);i++)
		sendBuff[i] = '\0';
        send(connfd, sendBuff, strlen(sendBuff), 0); 
	if (c == EOF) close(connfd);
	memset(sendBuff, '0', sizeof(sendBuff));
	 
	sleep(1);
     }
}
