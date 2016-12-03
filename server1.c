#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#define FNAME_LEN 100
int main()
{	int fd;
        int server_sockfd,client_sockfd;
        int server_len,client_len;
        struct sockaddr_in server_address;
        struct sockaddr_in client_address;
	char ch;
	char file_name[FNAME_LEN];
	memset((void *)file_name,0,(size_t)FNAME_LEN);

        server_sockfd=socket(AF_INET,SOCK_STREAM,0);
        server_address.sin_family=AF_INET;
        server_address.sin_addr.s_addr=inet_addr("10.42.0.1");
        server_address.sin_port=9734;
        server_len=sizeof(server_address);
        bind(server_sockfd, (struct sockaddr *)&server_address,server_len);
        listen(server_sockfd,5);


  while(1)
{	
      	
        printf("server waiting\n");
        client_len=sizeof(client_address);
        client_sockfd= accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);
        read(client_sockfd,(void *)&file_name,FNAME_LEN);
	fd=open("file1",O_RDONLY);
	while(read(fd,&ch,1)&& ch!=EOF)
{
	write(client_sockfd,&ch,1);
	printf("%c",ch);
}
        
        write(client_sockfd,&ch,1);
        close(fd);
	
	close(client_sockfd);

}
}

