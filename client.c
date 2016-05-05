/*
Function : Socket code for clinit
Arthur : SheldonRush Peng
Date : 2013/7/26
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "client.h"


int socket_clinit_main(int argc, char *argv[])
{
    int sockfd = 0, n = 0, i;
    char sendBuff[1024];
    char recvBuff[1024];
    char sendtest[]="get device info";


    struct sockaddr_in serv_addr;

    if (argc != 3)
    {
	printf("Usage : %s <Name> <command>\n", argv[0]);
	return 1;
    }
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
	   printf("Error : cannot create a socket\n"); 
        return 1;
    }
    memset(sendBuff, '\0', sizeof(sendBuff));
    memset(recvBuff, '\0', sizeof(recvBuff));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(Port);

    if (inet_pton(AF_INET, HostIp, &serv_addr.sin_addr) <= 0 )
    {
	   printf("%s \n" , " Error : cannot convert text to ip binary");
        return 1;
    }

    if ( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 )
    {
	   printf("Error : canot connect server\n");
        exit(1);
    }

    printf("Clinit: Send data to server, station id = [%s]\n", argv[1]);





    if (strcmp("info",argv[2]) == 0)
    {
        write(sockfd, "name",4);
        write(sockfd, Name, strlen(Name));
        write(sockfd, sendtest, strlen(sendtest));
    }
    else 
    {
        printf("wrong command\n");
        close(sockfd);
        exit(1);
    }
    

    n = read(sockfd, recvBuff, sizeof(recvBuff)-1); 
    if (n > 0)
    {
       recvBuff[n] = 0;
       printf("clinit: read %d bytes \n", n);
        {printf("%s\n",recvBuff);}
    }
    if (n < 0)
       {printf("Error : read errpr \n");}


    close(sockfd);

   return 0;
}

int main(int argc, char *argv[])
{  


    if (0 != socket_clinit_main(argc,argv))
    {
        printf("cannot call help \n");
        return 1;
    }

}
