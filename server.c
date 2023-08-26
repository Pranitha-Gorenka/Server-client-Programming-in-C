#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/stat.h>

#include "../include/formula.h"

void handle_connection(int client_sock,int id) {
while (1)
{
char command[4096];

    int bytes_received = recv(client_sock, command, sizeof(command), 0);
    if (bytes_received > 0) {
        fprintf(stderr, "\nclient command received is %s\n", command);
    } else if (bytes_received == -1 ) {
        perror("recv error");
        exit(EXIT_FAILURE);
    }
if (strcmp(command,"./kmeans")==0)
{
char filename[256];
 mkdir("../computedresults",S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) ;
snprintf(filename, sizeof(filename),"../computedresults/kmeans_%d.txt",id++);

FILE *fp=fopen(filename,"w");
if (fp == NULL) {
        perror("Cannot open the file");
        exit(EXIT_FAILURE);
    }
    if (freopen(filename,"w",stdout)== NULL)
    {
    perror("cannot redirect stdout");
    exit(EXIT_FAILURE);
    }
system(command);
fclose(fp);
if (freopen("/dev/tty","w",stdout) == NULL){
    perror("cannot restore stdout");
     exit(EXIT_FAILURE);
     }
if(send(client_sock,&filename,sizeof(filename),0)>0){
fprintf(stderr,"sending solution to client : %s\n",filename);
}  
}
    
if(strcmp(command,"./kmeans")!=0)
{
char filename[256];
mkdir("../computedresults",S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
sprintf(filename, "../computedresults/matrixoutput_%d.txt",id++);
FILE *fs=fopen(filename,"w");
if (fs == NULL) {
        perror("Cannot open the file");
        exit(EXIT_FAILURE);
    }
    if (freopen(filename,"w",stdout)== NULL)
    {
    perror("cannot redirect stdout");
    exit(EXIT_FAILURE);
    }
    if (freopen("/dev/null","r",stdin) == NULL){
    perror("cannot redirect stdin");
     exit(EXIT_FAILURE);
     }
system(command);
fclose(fs);
if (freopen("/dev/tty","w",stdout) == NULL){
    perror("cannot restore stdout");
     exit(EXIT_FAILURE);
     }
if (freopen("/dev/tty","r",stdin) == NULL){
    perror("cannot restore stdin");
     exit(EXIT_FAILURE);
     }
if(send(client_sock,&filename,sizeof(filename),0)>0){
fprintf(stderr,"sending solution: %s\n",filename);
}  		
}


}
}

int main(int argc, char *argv[]){
  
  /*
    Read first input, assumes <ip>:<port> syntax, convert into one string (Desthost) and one integer (port). 
     Atm, works only on dotted notation, i.e. IPv4 and DNS. IPv6 does not work if its using ':'. 
  */
  
  
  int port=9999;
  int n,server_sock,client_sock;
  socklen_t clientAddrlength;
  struct sockaddr_in serverAddr;
  struct hostent *server;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
  
server_sock=socket(AF_INET,SOCK_STREAM,0);
if(server_sock<0){
perror("socket error");
exit(1);
}
printf("server socket created\n");
server=gethostbyname(argv[1]);
if(server==NULL)
{
fprintf(stderr,"error,no such host\n");
exit(1);
}	

n=bind(server_sock,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
if(n<0)
{
perror("bind error\n");
exit(1);
}
printf("binding to the port :%d\n",port);


listen(server_sock,5);
printf("listening for clients\n");
struct sockaddr_in clientAddr;
clientAddrlength=sizeof(clientAddr);
int client_id;
while(1)
{
client_sock=accept(server_sock, (struct sockaddr*)&clientAddr,&clientAddrlength);
if(client_sock < 0) {
		return 0;
	}
	
printf("\nclient connected with %d\n",client_id++);
int pid;
pid =fork();
   if(pid == 0)//child process rec and send
     {
handle_connection(client_sock,client_id);
}
}
close(client_sock);
return 0;
}



