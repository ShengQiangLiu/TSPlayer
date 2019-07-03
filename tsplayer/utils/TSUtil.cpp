//
//  TSUtil.cpp
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/6/30.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#include "TSUtil.hpp"

void TSUSleep(TS_U32 nTime)
{
#ifdef _WIN32
    __int64 time1 = 0, time2 = 0, freq = 0;
    
    QueryPerformanceCounter((LARGE_INTEGER *)&time1);
    QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
    
    do {
        QueryPerformanceCounter((LARGE_INTEGER *)&time2);
    } while ((time2 - time1) < nTime*freq / 1000000);
#elif defined __linux__
    usleep(nTime);
#elif defined TARGET_OS_IPHONE
    usleep(nTime);
#elif defined TARGET_IPHONE_SIMULATOR
    usleep(nTime);
#elif defined __ANDROID__
    usleep(nTime);
#endif
    
}
