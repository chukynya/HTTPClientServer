/* Creates a datagram server.  The port 
   number is passed as an argument.  This
   server runs forever */

#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
       fprintf(stderr, "ERROR, no port provided\n");
       exit(0);
    }
    
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) error("Opening socket");

    struct sockaddr_in server = {
        .sin_family         = AF_INET,
        .sin_addr.s_addr    = INADDR_ANY,
        .sin_port           = htons(atoi(argv[1]))
    };
    int length = sizeof(server);
    if (bind(sock,(struct sockaddr *)&server,length)<0) error("binding");

    struct sockaddr_in from;
    socklen_t fromlen = sizeof(struct sockaddr_in);
    ssize_t n;
    char buf[1024];

    while (1) {
        n = recvfrom(sock,buf,1024,0,(struct sockaddr *)&from,&fromlen);
        if (n < 0) error("recvfrom");
        write(1,"Received a datagram: ",21);
        write(1,buf,n);
        n = sendto(sock,"Got your message\n",17,0,(struct sockaddr *)&from,fromlen);
        if (n  < 0) error("sendto");
    }
    return 0;
 }


