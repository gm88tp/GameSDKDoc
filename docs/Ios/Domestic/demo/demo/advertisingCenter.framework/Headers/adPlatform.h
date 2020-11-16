//
//  adPlatform.h
//  advertisingCenter
//
//  Created by xyting on 2019/4/29.
//  Copyright © 2019 Advertising. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN

@interface adPlatform : NSObject
@property (nonatomic,strong)NSString  * gameID;
//注册方法
+ (void)setupPlatformReyunKey:(NSString *)key gameID:(NSString *)gameID  GDTID:(NSString *)gdtID GDTKey:(NSString *)gdtkey;
//获取设备标识符
+ (NSString *)getUserSing;
//拉起激励视屏
+(void)pulladvertisingCenterRequest;
/**
 
 上传用户信息用户排行榜
 @param name 昵称
 @param score 分数
 @param usersing 唯一标识
 @param result 返回结果
 
 */
+(void)uploadRanklistUserName:(NSString *)name userScore:(NSString *)score userSing:(NSString *)usersing resultInfo:(void(^)(NSDictionary *info))result;
            
            
/**
 获取排行版信息
 
 @param usersing 唯一标识
 @param result 返回结果
 */
+ (void)getRanklistuserSing:(NSString * )usersing resultInfo:(void(^)(NSDictionary *info))result;


@end

NS_ASSUME_NONNULL_END
