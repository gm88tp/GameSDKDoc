# 怪猫海外接入文档

### **一、**  **登录验证接口**

由商户发起

**接口接入地址：**

正式：https://m.hkpctimes.com/api/ 

测试：https://mdemo.hkpctimes.com/api/ 

**请求类型：**

POST

| 字段      | 类型 | 说明    |
| ------------- | -------- | ----------- |
| action    | string   | 定值：user.info |
| token | varchar | 登录凭证       |

**正确返回示例**

```json
{
    "uid":"1063242",
    "nickname":"GM_1063242",
    "status":true
}
```

**错误返回示例**
```json
{
    "status":false,
    "errorno":2,
    "errortext":"登錄狀態已失效，請重新登錄"
}
```

<div style="page-break-after: always;"></div>




### **二、** **支付异步通知**

这是⽤用户⽀支付完成之后，怪猫方确认用户已经付款完成时，发起的异步支付成功通知，CP方应有后端程序接收此请求，并在接收到此通知后，在游戏内向⽤用户发货，并返回正确的响应，以便怪猫后端知晓发货成功。

异步通知 

**请求类型：**

POST

**回调参数**

| 字段      | 类型   | 参与签名   | 说明                          |
| ------------- | ----------| ---------- | --------------------------------- |
| order_id      | string |Y| 怪猫订单号                    |
| server_id     | string |Y| 区服号                         |
| role_id       | string | Y|角色ID  |
| developerinfo | string | Y|订单附加信息，透传参数 |
| coin          | float  | Y|订单金额，单位：元            |
| signature     | string | N|签名字段                      |
| status | string |N| ORDER_ACCEPTED 支付成功；<br />ORDER_REFUNDED 已退款；<br />默认为 ORDER_ACCEPTED |

 

**signature签名**

* 将以上签名字段连接,再加上app私钥,最后计算md5值。如：

```php
signature = md5(order_id=xxx&server_id=xxx&role_id=xxx&developerinfo=xxx&coin=xxx&appSecret)
```

收到请求，验证正确后返回“ok” 表示已经接收支付结果，如未收到ok，系统会每隔5分钟发起一次通知。

<div style="page-break-after: always;"></div>

### **三、**  **支付订单查询**

由商户发起

**接口接入地址：**

正式：https://m.hkpctimes.com/api/ 

测试：https://mdemo.hkpctimes.com/api/ 

**请求类型：**

POST

| 字段      | 类型 | 说明    |
| ------------- | -------- | ----------- |
| action    | string   | 定值：verify |
| game_id   | int      | appID       |
| order_id  | Int      | 订单ID      |
| signature | string   | 签名字段    |

**signature签名**

* 将以上字段连接,再加上app私钥,最后计算md5值。如

```php
signature = md5(action=verify&game_id=xxx&order_id=xxx&appSecret)
```

**正确返回示例**
```json
{
    "data":{
        "status":"N",  // Y：成功
        "server_id":"3服", // 区服
        "role_id":"668", // ⻆角⾊色ID
        "developerinfo":"game_3-668-7878", // 透传参数  
        "coin":"648", // 订单⾦金金额
        "pay_time":"2018-12-30 02:54:39" // ⽀支付时间
    },
    "status":true
}
```

**错误返回示例**
```json
{
    "status":false,
    "errorno":101,
    "errortext":"签名错误"
}

```