#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 9000

void do_echo(int);

main(){
    int c_socket, s_socket;
    struct sockaddr_in s_addr, c_addr;
    int len;
    int pid;

    s_socket = socket(PF_INET, SOCK_STREAM, 0);

    memset(&s_addr, 0 , sizeof(s_addr));
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);

    if (bind(s_socket, (struct sockaddr*)&s_addr, sizeof(s_addr)) == -1){
        printf("Can not Bind\n");
        return -1;
    }
    if (listen(s_socket, 5) == -1){
        printf("listen fail!\n");
        return -1;
    }

    while(1){
        len = sizeof(c_addr);
        c_socket = accept(s_socket, (struct sockaddr *)&c_addr, &len);

        pid = fork();
        if (pid < 0){
            printf("echo server can not fork()\n");
            exit(0);
        }
        else if( pid > 0 ){
            close(c_socket);
            continue;
        }
        else if (pid == 0){
            close(s_socket);
            do_echo(c_socket);
        }
    }
    close(s_socket);
}

void do_echo(int c_socket){
    int n ,length;
    char *temp;
    char rBuffer[BUFSIZ]; //receive buffer

    while(1){
        memset(rBuffer, 0, sizeof(rBuffer));
        length = 0;
        temp = rBuffer;
        while((n= read(c_socket, temp , 1)) > 0){
            if (*temp == '\r') continue;
            if (*temp =='\n')break;
            if (*temp =='\0')break;

            if(length == BUFSIZ)break;
            temp++; length++;
        }
        rBuffer[length] = '\0';

        if(!strcmp(rBuffer, "quit")){
            break;
        }
        else{
            write(c_socket, rBuffer, strlen(rBuffer));
            write(c_socket, "\n", 1);
        }
    }
    close(c_socket);
    exit(-1);
}