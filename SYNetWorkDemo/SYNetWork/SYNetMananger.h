//
//  SYHttpNetMananger.h
//  SYNetDome
//
//  Created by ksw on 2017/9/14.
//  Copyright © 2017年 ksw. All rights reserved.
//  github地址:https://github.com/sunyong445

#import <Foundation/Foundation.h>
#import "SYNetRequestInfo.h"

NS_ASSUME_NONNULL_BEGIN

#define NetSuccess(result) ([[result objectForKey:@"code"] intValue] == 1)

#define NetCacheDuration 60*5


@interface SYNetMananger : NSObject

@property (nonatomic, copy) NSString *netState;

+ (nonnull instancetype)sharedInstance;


// 请求参数条件 处理
@property (nonatomic, copy)SYRequsetParamConditionBlock requestParamCondictionBlock;
/**
 外部添加异常处理 （根据服务器返回的数据，统一处理，如处理登录实效），默认不做处理
 */
@property (nonatomic, copy)SYRequestCompletionAddExcepetionHanle exceptionBlock;
// 返回NO， cache不保存
@property (nonatomic, copy)SYRequestCompletionAddCacheCondition cacheConditionBlock;


// 使用默认配置的缓存策略
- (void)syGetCacheWithUrl:(NSString*)urlString
                   parameters:(NSDictionary * _Nullable)parameters
            completionHandler:(SYRequestCompletionHandler)completionHandler;

- (void)syPostCacheWithUrl:(NSString*)urlString
               parameters:(NSDictionary * _Nullable)parameters
        completionHandler:(SYRequestCompletionHandler)completionHandler;

// 不使用缓存
- (void)syPostNoCacheWithUrl:(NSString*)urlString
                      parameters:(NSDictionary * _Nullable)parameters
               completionHandler:(SYRequestCompletionHandler)completionHandler;

- (void)syGetNoCacheWithUrl:(NSString*)urlString
                  parameters:(NSDictionary * _Nullable)parameters
          completionHandler:(SYRequestCompletionHandler)completionHandler;
/**
 POST请求
 @param URLString url地址
 @param parameters 请求参数
 @param ignoreCache 是否忽略缓存，YES 忽略，NO 不忽略
 @param cacheDuration 缓存实效
 @param completionHandler 请求结果处理
 */
- (void)syPostWithURLString:(NSString *)URLString
               parameters:(NSDictionary * _Nullable)parameters
              ignoreCache:(BOOL)ignoreCache
            cacheDuration:(NSTimeInterval)cacheDuration
        completionHandler:(SYRequestCompletionHandler)completionHandler;


/**
 GET请求
 
 @param URLString url地址
 @param parameters 请求参数
 @param ignoreCache 是否忽略缓存，YES 忽略，NO 不忽略
 @param cacheDuration 缓存实效
 @param completionHandler 请求结果处理
 */
- (void)syGetWithURLString:(NSString *)URLString
              parameters:(NSDictionary *)parameters
             ignoreCache:(BOOL)ignoreCache
           cacheDuration:(NSTimeInterval)cacheDuration
       completionHandler:(SYRequestCompletionHandler)completionHandler;




#pragma mark - Net 多任务

/**
 保存网络请求信息 和 batchOfRequestOperations方法一起用
 */
- (SYNetRequestInfo*)syNetRequestWithURLStr:(NSString *)URLString
                                     method:(NSString*)method
                                 parameters:(NSDictionary *)parameters
                                ignoreCache:(BOOL)ignoreCache
                              cacheDuration:(NSTimeInterval)cacheDuration
                          completionHandler:(SYRequestCompletionHandler)completionHandler;



- (SYNetRequestInfo*)syGetRequestNoCacheWithURL:(NSString *)URLString
                                     parameters:(NSDictionary *)parameters
                              completionHandler:(SYRequestCompletionHandler)completionHandler;

- (SYNetRequestInfo*)syPostRequestNoCacheWithURL:(NSString *)URLString
                                 parameters:(NSDictionary *)parameters
                          completionHandler:(SYRequestCompletionHandler)completionHandler;


// 开启任务 用SYNetRequestInfo
+ (void)syResumeTask:(SYNetRequestInfo*)requestInfo;


/**
 执行多个网络请求
 
 @param tasks 请求信息
 @param progressBlock 网络任务完成的进度
 @param completionBlock tasks中所有网络任务结束
 */
- (void)syBatchOfRequestOperations:(NSArray<SYNetRequestInfo *> *)tasks
                   progressBlock:(nullable void (^)(NSUInteger numberOfFinishedTasks, NSUInteger totalNumberOfTasks))progressBlock
                 completionBlock:(netSuccessbatchBlock)completionBlock;

/**
 执行多个网络请求，同上 没有进度progress参数
 
 @param tasks 请求信息
 @param completionBlock tasks中所有网络任务结束
 */
- (void)syBatchOfRequestOperations:(NSArray<SYNetRequestInfo *> *)tasks completionBlock:(netSuccessbatchBlock)completionBlock;

/**
 执行多个网络请求，注意⚠️按照tasks里的顺序先后执行

 @param tasks 请求信信
 @param completionBlock tasks中所有网络任务结束
 */
- (void)syBatchOfRequestSynOperations:(NSArray<SYNetRequestInfo *> *)tasks completionBlock:(netSuccessbatchBlock)completionBlock;

NS_ASSUME_NONNULL_END

@end
