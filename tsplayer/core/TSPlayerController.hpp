//
//  TSPlayerController.hpp
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/5/18.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#ifndef TSPlayerController_hpp
#define TSPlayerController_hpp

#include "TSType.h"
#include "TSDemux.hpp"
#include <pthread.h>
#include "TSErrorDefine.h"
#include "TSSignal.hpp"

class TSPlayerController {
public:
    TSPlayerController();
    TS_U32 OpenMedia(const char *pPath,
                TS_PTR pVideoView = NULL,
                TS_U32 nViewWidth = 0,
                TS_U32 nViewHeight = 0
                );
    TS_U32 Play(TS_U32 nStartPos = 0);

private:
    static void* ReadFrameThreadCallback(void *pArgs);
private:
    TSDemux *m_pDemux;
    pthread_t m_readFrameThread;
    TSPlayerStatus playerStatus;
    TSSignal playSignal;
};

#endif /* TSPlayerController_hpp */
