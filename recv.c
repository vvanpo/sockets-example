
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "sockets-example.h"

// type definitions
struct datagram {
    int sockfd;
    void *buffer;
    const int buf_length;
    unsigned long src_address;
    unsigned short src_port;
    int length;
};

// static function declarations
static int recv_message(struct datagram *);

// recv_message waits for an incoming datagram and writes it to
//  datagram->sock->buffer
//  if the socket is unbound, this call will cause the program to hang
int recv_message(struct datagram *datagram){
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    int ret = recvfrom(datagram->sockfd, datagram->buffer, datagram->buf_length,
            MSG_TRUNC, (struct sockaddr *) &addr, &addrlen);
    if (ret == -1){
        error(recv);
        return -1;
    }
    datagram->src_address = ntohl(addr.sin_addr.s_addr);
    datagram->src_port = ntohs(addr.sin_port);
    if (ret > datagram->buf_length)
        datagram->length = datagram->buf_length;
    else
        datagram->length = ret;
    return 0;
}

// recv_start begins the read loop for incoming datagrams
int recv_start(int sockfd){
    // using a buffer length of 512 bytes to stay within the usual MTUs
    const int buf_length = 512;
    void *buffer = malloc(buf_length);
    if (!buffer){
        error(malloc);
        return -1;
    }
    while (1){
        struct datagram datagram = { sockfd, buffer, buf_length };
        if (recv_message(&datagram)) return -1;
        ///////temp//  format ip address
        unsigned char a, b, c, d;
        unsigned int ip = datagram.src_address;
        a = (0xff000000 & ip) >> 24;
        b = (0x00ff0000 & ip) >> 16;
        c = (0x0000ff00 & ip) >> 8;
        d = 0x000000ff & ip;
        printf("Source: %u.%u.%u.%u:%u\n", a, b, c, d, datagram.src_port);
        printf("Length: %d bytes\n", datagram.length);
        printf("%s\n", (char *) buffer);
        memset(buffer, 0, 512);
    }
    free(buffer);
    return 0;
}