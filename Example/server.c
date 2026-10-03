/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void dostuff(int);
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)  error("ERROR opening socket");
    
    // bzero((char *) &serv_addr, sizeof(serv_addr));
    int portno = atoi(argv[1]);
    struct sockaddr_in serv_addr = {
        .sin_family         = AF_INET,
        .sin_port           = htons(portno),
        .sin_addr.s_addr    = INADDR_ANY
    };
    if (bind(sockfd, (const struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
            error("ERROR on binding");
    listen(sockfd,5);
    
    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    while (1)
    {
        int newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) 
                error("ERROR on accept");
        pid_t pid = fork();
        if(pid < 0)
            error("ERROR on fork");
        if(pid == 0)
        {
            close(sockfd);
            dostuff(newsockfd);
            exit(0);
        }
        else
            close(newsockfd);
    }
    close(sockfd);
    return 0; 
}

void dostuff(int sock)
{
    char buffer[256];
    bzero(buffer, 256);

    ssize_t rwnum = read(sock, buffer, 255);
    if (rwnum < 0)
        error("ERROR reading from socket");
    printf("Here's the message: %s\n", buffer);
    rwnum = write(sock, "I got your message", 18);
    if(rwnum < 0)
        error("ERROR writing to socket");
}
