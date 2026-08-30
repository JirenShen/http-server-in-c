#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>


// struct sockaddr{
//     unsigned short sa_family; // address family, AF_xxx ip类型
//     char sa_data[14]; // 14 bytes of protocol address: port+ip
// };

// struct in_addr {
//     uint32_t s_addr; // that's a 32-bit int (4 bytes)
// };

// struct sockaddr_in { // sockaddr_in结构体用于IPv4地址
//     short int sin_family; // Address family, AF_INET
//     unsigned short int sin_port; // Port number
//     struct in_addr sin_addr; // Internet address
//     unsigned char sin_zero[8]; //补位置的，可以和标准的 sockaddr结构体互换使用
// };

int main(){
    int sockfd =socket(AF_INET, SOCK_STREAM, 0); //if socket creation fails, sockfd will be -1

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr)); //zero out the struct before filling it
    inet_pton(AF_INET, "0.0.0.0", &(addr.sin_addr)); //presentation to network address conversion, 0.0.0.0 means any IP address in the host
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    memset(addr.sin_zero, 0, sizeof(addr.sin_zero)); 
    //bind to port 8080, any IP address
    int bind_result = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)); //return 0 on success, -1 on error
    if(bind_result == -1){
        perror("bind failed");
        return 1;
    }
    printf("bind result: %d\n", bind_result);

    int listen_result = listen(sockfd, 5); //listen for incoming connections, 5 is the backlog size,是否成功开始监听
    if(listen_result == -1){
        perror("listen failed");
        return 1;
    }
    
    struct sockaddr_sotragre their_addr; //this struct will hold the client address information
    socklen_t addr_size = sizeof(their_addr);
    memset(&their_addr, 0, sizeof(their_addr)); //zero out the struct

    int client_sockfd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size); //accept a connection, return a new socket file descriptor for the accepted connection`

    while(1){
        //some kind of request must be received here.
        printf("%s\n", "Waiting for request...");
        sleep(1);
    }
    return 0;
}