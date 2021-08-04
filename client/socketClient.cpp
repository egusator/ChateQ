#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

	int main(int argc, char *argv[]) {
	int sockfd = 0;
	int r = 0, s = 0;
	char recvBuff[1024];
	char sendBuff[1025];
	struct sockaddr_in serv_addr;

	if (argc != 3) {
		printf("\n Usage: %s <ip of server> <port> \n", argv[0]);
		return 1;
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Error : Could not create socket \n");
		return 1;
	}



	memset(&serv_addr, '\0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));

	if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
		printf("\n inet_pton error occured\n");
		return 1;
	}

	if (connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("\n Error : Connect Failed \n");
		return 1;
	}
	while (1) {
		memset(sendBuff, '\0', sizeof(sendBuff));
		int i = 0;
		char c;
		while ((c = getchar())!= '\n'){
			sendBuff[i++] = c;
		}
		if (strlen(sendBuff))
			s = send(sockfd, sendBuff, sizeof(sendBuff), 0);
		if (s < 0) break;

		memset(recvBuff, '\0', sizeof(recvBuff));
		r = recv(sockfd, recvBuff, sizeof(recvBuff) - 1, 0);
		if (r < 0) break;

		if (fputs(recvBuff, stdout) == EOF) {
			printf("\n Error : Fputs error\n");
			break;
		}

	}
	if (s < 0) {
		printf("\n Send error  \n");
	}

	if (r < 0) {
		printf("\n Read error \n");
	}

	return 0;
}
