//
//  NSData+ZstdCompression.h
//  ZstdKit
//
//  Created by Micha Mazaheri on 4/12/18.
//  Copyright © 2018 Paw. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSData (ZstdCompression)

/// 普通模式压缩
- (nullable NSData*)compressZstd;

/// 普通模式解压缩
- (nullable NSData*)decompressZstd;

/// 字典模式压缩
/// - Parameter dictionary: 字典数据
- (nullable NSData *)compressZstdWithdictionary:(NSData * _Nonnull)dictionary;

/// 字典模式解压缩
/// - Parameter dictionary: 字典数据
- (nullable NSData *)decompressZstdWithdictionary:(NSData * _Nonnull)dictionary;
@end
