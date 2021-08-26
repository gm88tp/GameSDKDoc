# iOS_SDK_接入说明文档(v3.9.2)

## 适用范围

本文档适用于IOS 9.0及以上的操作系统。
SDK放在SDK文件夹内

本文档按照SDK区分，分为如下：登陆SDK，推送SDK，广告SDK

请按需接入。



## 更新日志

2021.08.25 V3.9.2

1、新增TA SDK，用于数据统计，无接口变化

2、新增七鱼 SDK数据上报，无接口变化

3、新增原生pushCenter.framework



## 登陆SDK

### 一、导入SDK

```objectivec
1、将目录中的(根据给到SDK添加).framework  和(根据给到SDK添加).bundle导入到您的工程中。
2、将目录中的NIMSDK.framework、QYSDK.framework、QYCustomerResource.bundle、QYLanguage.bundle、QYResource.bundle导入到您的工程中。
```

**1、导入方法**

```objectivec
选择(根据给到SDK添加).framework, (根据给到SDK添加).bundle（或将文件拖入Xcode工程目录结构中）文件，在弹出的界面中勾选Copy items into destination group's folder(if needed)，并确保Add To Targets勾选相应target。
```

**2、项目设置**

如下：

（1）点击项目：TARGETS -> General -> Frameworks,Libraries,and Embedded Content ->添加的framework -> Embed & Sign

（2）点击项目：TARGETS -> Build Settings -> Other Linker Flags ->点击“+” -> -ObjC

（3）由于iOS 9 改为https，如果您的项目有使用http，可在Info.plist中添加如下代码：（右键Info.plist用source code打开）

```xml
<key>NSAppTransportSecurity</key> 
<dict> <key>NSAllowsArbitraryLoads</key> <true/> 
</dict> 
```



**3、参数表配置**

* 相关参数需要填写在给到的.bundle的infoset.plist中，详见下表所示。

| 参数       | 类型   | 描述                  | 示例                                |
| ---------- | ------ | --------------------- | ----------------------------------- |
| channel    | String | 渠道id，默认不用修改  | 2                                   |
| gameid     | String | 游戏ID                | 1156                                |
| sdkversion | String | SDK版本（不需要修改） | 3.9.2                               |
| appversion | String | 当前应用的版本        | 1.0                                 |
| trackIoKey | String | 热云数据统计的key     | b17e8a65fd93353c00349ee3a2a565b8    |
| kfkey      | String | 七鱼客服appkey        | 23b744c7f4a4b0688866f1d50facdae8    |
| TAAppId    | String | 数数的appid           | 06842647fb7c48e794aafa3d6d3fc7d9    |
| TAUrl      | String | 数数的url             | https://receiver.ta.thinkingdata.cn |

注：按照需要接入的功能模块接入，修改相关的参数（其他未说明参数均无需修改，此处不说明）。

**4、Info.plist 设置**

```css
<key>NSCameraUsageDescription</key>
	<string>客服功能需要相机权限</string>
	<key>NSMicrophoneUsageDescription</key>
	<string>客服功能需要麦克风权限</string>
	<key>NSPhotoLibraryAddUsageDescription</key>
	<string>使用相册功能为你存储账号密码</string>
  
  <key>NSUserTrackingUsageDescription</key>
	<string>该标识符将用于向您投放个性化广告</string>
```



### 二、接入方法

### 初始化

- 简介：执行全局设置，用于应用启动后，初始化SDK。（必接接口）

**引入头文件**

```objectivec
#import <loginSDK/platInit.h>
```

**调用初始化**

**方法：**

> 此方法默认读取bundle中的参数，如使用此初始化方法，请确认给到的SDK的bundle中的infoset.plist所有参数是否与提供的参数表一致。

```objectivec
+ (void) initSDKapplication:(UIApplication *)application
didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
                    Applede:(id) app;
```

**参数**

| 参数名        | 参数类型      | 是否必需 | 示例          | 描述         |
| ------------- | ------------- | -------- | ------------- | ------------ |
| application   | UIApplication | 是       | application   | 默认参数     |
| launchOptions | NSDictionary  | 是       | launchOptions | 默认参数     |
| app           | AppDelegate   | 是       | self          | 用于数据打点 |

**示例**

```objectivec
-(BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions 
   [platInit initSDKapplication:application didFinishLaunchingWithOptions:launchOptions Applede:self];
    return YES;
}
```

### 其他接口（必接）

- 所有接口都必须接入，每个接口具体含义，请看示例代码

**示例代码**

```objectivec
//这些方法需在AppDelegate（引擎生成相对应的类）中实现，这些方法必须接入，不接入会影响数据打点等相关功能
//记录应用进入后台
- (void)applicationDidEnterBackground:(UIApplication *)application {
     //此接口用于应用进入后台，功能结合打点，推送等
     [platInit applicationDidBecomeActive:application];
}

//记录应用即将进入前台
- (void)applicationWillEnterForeground:(UIApplication *)application {
     [platInit applicationWillEnterForeground:application];
}

//应用被激活
- (void)applicationDidBecomeActive:(UIApplication *)application {      
     [platInit applicationDidBecomeActive:application];
}

//应用即将被终止
- (void)applicationWillTerminate:(UIApplication *)application {
    [platInit applicationWillTerminate:application];
}

//跳转链接两接口均需接入
//跳转链接
-(BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<NSString *,id> *)options{
    return [platInit application:app openURL:url options:options];
}

//跳转链接，此接口用于跳转iOS9之前的方法
-(BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation{
    return  [platInit application:application openURL:url sourceApplication:sourceApplication annotation:annotation];
}
```

### 登陆（模块方法）

* platLogin这个模块是所有登陆相关的方法。

* LoginCallBack这个模块是登陆回调信息的（登陆、登出、切换账号均在此模块的方法中回调结果）。

**引入头文件**

```objectivec
#import <loginSDK/platLogin.h>
#import <loginSDK/LoginCallBack.h>
```

#### 登陆

**参数**

| 参数名         | 类型 | 是否必需 | 示例 | 说明                                     |
| -------------- | ---- | -------- | ---- | ---------------------------------------- |
| mLoginCallBack | id   | 是       | self | 登陆的代理，登陆结果在该代理的方法中回调 |

**方法**

```objectivec
+ (void) login:(id<LoginCallBack>)mLoginCallBack;
```

**示例**

```objectivec
[platLogin login:self];
```

#### 登出

**方法**

```objectivec
+ (void) logout;
```

**示例**

```objectivec
[platLogin logout];
```

#### 切换账号

**方法**

```objectivec
+ (void)logSwitch;
```

**示例**

```objectivec
[platLogin logSwitch];
```

#### 登陆模块代理

```objectivec
<LoginCallBack>
```

设置了代理的地方，可以直接接入代理中的方法

**方法**

```objectivec
-(void)loginOnFinish:(loginStatus)code   Data:(NSDictionary*)Data;
```

**示例**

```objectivec
-(void)loginOnFinish:(loginStatus)code   Data:(NSDictionary*)Data
{
    NSLog(@"回调状态值：%ld",(long)code);
    
    
    NSLog(@"回调：%@",Data);
    if(code==LOGIN_SUCCESS){
      //登陆成功
    }else if(code ==LOGIN_SWITCH){
      //切换账号
    }else if(code== LOGOUT_SUCCESS){
      //登出成功
    } else if (code == LOGIN_UNUSE) {
      //登陆未知，请调用如下
        exit(0);
    }
}
```

#### 查询登陆状态

此方法可用于查询，当前是否已登陆，返回bool类型：YES 已登陆 ；NO 未登陆

**方法**

```objectivec
+ (bool)LoginStaus;
```

**示例**

```objectivec
[platLogin LoginStaus];
```

#### 实名认证

##### 1、实名认证查询

此方法用于查询用户是否实名认证：0:未实名； 1:已实名； 2: 查询失败

**方法**

```objectivec
+(void)checkRealName:(void(^)(int status))success;
```

**示例**

```objectivec
[platLogin checkRealName:^(int status) {
        if (status == 0) {
            //未实名
        } else if (status == 1) {
            //已实名
        } else if (status == 2) {
            //查询失败
        }
    }];
```

##### 2、实名认证页面

此方法用于唤起实名认证的页面

**方法**

```objectivec
+(void)bindSetInfo;
```

**示例**

```objectivec
[platLogin bindSetInfo];
```

#### 防沉迷

##### 1、剩余时长

此方法用于查询用户还有多少游戏时长，返回一个字符串类型

返回 -1 表示没有开启防沉迷

**方法**

```objectivec
+ (NSString *)remainingTime;
```

**示例**

```objectivec
[platLogin remainingTime];
```

##### 2、防沉迷信息

此方法用来返回防沉迷的信息（用户年龄）

返回： 1 表示未实名认证 ；2 表示8岁以下（不包含8岁）； 3 表示8-16（包含8岁，不包含16岁）； 4 表示16-18（包含16岁，不包含18岁）；5 表示18岁以上（包含18） 

**方法**

```objectivec
+ (NSString *)antiaddictionInfo;
```

**示例**

```objectivec
[platLogin antiaddictionInfo];
```

#### 用户相关

在用户登陆后，可使用如下接口，查询用户的一些信息。

##### 1、用户信息

返回的是UserInfoModel这个类的对象，里面包含所有用户信息

**方法**

```objectivec
+(UserInfoModel*)getUserInfo;
```

**示例**

```objectivec
UserInfoModel *userInfo = [platLogin getUserInfo];
```

##### 2、用户uid

返回用户的唯一id，字符串类型

**方法**

```objectivec
+ (NSString*) getUid;
```

**示例**

```objectivec
[platLogin getUid];
```

##### 3、用户昵称

返回用户昵称，字符串类型

**方法**

```objectivec
+ (NSString*) getNickname;
```

**示例**

```objectivec
[platLogin getNickname];
```

##### 4、用户token

返回用户token，字符串类型

**方法**

```objectivec
+ (NSString*) getToken;
```

**示例**

```objectivec
[platLogin getToken];
```

### 支付（模块方法）

* platPurchase类是支付接口类

* purchaseModel是支付对象，需要将所有支付相关的参数赋值给这个对象

* PurchaseCallBack是支付的回调类，客户端回调支付相关结果信息

**引入头文件**

```objectivec
#import <loginSDK/platPurchase.h>
#import <loginSDK/purchaseModel.h>
#import <loginSDK/PurchaseCallBack.h>
```

#### 支付

**参数**

| 参数名   | 类型             | 是否必需 | 说明                           |
| -------- | ---------------- | -------- | ------------------------------ |
| payInfo  | purchaseModel    | 是       | 传入支付信息                   |
| CallBack | PurchaseCallBack | 是       | 设置支付回调的代理，请输入self |

**方法**

```objectivec
/*
 <purchaseModel>
 productID： id <必传>
 productName： 名<必传>
 productPrice：价格，可能有的SDK只支持整数<必传>
 productDes： 描述
 gameReceipts： 透传参数，订单信息<必传>
 roleID：游戏角色id
 roleName：游戏角色名
 roleLevel： 游戏角色等级
 vipLevel：Vip等级
 partyName： 帮派、公会等
 zoneID： 服务器id，若无填1
 zoneName： 服务器名
 text：扩展字段
 notifyURL：回调地址 可传可不传，不传使用默认
 */
+ (void) purchase:(purchaseModel *)payInfo CallBack:(id<PurchaseCallBack>) callBack;
```

**示例**

```objectivec
purchaseModel* mPayInfo = [[purchaseModel alloc] init];
    /** 商品id *///1101
    mPayInfo.productID = @"商品id ";
    /** Y 商品名 */
    mPayInfo.productName = @"商品名";
    /** Y 商品价格 */
    mPayInfo.productPrice = @"商品价格";
    /** 商品描述（不传则使用productName） */
    mPayInfo.productDes=@"商品描述";
    /** Y 商品订单号 透传数据*/
    mPayInfo.gameReceipts=@"商品订单号 透传数据 请保持唯一性";
    /** Y 游戏角色id */
    mPayInfo.roleID=@"554";
    /** Y 游戏角色名 */
    mPayInfo.roleName=@"这是角色名字";
    /** Role_Name */
    mPayInfo.roleLevel=@"10";
    /** Y Vip等级 */
    mPayInfo.vipLevel=@"10";
    /** Y 帮派、公会等 */
    mPayInfo.partyName=@"这是工会";
    /** Y 服务器id，若无填“1” */
    mPayInfo.zoneID=@"1";
    /** Y 服务器名 */
    mPayInfo.zoneName=@"这是服务器";
    /** N 扩展字段 */
    mPayInfo.text=@"这是扩展字段";
    /**
     回调地址 可传可不传，不传使用默认
     */
    //mPayInfo.tenovnotifyURL = @"http://demo.gm88.com/ok.php?gameid=1156&promote=2";
    [platPurchase purchase:mPayInfo CallBack:self];
```

#### 支付回调代理

```objectivec
<PurchaseCallBack>
```

设置了代理的地方，可以直接接入代理中的方法

**方法**

```objectivec
-(void)purchaseOnFinish:(purchaseStatus)code   Data:(NSDictionary*)Data;
```

**示例**

```objectivec
- (void)purchaseOnFinish:(purchaseStatus)code Data:(NSDictionary *)Data{
    if (code ==PURCHASE_SUCCESS){
        //购买成功
       } else if (code== PURCHASE_FAILED){
        //购买失败
       } else if (code==PURCHASE_CANCEL){
        //取消购买
       } else if (code==PURCHASE_UNKNOWN){
        //未知问题
       }
}
```

### 工具（模块方法）

**引入头文件**

```objectivec
#import <loginSDK/platTools.h>
```

#### 1、SDK版本

此方法用于获取SDK版本号，返回字符串类型

**方法**

```objectivec
+(NSString*)versions;
```

**示例**

```objectivec
[platTools versions];
```

#### 2、角色上报

此方法用于角色上报

**参数**

| 参数名   | 类型     | 是否必需 | 示例 | 说明                                           |
| -------- | -------- | -------- | ---- | ---------------------------------------------- |
| name     | NSString | 是       | a    | 角色名称                                       |
| level    | NSString | 是       | 1    | 游戏等级                                       |
| serverID | NSString | 是       | 1    | 区服                                           |
| roleID   | NSString | 是       | 1    | 角色id                                         |
| status   | NSString | 是       | 1    | 状态值：1:创建角色；2:完成新手引导；3:等级升级 |
| vipLevel | NSString | 是       | 0    | 游戏vip等级（没有vip制度，可以传0）            |

**方法**

```objectivec
+ (void)platRoleName:(NSString *)name
            gameLevel:(NSString *)level
             serverID:(NSString *)serverID
               roleID:(NSString *)roleID
               status:(NSString *)status
            vipLevel:(NSString *)vipLevel;
```

**示例**

```objectivec
[platTools platRoleName:@"a"
            gameLevel:@"1"
             serverID:@"1"
               roleID:@"1"
               status:@"1"
            vipLevel:@"0"];
```

#### 3、打开链接

此方法用于在游戏内打开链接，显示web页面

**参数**

| 参数名 | 类型     | 是否必需 | 示例                  | 说明     |
| ------ | -------- | -------- | --------------------- | -------- |
| info   | NSString | 是       | https://www.baidu.com | 链接地址 |

**方法**

```objectivec
+ (void)agreement:(NSString * )info;
```

**示例**

```objectivec
[platTools agreement:@"https://www.baidu.com"];
```

#### 4、获取idfa

**方法**

```objectivec
+ (NSString *)returnIDFA;
```

**示例**

```objectivec
[platTools returnIDFA];
```

#### 5、获取资源包中的配置参数

**参数**

| 参数名 | 类型     | 是否必需 | 示例   | 说明          |
| ------ | -------- | -------- | ------ | ------------- |
| str    | NSString | 是       | gameid | 配置参数的key |

**方法**

```objectivec
+ (NSString*)getInfoString:(NSString*)str;
```

**示例**

```objectivec
[platTools getInfoString:@"gameid"];
```

#### 



















## 广告SDK

### 一、导入SDK

```objectivec
1、将目录中的advertisingCenter.framework  和(根据给到SDK添加).bundle导入到您的工程中。
```

**1、导入方法**

```objectivec
选择(根据给到SDK添加).framework, (根据给到SDK添加).bundle（或将文件拖入Xcode工程目录结构中）文件，在弹出的界面中勾选Copy items into destination group's folder(if needed)，并确保Add To Targets勾选相应target。
```

**2、项目设置**

如下：

（1）点击项目：TARGETS -> General -> Frameworks,Libraries,and Embedded Content ->添加的framework -> Embed & Sign

（2）点击项目：TARGETS -> Build Settings -> Other Linker Flags ->点击“+” -> -ObjC

（3）由于iOS 9 改为https，如果您的项目有使用http，可在Info.plist中添加如下代码：（右键Info.plist用source code打开）

```xml
<key>NSAppTransportSecurity</key> 
<dict> <key>NSAllowsArbitraryLoads</key> <true/> 
</dict> 
```

**3、Info.plist 设置**

```css
<key>SKAdNetworkItems</key>
	<array>
		<dict>
			<key>SKAdNetworkIdentifier</key>
			<string>238da6jt44.skadnetwork</string>
		</dict>
		<dict>
			<key>SKAdNetworkIdentifier</key>
			<string>22mmun2rn5.skadnetwork</string>
		</dict>
	</array>
```



### 二、接入方法

#### 头文件

```objectivec
#import <advertisingCenter/adPlatform.h>
```

#### 初始化

**参数**

| 参数名 | 类型     | 是否必需 | 示例 | 说明   |
| ------ | -------- | -------- | ---- | ------ |
| gameID | NSString | 是       | 1156 | 游戏id |

**方法**

```objectivec
+ (void)setupPlatformGameID:(NSString *)gameID;
```

**示例**

```objectivec
[adPlatform setupPlatformGameID:@"2780"];
```

#### 播放广告

**方法**

```objectivec
+ (void)pullAdvertisingReward;
```

**示例**

```objectivec
[adPlatform pullAdvertisingReward];
```

#### 





















## 推送SDK

#### 适用范围

本文档适用于IOS 9.0及以上的操作系统。 SDK放在SDK文件夹内

### 信鸽推送

#### 接入流程

#### 1.导入SDK

```objectivec
将目录中的(根据给到SDK添加).framework  和(根据给到SDK添加).bundle导入到您的工程中。
```

**导入方法：在工程目录结构中，右键选择Add->Existing Files...，**

```
选择(根据给到SDK添加).framework, (根据给到SDK添加).bundle（或将文件拖入Xcode工程目录结构中）文件，在弹出的界面中勾选Copy items into destination group's folder(if needed)，并确保Add To Targets勾选相应target。
```

#### 接入方法说明

##### AppDelegate导入头文件

引入头文件 `

```objectivec
#import <serverPush/pushPlatform.h>
```

#### 方法用途：

##### 初始化

用于应用启动后，初始化推送SDK。

**使用地方**

在-(**BOOL**)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions方法中调用

**参数**

| 参数名   | 类型     | 必需 | 示例            | 说明        |
| -------- | -------- | ---- | --------------- | ----------- |
| appID    | UInt32   | 是   | 1600005427      | push应用id  |
| appKey   | NSString | 是   | @"IIOMAQYO58GB" | push应用key |
| delegate | id       | 是   | self            | 代理        |

**方法**

```objectivec
+ (void)startXGWithAppID:(uint32_t)appID appKey:(nonnull NSString *)appKey delegate:(  id )delegate;
```

**示例**

```objectivec
[pushPlatform startXGWithAppID:1600005427 appKey:@"IIOMAQYO58GB"  delegate:self ];
```

**注：如果接入时使用了给到的loginSDK.h和loginSDK.m，那么在`+ (void)initDelegate:( id )delegate;`方法中，当pushFoundation设置为YES时，已经调用初始化推送SDK，相关参数配置在login.bundle的infoset.plist中。**

### 原生推送

#### 接入流程

#### 1、导入SDK

```
将pushCenter.framework导入到您的工程中。
```

**导入方法：在工程目录结构中，右键选择Add->Existing Files...，**

```
选择(根据给到SDK添加).framework, (根据给到SDK添加).bundle（或将文件拖入Xcode工程目录结构中）文件，在弹出的界面中勾选Copy items into destination group's folder(if needed)，并确保Add To Targets勾选相应target。
```

**点击项目：TARGETS -> General -> Frameworks,Libraries,and Embedded Content ->pushCenter.framework -> Embed & Sign **

#### 2、开启push

（1）点击项目：TARGETS -> Signing & Capabilities -> 点击“+” -> 添加Push Notifications

（2）点击项目：TARGETS -> Signing & Capabilities -> 点击“+” -> 添加Background Modes ->勾选“Remote notifications”

#### 接入方法说明

#### AppDelegate导入头文件

引入头文件 

```objectivec
#import <pushCenter/pushPlat.h>
```

#### 3、方法

#### 初始化

用于应用启动后，初始化推送SDK。

**使用地方**

在-(**BOOL**)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions方法中调用

**参数**

| 参数名   | 类型     | 必需 | 示例    | 说明   |
| -------- | -------- | ---- | ------- | ------ |
| gameId   | NSString | 是   | @"1156" | 游戏id |
| delegate | id       | 是   | self    | 代理   |

**方法**

```objectivec
+ (void)initPush:(id)delegate gameId:(NSString *)gameId;
```

**示例**

```objectivec
[pushPlat initPush:self gameId:@"1156"];
```

#### 代理

```
<UNUserNotificationCenterDelegate>
```

**使用地方**

在AppDelegate添加。

**方法和示例**

```objectivec
//即将展示通知
- (void)userNotificationCenter:(UNUserNotificationCenter *)center willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(UNNotificationPresentationOptions options))completionHandler __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0)) {
    //此处设置声音，角标，警告。设置了即使app在前台也可以显示推送信息
    completionHandler(UNNotificationPresentationOptionBadge|UNNotificationPresentationOptionSound|UNNotificationPresentationOptionAlert);
}

// 收到通知，在后台或者前台点击消息时会触发
- (void)userNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void(^)(void))completionHandler __API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0)) __API_UNAVAILABLE(tvos) {
    //可以解析相关信息，做相应页面跳转
    NSDictionary *dic = response.notification.request.content.userInfo;
    NSLog(@"推送信息%@", dic);
  
  //上报接收到消息
    [pushPlat receiveRemoteNotifications:dic];
  
    completionHandler();
}

// 消息管理的设置
- (void)userNotificationCenter:(UNUserNotificationCenter *)center openSettingsForNotification:(nullable UNNotification *)notification __API_AVAILABLE(macos(10.14), ios(12.0)) __API_UNAVAILABLE(watchos, tvos) {
//如果没有需要特殊设置，可以不设置
}
```



#### 授权

用于获取通知权限

调用方法会获得权限结果：1:表示允许通知；2:表示不允许

**方法**

```objectivec
+ (void)requestAuthorizationForRemoteNotifications:(void(^)(NSInteger result))callback;
```

**示例**

```objectivec
[pushPlat requestAuthorizationForRemoteNotifications:^(NSInteger result) {
             if (result == 1) {
                 NSLog(@"允许");
             } else if (result == 2) {
                 NSLog(@"不允许");
             }
         }];
```



#### 获取deviceToken

用于获取APNS的用户手机的deviceToken

**使用地方**

在AppDelegate的\- (**void**)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken；方法中调用

**参数**

| 参数名      | 类型   | 必需 | 示例        | 说明                                  |
| ----------- | ------ | ---- | ----------- | ------------------------------------- |
| deviceToken | NSData | 是   | deviceToken | 系统在注册远程通知后返回给的设备token |

**方法**

```objectivec
+ (void)didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;
```

**示例**

```objectivec
[pushPlat  didRegisterForRemoteNotificationsWithDeviceToken:deviceToken];
```

#### 上报deviceToken

在用户登陆后，用于上报系统返回的deviceToken

**使用地方**

登陆回调方法中。

**参数**

| 参数名   | 类型     | 必需 | 示例           | 说明                        |
| -------- | -------- | ---- | -------------- | --------------------------- |
| userInfo | NSString | 是   | ODc3***25HR0U= | 传入登陆的token（用户标识） |

**方法**

```objectivec
+ (void)upDeviceTokenWithUser:(NSString *)userInfo;
```

**示例**

```objectivec
[pushPlat upDeviceTokenWithUser:[NSString stringWithFormat:@"%@",[Data objectForKey:@"token"]]];
```

#### 上报通知

**使用地方**

请在代理方法\- (**void**)userNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(**void**(^)(**void**))completionHandler中调用。

**参数**

| 参数名 | 类型         | 必需 | 示例                                           | 说明                     |
| ------ | ------------ | ---- | ---------------------------------------------- | ------------------------ |
| dic    | NSDictionary | 是   | response.notification.request.content.userInfo | 代理方法中解析的推送信息 |

**方法**

```objectivec
+ (void)receiveRemoteNotifications:(NSDictionary *)dic;
```

**示例**

```objectivec
[pushPlat receiveRemoteNotifications:dic];
```

#### 清除角标

调用此方法，可以清除角标，请按需调用

**方法**

```objectivec
+ (void)applicationIconBadgeClear;
```

**示例**

```objectivec
[pushPlat applicationIconBadgeClear];
```



