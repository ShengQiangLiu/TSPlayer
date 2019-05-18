//
//  TSAutoLock.hpp
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/5/16.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#ifndef TSAutoLock_hpp
#define TSAutoLock_hpp

#include "TSMutex.hpp"

class TSAutoLock {

public:
    TSAutoLock(TSMutex *mutex);
    ~TSAutoLock();
private:
    TSMutex *m_pMutex;
};

#endif /* TSAutoLock_hpp */
