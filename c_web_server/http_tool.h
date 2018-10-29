//
//  http_tool.h
//  c_web_server
//
//  Created by MacOS on 2018/10/29.
//  Copyright © 2018年 MacOS. All rights reserved.
//

#ifndef http_tool_h
#define http_tool_h

#include "http_types.h"

extern int init_server(void);
extern int accept_client(int sockfd);
extern int parse_http_header(char *http_msg, http_header *p_h, APIMsg *p_api);
extern int url_map(http_header *p_h, APIMsg *p_api, int client_fd);
extern int parse_http_protocol(int client_fd);
extern void  parse_command(char *cmd[]);

#endif /* http_tool_h */
