//Daytime_client.c
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<signal.h>
#include<sys/types.h>
#include<netdb.h>
#include<time.h>
int main(int argc,char **argv)
{
system("clear");
int n,sfd,connfd;
time_t ticks;
char buff[200];
printf("Lets start Daytime Client \n");
printf("Hello World\n");
struct addrinfo hints,*res,*ressave;bzero(&hints,sizeof(hints));
hints.ai_flags=AI_PASSIVE;
hints.ai_socktype=SOCK_STREAM;
hints.ai_family=AF_UNSPEC;
n=getaddrinfo(NULL,"daytime",&hints,&res);
if(n==0)
{
printf("SUCCESSFULLY RETURN\n");
}
else
{
printf("ERROR IN GETADDRINFO\n");
exit(0);
}
ressave=res;
do
{
sfd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
if(sfd < 0)
{
continue;
}
n = bind(sfd,res->ai_addr,res->ai_addrlen);if(n == 0)
{
printf("SUCCESSFULLY BIND\n");
break;
}
close(sfd);
}
while((res=res->ai_next)!=NULL);
if(res==NULL)
{
printf("ERROR, NO ENTRY GET SUCCESS TO BIND\n");
exit(0);
}
ticks=time(NULL);
snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
printf("%s",buff);
listen(sfd,15);
freeaddrinfo(ressave);
for(;;)
{
connfd=accept(sfd,NULL,NULL);ticks=time(NULL);
snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
printf("%s",buff);
write(connfd,buff,strlen(buff));
close(connfd);
}
}
