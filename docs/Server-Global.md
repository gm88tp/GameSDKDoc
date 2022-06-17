# 怪猫海外接入文档

## **接口列表** 
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
<div style="page-break-after: always;"></div>


### **四、** **预注册异步通知**

这是用户预注册之后，怪猫方发起的异步通知，CP方应有后端程序接收此请求，并在接收到此通知后，在游戏内向用户发货，并返回正确的响应，以便怪猫后端知晓发放成功。

异步通知 

**请求类型：**

POST

**回调参数**

| 字段      | 类型   | 参与签名   | 说明                          |
| ------------- | ----------| ---------- | --------------------------------- |
| openid     | string | 用户唯一ID                             ||
| server_id    | int    | 区服ID                                ||
| role_id      | int    | 角色ID    ||
| product_id | string | product_id道具ID ||
| signature     | string | 签名字段                              ||
| extra | string | 透传参数，不参与签名 ||

**signature签名**

* 将以上字段连接,再加上app私钥,最后计算md5值。如

```
signature = md5(openid_id=xxx&server_id=xxx&role_id=xxx&product=xxx&appSecret)
```

**加密示例(PHP)**

```php
$appSecret = 'nHxJ8D8YkbZmYfTE';

$data = array(
    'openid' => 'b34d8ba386b95d96f4f9337cafd0616b',
    'server_id' => '1',
    'role_id' => '110001042305',
    'product_id' => '11001',
    'signature' => 'e96a7e4f7373adb8a39bd5a4ed3084e6',
    'extra' => '{"server_index":"1","server_name":"一服"}'
);

$perstr = 'openid=b34d8ba386b95d96f4f9337cafd0616b&server_id=1&role_id=110001042305&product_id=11001&nHxJ8D8YkbZmYfTE';

$signature = md5($perstr); // e96a7e4f7373adb8a39bd5a4ed3084e6
```

CP收到请求后，应进行发货操作，在发货成功后返回“ok“(字符串)，表示已经接收支付结果，如未收到ok，系统会每隔5分钟发起一次通知，如果发货是异步的，可以返回"ok"，但请保证后续发货一定成功。

### **五、** **问卷调查链接**

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
https://mdemo.hkpctimes.com/api/?action=wjx.activity&wjx_id=1&uid=1&game_id=11001&payload=1&timestamp=110001042305&signature=e96a7e4f7373adb8a39bd5a4ed3084e6


### **六、** **问卷调查异步通知**

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

### **七、** **账号删除异步通知**

这是用户删除且过了冷静期后，怪猫方发起的异步通知，CP方应有后端程序接收此请求，并在接收到此通知后返回正确的响应，以便怪猫后端知晓通知成功。

异步通知 

**请求类型：**

POST

**回调参数**

| 字段      | 类型   | 参与签名   | 说明                          |
| ------------- | ----------| ---------- | --------------------------------- |
| uid    | int    | GM ID                                ||
| game_id   | int      | appID       |
| status      | int    | 40:删除账号||
| timestamp | string | 时间戳 ||
| signature     | string | 签名字段 不参与签名                       ||

**signature签名**

* 将以上字段连接,再加上app私钥,最后计算md5值。如

```
signature = md5(uid=xxx&game_id=xxx&status=xxx&timestamp=xxx&appSecret)
```

**加密示例(PHP)**

```php
$appSecret = 'nHxJ8D8YkbZmYfTE';

$data = array(
    'uid' => '11001',
    'game_id' => '1',
    'status' => '40',
    'timestamp' => '110001042',
    'signature' => 'e96a7e4f7373adb8a39bd5a4ed3084e6',
);

$perstr = 'uid=11001&game_id=1&status=40&timestamp=110001042&nHxJ8D8YkbZmYfTE';

$signature = md5($perstr); 
```

CP收到请求且处理完内部逻辑后就返回“ok“(字符串)，表示已经接收通知结果，如未收到ok，系统会每隔5分钟发起一次通知。

# 网页充值文档说明

请按以下标准，提供3个接口地址给到我方运营

## 接口说明

所有的接口的返回形式都是统一为：

- 正常返回

```json
{
    "status":true,
    "errorno":0,
    "errortext":"OK",
    "data":"某种类型的数据，比如字符串，数字，字典等等"
}
```

- 错误返回

```json
{
    "status":true,
    "errorno":500,
    "errortext":"具体的错误信息字符串"
}
```

签名生成规则：

1. Reuqest Body 按照键名 ASCII 排序
2. 对排序后数组按key=value格式用&连接得出加密串
3. md5( 加密串 + & + 密钥) 得出签名

- PHP 签名示例

```php
$body = [
    "uid" => "73146",
    "server_id" => "1",
    "timestamp" => "1631173146",
];

$secret_key = "H2CMZgDAL40zGJHn";

ksort($body);

$prestr = urldecode(http_build_query($body));

$signature = md5($prestr.'&'.$secret_key);
```

## 接口列表

### 获取角色列表
#### Reuqest

- Method: **GET**
- URL: ```CP提供```
- Headers： Content-Type:application/json
- Body:
```
{
    "uid" : "73146", // 我方用户ID
    "timestamp" : "1631173146", // 当前时间戳
    "signature" : "0af83fcf08d75ca5aae48383154cb037" // 签名
}
```

#### Response
- Body
```
{
    "status":true,
    "errorno":0,
    "errortext":"OK",
    "data":[
        {
            "zone_id":"1", // 大区ID，如无大区此处传0
            "zone_name":"测试大区", // 大区名称
            "server_id":"1", // 服务器ID
            "server_name":"测试1服", // 服务器名称
            "role_id":"100001", // 角色ID
            "role_name":"角色1" // 角色名称
        },
        {
            "zone_id":"1",
            "zone_name":"测试大区",
            "server_id":"2",
            "server_name":"测试2服",
            "role_id":"100002",
            "role_name":"角色2"
        }
    ]
}
```

### 发货通知接口
#### Reuqest

- Method: **POST**
- URL: ```CP提供```
- Headers： Content-Type:application/json
- Body:
```
{
    "order_id" : "1631173146", // 我方订单号
    "uid" : "73146", // 我方用户ID
    "zone_id" : "73146", // 大区ID
    "server_id" : "1", // 服务器ID
    "role_id" : "73146", // 角色ID
    "coin" : "1", // 付款金额
    "game_coin" : "8001", // 实发游戏币
    "timestamp" : "1631173146", // 当前时间戳
    "item_type" : 1, // 商品类型  1游戏币商品 2礼包类商品
    "gift_item_id" : 1, // 礼包id item_type=1是 为0  等于2时是礼包id
    "signature" : "0af83fcf08d75ca5aae48383154cb037" // 签名
}
```

#### Response
- Body
```json
{
    "status":true,
    "errorno":0,
    "errortext":"OK",
    "data":{
        "out_trade_no":"20210909110001", // CP方订单ID
    }
}
```

### 大区列表接口
此接口返回游戏大区列表及大区对应的“获取角色列表”和“发货通知接口”接口地址
#### Reuqest

- Method: **POST**
- URL: ```CP提供```
- Headers： Content-Type:application/json
- Body:
```
{
    "timestamp" : "1631173146", // 当前时间戳
    "signature" : "0af83fcf08d75ca5aae48383154cb037" // 签名
}
```

#### Response
- Body
```json
{
    "status":true,
    "errorno":0,
    "errortext":"OK",
    "data": [
        {
            "zone_id": "0",
            "zone_name": "默认大区",
            "role_list_url": "https://domain/role_list.php",
            "gift_product_url": "https://domain/gift_product.php",   // 脚本礼包列表
            "cate_gift_url": "https://domain/gift_product.php",   // h5页面下角色可用的礼包列表
            "verift_gift_url": "https://domain/gift_product.php",   // h5页面下购买时验证该礼包该角色是否可买
            "gift_cate_url": "https://domain/gift_product.php",   // 礼包分类信息
            "notify_url": "https://domain/notify.php"
        }
    ]
}
```

### 脚本获取礼品商品列表
#### Reuqest

- Method: **GET**
- URL: ```CP提供```
- Headers： Content-Type:application/json
- Body:
```
{
    "group_id" : "1", // 母游戏id
    "timestamp" : "1631173146", // 当前时间戳
    "signature" : "0af83fcf08d75ca5aae48383154cb037" // 签名
}
```

#### Response
- Body
```
{
    "status":true,
    "errorno":0,
    "errortext":"OK",
    "data":[
        {
            "item_id":"1", // 礼包id
            "item_name":"测试大区", // 礼包名称
            "price":"1", // 价格
            "total_num":"1", // 总共可购数量
            "purchase_num":"1", // 剩余可购数量
            "is_buy":"1", // 1角色可购买 0不可购买
            "context":"xxxx", // 购买条件文案
            "cate_id":"1", // 分类id
            "cate_name":"1", // 分类名称
            "props_desc":"1", // 礼包描述
            "props_list": [
                {
                    "id":1, 道具id
                    "img":"https://xxxxx", 道具图片全连接
                    "num":0, 道具数量
                }
            ]
        },
    ]
}
```

### 分类获取礼品商品列表
#### Reuqest

- Method: **GET**
- URL: ```CP提供```
- Headers： Content-Type:application/json
- Body:
```
{
    "group_id" : "1", // 母游戏id
    "cate_id" : "1", // 分类id
    "role_id" : "1", // 角色id
    "user_id" : "1", // 用户id
    "timestamp" : "1631173146", // 当前时间戳
    "signature" : "0af83fcf08d75ca5aae48383154cb037" // 签名
}
```

#### Response
- Body
```
{
    "status":true,
    "errorno":0,
    "errortext":"OK",
    "data":[
        {
            "item_id":"1", // 礼包id
            "item_name":"测试大区", // 礼包名称
            "price":"1", // 价格
            "total_num":"1", // 总共可购数量
            "purchase_num":"1", // 剩余可购数量
            "is_buy":"1", // 1角色可购买 0不可购买
            "context":"xxxx", // 购买条件文案
            "cate_id":"1", // 分类id
            "cate_name":"1", // 分类名称
            "props_desc":"1", // 礼包描述
            "props_list": [
                {
                    "id":1, 道具id
                    "img":"https://xxxxx", 道具图片全连接
                    "num":0, 道具数量
                }
            ]
        },
    ]
}
```

### 验证礼品商品是否可购买
#### Reuqest

- Method: **GET**
- URL: ```CP提供```
- Headers： Content-Type:application/json
- Body:
```
{
    "item_id" : "1", // 分类id
    "role_id" : "1", // 角色id
    "user_id" : "1", // 用户id
    "timestamp" : "1631173146", // 当前时间戳
    "signature" : "0af83fcf08d75ca5aae48383154cb037" // 签名
}
```

#### Response
- Body
```
{
    "status":true,
    "errorno":0,
    "errortext":"OK",
    "data": true  true 可购买 false 不可购买
}
```

### 获取礼品分类列表
#### Reuqest

- Method: **GET**
- URL: ```CP提供```
- Headers： Content-Type:application/json
- Body:
```
{
    "group_id" : "1", // 母游戏id
    "role_id" : "0", // 角色id  登录前为0
    "user_id" : "0", // 用户id  登录前为0
    "timestamp" : "1631173146", // 当前时间戳
    "signature" : "0af83fcf08d75ca5aae48383154cb037" // 签名
}
```

#### Response
- Body
```
{
    "status":true,
    "errorno":0,
    "errortext":"OK",
    "data":[
        {
            "cate_id":"1", // 分类id
            "cate_name":"测试大区", // 分类名称
            "is_show":true, // 是否显示 true显示 false 不显示
        },
    ]
}
```
