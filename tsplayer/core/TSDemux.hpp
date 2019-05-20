//
//  TSDemux.hpp
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/5/18.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#ifndef TSDemux_hpp
#define TSDemux_hpp

#include "TSType.h"
#include "TSError.hpp"

extern "C"
{
#include "libavutil/display.h"
#include "libavformat/avformat.h"
};

typedef struct
{
    AVFormatContext *pFormatCtx;

    TS_U32 nVideoIndex;
    bool   hasVideo;
    AVCodecContext *pVideoCodecCtx;
    AVCodecParameters *pVideoDecParam;
    TS_U64 nDuration; // 视频总时长(ms)
    TS_U32 nVideoWidth;
    TS_U32 nVideoHeight;
    int    videoRotation;
    
    TS_U32 nAudioIndex;
    bool   hasAudio;
    AVCodecContext* pAudioCodecCtx;
    AVCodecParameters* pAudioDecParam;
    TS_U32 nChannels;
    TS_U32 nSampleRate; // 采样率(48000)
    TS_U32 nSampleSize; // 采样大小(1024)
    TS_U32 nSampleFormat; // 采样格式
    
    TS_U64 nTimeBase; //(ms)
    bool   seekable;
}TSMediaContext;


class TSDemux {
public:
    TSDemux();
    ~TSDemux();
    TSError OpenMedia(const char *pPath);
    void CloseMedia();
    TSError ReadPacket(AVPacket *pPacket);
public:
    TSMediaContext m_mediaContext;
private:
    TS_U32 m_nAudioIndex;
    TS_U32 m_nVideoIndex;
    TS_U64 m_TimeBase; // 时间基（ms）
    
    TS_U32 FindVideoStream();
    TS_U32 FindAudioStream();
};


#endif /* TSDemux_hpp */
