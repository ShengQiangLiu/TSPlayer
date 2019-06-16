//
//  TSDecode.cpp
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/6/16.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#include "TSDecode.hpp"

TSDecode::TSDecode()
:m_TimeBase(0)
,m_pFrame(NULL)
,m_pFrameRnd(NULL)
,m_pCodecCtx(NULL)
,m_pCodecParam(NULL)
,m_PlanarPCM(false)
,m_nMaxPCMBufSize(0)
{
    
}

TSDecode::~TSDecode()
{
    
}

TS_U32 TSDecode::OpenDecoder(TSMediaContext* pMediaContext)
{
    int ret = -1;

    ret = OpenVideoDecoder(pMediaContext);
    ret = OpenAudioDecoder(pMediaContext);
    
    return ret;
}

TS_U32 TSDecode::OpenAudioDecoder(TSMediaContext* pMediaContext)
{
    if (NULL == pMediaContext)
        return -1;
    
    m_pCodecCtx = pMediaContext->pAudioCodecCtx;
    m_pCodecParam = pMediaContext->pAudioDecParam;
    m_PlanarPCM = av_sample_fmt_is_planar((AVSampleFormat)pMediaContext->nSampleFormat);
    AVStream* pStream = pMediaContext->pFormatCtx->streams[pMediaContext->nAudioIndex];
    
    m_TimeBase = av_q2d(pStream->time_base);
    AVCodec* pCodec = avcodec_find_decoder(m_pCodecCtx->codec_id);
    av_codec_set_pkt_timebase(m_pCodecCtx, m_pCodecCtx->time_base);
    
    if (NULL == pCodec)
    {
        return -1;
    }
    // 打开解码器
    if (avcodec_open2(m_pCodecCtx, pCodec, NULL) < 0)
    {
        return -1;
    }
    m_pPCM = av_frame_alloc();
    if (NULL == m_pPCM)
    {
        return -1;
    }
    
    return 0;
}

TS_U32 TSDecode::OpenVideoDecoder(TSMediaContext* pMediaContext)
{
    int ret = -1;
    
    m_pCodecCtx = pMediaContext->pVideoCodecCtx;
    m_pCodecParam = pMediaContext->pVideoDecParam;
#ifdef __APPLE__
    //    m_pCodecCtx->get_format = TSDecode::GetDecoderFormat;
#endif
    AVStream* pStream = pMediaContext->pFormatCtx->streams[pMediaContext->nVideoIndex];
    
    m_TimeBase = av_q2d(pStream->time_base);
    
    AVCodec* pCodec = avcodec_find_decoder(m_pCodecCtx->codec_id);
    av_codec_set_pkt_timebase(m_pCodecCtx, m_pCodecCtx->time_base);
    
    if (NULL == pCodec)
    {
        return -1;
    }
    if (avcodec_open2(m_pCodecCtx, pCodec, NULL) < 0)
    {
        return -1;
    }
    m_pFrame = av_frame_alloc();
    if (NULL == m_pFrame)
    {
        return -1;
    }
    return ret;
}


//AVPixelFormat TSDecode::GetDecoderFormat(AVCodecContext* context, AVPixelFormat const formats[])
//{
//    TS_U32 i = 0;
//    for (i = 0; formats[i] != AV_PIX_FMT_NONE; ++i)
//    {
//        printf("ffmpeg supported format[ %d ]: %s", i, av_get_pix_fmt_name(formats[i]));
//    }
//#ifdef __APPLE__
//    for (auto j = 0; formats[j] != AV_PIX_FMT_NONE; ++j)
//    {
//        if (formats[j] == AV_PIX_FMT_VIDEOTOOLBOX)
//        {
//            auto result = av_videotoolbox_default_init(context);
//            if (result < 0)
//            {
////                ecLogW("av_videotoolbox_default_init failed: %s", av_err2str(result));
//                break;
//            }
//            else
//            {
////                ecLogI("hw decoder: selecting fromat AV_PIX_FMT_VIDEOTOOLBOX");
//                return AV_PIX_FMT_VIDEOTOOLBOX;
//            }
//        }
//    }
//#endif
//    return formats[i-1];
//}
