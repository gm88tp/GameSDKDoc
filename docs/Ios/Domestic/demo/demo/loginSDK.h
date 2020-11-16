//
//  loginSDK.h
//  demo
//
//  Created by dingqw on 2020/3/23.
//  Copyright © 2020 com.english. All rights reserved.
//
#import <UIKit/UIKit.h>
#import <loginSDK/wfnjiPlat.h>
#define shareFoundation  YES
#define pushFoundation   YES

#ifdef shareFoundation
#import <shareGroup/sharePlatform.h>
#endif

#ifdef pushFoundation
#import <serverPush/pushPlatform.h>
#endif
 


NS_ASSUME_NONNULL_BEGIN

@interface loginSDK : wfnjiPlat
+ (void)initDelegate:(  id )delegate;


+(BOOL)shareApplication:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options;
@end


NS_ASSUME_NONNULL_END
