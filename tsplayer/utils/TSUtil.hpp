//
//  TSUtil.hpp
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/6/30.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#ifndef TSUtil_hpp
#define TSUtil_hpp
#include "TSType.h"

#ifdef _WIN32
//define something for Windows (32-bit and 64-bit, this part is common)
#include <windows.h>
#ifdef _WIN64
//define something for Windows (64-bit only)
#else
//define something for Windows (32-bit only)
#endif

#elif __APPLE__

#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#include <unistd.h>
#include <sys/time.h>
#elif TARGET_OS_IPHONE
// iOS device
#include <unistd.h>
#include <sys/time.h>
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#include <unistd.h>
#else
//    # error "Unknown Apple platform"
#endif

#elif __ANDROID__
// android
#include <unistd.h>
#include <sys/time.h>
#elif __linux__
// linux
#include <unistd.h>
#include <sysconf.h>
#elif __unix__ // all unices not caught above
// Unix
#elif defined(_POSIX_VERSION)
// POSIX
#else
//#   error "Unknown compiler"
#endif



#ifdef __cplusplus
extern "C" {
#endif
    
/*Sleep microsecond (us)*/
void TSUSleep(TS_U32 nTime);
    
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TSUtil_hpp */
