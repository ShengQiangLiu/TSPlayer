//
//  TSDemux.cpp
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/5/18.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#include "TSDemux.hpp"

#define TS_MAX_READ_PACKET_RETRY    32


TSDemux::TSDemux()
:m_TimeBase(0),
m_nAudioIndex(-1),
m_nVideoIndex(-1)
{

    av_register_all();
    avformat_network_init();
    printf("%s", av_version_info());
}

TSDemux::~TSDemux()
{
    if (m_mediaContext.pFormatCtx!=NULL)
    {
        avformat_close_input(&m_mediaContext.pFormatCtx);
    }
}

void TSDemux::CloseMedia()
{
    m_nAudioIndex = -1;
    m_nVideoIndex = -1;
    
    avformat_close_input(&m_mediaContext.pFormatCtx);
    avcodec_free_context(&m_mediaContext.pAudioCodecCtx);
    avcodec_free_context(&m_mediaContext.pVideoCodecCtx);
    avformat_free_context(m_mediaContext.pFormatCtx);
}

TSError TSDemux::OpenMedia(const TS_BUF pPath)
{
    AVDictionary *options = NULL;
    int ret = -1;
    
    ret = avformat_open_input(&m_mediaContext.pFormatCtx, pPath, NULL, &options);
    
    if (ret != 0)
    {
        if (m_mediaContext.pFormatCtx!=NULL)
        {
            avformat_close_input(&m_mediaContext.pFormatCtx);
        }
        return TSError(ret);
    }
    
    ret = avformat_find_stream_info(m_mediaContext.pFormatCtx, NULL);
    if (ret != 0)
    {
        avformat_close_input(&m_mediaContext.pFormatCtx);
        return TSError(ret);
    }
    
    av_dump_format(m_mediaContext.pFormatCtx, 0, pPath, 0);
    
    m_nAudioIndex = FindAudioStream();
    
    m_nVideoIndex = FindVideoStream();
    
    if (m_nVideoIndex && m_nAudioIndex)
    {
        m_mediaContext.nDuration = (TS_U32)(m_mediaContext.pFormatCtx->duration / 1000);
    }
    if(m_mediaContext.nDuration > 0)
    {
        m_mediaContext.seekable = true;
    }
    else
    {
        m_mediaContext.seekable = false;
    }
    
    return TSError(ret);
}


TS_U32 TSDemux::FindAudioStream()
{
    int audioIndex = av_find_best_stream(m_mediaContext.pFormatCtx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
    if (audioIndex>=0)
    {
        AVCodecParameters *pCodecParam = m_mediaContext.pFormatCtx->streams[m_nAudioIndex]->codecpar;
        AVCodec *pCodec = avcodec_find_decoder(pCodecParam->codec_id);
        AVCodecContext *pAVCodecCtx = avcodec_alloc_context3(pCodec);
        AVStream* pStream = m_mediaContext.pFormatCtx->streams[m_nAudioIndex];
        avcodec_parameters_to_context(pAVCodecCtx, pCodecParam);
        // 将音频流的时间基分数转换为浮点数
        m_TimeBase = av_q2d(pStream->time_base);
        m_mediaContext.hasAudio = true;
        m_mediaContext.nAudioIndex = audioIndex;
        m_mediaContext.pAudioCodecCtx = pAVCodecCtx;
        m_mediaContext.pAudioDecParam = pCodecParam;
        m_mediaContext.nSampleFormat = pCodecParam->format;
        m_mediaContext.nChannels = pCodecParam->channels;
        m_mediaContext.nSampleSize = pCodecParam->frame_size;
        m_mediaContext.nSampleRate = pCodecParam->sample_rate;
    }
    return audioIndex;
}

TS_U32 TSDemux::FindVideoStream()
{
    int videoIndex = av_find_best_stream(m_mediaContext.pFormatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    if (videoIndex >= 0)
    {
        AVCodecParameters *pCodecParam = m_mediaContext.pFormatCtx->streams[m_nVideoIndex]->codecpar;
        AVCodec *pCodec = avcodec_find_decoder(pCodecParam->codec_id);
        AVCodecContext *pAVCodecCtx = avcodec_alloc_context3(pCodec);
        pAVCodecCtx->thread_count = 8;
        AVStream* pStream = m_mediaContext.pFormatCtx->streams[m_nVideoIndex];
        avcodec_parameters_to_context(pAVCodecCtx, pCodecParam);
        if(m_TimeBase == 0)
        {
            // 将视频流的时间基分数转换为浮点数
            m_TimeBase = av_q2d(pStream->time_base);
        }
        m_mediaContext.hasVideo = true;
        m_mediaContext.videoRotation = 0;
        m_mediaContext.nVideoIndex = videoIndex;
        m_mediaContext.pVideoCodecCtx = pAVCodecCtx;
        m_mediaContext.pVideoDecParam = pCodecParam;
        m_mediaContext.nVideoWidth = pCodecParam->width;
        m_mediaContext.nVideoHeight = pCodecParam->height;
        
        for (TS_U32 i = 0; i < pStream->nb_side_data; i++)
        {
            AVPacketSideData sd = pStream->side_data[i];
            if(sd.type == AV_PKT_DATA_DISPLAYMATRIX)
            {
                m_mediaContext.videoRotation = av_display_rotation_get((int32_t*)sd.data);
            }
        }
    }
    return videoIndex;
}


TSError TSDemux::ReadPacket(AVPacket *pPacket)
{
    int ret = -1;
    TS_U32 nRetryTimes = 0;
    if (pPacket)
    {
        while (nRetryTimes < TS_MAX_READ_PACKET_RETRY)
        {
            ret = av_read_frame(m_mediaContext.pFormatCtx, pPacket);
            if (ret == 0)
            {
                if (pPacket->pts != AV_NOPTS_VALUE)
                {
                    m_TimeBase = pPacket->pts;
                }
                else if (pPacket->dts != AV_NOPTS_VALUE)
                {
                    m_TimeBase = pPacket->dts;
                }
                return TSError(ret);
            }
            else if (ret == AVERROR_EOF)
            {
                return TSError(ret);
            }
            else
            {
                nRetryTimes++;
            }
        }
    }
    return TSError(ret);
}
