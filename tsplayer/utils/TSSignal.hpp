//
//  TSSignal.hpp
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/5/15.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#ifndef TSSignal_hpp
#define TSSignal_hpp

#include "TSType.h"
#include <pthread.h>

class TSSignal
{
public:
    TSSignal();
    ~TSSignal();
    void Send();
    void Wait();
    void TimedWait(TS_U32 nTimeout);
    
private:
    pthread_cond_t m_Cond;
    pthread_mutex_t m_Mutex;
};

#endif /* TSSignal_hpp */
