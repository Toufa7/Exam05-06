#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int new, id;
} t_client;

t_client clients[10000];
char buffer[10000], c;
int serv_fd, clt_fd, max_fd, clt_cnt = 0;
fd_set sockets,readfds, writefds;

int ft_error(char* msg) {
    return write(2, msg, strlen(msg)) || 1;
}

void broadcast(char* msg, int arg, int owner_fd) {
    sprintf(buffer, msg, arg);
    for (int fd = 0; fd <= max_fd; fd++)
        if(FD_ISSET(fd, &writefds) && fd != owner_fd)
            write(fd, buffer, strlen(buffer));
}

int main(int ac, char** av) {
    memset(&clients, 1, sizeof(clients));
    if (ac != 2)
        return ft_error("Wrong number of arguments\n");
    if ((serv_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return ft_error("Fatal error\n");
    struct sockaddr_in servaddr = (struct sockaddr_in){0};
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(av[1]));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(serv_fd, (struct sockaddr*)&servaddr, sizeof(struct sockaddr)) < 0)
        return ft_error("Fatal error\n");
    if (listen(serv_fd, 10) < 0)
        return ft_error("Fatal error\n");

    FD_ZERO(&sockets);
    FD_SET(serv_fd, &sockets);
    max_fd = serv_fd;

    while(1) {
        for (int curr = 0; curr <= max_fd; curr++) {
            readfds = writefds = sockets;
            if(select(max_fd + 1, &readfds, &writefds, NULL, NULL) < 0)
                continue;
            if(FD_ISSET(curr, &readfds)) {
                if(curr == serv_fd)
                {
                    if ((clt_fd = accept(serv_fd, NULL, NULL)) < 0)
                        continue;
                    broadcast ("server: client %d just arrived\n", clt_cnt, clt_fd);
                    clients[clt_fd].id = clt_cnt++;
                    FD_SET(clt_fd, &sockets);
                    max_fd = clt_fd > max_fd ? clt_fd : max_fd;
                }
                else
                {
                    if(recv(curr, &c, 1, 0) <= 0) {
                        broadcast("server: client %d just left\n", clients[curr].id, curr);
                        FD_CLR(curr, &sockets);
                        close(curr);
                    }
                    else {
                        if (clients[curr].new) {
                            clients[curr].new = 0;
                            broadcast("client %d: ", clients[curr].id, curr);
                        }
                        if (c == '\n')
                            clients[curr].new = 1;
                        broadcast(&c, 0, curr);
                    }
                }
            }
        }
    }
}

