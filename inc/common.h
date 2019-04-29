/*************************************************************************
	> File Name: common.h
	> Author: lvsenlv
	> Mail: lvsen46000@163.com
	> Created Time: 23/09/2018
 ************************************************************************/

#ifndef __COMMON_H
#define __COMMON_H

typedef unsigned char           uint8_t;
typedef unsigned short          uint16_t;
typedef unsigned int            uint32_t;

#ifdef __LINUX
typedef unsigned long           uint64_t;
#elif defined __WINDOWS
typedef unsigned long long      uint64_t;
#endif

#ifndef _FILE_OFFSET_BITS
#define _FILE_OFFSET_BITS                       64 //Make sure st_size is 64bits instead of 32bits
#endif

#define PACKED                                  __attribute__((packed))
#define ARRAY_SIZE(a)                           (sizeof(a)/sizeof(a[0]))

#endif
