
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
char s[500],c[500];
int connfd = 0;
pthread_t threads1, threads2;
void *reads(void *arg)
{	
		
		while(1)
		{
			read(connfd,c,500);	
			printf( "CLIENT SAID : %s\n",c);
		}
		return (NULL);	
}
void *writes(void *arg)
{
	while(1)
	{
		//printf("SERVER : ");		
		scanf("%s",s);
		write(connfd,s,500);	
	}
	return(NULL);
}
int main(int argc, char *argv[])
{
    int listenfd = 0;
    int *p;
    struct sockaddr_in serv_addr; 
    pthread_attr_t pthread_custom_attr1, pthread_custom_attr2;
    char sendBuff[1025];
   /* int temp;
    time_t ticks;*/ 
    pthread_attr_init(&pthread_custom_attr1);
    pthread_attr_init(&pthread_custom_attr2);
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 	
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
    listen(listenfd, 10); 
    while(1)
    {	
    	connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
   	printf("I am reading from client\n");
    	printf("client requested\n");	
	pthread_create(&threads1, &pthread_custom_attr1,&reads, (void *)(connfd));		
	pthread_create(&threads2, &pthread_custom_attr2,&writes, (void *)(connfd));	
	pthread_join(threads1,NULL);
	pthread_join(threads2,NULL);   
	close(connfd);
        sleep(1);     	
   }
	
}
