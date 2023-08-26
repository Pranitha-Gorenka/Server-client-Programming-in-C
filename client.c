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

#define DEBUG

int port;

void Read_Options(int, char**);
int main(int argc, char *argv[]){

Read_Options(argc, argv);
	int tcpsock;
	char *Destport=argv[4];
	char *Desthost=argv[2];
	
	// *Desthost now points to a sting holding whatever came before the delimiter, ':'.
	// *Destport points to whatever string came after the delimiter. 

	port=atoi(Destport);
	#ifdef DEBUG 
		printf("\nHost %s, and port %d.\n",Desthost,port);
	#endif
	tcpsock = socket(AF_INET, SOCK_STREAM, 0);
	if (tcpsock < 0) {
		printf("Cannot create socket");
		return 0;
	}
	
	 // Client socket structure
    struct sockaddr_in cliAddr;
 
    // char array to store incoming message
    char buffer[2048];
 
  // Initializing socket structure with NULL
    memset(&cliAddr, '\0', sizeof(cliAddr));
 
    // Initializing buffer array with NULL
    memset(buffer, '\0', sizeof(buffer));
	struct sockaddr_in addr;
	
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr= inet_addr(Desthost);
	

	//socketconnection to socket address and client 
	int create = connect(tcpsock, (struct sockaddr*)&addr, sizeof(addr));
	if(create < 0) {
		return 0;
	}
	
	printf("connected to server\n");
	while (1)
	{
	printf("\nEnter the command for the server: ");
	char command[4096];
	scanf("%[^\n]",command);
	getchar();
	write(tcpsock, command, sizeof(command));
     printf("sending command to the server : %s\n",command);

    // Receive the file from the server
    
    int bytes_received = recv(tcpsock, buffer, sizeof(buffer), 0);
    if (bytes_received > 0) {
        printf("\nReceived solution from server is : %s\n", buffer);
        
    } else if (bytes_received == -1) {
        perror("recv error");
        exit(EXIT_FAILURE);
    }
    }
    close(tcpsock);
    return 0;
	}
	
	
	
void Read_Options(int argc, char** argv)
{
    char* prog;

    prog = *argv;
    while (++argv, --argc > 0)
        if (**argv == '-')
            switch (*++ * argv) {
            case 'i':
                if((*++ * argv) == 'p'){
                    --argc;
                }                
                break;
            case 'p':
                --argc;
               port= atoi(*++argv);
                break;
            case 'h':
                printf("\nHELP: try clientmatrix -p \n\n");
                exit(0);
                break;
                default:
                printf("%s: ignored option: -%s\n", prog, *argv);
                printf("HELP: try %s -u \n\n", prog);
                break;
            }
}

	

 

