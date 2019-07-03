//
//  TSPlayerController.cpp
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/5/18.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#include "TSPlayerController.hpp"
#include "TSError.hpp"
#include "TSUtil.hpp"

#define A_PACKET_QUEUE_MAX_SIZE 256
#define V_PACKET_QUEUE_MAX_SIZE 512

TSPlayerController::TSPlayerController()
{
    m_pDemux = new TSDemux();
    m_pDecode = new TSDecode();
    playerStatus = TSPlayerStatus_Init;

    m_pVideoPacketQueue = new TSRingQueue<AVPacket *>(V_PACKET_QUEUE_MAX_SIZE);
    m_pAudioPacketQueue = new TSRingQueue<AVPacket *>(A_PACKET_QUEUE_MAX_SIZE);
    m_pVideoFrameQueue = new TSRingQueue<AVFrame *>(V_PACKET_QUEUE_MAX_SIZE);
    

}

TSPlayerController::~TSPlayerController()
{
    delete m_pDemux;
    delete m_pDecode;
    delete m_pVideoPacketQueue;
    delete m_pAudioPacketQueue;
    delete m_pVideoFrameQueue;
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
//    readSignal.Send();
//    decodeSignal.Send();
//
    m_pDecode->OpenDecoder(&m_pDemux->m_mediaContext);
    pthread_create(&m_readFrameThread, NULL, ReadFrameThreadCallback, this);
    pthread_create(&m_decodePacketThread, NULL, DecodePacketThreadCallback, this);
    
    return ret;
}

void* TSPlayerController::DecodePacketThreadCallback(void *pArgs)
{
    if (NULL == pArgs) return NULL;
    pthread_setname_np("DecodePacketThread");
    
    TSPlayerController *playCtrl = (TSPlayerController *)pArgs;
    for (;;)
    {
        if (playCtrl->playerStatus != TSPlayerStatus_Playing)
        {
//            playCtrl->decodeSignal.Wait();
        }
        int ret = -1;
        AVPacket *packet = NULL;
//        playCtrl->m_videoPacketQueueMutex.Lock();
        playCtrl->m_pVideoPacketQueue->Pop(&packet, 0, 1);
//        playCtrl->m_videoPacketQueueMutex.UnLock();
        
        if (packet && packet->size>0)
        {
            ret = avcodec_send_packet(playCtrl->m_pDemux->m_mediaContext.pVideoCodecCtx, packet);
            do {
                AVFrame *videoFrame = av_frame_alloc();

                ret = avcodec_receive_frame(playCtrl->m_pDemux->m_mediaContext.pVideoCodecCtx, videoFrame);
                if (ret == 0)
                {
                    playCtrl->m_pVideoFrameQueue->Push(videoFrame);
                    printf("Decode Video Frame pts : %lld\n", videoFrame->pts);
                }
                av_frame_free(&videoFrame);
                videoFrame = NULL;
            } while (ret != AVERROR(EAGAIN));
        }
        else
        {
//            playCtrl->decodeSignal.Wait();
//            printf("No packet!\n");
        }
        av_packet_free(&packet);
    }

    printf("DecodePacketThreadEnd!\n");

    return NULL;
}

void* TSPlayerController::ReadFrameThreadCallback(void *pArgs)
{
    if (NULL == pArgs) return NULL;
    pthread_setname_np("ReadFrameThread");

    TSPlayerController *playCtrl = (TSPlayerController *)pArgs;
    AVPacket *pPkt;
    for (;;)
    {
        if (playCtrl->playerStatus != TSPlayerStatus_Playing)
        {
//            playCtrl->readSignal.Wait();
        }
        pPkt = av_packet_alloc();
        TSError error = playCtrl->m_pDemux->ReadPacket(pPkt);
        if (pPkt->stream_index == playCtrl->m_pDemux->m_mediaContext.nAudioIndex)
        {
//            printf("Audio Packet pts : %lld\n", pPkt->pts);
//            playCtrl->m_audioPacketQueueMutex.Lock();
            playCtrl->m_pAudioPacketQueue->Push(pPkt);
//            playCtrl->m_audioPacketQueueMutex.UnLock();
            
        }
        else if (pPkt->stream_index == playCtrl->m_pDemux->m_mediaContext.nVideoIndex)
        {
//            printf("Read Video Packet pts : %lld\n", pPkt->pts);
//            playCtrl->m_videoPacketQueueMutex.Lock();
            playCtrl->m_pVideoPacketQueue->Push(pPkt);
//            playCtrl->m_videoPacketQueueMutex.UnLock();
        }
        
        if (error.m_nCode != 0)
        {
            av_packet_free(&pPkt);
            return NULL;
        }
        else
        {
//            playCtrl->decodeSignal.Send();
//            av_packet_free(&pPkt);
        }
//        printf("VideoPacketCount: %d", playCtrl->m_pVideoPacketQueue->Count());
    }
    return NULL;
}
