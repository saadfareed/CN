#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#define MAXLINE 50
void str_echo(int sockfd)
{
ssize_t n;
char line [MAXLINE];
for(;;)
{
if ((n=read(sockfd,line,MAXLINE))==0)return;
write (sockfd,line,n);
}
}
int main(int argc, char** argv)
{
pid_t childpid;
int listenfd, connfd;
char buff1 [50];
struct sockaddr_in servaddr;
struct sockaddr_in cliaddr;
socklen_t siz=sizeof(cliaddr);
listenfd = socket(AF_INET, SOCK_STREAM, 0);
char buff[50]="I m a server";
printf("\nbefore bzero %d",listenfd);
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family= AF_INET;
printf("\nbefore bzero %d",listenfd);
servaddr.sin_port= htons(1024);
printf("\nbefore bzero %d",listenfd);
printf("\n before listenne");
//inet_pton(AF_INET,"127.0.0.1", &servaddr.sin_addr);
int j= inet_aton("127.0.0.1",&servaddr.sin_addr);
printf("J is %d ", j);
bind(listenfd,(const struct sockaddr*)&servaddr, sizeof(servaddr));
printf("\nbefore listen %d",listenfd);
listen(listenfd, 5);
for(;;)
{
printf("hello");
printf("\n hello.0000000");
connfd= accept(listenfd, (struct sockaddr*)&cliaddr, &siz);
if ((childpid=fork())==0)
{
close(listenfd);
str_echo (connfd);
close(connfd);
exit(0);
}
printf("\n after accept...");
printf("\nThe client IP is %s", inet_ntoa(cliaddr.sin_addr));
printf("\nThe client IP is %s", inet_ntop(AF_INET, &cliaddr.sin_addr,buff1,sizeof(buff1)));
printf("\nThe client IP is %s", buff1);
printf("\n client port no is %d",ntohs(cliaddr.sin_port));//write(connfd,buff, strlen(buff));
close(connfd);
//return 0;
}
return 0;
}
