/* UDP client in the internet domain */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void error(const char *);
int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage: server port\n");
        exit(1);
    }

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) error("socket");

    struct sockaddr_in server = {
        .sin_family         = AF_INET,
        .sin_port           = htons(atoi(argv[2]))
    };

    struct hostent *hp = gethostbyname(argv[1]);
    if (hp==0) error("Unknown host");
    bcopy((char *)hp->h_addr_list[0], (char *)&server.sin_addr, hp->h_length);
    
    printf("Please enter the message: ");
    char buffer[256];
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    unsigned int length=sizeof(struct sockaddr_in);

    int n = sendto(sock,buffer,
                strlen(buffer),0,(const struct sockaddr *)&server,length);
    if (n < 0) error("Sendto");
    
    struct sockaddr_in from;
    n = recvfrom(sock,buffer,256,0,(struct sockaddr *)&from, &length);
    if (n < 0) error("recvfrom");
    write(1,"Got an ack: ",12);
    write(1,buffer,n);
    close(sock);
    return 0;
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

