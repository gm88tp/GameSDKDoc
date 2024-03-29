# iOS_SDK_接入说明文档

## 适用范围

本文档适用于IOS 9.0及以上的操作系统。
SDK放在SDK文件夹内

如需接入除本文功能之外，详见如下：

[分享/接入文档](https://github.com/gm88tp/Ios-Domestic-SDK-Demo/blob/master/docs/share.md)

[广告/接入文档](advertising.md)



## 更新日志

自V3.8.3开始，loginSDK的头文件名称从wfnji开头更改为tenov开头。

## 接入流程

### 准备

#### 1.导入SDK

```objectivec
将目录中的loginSDK.h,loginSDK.m (根据给到SDK添加).framework  和(根据给到SDK添加).bundle导入到您的工程中。
```

**导入方法：在工程目录结构中，右键选择Add->Existing Files...，**

```objectivec
选择(根据给到SDK添加).framework, (根据给到SDK添加).bundle（或将文件拖入Xcode工程目录结构中）文件，在弹出的界面中勾选Copy items into destination group's folder(if needed)，并确保Add To Targets勾选相应target。
```

**注：**

- 在General—— >>Frameworks,Libraries,and Embedded Content—— >>将添加的framework设置成Embed & Sign
- 在Build Settings——>> Other linker Flags 设置-ObjC
- 如果使用推送framework，请在Signing & Capabilities ——>>1、 添加Background Modes 勾选Remote notifications；2、添加Push Notifications。

### 参数相关

#### 给到的.bundle

* 使用给到的loginSDK.h和loginSDK.m，可以使用此文档所有书写的接口。
* 相关参数需要填写在给到的.bundle的infoset.plist中，详见下表所示，所有参数的注释。

| 参数         | 类型   | 描述                   | 示例                             |
| ------------ | ------ | ---------------------- | -------------------------------- |
| channel      | String | 渠道id，默认不用修改   | 121                              |
| gameid       | String | 游戏ID                 | 1156                             |
| trackKey     | String | 热云数据统计的key      | b17e8a65fd93353c00349ee3a2a565b8 |
| weichatAppid | String | 微信的appid            | wx180c8f3360de0b12               |
| wlink        | String | 微信的链接地址         | https://......                   |
| wbAppKey     | String | 微博的appkey           | 3118377197                       |
| wblink       | String | 微博的链接地址         | https://......                   |
| rolelevel    | String | 角色等级，默认不用修改 | 6                                |
| tlink        | String | 腾讯的链接地址         | https://......                   |
| tenchentId   | String | 腾讯的客户端id         | 101860838                        |
| pushAppid    | String | push的appid            | 1600005427                       |
| pushAppkey   | String | push的appkey           | IIOMAQYO58GB                     |

注：按照需要接入的功能模块接入，修改相关的参数。

### 接入方法说明

#### AppDelegate导入头文件

   引入头文件  

```objectivec
#import "loginSDK.h"
```

### 初始化

用于应用启动后，初始SDK。

**使用地方**

在-(**BOOL**)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions方法中调用

| 参数名   | 类型 | 必需 | 示例 | 说明     |
| :------- | :--- | ---- | ---- | -------- |
| delegate | id   | 是   | self | 对象传递 |

**方法**

```objectivec
+ (void)initDelegate:(  id )delegate;
```

**示例**

```objectivec
[loginSDK  initDelegate: self ];
```

### 进入后台

记录应用进入后台

**使用地方**

在-(void)applicationDidEnterBackground:(UIApplication *)application方法中调用

| 参数名      | 类型          | 必需 | 示例        | 说明 |
| ----------- | ------------- | ---- | ----------- | ---- |
| application | UIApplication | 是   | application | 默认 |

**方法**

```objectivec
+(void)applicationDidEnterBackground:(UIApplication *)application
```

**示例**

```objectivec
 [loginSDk applicationDidEnterBackground:application];
```

### 进入前台

记录应用进入前台

**使用地方**

在- (void)applicationWillEnterForeground:(UIApplication *)application方法中调用

| 参数名      | 类型          | 必需 | 示例        | 说明 |
| ----------- | ------------- | ---- | ----------- | ---- |
| application | UIApplication | 是   | application | 默认 |

**方法**

```objectivec
+(void)applicationDidEnterBackground:(UIApplication *)application
```

**示例**

```objectivec
 [loginSDK applicationWillEnterForeground:application];

```

###方法用途：

分享回调

**使用地方**

在-(BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options方法中调用

**方法**

```objectivec
+(BOOL)shareApplication:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options;

```

**示例**

```objectivec
 [loginSDK shareApplication:app openURL:url options:options];

```

### 即将终止

即将杀死进程，用于计算时长

**使用地方**

在\- (void)applicationWillTerminate:(UIApplication *)application方法总调用

**方法**

```objectivec
+ (void)applicationWillTerminate:(UIApplication *)application;
```

**示例**

```objectivec
[loginSDK applicationWillTerminate:application];
```



### 项目info.plist 配置

```css
  <key>NSCameraUsageDescription</key>
	<string>客服功能需要相机权限</string>
	<key>NSMicrophoneUsageDescription</key>
	<string>客服功能需要麦克风权限</string>
	<key>NSPhotoLibraryAddUsageDescription</key>
	<string>使用相册功能为你存储账号密码</string>
  
  //不接入广告SDK，此权限可不申请
  <key>NSUserTrackingUsageDescription</key>
	<string>该标识符将用于向您投放个性化广告</string>

```

如果使用了分享SDK，需要配置如下

```css
<key>CFBundleURLTypes</key>
	<array>
		<dict>
			<key>CFBundleTypeRole</key>
			<string>Editor</string>
			<key>CFBundleURLName</key>
			<string>com.weibo</string>
			<key>CFBundleURLSchemes</key>
			<array>
        <!----需要替换参数-----!>
				<string>wb3118377197</string>
			</array>
		</dict>
		<dict>
			<key>CFBundleTypeRole</key>
			<string>Editor</string>
			<key>CFBundleURLName</key>
			<string>tencent</string>
			<key>CFBundleURLSchemes</key>
			<array>
        <!----需要替换参数-----!>
				<string>tencent101860838</string>
			</array>
		</dict>
		<dict>
			<key>CFBundleTypeRole</key>
			<string>Editor</string>
			<key>CFBundleURLName</key>
			<string>weixin</string>
			<key>CFBundleURLSchemes</key>
			<array>
        <!----需要替换参数-----!>
				<string>wx180c8f3360de0b12</string>
			</array>
		</dict>
	</array>

<key>LSApplicationQueriesSchemes</key>
	<array>
		<string>tim</string>
		<string>mqq</string>
		<string>mqqapi</string>
		<string>mqqbrowser</string>
		<string>mttbrowser</string>
		<string>mqqopensdkapiV2</string>
		<string>mqqopensdkapiV4</string>
		<string>mqzone</string>
		<string>mqzoneopensdk</string>
		<string>mqzoneopensdkapi</string>
		<string>mqzoneopensdkapi19</string>
		<string>mqzoneopensdkapiV2</string>
		<string>mqqopensdkfriend</string>
		<string>mqqopensdkavatar</string>
		<string>mqqopensdkminiapp</string>
		<string>mqqopensdkdataline</string>
		<string>mqqgamebindinggroup</string>
		<string>mqqopensdkgrouptribeshare</string>
		<string>tencentapi.qq.reqContent</string>
		<string>tencentapi.qzone.reqContent</string>
		<string>mqqthirdappgroup</string>
		<string>mqqopensdklaunchminiapp</string>
		<string>weixin</string>
		<string>weixinULAPI</string>
		<string>sinaweibohd</string>
		<string>sinaweibo</string>
		<string>weibosdk</string>
		<string>weibosdk2.5</string>
    <string>weibosdk3.3</string>
	</array>
```

如果使用了广告SDK，需要配置如下

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



### 代理《重要》

#### 引入头文件

```objectivec
#import "loginSDK.h"
```

#### 协议名

```objectivec
<tenovLoginCallBack,tenovPurchaseCallBack>
```

#### 代理方法

```objectivec
-(void)onFinish:(tenovStatus)code   Data:(NSDictionary*)Data
{
    NSLog(@"回调状态值：%ld",(long)code);
    NSLog(@"回调：%@",Data);

    if(code==LOGIN_SUCCESS){
      //登录成功，回调用户信息
    }else if(code== LOGOUT_SUCCESS){
      //需要调用主动调用登录

    }else if(code== LOGIN_SWITCH){
      //不需要调用主动调用登录
    } else if (code ==PAY_SUCCESS){

      //"支付成功"

    } else if (code== PAY_FAILED){

       //"支付失败"

    }else if (code==PAY_CANCEL){

       //"支付取消"   
    }else if (code==PAY_UNKNOWN){

      //"支付未知"

    } 
}
```

### 用户登录

登录返回的传递数据
退出返回的传递数据

**方法**

```objectivec
+ (void) login:(id<tenovLoginCallBack>)mLoginCallBack;

```

**示例**

```objectivec
[loginSDK login:self];

```

### 用户退出

**方法**

```objectivec
  + (void)logOut;
```

**示例**

```objectivec
[loginSDK logOut];
```

### 支付

**model参数**

| 参数名       | 类型   | 必需   | 说明                                                         |
| ------------ | ------ | ------ | ------------------------------------------------------------ |
| productID    | string | 是     | 商品ID                                                       |
| productName  | string | 是     | 商品名                                                       |
| productPrice | string | 是     | 商品价格                                                     |
| productDes   | string | 是     | 商品描述（不传则使用productName)                             |
| productDes   | string | 是     | 游戏传入的有关用户的区id，服务器id，角色id,订单等，属于透传数据功能 |
| roleID       | string | 否     | 角色ID                                                       |
| roleName     | string | 否     | 角色名字                                                     |
| roleLevel    | string | 否     | 角色等级                                                     |
| vipLevel     | string | 否     | vip等级                                                      |
| zoneID       | string | 是     | 服务器id，若无填“1”                                          |
| zoneName     | string | 否     | 服务器名                                                     |
| text         | string | string | 否                                                           |
| notifyURL    | string | 否     | 回调地址 可传可不传，不传使用默认                            |

**方法**

```objectivec
+ (void) tenovpay:(tenovOrderModel *)payInfo CallBack:(id<tenovPayCallBack>) callBack

```

**示例**

```objectivec
    
    tenovOrderModel* mPayInfo = [[tenovOrderModel alloc] init];
    mPayInfo.productID=payID;
    mPayInfo.productName=payName;
    mPayInfo.productPrice=price;
    mPayInfo.productDes=payName;
    mPayInfo.gameReceipts=receipts;
    mPayInfo.roleID=@"";
    mPayInfo.roleName=@"";
    mPayInfo.roleLevel=@"";
    mPayInfo.vipLevel=@"";
    mPayInfo.partyName=@"";
    mPayInfo.zoneID=@"";
    mPayInfo.zoneName=@"";
    mPayInfo.text=@"";
    mPayInfo.notifyURL = @"http://demo.tenov88.com/ok.php?gameid=1156&promote=2";
    [loginSDK tenovpay:mPayInfo CallBack:self];

```

### 数据打点方法

### 角色创建，新手引导，升级

| 参数名  | 类型   | 必需 | 说明                                 |
| ------- | ------ | ---- | ------------------------------------ |
| name    | string | 是   | 角色名                               |
| level   | string | 是   | 等级                                 |
| severID | string | 是   | 区服ID                               |
| roleID  | string | 是   | 角色ID                               |
| status  | string | 是   | 1:创建角色 2:完成新手引导 3:等级升级 |

**方法**

```objectivec
+ (void)setGameRoleName:(NSString *)name
            gameLevel:(NSString *)level
             serverID:(NSString *)serverID
               roleID:(NSString *)roleID
               status:(NSString *)status;
```

**示例**

```objectivec
 [loginSDK setGameRoleName:@"名字" gameLevel:@"等级" serverID:@"区服ID" roleID:@"角色ID" status:@"2"];
```

### 通用打点方法

| 参数名    | 类型         | 必需 | 说明     |
| --------- | ------------ | ---- | -------- |
| eventName | string       | 是   | 事件名   |
| info      | NSDictionary | 否   | 下级参数 |

**方法**

```objectivec
+ (void)LogInfo:(NSString *)eventName EventDic:(NSDictionary *)info
```

**示例**

```objectivec
 [loginSDK LogInfo:@"事件名" EventDic:@{}];
```

### 返回设备号

**方法**

```objectivec
+ (NSString *) returnIDFV 
```

**示例**

```objectivec
[loginSDK returnIDFV];
```

### 防沉迷

### 剩余时长

返回剩余时长，-1表示没有开启防沉迷；18岁（包含18岁）以上均返回0；如有需要可以结合用户年龄接口返回做相应处理;返回数值单位是秒。

**方法**

```objectivec
+ (NSString *)remainingTime;
```

**示例**

```objectivec
NSString *str = [loginSDK remainingTime];
//输出结果 str
```



### 用户年龄

返回用户年龄。

返回数值：

* 1、 未实名；
*  2、8岁以下（不包含8岁）；
*  3、8-16（包含8岁，不包含16岁）；
*  4、16-18（包含16岁，不包含18岁）；
*  5、18岁以上（包含18）；

**方法**

```objectivec
+ (NSString *)antiaddictionInfo;
```

**示例**

```objectivec
NSString *str = [loginSDK antiaddictionInfo];
//输出结果 str
```



## 推送-接入说明文档

#### 适用范围

本文档适用于IOS 9.0及以上的操作系统。 SDK放在SDK文件夹内

#### 接入流程

### 准备

#### 1.导入SDK

```
将目录中的(根据给到SDK添加).framework  和(根据给到SDK添加).bundle导入到您的工程中。
```

#### 导入方法：在工程目录结构中，右键选择Add->Existing Files...，

```
选择(根据给到SDK添加).framework, (根据给到SDK添加).bundle（或将文件拖入Xcode工程目录结构中）文件，在弹出的界面中勾选Copy items into destination group's folder(if needed)，并确保Add To Targets勾选相应target。
```

### 接入方法说明

#### AppDelegate导入头文件

引入头文件 `

```
#import <serverPush/pushPlatform.h>
```

### 方法用途：

#### 初始化

用于应用启动后，初始化推送SDK。

###### 使用地方

在-(**BOOL**)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions方法中调用

###### 参数

| 参数名   | 类型     | 必需 | 示例            | 说明        |
| -------- | -------- | ---- | --------------- | ----------- |
| appID    | UInt32   | 是   | 1600005427      | push应用id  |
| appKey   | NSString | 是   | @"IIOMAQYO58GB" | push应用key |
| delegate | id       | 是   | self            | 代理        |

###### 方法

```
+ (void)startXGWithAppID:(uint32_t)appID appKey:(nonnull NSString *)appKey delegate:(  id )delegate;
```

###### 示例

```
[pushPlatform startXGWithAppID:1600005427 appKey:@"IIOMAQYO58GB"  delegate:self ];
```

**注：如果接入时使用了给到的loginSDK.h和loginSDK.m，那么在`+ (void)initDelegate:( id )delegate;`方法中，当pushFoundation设置为YES时，已经调用初始化推送SDK，相关参数配置在login.bundle的infoset.plist中。**