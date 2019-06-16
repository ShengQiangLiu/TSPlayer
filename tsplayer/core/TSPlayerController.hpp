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
#include "TSRingQueue.hpp"
#include "TSMutex.hpp"
#include "TSAutoLock.hpp"
#include "TSDecode.hpp"

typedef pthread_t TSThreadHandle;

class TSPlayerController {
public:
    TSPlayerController();
    ~TSPlayerController();
    TS_U32 OpenMedia(const char *pPath,
                TS_PTR pVideoView = NULL,
                TS_U32 nViewWidth = 0,
                TS_U32 nViewHeight = 0
                );
    TS_U32 Play(TS_U32 nStartPos = 0);

private:
    static void* ReadFrameThreadCallback(void *pArgs);
    static void* DecodePacketThreadCallback(void *pArgs);
private:
    TSDemux *m_pDemux;
    TSThreadHandle m_readFrameThread;
    TSPlayerStatus playerStatus;
    TSSignal readSignal;
    TSSignal decodeSignal;
    TSThreadHandle m_decodePacketThread;
    TSDecode *m_pDecode;
    
    TSRingQueue<AVPacket *> *m_pVideoPacketQueue;
    TSRingQueue<AVPacket *> *m_pAudioPacketQueue;
    TSMutex m_videoPacketQueueMutex;
    TSMutex m_audioPacketQueueMutex;
    
    TSRingQueue<AVFrame *> *m_pVideoFrameQueue;
    TSMutex m_videoFrameQueueMutex;
};

#endif /* TSPlayerController_hpp */
