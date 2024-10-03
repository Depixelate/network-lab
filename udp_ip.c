#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    struct addrinfo hints;
    struct addrinfo *addrs;
    struct addrinfo *start;
    memset(&hints, 0, sizeof(struct addrinfo)); // sets ai.protocol to 0, no need to manually set
    hints.ai_flags = AI_CANONNAME;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    int s;
    if((s = getaddrinfo(NULL, "4398", &hints, &addrs)) != 0) {
        fprintf(stderr, "error in getaddrinfo: %s\n", gai_strerror(s));
    }
    start = addrs;

    while (addrs != NULL) {
        char ip[4096];
        
        inet_ntop(addrs->ai_family, &(((struct sockaddr_in *)addrs->ai_addr)->sin_addr), ip, 4096);

        printf("%s\n", ip);
    
        if(addrs->ai_canonname == NULL) {
            printf("NULL\n");
        } else {
            printf("%s\n", addrs->ai_canonname);
        }
        addrs = addrs->ai_next;
    }

    freeaddrinfo(start);

    // int s = socket(AF_INET, SOCK_DGRAM, 0);
    // if(s < 0) {
    //     perror("The following error occurred while creating a socket: ");
    //     return 1;
    // }
    // struct sockaddr_in my_addr;
    // memset((char *)&my_addr, 0, sizeof(sockaddr_in));
    // my_addr.sin_family = AF_INET;
    // my_addr.sin_port = htons(0);
    // my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    return 0;
}
