//
//  TSSignal.cpp
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/5/15.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#include "TSSignal.hpp"


TSSignal::TSSignal()
{
    pthread_cond_init(&m_Cond, 0);
    pthread_mutex_init(&m_Mutex, NULL);
}

TSSignal::~TSSignal()
{
    pthread_cond_destroy(&m_Cond);
    pthread_mutex_destroy(&m_Mutex);
}

void TSSignal::Send()
{
    pthread_cond_signal(&m_Cond);
}

void TSSignal::Wait()
{
    pthread_cond_wait(&m_Cond, &m_Mutex);
}

void TSSignal::TimedWait(TS_U32 nTimeout)
{
    struct timespec timeout;
    timeout.tv_nsec = 0;
    timeout.tv_sec = time(NULL) + nTimeout;
    
    pthread_cond_timedwait(&m_Cond, &m_Mutex, &timeout);;
}
