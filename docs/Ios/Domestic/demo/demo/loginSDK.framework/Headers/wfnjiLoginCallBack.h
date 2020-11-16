//
//  LoginCallBack.h  
//  wfnjiSDK
//
//  Created by wfnji on 2018/6/11.
//  Copyright © 2018年 wfnji. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "wfnjiStatus.h"
@protocol wfnjiLoginCallBack <NSObject>

/**
 登录回调接口
 
 @param code 状态值
 @param Data 数据
 */
-(void)onFinish:(wfnjiStatus)code Data:(NSDictionary *)Data;
@end
