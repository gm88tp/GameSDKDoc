//
//  AppDelegate.m
//  demo
//
//  Created by rosehyird on 2020/6/3.
//  Copyright © 2020 rosehyird. All rights reserved.
//

#import "AppDelegate.h"
#import "loginSDK.h"
#import "advertisingCenter/adPlatform.h"
@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    [loginSDK initDelegate:self];
    [adPlatform setupPlatformReyunKey:@"0104c3cf2210c0973cf8b59be52635cd" gameID:@"2536"  GDTID: @"1109157353" GDTKey:@"657084a6a4ad02dcb6f7504af81c587b"];
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
     [loginSDK   applicationDidEnterBackground:application];
   
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    
     [loginSDK  applicationWillEnterForeground:application];
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}
-(BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options{
    
    [loginSDK shareApplication:app openURL:url options:options];
    return YES;
}


@end
