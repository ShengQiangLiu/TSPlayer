//
//  TSError.hpp
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/5/18.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#ifndef TSError_hpp
#define TSError_hpp

class TSError {
public:
    TSError();
    TSError(int nCode=0);
    void SetError(int nCode=0);
public:
    char *m_pErrorMessage;
    int m_nCode;
};

#endif /* TSError_hpp */
