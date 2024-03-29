# **Gm88服务器接口文档**

## 请求说明

### HTTP请求⽅式 

>  POST 

### 请求地址

> 生产环境：http://m.gm88.com/api/index.php
>
> 测试环境：http://demo.gm88.com/api/index.php

## 接口列表

### 登录验证接口

* 请求方：商户

* 请求参数

| 参数   | 必填 | 类型   | 描述             |
| ------ | ---- | ------ | ---------------- |
| action | Y    | String | 填写：user.check_token  |
| token  | Y    | String | Gm88用户登录凭证 |

* 返回参数

| 参数     | 描述               |
| -------- | ------------------ |
| uid      | Gm88游戏用户 ID    |
| nickname | Gm88游戏用户昵称   |
| ...      | 其他返回内容可忽略 |

* 返回示例

~~~
{
    "sid": "de5aae85335b7f6dd5f31ce75bb277c8",
    "uid": "1028029",
    "nickname": "GM_1028029",
     ...
}
~~~

<div style="page-break-after: always;"></div>

### 支付异步通知

* 请求方：Gm88服务器

* 请求参数

| 参数       | 类型         | 描述                                                         |
| ------------- | ------------ | ------------------------------------------------------------ |
| order_id      | int          | 订单号，由Gm88方生成，用于后期对账和查询                     |
| server_id     | int          |            区服号                                                  |
| role_id       | String(32) |                角色ID                                              |
| developerinfo | String(255) |                         订单附加信息，原样返回商户的 developerinfo               |
| coin          | float     | Gm88币，等同人民币的元。支持两位小数                                    |
| signature     | String(32) | md5加密后的签名 |

* 签名规则

  以上字段都参与签名，签名方式为MD5，签名串规则为：

  order_id=xxx&server_id=xxx&role_id=xxx&developerinfo=xxx&coin=xxx&支付通知密钥

* 商户同步返回

  商户执行完业务逻辑后在当前页面打印 ok，表示已经接收支付结果，如未收到 ok，系统会每隔 5 分钟发起一次通知

### 支付订单查询

* 请求方：商户
* 请求参数

| 参数      | 必填 | 类型   | 描述                                    |
| --------- | ---- | ------ | --------------------------------------- |
| action    | Y    | String | 填写： verify                           |
| game_id   | Y    | int    | 商户 ID                                 |
| order_id  | Y    | int    | 订单 ID，取自“支付异步通知”中的order_id |
| signature | Y    | String | md5加密后的签名                         |

* 签名规则

  以上字段都参与签名，签名方式为MD5，签名串规则为action=verify&game_id=xxx&order_id=xxx&支付通知密钥

* 返回参数

| 参数          | 描述                                       |
| ------------- | ------------------------------------------ |
| status        | 订单状态：Y 支付成功，N 未支付成功         |
| server_id     | 区服号                                     |
| role_id       | 角色ID                                     |
| developerinfo | 订单附加信息，原样返回商户的 developerinfo |
| coin          | Gm88币                                     |
| pay_time      | 支付时间，格式  yyyy-MM-dd HH:mm:ss        |

* 返回示例

~~~
{
    "data":{
        "status":"Y",
        "server_id":"1",
        "role_id":"12345",
        "developerinfo":"123456",
        "coin":"1.00",
        "pay_time":"2018-07-10 21:38:21"
    },
    "status":true
}
~~~
* 错误示例

~~~
{
    "status":false,
    "errorno":102,
    "errortext":"订单号不存在"
}
~~~

* 错误状态码

| 状态码 | 说明             |
| ------ | ---------------- |
| 100    | 游戏 ID 错误     |
| 101    | 签名错误         |
| 102    | 订单号不存在     |
| 103    | 订单不属于该游戏 |

### 支付订单查询

* 请求方：商户
* 请求参数

| 参数      | 必填 | 类型   | 描述                                    |
| --------- | ---- | ------ | --------------------------------------- |
| action    | Y    | String | 填写： verify                           |
| game_id   | Y    | int    | 商户 ID                                 |
| order_id  | Y    | int    | 订单 ID，取自“支付异步通知”中的order_id |
| signature | Y    | String | md5加密后的签名                         |

* 签名规则

  以上字段都参与签名，签名方式为MD5，签名串规则为action=verify&game_id=xxx&order_id=xxx&支付通知密钥

* 返回参数

| 参数          | 描述                                       |
| ------------- | ------------------------------------------ |
| status        | 订单状态：Y 支付成功，N 未支付成功         |
| server_id     | 区服号                                     |
| role_id       | 角色ID                                     |
| developerinfo | 订单附加信息，原样返回商户的 developerinfo |
| coin          | Gm88币                                     |
| pay_time      | 支付时间，格式  yyyy-MM-dd HH:mm:ss        |

* 返回示例

~~~
{
    "data":{
        "status":"Y",
        "server_id":"1",
        "role_id":"12345",
        "developerinfo":"123456",
        "coin":"1.00",
        "pay_time":"2018-07-10 21:38:21"
    },
    "status":true
}
~~~
* 错误示例

~~~
{
    "status":false,
    "errorno":102,
    "errortext":"订单号不存在"
}
~~~

* 错误状态码

| 状态码 | 说明             |
| ------ | ---------------- |
| 100    | 游戏 ID 错误     |
| 101    | 签名错误         |
| 102    | 订单号不存在     |
| 103    | 订单不属于该游戏 |

### 问卷调查链接

我方提供问卷ID，CP组合对应参数后生成完整链接 

**请求类型：**

GET

**参数**

| 字段      | 类型   | 参与签名   | 说明                          |
| ------------- | ----------| ---------- | --------------------------------- |
| uid    | int    | 是       |GM ID|
| game_id   | int      | 是      |appID|
| payload      | string    | 是       |透传参数，长度不超过30，仅支持 英文、数字、-_|
| timestamp | string | 是       |时间戳|
| signature     | string | 否                      |签名字段|
| wjx_id | int | 否 |问卷ID，由我方提供|
| action | string | 否 |固定值：wjx.activity|

**signature签名**

* 将以上字段连接,再加上app私钥,最后计算md5值。如

```
signature = md5(uid=xxx&game_id=xxx&payload=xxx&timestamp=xxx&appSecret)
```

**加密示例(PHP)**

```php
$appSecret = 'nHxJ8D8YkbZmYfTE';

$data = array(
    'uid' => '1',
    'game_id' => '1',
    'payload' => '110001042305',
    'timestamp' => '11001',
    'signature' => 'e96a7e4f7373adb8a39bd5a4ed3084e6',
);

$perstr = 'uid=1&game_id=11001&payload=1&timestamp=110001042305&nHxJ8D8YkbZmYfTE';

$signature = md5($perstr); 
```

**链接生成示例**

完整链接：
https://demo.gm88.com/api/?action=wjx.activity&wjx_id=1&uid=1&game_id=11001&payload=1&timestamp=110001042305&signature=e96a7e4f7373adb8a39bd5a4ed3084e6


### 问卷调查异步通知

这是用户完成问卷调查之后，怪猫方发起的异步通知，CP方应有后端程序接收此请求，并在接收到此通知后返回正确的响应，以便怪猫后端知晓通知成功。

异步通知 

**请求类型：**

POST

**回调参数**

| 字段      | 类型   | 参与签名   | 说明                          |
| ------------- | ----------| ---------- | --------------------------------- |
| wjx_id      | int    | 问卷ID    ||
| uid    | int    | GM ID                                ||
| game_id   | int      | appID       |
| payload      | string    | 透传参数，长度不超过30，仅支持 英文、数字、-_ ||
| timestamp | string | 时间戳 ||
| signature     | string | 签名字段 不参与签名                       ||

**signature签名**

* 将以上字段连接,再加上app私钥,最后计算md5值。如

```
signature = md5(wjx_id=xxx&uid=xxx&game_id=xxx&payload=xxx&timestamp=xxx&appSecret)
```

**加密示例(PHP)**

```php
$appSecret = 'nHxJ8D8YkbZmYfTE';

$data = array(
    'wjx_id' => '1',
    'uid' => '1',
    'game_id' => '110001042305',
    'payload' => '110001042305',
    'timestamp' => '11001',
    'signature' => 'e96a7e4f7373adb8a39bd5a4ed3084e6',
);

$perstr = 'wjx_id=1&uid=11001&game_id=1&payload=110001042305&timestamp=11001&nHxJ8D8YkbZmYfTE';

$signature = md5($perstr); 
```

CP收到请求且处理完内部逻辑后就返回“ok“(字符串)，表示已经接收通知结果，如未收到ok，系统会每隔5分钟发起一次通知。
