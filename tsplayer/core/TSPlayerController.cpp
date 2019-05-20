//
//  TSPlayerController.cpp
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/5/18.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#include "TSPlayerController.hpp"
#include "TSError.hpp"


TSPlayerController::TSPlayerController()
{
    m_pDemux = new TSDemux();
    pthread_create(&m_readFrameThread, NULL, ReadFrameThreadCallback, this);
    playerStatus = TSPlayerStatus_Init;
}

TS_U32 TSPlayerController::OpenMedia(const char *pPath,
                 TS_PTR pVideoView,
                 TS_U32 nViewWidth,
                 TS_U32 nViewHeight
                 )
{
    TS_U32 ret = -1;
    TSError err = m_pDemux->OpenMedia(pPath);
    playerStatus = TSPlayerStatus_Opened;
    
    return ret;
}

TS_U32 TSPlayerController::Play(TS_U32 nStartPos)
{
    TS_U32 ret = -1;
    
    playerStatus = TSPlayerStatus_Playing;
    playSignal.Send();
    
    return ret;
}

void* TSPlayerController::ReadFrameThreadCallback(void *pArgs)
{
    if (NULL == pArgs) return NULL;
    TSPlayerController *playCtrl = (TSPlayerController *)pArgs;
    AVPacket *pPkt;
    while (1)
    {
        if (playCtrl->playerStatus != TSPlayerStatus_Playing)
        {
            playCtrl->playSignal.Wait();
        }
        pPkt = av_packet_alloc();
        TSError error = playCtrl->m_pDemux->ReadPacket(pPkt);
        if (pPkt->stream_index == playCtrl->m_pDemux->m_mediaContext.nAudioIndex)
        {
            printf("Audio Packet pts : %lld\n", pPkt->pts);
        }
        else
        {
            printf("Video Packet pts : %lld\n", pPkt->pts);
        }
        if (error.m_nCode != 0)
        {
            av_packet_free(&pPkt);
            return NULL;
        }
        else
        {
            
        }
    }
    return NULL;
}
