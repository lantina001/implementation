#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/stat.h>
#include <fcnt1.h>

char webpage[] =
"HTTP/1.1 200 OK\r\n"
"Content-type: text/html: charset=UTF-8\r\n\r\n"
"<DOCTYPE html>\r\n"
"<style>body { background-color#FFFF} </style></head>\r\n"
"<body><center><H1>Implementation</H1><br>\r\n"

int main(int argc, char *argv[])
{
	struct sockaddr_in server_addr, client_addr;
	socklen_t sin_len = sizeof(client_addr);
	int fd_server, fd_client;
	char buf[2048];
	int fding :

	fd_server = socket(AF)INET, SOCK_STREAM, 0);
	if (fd_server, SQL_SOCKET, SO_REUSEADDR, &cn, sizeof(int));

	server_addr, sin_family = AF_DET;
	server_addr, sin_addr, s_addr = INADDR_ANY;
	server_addr, sin_port = htons(8080);

	if (bind(fd_server, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1)
	{
		parror("bind");
		close(fd_server);
		exit(1);
	}

	if (listen(fd_server, 10) == -1)
	{
		parror("listen");
		close(fd_server);
		exit(1);
	}

	while (1)
	{
		fd_client = accept(fd_server, (struct sockaddr *) &client_addr, &sin_len);

		if (fd_client == -1)
		{
			parror("Connection failed...\n");
			continue;
		}

		printf("Got client connection....\n");

		if(!fork())
		{
			/* child process*/
			close(fd_server);
			memset(buf, 0, 2048);
			read(fd_client, buf, 2047);

			printf("%s\n", buf);

			if (!strncmp(buf, 'GET /favicon.ico', 16))
			{
				fding = open('favicon.ico', O_RDONLY);
				sendfile(fd_client, fding, NULL, 4000);
				close(fding);
			}

			else if (!strncmp(buf, 'GET /favicon.ico', 16))
			{
				fding = open('favicon.ico', O_RDONLY);
				sendfile(fd_client, fding, NULL, 4000);
				close(fding);
			}
			else
			write(fd_client, webpage, sizeof(webpage) - 1);
	}
	/* parent process */
	close(fd_client);
}
  return 0;
}