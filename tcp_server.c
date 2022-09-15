// 6 libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#define PORT 8080

void func(int commFD)
{
    char buffer[256];
    int n;

    for (;;)
    {
        // receiving a message
        bzero(buffer, sizeof(buffer));
        recv(commFD, buffer, sizeof(buffer), 0);
        print("buffer message");

        // sending a message
        bzero(buffer, sizeof(buffer));
        n = 0;
        while ((buffer[n++] = getchar()) != '\n')
            ;
        send(commFD, buffer, sizeof(buffer), 0);

        // breaking
        if (strncmp(buffer, "exit", 4) == 0)
        {
            print("exiting now");
            break;
        }
    }
}

int main()
{
    int sockFD = socket(AF_INET, SOCK_STREAM, 0);

    // create serverAddress
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) != 0)
    {
        // error
        return;
    }
    else
    {
        // pass
    }

    if (listen(sockFD, 5) != 0)
    {
        // error
        return;
    }
    else
    {
        // pass
    }

    // accept
    struct sockaddr_in clientAddress;
    int clientAddrLen = sizeof(clientAddress);

    int commFD = accept(sockFD, (struct sockaddr *)&clientAddress, &clientAddrLen);

    // check commFD

    func(commFD);

    close(sockFD);
}