//
//  TSError.h
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/5/15.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#ifndef TSError_h
#define TSError_h

#ifdef __cplusplus
extern "C" {
#endif
    
#define    TS_Err_None                   0x00000000
#define    TS_Err_BadParam               0x00000001
#define    TS_Err_DataNotExist           0x00000002
#define    TS_Err_NotImplement           0x00000003
#define    TS_Err_FileOpenFaild          0x00000004
#define    TS_Err_OperatorFaild          0x00000005
#define    TS_Err_ContainerFull          0x00000006
#define    TS_Err_ContainerEmpty         0x00000007
#define    TS_Err_DataAlreadyExist       0x00000008
    
#define    TS_Err_Memory_Base            0x0000F000
#define    TS_Err_Memory_Low             (TS_Err_Memory_Base|0x01)
#define    TS_Err_Memory_Overflow        (TS_Err_Memory_Base|0x02)
#define    TS_Err_Memory_NotAvailable    (TS_Err_Memory_Base|0x03)
    
typedef enum
{
    TSPlayerStatus_Init = 0,
    TSPlayerStatus_Opened,
    TSPlayerStatus_Playing,
    TSPlayerStatus_Seeking,
    TSPlayerStatus_Paused,
    TSPlayerStatus_Closed,
}TSPlayerStatus;

    
#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* TSError_h */
