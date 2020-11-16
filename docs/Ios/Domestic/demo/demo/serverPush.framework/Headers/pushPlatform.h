//
//  pushPlatform.h
//  serverPush
//
//  Created by dingqw on 2020/3/24.
//  Copyright © 2020 server. All rights reserved.
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

@interface pushPlatform : NSObject

+ (void)startXGWithAppID:(uint32_t)appID appKey:(nonnull NSString *)appKey delegate:(  id )delegate;

@end

NS_ASSUME_NONNULL_END
