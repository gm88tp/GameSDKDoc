## 推送-接入说明文档

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
#import <serverPush/pushPlatform.h>
```

### 方法用途：

#### 初始化

用于应用启动后，初始化推送SDK。

###### 使用地方

在-(**BOOL**)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions方法中调用

###### 参数

| 参数名   | 类型     | 必需 | 示例            | 说明        |
| :------- | :------- | ---- | --------------- | ----------- |
| appID    | UInt32   | 是   | 1600005427      | push应用id  |
| appKey   | NSString | 是   | @"IIOMAQYO58GB" | push应用key |
| delegate | id       | 是   | self            | 代理        |

###### 方法

```objectivec
+ (void)startXGWithAppID:(uint32_t)appID appKey:(nonnull NSString *)appKey delegate:(  id )delegate;
```

###### 示例

```objectivec
[pushPlatform startXGWithAppID:1600005427 appKey:@"IIOMAQYO58GB"  delegate:self ];
```

## 