//
//  TSPlayer.cpp
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/5/15.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#include "TSPlayer.hpp"


TSPlayer::TSPlayer()
{
    m_pPlayerCtrl = new TSPlayerController();
}


TS_U32 TSPlayer::Open(const char *pPath,
                      TS_PTR pVideoView,
                      TS_U32 nViewWidth,
                      TS_U32 nViewHeight)
{
    TS_U32 ret = -1;
    
    ret = m_pPlayerCtrl->OpenMedia(pPath);
    
    return ret;
}

TS_U32 TSPlayer::Close()
{
    TS_U32 ret = -1;
    
    
    return ret;
}

TS_U32 TSPlayer::Play(TS_U32 nStartPos)
{
    TS_U32 ret = -1;
    ret = m_pPlayerCtrl->Play();

    return ret;
}

TS_U32 TSPlayer::Pause()
{
    TS_U32 ret = -1;
    
    
    return ret;
}

TS_U32 TSPlayer::Seek(TS_U32 nSeekPos)
{
    TS_U32 ret = -1;
    
    
    return ret;
}

void TSPlayer::SetCallback(void *pUserData, void(*callback)(void *, TS_U32 msg))
{
 
}
