//
//  TSPlayer.hpp
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/5/15.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#ifndef TSPlayer_hpp
#define TSPlayer_hpp

#include "TSType.h"
#include "TSPlayerController.hpp"

class TSPlayer {
public:
    TSPlayer();
    TS_U32 Open(const char *pPath,
                TS_PTR pVideoView = NULL,
                TS_U32 nViewWidth = 0,
                TS_U32 nViewHeight = 0
                );
    TS_U32 Close();
    TS_U32 Play(TS_U32 nStartPos = 0);
    TS_U32 Pause();
    TS_U32 Seek(TS_U32 nSeekPos);
    void SetCallback(void *pUserData, void(*callback)(void *, TS_U32 msg));
    
public:
    
private:
    TSPlayerController *m_pPlayerCtrl;
};

#endif /* TSPlayer_hpp */
