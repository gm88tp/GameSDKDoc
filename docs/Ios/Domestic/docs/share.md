## 分享-接入说明文档

#### 适用范围

本文档适用于IOS 9.0及以上的操作系统。
SDK放在SDK文件夹内

#### 接入流程

### 准备

#### 1.导入SDK

```objectivec
将目录中的(根据给到SDK添加).framework  和(根据给到SDK添加).bundle导入到您的工程中。
```

#### 导入方法：在工程目录结构中，右键选择Add->Existing Files...，

```objectivec
选择(根据给到SDK添加).framework, (根据给到SDK添加).bundle（或将文件拖入Xcode工程目录结构中）文件，在弹出的界面中勾选Copy items into destination group's folder(if needed)，并确保Add To Targets勾选相应target。
```

### 接入方法说明

#### AppDelegate导入头文件

 引入头文件  `

```objectivec
#import <shareGroup/sharePlatform.h>
```

### 方法用途：

#### 初始化

用于应用启动后，初始化推送SDK。

###### 使用地方

在-(**BOOL**)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions方法中调用

###### 参数

| 参数名                | 类型     | 必需 | 示例               | 说明              |
| :-------------------- | :------- | ---- | ------------------ | ----------------- |
| Appwchat              | NSString | 是   | wx180c8f3360de0b12 | 微信应用id        |
| universalLinkAppwchat | NSString | 是   | https://….         | 微信universalLink |
| wbAppkey              | NSString | 是   | 3118377197         | 微博appkey        |
| tenchentId            | NSString | 是   | 101860838          | qq应用id          |
| universalLinkqwchat   | NSString | 是   | https://….         | qquniversalLink   |

###### 方法

```objectivec
- (void)registerAppwchat:(NSString *)wappid universalLinkAppwchat:(NSString *)wchatlink wbAppkey:(NSString *)appkey tenchentId :(NSString *)qAppid universalLinkqwchat:(NSString *)qlink;
```

###### 示例

```objectivec
[[sharePlatform getInit] registerAppwchat:[loginSDK getInfoString:@"weichatAppid"] universalLinkAppwchat:[loginSDK getInfoString:@"wlink"] wbAppkey:[loginSDK getInfoString:@"wbAppKey"] tenchentId:[loginSDK getInfoString:@"tenchentId"] universalLinkqwchat:[loginSDK getInfoString:@"tlink"]];
```

## 

#### 打开url

用于打开url，进行应用跳转。

###### 使用地方

在-(BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options方法中调用

###### 参数

| 参数名  | 类型          | 必需 | 示例    |
| :------ | :------------ | ---- | ------- |
| app     | UIApplication | 是   | app     |
| url     | NSString      | 是   | url     |
| options | NSString      | 是   | options |

###### 方法

```objectivec
-(BOOL)shareApplication:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options;
```

###### 示例

```objectivec
[loginSDK shareApplication:app openURL:url options:options];
```

## 



#### 分享

用于需要调用分享的地方

###### 参数

| 参数名      | 类型              | 必需 | 示例 | 说明                         |
| :---------- | :---------------- | ---- | ---- | ---------------------------- |
| contentObj  | shareContentItem  | 是   |      | 分享的内容对象，具体参照如下 |
| shareType   | shareType         | 是   |      | 分享的类型，具体如下         |
| shareResult | ShareResultlBlock |      |      | 分享结果回调                 |

shareContentItem：分享的内容对象。包含如下表所示的内容：

| 参数名          | 类型     | 说明           |
| --------------- | -------- | -------------- |
| share_title     | NSString | 分享的标题     |
| share_msg       | NSString | 分享的信息     |
| share_imgurl    | NSString | 分享的图片链接 |
| share_targeturl | NSString | 点击跳转的链接 |

shareType：分享的类型，具体如下：

```
typedef NS_ENUM(NSInteger, shareType){
    
       ShareTypeWeiBo = 0,   // 新浪微博
       ShareTypeQQ,          // QQ好友
       ShareTypeQQZone,      // QQ空间
       ShareTypeWTimeline,   // 朋友圈
       ShareTypeWSession,    // 微信朋友
       ShareTypeWFavorite,   // 微信收藏
};
```

ShareResultlBlock：分享结果回调，具体回调值如下：

```
typedef NS_ENUM(NSInteger , statusCode) {
    statusCodeSuccess=0,
    statusCodeCancel=-2
};
```

###### 方法

```objectivec
+ (void)shareWithContent:(shareContentItem *)contentObj
               shareType:(shareType)shareType
             shareResult:(ShareResultlBlock)shareResult;
```

###### 示例

```objectivec
shareContentItem * item = [[shareContentItem alloc]init];
item.share_title = @"分享测试";
item.share_targeturl = @"https://www.baidu.com";
item.share_imgurl =@"123";//https://dl03.gm88.com/xmjlogo/fxxz.png";
item.share_msg = @"一般情况新浪微博的Summary和微信,QQ的是不同的,新浪微博的是一般带链接的,而且总共字数不能超过140字";
//此处使用的示例是：分享至qq
[sharePlatform shareWithContent:item  shareType:ShareTypeQQ shareResult:^(NSInteger shareResult) {
        if(shareResult ==statusCodeSuccess){
                 NSLog(@"分享成功");
        }else if (shareResult ==statusCodeCancel){
                 NSLog(@"分享失败");
        }
    }];
```

## 