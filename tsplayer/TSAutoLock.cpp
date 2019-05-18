//
//  TSAutoLock.cpp
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/5/16.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#include "TSAutoLock.hpp"

TSAutoLock::TSAutoLock(TSMutex *mutex)
{
    m_pMutex->Lock();
}

TSAutoLock::~TSAutoLock()
{
    m_pMutex->UnLock();
}
