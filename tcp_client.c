// 6 libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#define PORT 8080

void func(int sockFD)
{
    char buffer[256];
    int n;

    for (;;)
    {
        // sending a message
        bzero(buffer, sizeof(buffer));
        n = 0;
        while ((buffer[n++] = getchar()) != '\n')
            ;
        send(sockFD, buffer, sizeof(buffer), 0);

        // receiving a message
        bzero(buffer, sizeof(buffer));
        recv(sockFD, buffer, sizeof(buffer), 0);
        print("buffer message");

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
    // check sockFD

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    // connect
    if (connect() != 0)
    {
        // error
        return;
    }
    else
    {
        // pass
    }

    func(sockFD);

    close(sockFD);
}