/*************************************************************************
	> File Name: debug.h
	> Author: lvsenlv
	> Mail: lvsen46000@163.com
	> Created Time: 2019.03.05
 ************************************************************************/

#ifndef __DEBUG_H
#define __DEBUG_H

#include <stdio.h>

#define STDOUT(format, args...) \
        do \
        { \
            fprintf(stdout, format, ##args); \
        }while(0)
        
#define STDERR(format, args...) \
        do \
        { \
            fprintf(stderr, format, ##args); \
        }while(0)

#ifndef __DEBUG
#define DEBUG(format, args...)                  ((void)0)
#define DEBUG_ERR(format, args...)              ((void)0)
#else
#define DEBUG(format, args...) \
        do \
        { \
            fprintf(stdout, format, ##args); \
        }while(0)
        
#define DEBUG_ERR(format, args...) \
        do \
        { \
            fprintf(stderr, "[%s][%d] ", __func__, __LINE__); \
            fprintf(stderr, format, ##args); \
        }while(0)
#endif

#endif
