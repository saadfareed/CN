#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 int main(int argc, char**argv)
{
int clientsocket;
struct sockaddr_in serverAddr;
char buffer[1024];

clientsocket=socket(PF_INET,SOCK_STREAM,0);
printf("Client Socket Created Successfully:\n");

memset(&serverAddr,'\0',sizeof(serverAddr));
serverAddr.sin_family=AF_INET;
serverAddr.sin_port=htons(4455);
serverAddr.sin_addr.s_addr=inet_addr("127.0.01");
connect(clientsocket,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
printf("Connecting to Server Successfully:\n ");

recv(clientsocket,buffer,1024,0);
printf("Data Recieved: %s", buffer );
exit(0);
}
