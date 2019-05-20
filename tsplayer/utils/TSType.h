//
//  TSType.h
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/5/15.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#ifndef TSType_h
#define TSType_h

#ifdef __cplusplus
extern "C" {
#endif
    
    /* NULL */
#ifndef NULL
#define NULL                   0
#endif
    
/* wchar */
typedef wchar_t                TS_WCHAR;

/* pointer */
typedef char*                  TS_BUF;
typedef void*                  TS_PTR;
typedef void*                  TS_HANDLE;

/* unsigned domain */
typedef unsigned char          TS_U8;
typedef unsigned short         TS_U16;
typedef unsigned int           TS_U32;
typedef unsigned long long     TS_U64;
    
    /* max define */
#define TS_U8_MAX              0xFF
#define TS_U16_MAX             0xFFFF
#define TS_U32_MAX             0xFFFFFFFF
#define TS_U64_MAX             0xFFFFFFFFFFFFFFFF
    
    
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TSType_h */
