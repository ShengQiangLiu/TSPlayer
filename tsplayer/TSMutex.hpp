//
//  TSMutex.hpp
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/5/15.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#ifndef TSMutex_hpp
#define TSMutex_hpp

#include "TSType.h"
#include <pthread.h>

class TSMutex
{
public:
    TSMutex();
    ~TSMutex();
    void Lock();
    void UnLock();
    
private:
    pthread_mutex_t     m_hMutex;
};

#endif /* TSMutex_hpp */
