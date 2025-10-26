#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

#define PORT 8080

int main(){
    int sock = 0;
    struct sockaddr_in serv_addr;
    const char *hello = "Hello from client";

    //create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock<0){
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // now we have to convert IPv4 and IPv6 addressses from text to binary

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){
        std::cerr << "Invalid address " << std::endl;
        return -1;
    }

    // connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        std::cerr << "Connection failed " << std::endl;
        return -1;
    }

    //send data
    send(sock, hello, strlen(hello),0);
    std::cout << "Message sent" << std::endl;

    //close socket 
    close(sock);
    return 0;
}