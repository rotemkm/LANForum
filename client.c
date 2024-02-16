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

    char* message="This is a message from the client";
    char recvBuffer[100];

    struct sockaddr_in serverAddr;

    clientSock = socket(AF_INET, SOCK_STREAM, 0);

    if(clientSock < 0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    int status = 0;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(CONNECTION_PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_zero[8] ='\0';

    status = connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    if(status<0)
   {
        perror("Couldn't connect with the server");
        exit(EXIT_FAILURE);
   }    

    write(clientSocket, message, strlen(message));

    read(clientSocket, recvBuffer, 100);
    printf("Message from server: %s\n", recvBuffer);

    close(clientSocket);
    return 0;
}