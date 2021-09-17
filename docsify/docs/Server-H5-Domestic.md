# Gm88 H5接入文档

###  **一、**  **接入流程**

1. 提供游戏名称、ICON、游戏描述等素材，提供游戏测试地址，充值回调地址
2. Gm88方提供 appId，appSecret 和游戏地址
3. 通过接口获取用户信息
4. 包含open.js，使用OPEN.goToPay方法发起支付
5. 处理支付回调

###  **二、**  **SDK文件地址**

正式：http(s)://g.gm88.com/js/open.js?v=20190415001

测试：http(s)://g.demo.gm88.com/js/open.js?v=20190415001

### **三、**  **获取用户信息接口**

UserInfo /GET

**地址**

正式：https://open.gm88.com/UserInfo

测试：https://open.demo.gm88.com/UserInfo

**参数**

| 字段        | 类型   | 描述                        |
| ----------- | ------ | --------------------------- |
| accessToken | string | 加载游戏时传入的accessToken |

**返回**

| 字段         | 类型   | 描述                |
| ------------ | ------ | ------------------- |
| code     | Int    | 0:正确   其他：错误 |
| res      | object | 用户信息            |
| msg      | string | 错误信息            |
| sys_time | Int    | 服务器时间戳        |

<div style="page-break-after: always;"></div>
**res 内容**

| 字段       | 类型   | 描述       |
| ---------- | ------ | ---------- |
| uid | int | 用户ID |
| openid | string | 用户唯一ID（老版本使用） |
| name   | string | 用户名     |
| channel_name | string | 渠道标识 |
| channel_uid | string | 渠道ID |

### **四、** **发起支付方法**

~~~ 
使用
OPEN.goToPay(appId,productId,productName,price,extra,sign,notifyUrl,extend)
调用支付
~~~

| 字段        | 类型   | 说明                                     |
| --------------- | ---------- | -------------------------------------------- |
| appId       | int    | 游戏ID                                   |
| productId   | int    | 商品ID                                   |
| productName | string | 商品名称(不参与签名)                     |
| price       | int    | 支付费用(单位:分)                        |
| extra       | string | 自定义参数，判断唯一，用于存放游戏订单号 |
| sign        | string |                                              |
| notifyUrl | string | 自定义支付成功回调地址，非必填 |
| extend | string | 自定义参数，非必填 {'roleName':'角色名称', 'roleServer':'角色区服', 'roleLevel':'角色等级'} |

**sign签名**

* 将key按照字母升序排列,然后使用&连接,再加上app私钥,最后计算md5值。如

```
appId 1
productId 123
price 123
extra 123
sign = md5(appId=1&extra=123&price=123&productId=123APP_SECREET)
```
<div style="page-break-after: always;"></div>
### **五、** **支付回调**

异步通知 

请求类型：POST

**回调参数**

| 字段      | 类型   | 说明                          |
| ------------- | ---------- | --------------------------------- |
| order_id      | int    | Gm88订单号                    |
| server_id     | int    | H5                            |
| role_id       | int    | 用户唯一ID，和用户openId相同  |
| developerinfo | string | 自定义参数，和下单的extra相同 |
| coin          | float  | 订单金额，单位：元            |
| signature     | string | 签名字段                      |

 

**signature签名**

* 将以上字段连接,再加上app私钥,最后计算md5值。如

```
signature = order_id=xxx&server_id=xxx&role_id=xxx&developerinfo=xxx&coin=xxx&appSecret
```

收到请求，验证正确后返回“ok“ 表示已经接收支付结果，如未收到ok，系统会每隔5分钟发起一次通知。

 

### **六、**  **订单查询**

由商户发起

**接口接入地址**

正式：https://m.gm88.com/api/index.php 

测试：https://demo.gm88.com/api/index.php 

请求类型：POST

| 字段      | 类型 | 说明    |
| ------------- | -------- | ----------- |
| action    | string   | 定值:verify |
| game_id   | int      | appID       |
| order_id  | Int      | 订单ID      |
| signature | string   | 签名字段    |

**signature签名**

* 将以上字段连接,再加上app私钥,最后计算md5值。如

```
signature = action=verify&game_id=xxx&order_id=xxx&appSecret
```

返回内容格式为json

正确返回

```
{
    "data":{
        "status":"N",  // Y：成功
        "server_id":"3服", // 区服
        "role_id":"668", // 角色ID
        "developerinfo":"game_3-668-7878", // 透传参数
        "coin":"648", // 订单金额
        "pay_time":"2018-12-30 02:54:39" // 支付时间
    },
    "status":true
}

```
错误返回

```

{
    "status":false,
    "errorno":101,
    "errortext":"签名错误"
}

```

### **七、** **游戏加载完成**

**在选服界面调用**

~~~ 
使用
OPEN.loadComplete()
~~~

### **八、** **自定义事件回传**

~~~ 
使用
OPEN.spot(appId,spotType,extra,sign)
调用事件回传
~~~

| 字段        | 类型   | 说明                                     |
| --------------- | ---------- | -------------------------------------------- |
| appId       | int    | 游戏ID                                   |
| spotType | int    | 事件类型：1.创建角色数据；2.新手引导完成数据；3.玩家等级数据；10.展示选区界面；11.选区界面点击开始按钮；12.展示创角界面；13.创角界面点击进入游戏按钮 |
| extra       | string | 事件参数：{'roleName':'角色名称', 'roleServer':'角色区服', 'roleLevel':'角色等级'}，无数据时非必填 |
| sign        | string |                                              |

**sign签名**

* 将key按照字母升序排列,然后使用&连接,再加上app私钥,最后计算md5值。如

```
appId 1
spotType 1
extra {'roleName':'角色名称', 'roleServer':'角色区服', 'roleLevel':'角色等级'}
sign = md5(appId=1&extra={'roleName':'角色名称', 'roleServer':'角色区服', 'roleLevel':'角色等级'}&spotType=1APP_SECREET)
```

### **九、** **游戏注销**

~~~ 
使用
OPEN.logout()
调用游戏注销
~~~

### **十、** **分享**

~~~ 
使用
OPEN.share()
调用游戏分享
~~~

### **十一、** **客服**

~~~ 
使用
OPEN.kefu()
调用游戏客服
~~~

### **十二、** **关注**

~~~ 
使用
OPEN.follow()
调用游戏关注
~~~