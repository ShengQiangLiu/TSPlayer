//
//  ViewController.m
//  TSPlayerDemo
//
//  Created by 刘胜强 on 2019/5/15.
//  Copyright © 2019年 TonyStarkPlayer. All rights reserved.
//

#import "ViewController.h"
#include "TSPlayer.hpp"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
//    NSString *path = [[NSBundle mainBundle] pathForResource:@"test_video1" ofType:@"mp4"];
    // 暂时不支持 https
//    NSString *path = @"https://media.w3.org/2010/05/sintel/trailer.mp4";
    NSString *path = @"http://mirror.aarnet.edu.au/pub/TED-talks/911Mothers_2010W-480p.mp4";
    TSPlayer *player = new TSPlayer();
    player->Open([path UTF8String]);
    player->Play();
    
}


@end
