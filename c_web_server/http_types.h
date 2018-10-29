//
//  http_types.h
//  c_web_server
//
//  Created by MacOS on 2018/10/29.
//  Copyright © 2018年 MacOS. All rights reserved.
//

#ifndef http_types_h
#define http_types_h

typedef struct {
    char method[8];
    char path[256];
} APIMsg;


typedef struct {
    char name[64];
    char value[256];
} http_header;

#endif /* http_types_h */
