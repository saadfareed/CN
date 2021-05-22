#include <arpa/inet.h>
#include <ctype.h>
int inet_aton(const char *cp, struct in_addr *inp);
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
int main(int argc, char** argv)
{
/* client */
int sockfd, n;
char buff[50];
sockfd = socket(AF_INET, SOCK_STREAM, 0);
printf("\n client has socketfd=%d",sockfd);
struct sockaddr_in myaddr , servaddr;
bzero(&myaddr, sizeof(myaddr));
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family= AF_INET;
servaddr.sin_port= htons(atoi(argv[1]));
int j= inet_aton("argv[2]",&servaddr.sin_addr);
myaddr.sin_family= AF_INET;
//specifing ip-address & port for client
printf("\nSpecify local IP-Address\n");
scanf("%s", &myaddr.sin_addr);
//printf("%s",&myaddr.sin_addr);
printf("\n specify local port\n");
scanf("%d",&myaddr.sin_port);
//printf("%d",myaddr.sin_port);
bind(sockfd,(struct sockaddr*) &myaddr, sizeof(myaddr));
int connfd= connect(sockfd,(const struct sockaddr*) &servaddr, sizeof(servaddr));
printf("\n after connect connfd=%d", connfd);
while((n = read(sockfd, buff, 50))>0)
{
buff[n]=0;
}
printf("The message from Server is\n %s",buff);
printf("\nMessage in uppercase is ");
int i;
for(i=0; buff[i]; i++)
buff[i] = toupper(buff[i]);
return 0;
}
