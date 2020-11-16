//
//  wfnjiPlat.h
//  wfnjiSDK
//
//  Created by wfnji on 2018/3/21.
//  Copyright © 2018年 wfnji. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "wfnjiOrderModel.h"
#import "wfnjiUserInfo.h"
#import "wfnjiLoginCallBack.h"
#import "wfnjiPayCallBack.h"
 
@interface wfnjiPlat : NSObject

/*!
 单例,预留接口
 
 @return wfnjiPlat
 */
+(wfnjiPlat*)getInstance;
/**
 SDK注册激活
 */

/**
 AppDelegate.h内的接口,主要用去支付.游戏从后台返回用
 
 @param application application
 */
+(void)applicationWillEnterForeground:(UIApplication *)application;



/**
 AppDelegate.h内的接口
 
 @param app application
 需要调用一些事件激活
 */
+ (void)applicationDidBecomeActive:(UIApplication *)app;
/**
 AppDelegate.h内的接口,进入后台
 
 @param application application
 */
+(void)applicationDidEnterBackground:(UIApplication *)application;
/*
 
 要针对所有广告系列（包括使用通用链接的广告系列）将应用内事件作为转化衡量，
 您必须将以下代码段添加到应用的 application:continueUserActivity:restorationHandler 方法。
 */
+ (BOOL)application:(UIApplication *)application  continueUserActivity:(NSUserActivity *)userActivity;

/**
 AppDelegate.
 
 @param app app
 @param url url
 @param options options
 @return BOOL
 */
+(BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<NSString *,id> *)options;

/**
 AppDelegate.h内的接口
 
 @param application application
 @param url url
 @param sourceApplication sourceApplication
 @param annotation annotation
 @return BOOL
 */
+(BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation;


 

/**
 必须最先接入的方法  平台初始化方法
 
 gameid 游戏的id
 promote 渠道
 
 */
+ (void) initSDK:(NSString*)gameid
      setPromote:(NSString*)promote
     application:(UIApplication *)application
didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
 appsFlyerDevKey:(NSString *)devKey
      appleAppID:(NSString *)appID
     GGkClientID:(NSString *)kClientID
         Applede:(id) app
         Result :(void(^)(NSInteger tag))tag;


+ (void) initSDK:(NSString*)gameid
setPromote:(NSString*)promote
        trackKey:(NSString *)Key;
/**
 登录返回的传递数据
 退出返回的传递数据
 */
//+ (void)loginUserInfo:(void(^)(NSDictionary *))userInfo;
/**
 必须接入的方法  登录
 
 @param mLoginCallBack 回调
 */
+ (void) login:(id<wfnjiLoginCallBack>)mLoginCallBack;


/**
 支付发起与结果
 */


+ (void) wfnjipay:(wfnjiOrderModel *)payInfo CallBack:(id<wfnjiPayCallBack>) callBack;



/**
 查看当前的登录状态
 
 @return true or false
 */
+ (BOOL) isLogin;

/**
 注销账号
 */
+ (void) logout;


/**
 获取用户信息
 
 @return 用户信息
 */
+(wfnjiUserInfo*)getUserInfo;

/**
 获取游戏用户的唯一ID
 
 @return uid
 */
+ (NSString*) getUid;


/**
 获取用户名
 
 @return Nickname
 */
+ (NSString*) getNickname;

/**
 获取Token
 
 @return Token
 */
+ (NSString*) getToken;


 
/**
 SDK切换账号方法
 */
+ (void)logSwitch;
/**
 判断是否已登录
 */
+ (bool)LoginStaus;

/**
 获取当前 SDK 的版本号
 
 @return SDK 版本号，用Jenkins 打包会自动加上时间戳
 */
+(NSString*)versions;





/**
 
 获取当前游戏用户注册或新手引导
 */
+(void)wfnjicreateTheRoleOrCompleteNewbieGuide:(selectStyle)selectStyle;






/**
 
 获取当前游戏的角色
 角色名字：name
 游戏等级：level
 区服:   serverID
 状态值默认选择<3>:status 1:创建角色 2:完成新手引导 3:等级升级
 */
+ (void)setGameRoleName:(NSString *)name  gameLevel:(NSString *)level serverID:(NSString *)serverID roleID:(NSString *)roleid statusType:(NSString *)status;


/**
 c创建角色页面
 */
+ (void)createRole;
/**
 进入游戏主页面
 */
+ (void)showGamePage;

/**
 选择屈服页面
 关闭
 */
+ (void)selectArea;

+ (NSString *)setlaugulgString:(NSString *)str;

+ (NSString*)getInfoString:(NSString*)str;

 + (void) showToolBar ;
  
  
  + (void) removeToolBar ;


+ (void)setLoadingImg:(UIImage *)image Color:(UIColor *)color loadingStyle:(NSInteger )style imgRect:(CGRect)rec;
+ (void)removeLoadingImg;



+ (void)setCheckoutV:(int )status checkoutStr:(NSString * )str  detaileTitle:(NSString *)detaileTitle;


+ (void)removeCheckoutVU;

//公开的打点数据方法
+ (void)LogInfo:(NSString *)eventName EventDic:(NSDictionary *)info;




//显示绑定页面
+ (void)userInfoBindView;


+ (void)showMarkView;


+ (void)showWinLog;

//返回渠道号
+ (NSString *)returnChannelID;

//返回设备号
+ (NSString *) returnIDFV ;

+ (NSString *) returnIDFA ;

+ (void)agreement:(NSString * )info;

//查询和谐配置的
+ (void)SysSetting:(void(^)(NSDictionary *info))Success;

/**
获取用户信息是否实名

status 0 未实名 1实名 2查询失败
*/
+(void)checkRealName:(void(^)(int status))success;

//唤起实名页面的
+(void)bindSetInfo;



+(void)log:(NSString*)str;

@end


