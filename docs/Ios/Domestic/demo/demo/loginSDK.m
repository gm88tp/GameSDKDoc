//
//  loginSDK.m
//  demo
//
//  Created by dingqw on 2020/3/23.
//  Copyright © 2020 com.english. All rights reserved.
//

#import "loginSDK.h"

@implementation loginSDK
+ (void)initDelegate:(  id )delegate{
    [loginSDK initSDK:[loginSDK getInfoString:@"gameid"] setPromote:[loginSDK  getInfoString:@"channel"] trackKey:[loginSDK getInfoString:@"trackKey"]];
    
    #ifdef shareFoundation

    [[sharePlatform getInit] registerAppwchat:[loginSDK getInfoString:@"weichatAppid"] universalLinkAppwchat:[loginSDK getInfoString:@"wlink"] wbAppkey:[loginSDK getInfoString:@"wbAppKey"] tenchentId:[loginSDK getInfoString:@"tenchentId"] universalLinkqwchat:[loginSDK getInfoString:@"tlink"]];
    #endif
    
    #ifdef pushFoundation
    
    
    NSString *str = [loginSDK getInfoString:@"pushAppid"];
    UInt32 num;
    sscanf([str UTF8String], "%u", &num);
    NSLog(@"%u",(unsigned int)num);
    [pushPlatform startXGWithAppID:num appKey:[loginSDK getInfoString:@"pushAppkey"]  delegate:delegate ];
  
    #endif
}

+(BOOL)shareApplication:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options{
     #ifdef shareFoundation
     return [[sharePlatform getInit] shareApplication:app openURL:url options:options];
     #endif
    return YES;
}
@end
