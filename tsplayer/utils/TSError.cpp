//
//  TSError.cpp
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/5/18.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#include "TSError.hpp"

extern "C"
{
#include "libavutil/error.h"
}
#include <stdio.h>


TSError::TSError()
{
    m_nCode = 0;
}

TSError::TSError(int nCode)
{
    m_nCode = nCode;
}

void TSError::SetError(int nCode)
{
    m_nCode = nCode;
    av_strerror(m_nCode, m_pErrorMessage, 1024);
    printf("Can't open file, (%d)%s", m_nCode, m_pErrorMessage);
}
