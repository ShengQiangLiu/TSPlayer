//
//  TSDecode.hpp
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/6/16.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#ifndef TSDecode_hpp
#define TSDecode_hpp

#include "TSType.h"
#include "TSDemux.hpp"

#include "libavutil/pixdesc.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#ifdef __APPLE__
//#include "libavcodec/videotoolbox.h"
#endif

typedef struct
{
    char* pPCMBuf;
    TS_U32 nSamples;
    TS_U32 nBufSize;
    TS_U32 nDataSize;
    TS_U64 nTimestamp;
} AudioFrameBuffer;

class TSDecode {
public:
    TSDecode();
    ~TSDecode();
    TS_U32 OpenDecoder(TSMediaContext* pMediaContext);
private:
    static AVPixelFormat GetDecoderFormat(AVCodecContext* context, AVPixelFormat const formats[]);
    TS_U32 OpenVideoDecoder(TSMediaContext* pMediaContext);
    TS_U32 OpenAudioDecoder(TSMediaContext* pMediaContext);
private:
    AVFrame*           m_pFrame;
    AVFrame*           m_pFrameRnd;
    AVCodecContext*    m_pCodecCtx;
    AVCodecParameters* m_pCodecParam;
    double             m_TimeBase;
    
    AVFrame*           m_pPCM;
    bool               m_PlanarPCM;
//    AVCodecContext*    m_pCodecCtx;
//    AVCodecParameters* m_pCodecParam;
//    double             m_TimeBase;
    AudioFrameBuffer   m_AudioFrameBuf;
    TS_U32             m_nMaxPCMBufSize;
};

#endif /* TSDecode_hpp */
