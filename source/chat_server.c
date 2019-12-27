#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 9000
#define MAX_CLIENT 10
#define CHATDATA 1024


void* do_chat(void *);
pthread_t thread;
idx = 0;

struct{
    int c_socket;
    char nickName[20];
}list_c[MAX_CLIENT];


main(){
    int c_socket, s_socket;
    struct sockaddr_in s_addr, c_addr;
    int len;
    int i, j , n;
    int res;
    
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

    for( i = 0; i < MAX_CLIENT; i++){
        list_c[i].c_socket = -1; //list init
        strcpy(list_c[i].nickName,"");
    }

    while(1){
        len = sizeof(c_addr);
        c_socket = accept(s_socket, (struct sockaddr *)&c_addr, &len);

        list_c[idx].c_socket = c_socket;
        sprintf(list_c[idx].nickName, "guest_%02d", idx);
        idx++;
        pthread_create(&thread, NULL, do_chat, (void *)&c_socket);
    }
}

void* do_chat(void *arg){
    int c_socket = *((int*)arg);
    char chatData[CHATDATA];
    int i , j , n;
    char *temp;
    int length;
    char cBuff[BUFSIZ];
    char myName[20];
    char systemBuff[BUFSIZ];

    strcpy(myName, "no_name");
    for (i = 0; i < idx; i++){
        if (list_c[i].c_socket == c_socket){
            strcpy(myName, list_c[i].nickName);
            break;
        }
    }
    sprintf(systemBuff, "*[System-Notice] :  \"%s\" has joined the chat room. \r\n", myName);
    for(i = 0; i < idx; i ++){
        if(list_c[i].c_socket != -1){
            write(list_c[i].c_socket, systemBuff, strlen(systemBuff));
        }
    }

    while(1){
        memset(chatData, 0, sizeof(chatData));
        length = 0;
        temp = chatData;
        while((n= read(c_socket, temp , 1)) > 0){
            if (*temp == '\r') continue;
            if (*temp =='\n')break;
            if (*temp =='\0')break;

            if(length == CHATDATA)break;
            temp++; length++;
        }
        chatData[length] = '\0';


        if(!strcmp(chatData, "exit")){
            sprintf(systemBuff, "*[System-Notice] :  \"%s\" left the chat room. \r\n", myName);
            for (i = 0; i < idx; i++){
                if(list_c[i].c_socket != -1 && list_c[i].c_socket != c_socket){
                    write(list_c[i].c_socket, systemBuff, strlen(systemBuff));
                }
            }

            for ( i = 0; i < idx; i++){
                if(list_c[i].c_socket == c_socket){
                    for( j = i ; j < MAX_CLIENT -1 ; j++){
                        list_c[j].c_socket = list_c[j+1].c_socket;
                    }
                    list_c[MAX_CLIENT].c_socket = -1;
                    idx--;
                    break;
                }
            }
            break;
        }
        else {
            for ( i = 0; i < idx; i++){
                if (list_c[i].c_socket != -1){
                    sprintf(cBuff, "[%s] : %s\r\n", myName, chatData);
                    write(list_c[i].c_socket, cBuff, strlen(cBuff));
                }
            }
        }
    }
    close(c_socket);
}

