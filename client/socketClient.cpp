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
	int r = 0, s = 0, i = 0, f = 0;
	char buffer[1025];
	char name[1025];
	memset(name, '\0', 1025);
	struct sockaddr_in serv_addr;

	if (argc != 4) {
		printf("\n Usage: %s <ip of server> <port> <your name> \n", argv[0]);
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
	strcpy(name, argv[3]);

	send(sockfd, name, 1025, 0);

	while (1) {

		memset(buffer, '\0', 1025);
		recv(sockfd, buffer, 1025, 0);
		printf("\n %s \n", buffer);грац диджей плаг
		printf("%s(you):", name);

		memset(buffer, '\0', 1025);
		fgets(buffer, 1025, stdin);
		send(sockfd, buffer, 1025, 0);

	}
	if (s < 0) {
		printf("\n Send error  \n");
	}

	if (r < 0) {
		printf("\n Read error \n");
	}

	return 0;
}
