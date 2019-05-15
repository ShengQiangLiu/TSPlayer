//
//  TSMutex.cpp
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/5/15.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#include "TSMutex.hpp"

TSMutex::TSMutex()
{
    pthread_mutex_init(&m_hMutex, NULL);
}

TSMutex::~TSMutex()
{
    pthread_mutex_destroy(&m_hMutex);
}

void TSMutex::Lock()
{
    pthread_mutex_lock(&m_hMutex);
}

void TSMutex::UnLock()
{
    pthread_mutex_unlock(&m_hMutex);
}
