client.c 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include<netinet/in.h>
#include<netdb.h>
#define PORT 6490

int main()
{
	int len,i=0,sockfd;
	char buf1[20],buf2[20000];
	struct sockaddr_in their_addr;
	FILE* fp;
	if((sockfd=(socket(AF_INET,SOCK_STREAM,0)))==-1)
	{
		perror("socket");
		exit(1);
	}
	their_addr.sin_family=AF_INET;
	their_addr.sin_port = htons(PORT);
	their_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if(connect(sockfd,(struct sockaddr*)&their_addr,sizeof(struct sockaddr))==-1)
	{
		perror("connect");
		exit(1);
	}
	printf("client is online \n enter file to be displayed\n");
	scanf("%s",buf1);
	send(sockfd,buf1,sizeof(buf1),0);
	if((recv(sockfd,buf2,sizeof(buf2),0))==-1)	
	{
		perror("recv");
		exit(1);
	}
	else
	{
		printf("the contents of file are %s\n",buf1);
		printf("\n%s\n",buf2);
	}
	close(sockfd);
	return 0;
}

server.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#define MYPORT 6490
#define BACKLOG 10

int main()
{
	int i=0,sockfd,fp,new_fd,sin_size;
	char buf1[20],buf2[20000];
	struct sockaddr_in my_addr,their_addr;
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket");
		exit(1);
	}
	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons(MYPORT);
	my_addr.sin_addr.s_addr=INADDR_ANY;
	if((bind(sockfd,(struct sockaddr*)&my_addr,sizeof(struct sockaddr)))==-1)
	{
		perror("bind");
		exit(1);
	}
	if(listen(sockfd,BACKLOG)==-1)
	{
		perror("listen");
		exit(1);
	}
	printf("server is online\n");
	printf("waiting for client...\n");
	sin_size = sizeof(struct sockaddr_in);
	if((new_fd = accept(sockfd,(struct sockaddr*)&their_addr,&sin_size))==-1)
	{
		perror("accept");
		exit(1);
	}
	printf("server got connection from %s\n",inet_ntoa(their_addr.sin_addr));
	recv(new_fd,&buf1,sizeof(buf1),0);
	printf("requested file is %s\n",buf1);
	if((fp=open(buf1,O_RDONLY))<0)
	{	
		printf("no file found\n");
		strcpy(buf2,"no file found");
	}
	else
	{
		printf("server ready for transfer %s\n",buf1);
		read(fp,&buf2,20000);
		close(fp);
	}
	send(new_fd,&buf2,sizeof(buf2),0);
	printf("transfer success\n");
	close(new_fd);
	close(sockfd);
	return 0;
}
