//
//  main.c
//  c_web_server
//
//  Created by MacOS on 2018/10/29.
//  Copyright © 2018年 MacOS. All rights reserved.
//

#include "common.h"
#include "http_format.h"
#include "http_tool.h"
#include "http_types.h"


int main(int args, char *argv[], char *env[])
{
    parse_command(argv);
    
    return 0;
}

