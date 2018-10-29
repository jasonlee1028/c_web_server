//
//  http_tool.c
//  c_web_server
//
//  Created by MacOS on 2018/10/29.
//  Copyright © 2018年 MacOS. All rights reserved.
//

#include "common.h"
#include "http_types.h"


int init_server(void)
{
    int sockfd = 0;
    
    struct sockaddr_in my_addr;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(8000);
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    bzero(&(my_addr.sin_zero), 8);
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    
    if (listen(sockfd, 5) == -1)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    return sockfd;
}

int accept_client(int sockfd)
{
    int client_fd = 0;
    int addr_length = 0;
    struct sockaddr_in client_addr;
    
    addr_length = sizeof(client_addr);
    client_fd = accept(sockfd, &client_addr, &addr_length);
    if (client_fd == -1)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    return client_fd;
}

int parse_http_header(char *http_msg, http_header *p_h, APIMsg *p_api)
{
    int i = 0;
    int len = 0;
    char *p = NULL;
    char *p1 = NULL;
    char *p2 = NULL;
    char *p_top = NULL;
    
    char tmp[256] = {};
    char top_header[128] = {};
    char header_str[1024] = {};
    
    p_top = strstr(http_msg, "\r\n");
    if (p_top == NULL)
    {
        return 0;
    }
    
    len = p_top - http_msg;
    
    strncpy(top_header, http_msg, len);
    
    p1 = strstr(top_header, " ");
    strncpy(p_api->method, top_header, p1 - top_header);
    
    p1 += 1;
    p2 = strstr(p1, " ");
    strncpy(p_api->path, p1, p2 - p1);
    
    p_top += 2;
    while (p_top)
    {
        p = strstr(p_top, "\r\n");
        if (p == NULL)
        {
            break;
        }
        
        p1 = strstr(p_top, ":");
        if (p1 == NULL)
        {
            break;
        }
        
        strncpy(p_h[i].name, p_top, p1 - p_top);
        strncpy(p_h[i].value, p1 + 1, p - p1 -1);
        
        i++;
        p_top = p + 2;
    }
    
    return 1;
}


int url_map(http_header *p_h, APIMsg *p_api, int client_fd)
{
    printf("%s %s\n", p_api->method, p_api->path);
    if (strcmp(p_api->path, "/hello") == 0)
    {
        hello(client_fd);
    }
    
    return 0;
}


int parse_http_protocol(int client_fd)
{
    int len = 0;
    char buffer[1024] = {};
    http_header h[64] = {};
    APIMsg api_msg = {};
    
    len = read(client_fd, buffer, sizeof(buffer));
    if (len < 0)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }
    
    parse_http_header(buffer, &h, &api_msg);
    url_map(&h, &api_msg, client_fd);
    
    return 0;
}

void  parse_command(char *cmd[])
{
    int sockfd = 0;
    int client_fd = 0;
    int recv_len = 0;
    
    if (strcmp(cmd[1], "runserver") == 0)
    {
        printf("Server at: %s ...\n", cmd[2]);
        sockfd = init_server();
        while (1) {
            /* code */
            client_fd = accept_client(sockfd);
            recv_len = parse_http_protocol(client_fd);
        }
    }
    
}

