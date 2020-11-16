//
//  wfnjiUserInfo.h
//  wfnjiSDK
//
//  Created by wfnji on 2018/3/23.
//  Copyright © 2018年 wfnji. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface wfnjiUserInfo : NSObject
/**
 用户的 UID
 */
@property (nonatomic, copy) NSString* uid;

/**
 用户的 Nickname
 */
@property (nonatomic, copy) NSString* nickname;

/**
 用户的 sid
 */
@property (nonatomic, copy) NSString* sid;

/**
 用户的 token
 */
@property (nonatomic, copy) NSString* token;

/**
 用户的头像地址
 */
@property (nonatomic, copy) NSString* face;//头像地址

/**
 用户的币数量
 */
@property (nonatomic, copy) NSString* coins;//怪币

/**
 用户是否绑定手机
 */
@property (nonatomic,assign) BOOL need_bind;//是否绑定手机

/**
 用户券数量
 */
@property (nonatomic,assign) int promote_coin;//代金券的数量

@property (nonatomic,assign) BOOL  has_discount;

/**
 用户积分
 */
@property (nonatomic) int user_point;//积分

@property (nonatomic, strong) NSString* phone;//手机号

@property (nonatomic, assign) BOOL  user_new;

@property (nonatomic) int vip_level;//vip等级

/**
 UserInfo转NSDictionary
 
 @param mUserInfo 用户信息
 @return NSDictionary
 */
+(NSDictionary*)UserInfoToNSDictionary:(wfnjiUserInfo*)mUserInfo;

/**
 NSDictionary转wfnjiUserInfo
 
 @param dic NSDictionary转wfnjiUserInfo
 @return wfnjiUserInfo
 */
+(wfnjiUserInfo*)NSDictionaryToUserInfo:(NSDictionary*)dic;
@end
