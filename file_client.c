#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#define BUF_SIZE 100

void error_handling(char *message);
int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[100];
	int str_len;
	int in;
	int buffer[100];
	int read_cnt;
	if(argc!=4){
		printf("Usage : %s <IP> <port> <file>\n", argv[0]);
		exit(1);
	}

    in = open(argv[3], O_RDONLY);
    if (in < 0) {
  	  printf("%s file open error\n", argv[3]);
      perror("open");
      exit(1);
    }

	sock=socket(PF_INET, SOCK_STREAM, 0);
	if(sock < 0)
		error_handling("socket() error");
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
	
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        error_handling("connect() error");

    while ((read_cnt = read(in, buffer, BUF_SIZE)) > 0) {
        write(sock, buffer, read_cnt);
    }

	printf("Done...\n");  

    close(in);
    close(sock);

    return 0;
    }



void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
