#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include "server.h"


void socket_server_buildup(void)
{
	int rc ,i;
    int connfd = 0, n = 0, listenfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;

    char charBuff[1024];
    char recvBuff[1024];

    char namebuffer[100];

    // init the data structure of serv_addr
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(charBuff  ,'\0', sizeof(charBuff ));
    memset(recvBuff  ,'\0', sizeof(recvBuff ));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SOCKET_PORT);
	
    // assign the scket port to socket
    rc = bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(rc == -1)
    {
    	printf("bad bind.\n");
    	close(listenfd);
    	exit(1);
    }

    listen(listenfd, 20);
    printf("======waiting for client's request======\n");

    while (1)
    {
    	connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
       
    	printf("%s %d \n", "server: connfd is", connfd);
        
          
        while ( (n = read(connfd, recvBuff, sizeof(recvBuff)-1)) > 0)
        {
        	recvBuff[n] = 0;
        	if
        	{
        		
        	}
        	


        	/*
	        recvBuff[n] = 0;
            printf("server: read %d bytes \n", n);
            printf("%s\n",recvBuff);

            rc = write(connfd, recvBuff, strlen(recvBuff));
            if(rc > 0)
            {printf(" send data [%d] bytes.\n",rc );}
            else if(rc < 0)
            {printf(" send data failed.\n");}
            */
	   }
        if (n < 0)
        {printf("Error : read errpr \n");}   


         

        close(connfd);
        sleep(1); 
    }
    close(listenfd);

}


