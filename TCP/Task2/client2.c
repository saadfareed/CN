#include<stdio.h>
#include <arpa/inet.h>
int inet_aton(const char *cp, struct in_addr *inp);
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#define MAXLINE 50
void str_cli(FILE* fp, int sockfd)
{
char sendline [MAXLINE], recvline [MAXLINE];
int n;
while (fgets(sendline, MAXLINE, fp) !=NULL)
{
write(sockfd,sendline,strlen(sendline));
if ((n=read(sockfd, recvline,MAXLINE)) == 0)
printf("\n str_cli:server terminated prematurely");
recvline [n]=0;
fputs(recvline,stdout);
}
}
int main(int argc, char** argv)
{
/* client */
int sockfd, n;char buff[50];
struct sockaddr_in myaddr;
bzero(&myaddr, sizeof(myaddr));
myaddr.sin_family= AF_INET;
myaddr.sin_port= htons(0);
inet_aton("INADDR_ANY",&myaddr.sin_addr);
printf("\n before connect in client");
//char *ipaddr= "172.168.9.53";
sockfd = socket(AF_INET, SOCK_STREAM, 0);
printf("\n client has %d",sockfd);
struct sockaddr_in servaddr;
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family= AF_INET;
servaddr.sin_port= htons(1024);
printf("\n before connect in client");
char *ipaddr= "172.168.9.53";
int i;
printf("\n client J has");
int j= inet_aton("127.0.0.1",&servaddr.sin_addr);
printf(" after aton J is %d ", j);
bind(sockfd,(struct sockaddr*) &myaddr, sizeof(myaddr));
int connfd= connect(sockfd,(const struct sockaddr*) &servaddr, sizeof(servaddr));
printf("\n after connect connfd %d", connfd);
//while((n = read(sockfd, buff, 50))>0)
//{
//buff[n]=0;
//}
str_cli(stdin, sockfd);
//printf("the input is\n %s",buff);
//printf("Hello sockfd %d", sockfd);
return 0;
}
