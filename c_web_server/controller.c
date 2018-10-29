//
//  controller.c
//  c_web_server
//
//  Created by MacOS on 2018/10/29.
//  Copyright © 2018年 MacOS. All rights reserved.
//

#include "http_format.h"


int hello(int client_fd)
{
    char *hello_msg = "Hello, World!";
    
    write(client_fd, HTTP_REPONSE_FORMAT, strlen(HTTP_REPONSE_FORMAT));
    write(client_fd, hello_msg, strlen(hello_msg));
    
    close(client_fd);
    
    return 0;
}
