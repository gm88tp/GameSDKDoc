//
//  sharePlatform.h
//  shareGroup
//
//  Created by xyting on 2020/3/17.
//  Copyright © 2020 com.group. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "shareContentItem.h"
NS_ASSUME_NONNULL_BEGIN
typedef void(^ShareResultlBlock)(NSInteger shareResult);

typedef  NS_ENUM(NSInteger,  channelType){
    channelTypeChatq = 0,
    channelTypeChatw ,
    channelTypeWB
};

typedef NS_ENUM(NSInteger, shareType){
    
       ShareTypeWeiBo = 0,   // 新浪微博
       ShareTypeQQ,          // QQ好友
       ShareTypeQQZone,      // QQ空间
       ShareTypeWTimeline,   // 朋友圈
       ShareTypeWSession,    // 微信朋友
       ShareTypeWFavorite,   // 微信收藏
};

typedef NS_ENUM(NSInteger , statusCode) {
    statusCodeSuccess=0,
    statusCodeCancel=-2
};
@interface sharePlatform : NSObject
+(sharePlatform *)getInit;

- (void)registerAppwchat:(NSString *)wappid universalLinkAppwchat:(NSString *)wchatlink wbAppkey:(NSString *)appkey tenchentId :(NSString *)qAppid universalLinkqwchat:(NSString *)qlink;

+ (void)shareWithContent:(shareContentItem *)contentObj
               shareType:(shareType)shareType
             shareResult:(ShareResultlBlock)shareResult;


-(BOOL)shareApplication:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options;
+ (void)wqewq;

@end

NS_ASSUME_NONNULL_END
