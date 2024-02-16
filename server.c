#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <string.h>

#define CONNECTION_PORT 3500

int main(){
    int serverSock;
    int clientSocket;

    char storageBuffer[80];
    int addrLen;

    int optionValue = 1;

    struct sockaddr_in serverAddr;
    struct sockaddr_in connectionAddr;

    serverSock = socket(AF_INET, SOCK_STREAM, 0);

    if(serverSock < 0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    int status = setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, &optionValue, sizeof(optionValue));

    if(status < 0){
        perror("Couldn't set options");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(CONNECTION_PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

    status = bind(serverSock, (struct sockaddr *) &serverAddr, sizeof(struct sockaddr_in));

    if(status < 0){
        perror("Couldn't bind socket");
        exit(EXIT_FAILURE);
    }

    status = listen(serverSock, 4);

    if(status < 0){
        perror("Couldn't listen for connections");
        exit(EXIT_FAILURE);
    }

    addrLen = sizeof(connectionAddr);
    
    clientSocket = accept(serverSock, (struct sockaddr*)&connectionAddr, &addrLen);

    if(clientSocket < 0){
        perror("Couldn't establish connection with client");
        exit(EXIT_FAILURE);
    }

    int bytes_read = read(clientSocket, storageBuffer, 80);

    if(bytes_read < 0){
        perror("Error reading from client");
        exit(EXIT_FAILURE);
    }
    storageBuffer[bytes_read] = '\0';
    
    ssize_t bytes_sent = send(clientSocket, storageBuffer, bytes_read, 0);

    if(bytes_sent < 0){
        perror("Error sending response to client");
        exit(EXIT_FAILURE);
    }

    close(serverSock);
    close(clientSocket);
    
    return 0;
}
