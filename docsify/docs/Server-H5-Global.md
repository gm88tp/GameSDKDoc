# Gm88 H5接入文档

###  **一、**  **接入流程**

1. 提供游戏名称、ICON、游戏描述等素材，提供游戏测试地址，充值回调地址

2. Gm88方提供 appId，appSecret 和游戏地址

3. 通过接口获取用户信息

4. 包含open.js，使用OPEN.goToPay方法发起支付

5. 处理支付回调

### **二、**  **获取用户信息接口**

UserInfo /GET

**地址**

正式：https://open.hkpctimes.com/UserInfo

测试：https://opendemo.hkpctimes.com/UserInfo

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

**res 内容**

| 字段       | 类型   | 描述       |
| ---------- | ------ | ---------- |
| openid | Int    | 用户唯一ID |
| name   | string | 用户名     |

<div style="page-break-after: always;"></div>
### **三、** **发起支付**

**open.js**

正式：https://g.hkpctimes.com/js/open.js?v=20181221001

测试：https://gdemo.hkpctimes.com/js/open.js?v=20181221001

**最后的v参数实际是个随机字符串，为了保证 JS 文件不被浏览器缓存**

~~~ 
使用
OPEN.goToPay(appId,productId,productName,price,extra,sign,roleName,roleServer)
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
| roleName | string | 角色名称，不参与签名 |
| roleServer | string | 角色区服，不参与签名 |

**sign签名**

* 将key按照字母升序排列,然后使用&连接,再加上app私钥,最后计算md5值。如

```
appId 1
productId 123
price 123
extra 123
sign = md5(appId=1&extra=123&price=123&productId=123APP_SECREET)
```

 

### **四、** **支付回调**

异步通知 

请求类型：POST

**回调参数**

| 字段      | 类型   | 参与签名 | 说明                          |
| ------------- | ---------- | --------------------------------- | --------------------------------- |
| order_id      | int    | Y   | Gm88订单号                    |
| server_id     | int    | Y   | H5                            |
| role_id       | int    | Y   | 用户唯一ID，和用户openId相同  |
| developerinfo | string | Y | 自定义参数，和下单的extra相同 |
| coin          | float  | Y | 订单金额，单位：元            |
| signature     | string | N | 签名字段                      |
| discount_type     | int | N | 1：多送                       |
| discount_value_type     | int | N | 优惠值类型 1：固定金额；2：百分比                      |
| discount_value     | float | N | 优惠值                      |



**signature签名**

* 将以上字段连接,再加上app私钥,最后计算md5值。如

```
signature = md5(order_id=xxx&server_id=xxx&role_id=xxx&developerinfo=xxx&coin=xxx&appSecret)
```

收到请求，验证正确后返回“ok“ 表示已经接收支付结果，如未收到ok，系统会每隔5分钟发起一次通知。

 

### **五、**  **订单查询**

由商户发起

接口接入地址：

正式：https://m.hkpctimes.com/api/

测试：https://mdemo.hkpctimes.com/api/

请求类型：POST

| 字段      | 类型 | 说明    |
| ------------- | -------- | ----------- |
| action    | string   | 定值：verify |
| game_id   | int      | appID       |
| order_id  | Int      | 订单ID      |
| signature | string   | 签名字段    |

**signature签名**

* 将以上字段连接,再加上app私钥,最后计算md5值。如

```
signature = md5(action=verify&game_id=xxx&order_id=xxx&appSecret)
```

正确返回示例：

```json
{
    "data":{
        "status":"N", // Y：成功
        "server_id":"3服", // 区服
        "role_id":"668", // ⻆角⾊色ID
        "developerinfo":"game_3-668-7878", // 透传参数
        "coin":"648", // 订单⾦金金额
        "pay_time":"2018-12-30 02:54:39" // ⽀支付时间
    },
    "status":true
}
```

错误返回示例

```json
{
    "status":false,
    "errorno":101,
    "errortext":"签名错误"
}
```

### **六、** **自定义事件回传**

**open.js**

正式：https://g.hkpctimes.com/js/open.js?v=20181221001

测试：https://gdemo.hkpctimes.com/js/open.js?v=20181221001

**最后的v参数实际是个随机字符串，为了保证 JS 文件不被浏览器缓存**

~~~ 
使用
OPEN.spot(appId,spotType,extra,sign)
调用事件回传
~~~

| 字段        | 类型   | 说明                                     |
| --------------- | ---------- | -------------------------------------------- |
| appId       | int    | 游戏ID                                   |
| spotType | int    | 事件类型：1.创建角色数据；2.新手引导完成数据；3.玩家等级数据；10.展示选区界面；11.选区界面点击开始按钮；12.展示创角界面；13.创角界面点击进入游戏按钮；100.拉起收藏到桌面 |
| extra       | string | 事件参数：{'roleName':'角色名称', 'roleServer':'角色区服', 'roleLevel':'角色等级'} |
| sign        | string |                                              |

**sign签名**

* 将key按照字母升序排列,然后使用&连接,再加上app私钥,最后计算md5值。如

```
appId 1
spotType 1
extra {'roleName':'角色名称', 'roleServer':'角色区服', 'roleLevel':'角色等级'}
sign = md5(appId=1&extra={'roleName':'角色名称', 'roleServer':'角色区服', 'roleLevel':'角色等级'}&spotType=1APP_SECREET)
```

### **七、** **游戏加载完成**

**open.js**

正式：https://g.hkpctimes.com/js/open.js?v=20181221001

测试：https://gdemo.hkpctimes.com/js/open.js?v=20181221001

**最后的v参数实际是个随机字符串，为了保证 JS 文件不被浏览器缓存**

~~~ js
使用
OPEN.loadComplete()
~~~

### **八、** **分享**

**open.js**

正式：https://g.hkpctimes.com/js/open.js?v=20181221001

测试：https://gdemo.hkpctimes.com/js/open.js?v=20181221001

**最后的v参数实际是个随机字符串，为了保证 JS 文件不被浏览器缓存**

~~~ js
使用
OPEN.share()
~~~

