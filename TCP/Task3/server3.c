#include <unistd.h> 
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
void str_echo(int sockfd)
{
char buff[50];
printf("\n Enter the message for client \n");
scanf("%s",buff);
write(sockfd,buff, strlen(buff));
return;
}
int main(int argc, char** argv)
{
int listenfd, connfd;
struct sockaddr_in servaddr, cliaddr;
pid_t childpid;
listenfd = socket(AF_INET, SOCK_STREAM, 0);
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family= AF_INET;
servaddr.sin_port= htons(atoi(argv[1]));
int j= inet_aton("argv[2]",&servaddr.sin_addr);
bind(listenfd,(const struct sockaddr*)&servaddr, sizeof(servaddr));
listen(listenfd, atoi(argv[3]));
for(;;)
{
printf("hello");
printf("\n hello.0000000");
socklen_t siz=sizeof(cliaddr);
connfd= accept(listenfd, (struct sockaddr*)&cliaddr, &siz);
printf("\n connection is established with the client at");
printf("\n IP= %s", inet_ntoa(cliaddr.sin_addr));
printf("\n and port_no= %d",ntohs(cliaddr.sin_port));
if ((childpid=fork())==0)
{
close(listenfd);
str_echo (connfd);
close(connfd);
exit(0);
}
close(connfd);
}
return 0;
}
