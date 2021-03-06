//
//  ONO Chat SDK
//
//  Created by Kevin Lai on 18/5.
//  Copyright (c) 2018 ONO Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ONOCMessage.h"
#import "ONORouteInfo.h"
#import "ONOUser.h"

//todo:重连机制，客户端保存session id
typedef void (^ONOSuccessResponse)(id msg);
typedef void (^ONOErrorResponse)(id msg);



@interface ONOCore : NSObject

+ (ONOCore *)sharedCore;


/**
 *  监听消息
 *
 *  @param route      监听指定类型消息
 *  @param response   获得消息回调函数
 *  @return 监听消息的唯一标识码
 */
- (NSInteger)addListenerForRoute:(NSString *)route withCallback:(ONOSuccessResponse)response;

/**
 *  移除监听消息
 *
 *  @param listenerId      监听消息的唯一标识码
 */
- (void)removeListenerWithId:(NSInteger)listenerId;


@property (nonatomic, strong) NSString *userId;
@property (nonatomic, strong) ONOUser *user;

- (void)connectToGateHost:(NSString *)host port:(int)port;
- (void)disconnect;

- (void)handleConnected:(NSDictionary *)response;
- (void)handleResponse:(ONOCMessage *)message;

- (NSString *)getRouteByMsgId:(NSUInteger)msgId;
- (NSString *)getRouteByRouteId:(NSUInteger)routeId;
- (ONORouteInfo *)getRouteInfo:(NSString *)route;

- (void)requestRoute:(NSString *)route withMessage:(GPBMessage *)msg onSuccess:(ONOSuccessResponse)success onError:(ONOErrorResponse)error;
- (void)notifyRoute:(NSString *)route withMessage:(GPBMessage *)msg;

- (void)bindClientId:(NSString *)clientId;
- (void)bindDeviceToken:(NSString *)deviceToken;

- (void)loginToGateHost:(NSString *)host port:(int)port token:(NSString *)token onSuccess:(ONOSuccessResponse)success onError:(ONOErrorResponse)error;


@end

