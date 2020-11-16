//
//  wfnjiStatus.h
//  wfnjiSDK_PLUS
//
//  Created by wfnji on 2018/3/21.
//  Copyright © 2018年 wfnji. All rights reserved.
//

#ifndef wfnjiStatus_h
#define wfnjiStatus_h

/**
 * wfnjiStatus 状态值
 * */
typedef NS_ENUM(NSInteger, wfnjiStatus){
    /** 登陆成功 */
    LOGIN_SUCCESS = 0,
    /** 切换账号*/
    LOGIN_SWITCH = 4,
    /** 退出成功*/
    LOGOUT_SUCCESS = 5,
    /**实名成功   */
    BIND_SUCCESS =6,
    /** 支付成功 */
    PAY_SUCCESS = 10,
    /** 支付失败*/
    PAY_FAILED = 11,
    /** 支付取消 */
    PAY_CANCEL = 12,
    /** 未知支付状态*/
    PAY_UNKNOWN = 13
};

typedef NS_ENUM(NSInteger ,  selectStyle) {
    selectStyleCreateTheRole   = 1 ,
    selectStyleCompleteNewbieGuide
    
};

/**
 用于内部界面切换的状态值
 
 - wfnji_CODE_LOGIN_SUCCESS: 登陆成功
 - wfnji_CODE_LOGIN_FAILED: 登陆失败
 - wfnji_CODE_LOGIN_CANCEL: 登陆取消
 - wfnji_CODE_LOGIN_SWITCH: 切换账号
 - wfnji_CODE_LOGIN_FINISH: 登录完成,显示登录框
 - wfnji_CODE_ACTION_LOGIN_TO_PHONE: 用户选择手机登录
 - wfnji_CODE_ACTION_REGISTER_AND_FORGETPASSWORD: 进入注册忘记密码界面
 */
typedef NS_ENUM(NSInteger, wfnjiUserStatus) {
    /** 登陆成功 */
    wfnji_CODE_LOGIN_SUCCESS = 0,
    /** 登陆失败*/
    wfnji_CODE_LOGIN_FAILED = 1,
    /** 登陆取消*/
    wfnji_CODE_LOGIN_CANCEL = 2,
    /** 切换账号*/
    wfnji_CODE_LOGIN_SWITCH = 3,
    /** 登录完成,显示登录框*/
    wfnji_CODE_LOGIN_FINISH = 100,
    /** 用户选择手机登录列表*/
    wfnji_CODE_ACTION_LOGIN_TO_PHONE_LIST = 1009,
    /** 用户选择手机登录*/
    wfnji_CODE_ACTION_LOGIN_TO_PHONE = 1010,
    /** 进入注册忘记密码界面*/
    wfnji_CODE_ACTION_REGISTER_AND_FORGETPASSWORD = 1015
};

#endif /* wfnjiStatus_h */
