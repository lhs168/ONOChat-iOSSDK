//
//  ONO Chat SDK
//
//  Created by Kevin Lai on 18/5.
//  Copyright (c) 2018 ONO Team. All rights reserved.
//  仅有此类对外调用

#import <Foundation/Foundation.h>
#import "ONOCMessage.h"
#import "ONOMessage.h"
#import "ONOConversation.h"
#import "ONOFriendRequest.h"

/** 收到信息delegate */
@protocol ONOReceiveMessageDelegate <NSObject>
/** 已经登陆状态下,收到消息 */
- (void)onReceived:(ONOMessage *)message;
/** 刚刚登陆状态下,收到未读消息,已存到本地数据库,刷新 conversion 会话列表即可 */
- (void)onGetUnreadMessages;
@end

/** 用户被踢出delegate */
@protocol ONOReceiveUserKickDelegate <NSObject>
- (void)onReceivedUserKick:(NSString *)message;
@end

/** 用户好友相关操作delegate */
@protocol ONOReceiveFriendMessageDelegate <NSObject>
/** 接到好友请求 */
- (void)onReceivedNewFriendRequest:(NSString *)message;
/** 新的好友 */
- (void)onReceivedNewFriend:(NSString *)message;
/** 好友列表更新,刷新好友列表即可 */
- (void)onReceivedFriendListUpdate;

@end


@interface ONOIMClient : NSObject

/** 单例 */
+ (ONOIMClient *)sharedClient;

/** 收到信息delegate */
@property (nonatomic, weak) id<ONOReceiveMessageDelegate> receiveMessageDelegate;

/** 用户被踢出delegate */
@property (nonatomic, weak) id<ONOReceiveUserKickDelegate> receiveUserKickDelegate;

/** 用户好友相关操作delegate */
@property (nonatomic, weak) id<ONOReceiveFriendMessageDelegate> receiveFriendMessageDelegate;

/**
 *  设置聊天服务器参数
 *
 *  @param host    帐号
 *  @param port    端口号
 */
- (void)setupGateHost:(NSString*)host port:(int)port;


/**
 *  登录
 *
 *  @param token      令牌 (在后台绑定的登录token)
 */
- (void)loginWithToken:(NSString *)token onSuccess:(void(^)(ONOUser *user))successBlock onError:(void(^)(int errorCode, NSString *errorMsg))errorBlock;

/**
 *  退出登录
 *
 */
- (void)logout;



/**
 *  发送消息
 *
 *  @param message   要发送的消息
 *  @param targetId    目标ID
 */

- (void)sendMessage:(ONOMessage *)message to:(NSString *)targetId onSuccess:(void (^)(NSString *messageId))successBlock onError:(void (^)(int errorCode, NSString *errorMessage))errorBlock;

/**
 *  获取会话列表
 */
- (NSArray <ONOConversation *>*)getConversationList;

/**
 *  获取单个会话信息
 *  @param userId    目标用户ID
 */
- (ONOConversation *)getConversation:(NSString *)userId;

/**
 *  获取消息列表
 */
- (NSArray <ONOMessage *>*)getMessageList:(NSString *)targetId offset:(NSString *)offset limit:(int)limit;

/**
 *  获取未读消息数目
 */
- (int)totalUnreadCount;

/**
 *  清空指定会话的未读消息数
 *  @param targetId    会话id
 */
- (void)clearConversationUnread:(NSString *)targetId;

- (ONOMessage *)createMessageByType:(int)type;


/**
 *  获取用户信息
 *  @param userId    会话id
 */
- (void)userProfile:(NSString *)userId onSuccess:(void (^)(ONOUser *user))successBlock onError:(void (^)(int errorCode, NSString *errorMessage))errorBlock;
- (void)userProfile:(NSString *)userId withCache:(BOOL)withCache onSuccess:(void (^)(ONOUser *user))successBlock onError:(void (^)(int errorCode, NSString *errorMessage))errorBlock;
- (void)userProfiles:(NSArray<NSString*> *)userIds onSuccess:(void (^)(NSArray<ONOUser *> *users))successBlock onError:(void (^)(int errorCode, NSString *errorMessage))errorBlock;

// 好友

/**
 *  获取 好友列表(从本地获取)
 */
- (NSArray <ONOUser *>*)getFriends;


/**
 *  好友模糊搜索
 *  @param keyword    搜索关键字
 */
- (void)friendSearchByKeyword:(NSString *)keyword onSuccess:(void (^)(NSArray<ONOUser *> *userArray))successBlock onError:(void (^)(int errorCode, NSString *errorMessage))errorBlock;

/**
 *  好友添加
 *  @param userId       添加好友的id
 *  @param greeting    添加好友的问候语
 */
- (void)friendAddWithUserId:(NSString *)userId andGreeting:(NSString *)greeting onSuccess:(void (^)(void))successBlock onError:(void (^)(int errorCode, NSString *errorMessage))errorBlock;

/**
 *  好友添加请求列表(offset时间点以前的请求列表)
 *  @param limit       条数
 *  @param offset    分页之前的最一条的createdAt
 */
- (void)friendRequestListWithLimit:(int)limit andOffset:(NSString *)offset onSuccess:(void (^)(NSArray<ONOFriendRequest *> *friendRequest))successBlock onError:(void (^)(int errorCode, NSString *errorMessage))errorBlock;

/**
 *  好友添加请求 -> 通过
 *  @param userId       添加请求好友的id
 */
- (void)friendAgreeWithUserId:(NSString *)userId onSuccess:(void (^)(void))successBlock onError:(void (^)(int errorCode, NSString *errorMessage))errorBlock;

/**
 *  好友添加请求 -> 忽略
 *  @param userId       添加请求好友的id
 */
- (void)friendIgnoreWithUserId:(NSString *)userId onSuccess:(void (^)(void))successBlock onError:(void (^)(int errorCode, NSString *errorMessage))errorBlock;

/**
 *  好友删除
 *  @param userId       要删除好友的id
 */
- (void)friendDeleteWithUserId:(NSString *)userId onSuccess:(void (^)(void))successBlock onError:(void (^)(int errorCode, NSString *errorMessage))errorBlock;

/**
 *  好友添加别名(备注名称)
 *  @param userId       好友的id
 *  @param alias       别名
 */
- (void)friendRemarkWithUserId:(NSString *)userId andAlias:(NSString *)alias onSuccess:(void (^)(void))successBlock onError:(void (^)(int errorCode, NSString *errorMessage))errorBlock;


@end

