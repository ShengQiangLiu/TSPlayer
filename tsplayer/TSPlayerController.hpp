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



class TSPlayerController {
public:
    TS_U32 OpenMedia(const TS_BUF pPath,
                TS_PTR pVideoView = NULL,
                TS_U32 nViewWidth = 0,
                TS_U32 nViewHeight = 0
                );
public:
    
};

#endif /* TSPlayerController_hpp */
