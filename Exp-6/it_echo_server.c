#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<arpa/inet.h>

void str_echo(int connfd)
{
	int n;
	int bufsize=1024;
	char *buffer=malloc(bufsize);
	do
	{
		while((n=recv(connfd, buffer, bufsize, 0))>0)
		{
			send(connfd, buffer, n, 0);
			//fputs(buffer,stdout);
			//printf("Port: %d\n",port);
		}
	}while(n<0);
}

int main()
{
  	int cont,listenfd,connfd,addrlen,addrlen2,fd,pid,addrlen3;
  
  	//char fname[256];
  	struct sockaddr_in address,cli_address;
  	if ((listenfd = socket(AF_INET,SOCK_STREAM,0)) > 0) 
    		printf("Socket has been created\n");
    	address.sin_family = AF_INET;
    	address.sin_addr.s_addr = INADDR_ANY;
    	address.sin_port = htons(15001);
	printf("Address before bind is %s.\n",inet_ntoa(address.sin_addr) );
    	if (bind(listenfd,(struct sockaddr *)&address,sizeof(address)) == 0)
    		printf("Binding Socket\n");
	printf("Address after bind is %s.\n",inet_ntoa(address.sin_addr) ); 
  
    	listen(listenfd,3);
     	printf("Server is listening.\n");

	for(;;){
    		addrlen = sizeof(struct sockaddr_in);
    		connfd = accept(listenfd,(struct sockaddr *)&cli_address,&addrlen);
		/*if(connfd>0)
			printf("The client is connected\n");*/
            	printf("Client  %s is connected via Port %d\n",inet_ntoa(cli_address.sin_addr),htons(cli_address.sin_port));	
   
	   	str_echo(connfd);
		close(connfd);
	}
    	return 0 ;
}

