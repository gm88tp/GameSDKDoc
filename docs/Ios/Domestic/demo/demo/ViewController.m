//
//  ViewController.m
//  demo
//
//  Created by rosehyird on 2020/6/3.
//  Copyright © 2020 rosehyird. All rights reserved.
//

#import "ViewController.h"
#import "loginSDK.h"
#import <shareGroup/shareContentItem.h>
#import <shareGroup/sharePlatform.h>
#import "advertisingCenter/adPlatform.h"

#define notificationName  @"adnotification"
@interface ViewController ()<wfnjiLoginCallBack,wfnjiPayCallBack,UITableViewDelegate,UITableViewDataSource>
@property (nonatomic,strong)UITableView  * tab;
@property (nonatomic,strong)NSArray      * arr;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.tab = [[UITableView alloc]initWithFrame:self.view.frame style:UITableViewStylePlain];
    [self.view addSubview:self.tab];
    self.tab.delegate = self;
    self.tab.dataSource = self;
    self.arr = @[@"登录",@"支付",@"退出",@"角色打点", @"通用打点方法",@"qq",@"空间",@"微博",@"微信好友",@"微信朋友圈",@"微信喜欢",@"广告"
    ];
    [[NSNotificationCenter defaultCenter] addObserver:self  selector:@selector(notificationFunc:) name:notificationName   object:nil];
}

#pragma mark - uitableview
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return  self.arr.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
     static   NSString * str  = @"wqewqeq";
        UITableViewCell * cell= [tableView  dequeueReusableCellWithIdentifier:str];
      if(!cell){
          cell  = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:str];
          
      }
      cell.textLabel.text = self.arr[indexPath.row];
      return cell;
}
 

 - (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    [tableView   deselectRowAtIndexPath:indexPath animated:YES];
     shareContentItem * item = [self setShareContent];
     if(indexPath.row==0){
         [self userLogin];
     }else if(indexPath.row==1){
         [self userBuy];
     }
     else if(indexPath.row==2){
         [self userExit];
         
     }
     else if(indexPath.row==3){
     
         [loginSDK setGameRoleName:@"名字" gameLevel:@"等级" serverID:@"区服ID" roleID:@"游戏角色ID" statusType:@"类型"];
     }
     else if(indexPath.row==4){
         [loginSDK LogInfo:@"ads_CXJ_request_failure" EventDic:@{}];
         
     }  else if(indexPath.row==5){
         [sharePlatform shareWithContent:item  shareType:ShareTypeQQ shareResult:^(NSInteger shareResult) {
             if(shareResult ==statusCodeSuccess){
                                      NSLog(@"分享成功");
                                  }else if (shareResult ==statusCodeCancel){
                                      NSLog(@"分享失败");
                                  }
         }];
         
             
     }  else if(indexPath.row==6){
         [sharePlatform shareWithContent:item  shareType:ShareTypeQQZone shareResult:^(NSInteger shareResult) {
             if(shareResult ==statusCodeSuccess){
                                      NSLog(@"分享成功");
                                  }else if (shareResult ==statusCodeCancel){
                                      NSLog(@"分享失败");
                                  }
         }];
                 
     }  else if(indexPath.row==7){
         [sharePlatform shareWithContent:item  shareType:ShareTypeWeiBo shareResult:^(NSInteger shareResult) {
             if(shareResult ==statusCodeSuccess){
                 NSLog(@"分享成功");
             }else if (shareResult ==statusCodeCancel){
                 NSLog(@"分享失败");
             }
         }];
                     
     }  else if(indexPath.row==8){
         
         [sharePlatform shareWithContent:item  shareType:ShareTypeWSession shareResult:^(NSInteger shareResult) {
             if(shareResult ==statusCodeSuccess){
                                      NSLog(@"分享成功");
                                  }else if (shareResult ==statusCodeCancel){
                                      NSLog(@"分享失败");
                                  }
         }];
         
     }
     else if(indexPath.row==9){
         [sharePlatform shareWithContent:item  shareType:ShareTypeWTimeline shareResult:^(NSInteger shareResult) {
             if(shareResult ==statusCodeSuccess){
                                      NSLog(@"分享成功");
                                  }else if (shareResult ==statusCodeCancel){
                                      NSLog(@"分享失败");
                                  }
         }];
         
     }
     else if(indexPath.row==10){
         [sharePlatform shareWithContent:item  shareType:ShareTypeWFavorite shareResult:^(NSInteger shareResult) {
             if(shareResult ==statusCodeSuccess){
                                      NSLog(@"分享成功");
                                  }else if (shareResult ==statusCodeCancel){
                                      NSLog(@"分享失败");
                                  }
         }];
     }else if(indexPath.row ==11){
         //广告
         [adPlatform pulladvertisingCenterRequest];
     }
 }

- (shareContentItem *)setShareContent {
    shareContentItem * item = [[shareContentItem alloc]init];
    item.share_title = @"分享测试";
    item.share_targeturl = @"https://www.baidu.com";
    item.share_imgurl =@"123";//https://dl03.gm88.com/xmjlogo/fxxz.png";
    item.share_msg = @"一般情况新浪微博的Summary和微信,QQ的是不同的,新浪微博的是一般带链接的,而且总共字数不能超过140字";
    return item;
}

#pragma mark - 方法
//登录
- (void)userLogin  {
    
    [loginSDK login:self];
 
}

//登出
- (void)userExit  {
    [loginSDK logout];
}

//支付
- (void)userBuy  {
    wfnjiOrderModel* mPayInfo = [[wfnjiOrderModel alloc] init];
    /** 商品id */
    mPayInfo.productID= @"1101";
    /** Y 商品名 */
    mPayInfo.productName=@"商品名字测试";
    /** Y 商品价格 */
    mPayInfo.productPrice=@"0.99";
    /** 商品描述（不传则使用productName） */
    mPayInfo.productDes=@"商品描述";
    /** Y 商品订单号 透传数据*/
    int y =100 +  (arc4random() % 100000000);
    mPayInfo.gameReceipts=[NSString stringWithFormat:@"%d",y];
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
    //mPayInfo.wfnjinotifyURL = @"http://demo.gm88.com/ok.php?gameid=1156&promote=2";
    [wfnjiPlat wfnjipay:mPayInfo CallBack:self];

}


#pragma mark -通知回调
- (void)notificationFunc:(NSNotification*)notification{
    NSDictionary * shearInfo = (NSDictionary *)notification.object;
    if([[shearInfo objectForKey:@"type"] isEqualToString:@"1"]){
        //成功
        NSLog(@"=========成功========");
        
          NSLog(@"shearInfo==%@",shearInfo);
    }else{
        //失败
        NSLog(@"shearInfo==%@",shearInfo);
        NSLog(@"=========失败========");
      
    }
}


#pragma mark -wfnjiLoginCallBack,wfnjiPayCallBack
-(void)onFinish:(wfnjiStatus)code Data:(NSDictionary *)Data {
    NSLog(@"%ld",code);
    NSLog(@"用户信息info==%@\n"   , Data);
    if(code== LOGIN_SUCCESS){
       NSLog(@"登录成功");
    }else if(code== LOGOUT_SUCCESS){
      //需要自己调用登录方法
        [self userLogin];
         NSLog(@"退出成功");
    }else if  (code == LOGIN_SWITCH){
         NSLog(@"切换账号");
    }else if(code==PAY_SUCCESS){
        NSLog(@"支付成功");
    }else if (code ==PAY_FAILED){
        
        NSLog(@"支付失败");
    }else if (code==PAY_CANCEL){
        
        NSLog(@"支付取消");
    }else if (code==PAY_UNKNOWN){
        NSLog(@"未知错误");
    }
}

@end
