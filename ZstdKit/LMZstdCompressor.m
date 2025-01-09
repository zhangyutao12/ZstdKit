//
//  LMZstdCompressor.m
//  ZstdKit
//
//  Created by Micha Mazaheri on 4/12/18.
//  Copyright © 2018 Paw. All rights reserved.
//

#import "LMZstdCompressor.h"

#import "LMZstdCompression.h"
#include <stdio.h>
#include <stdlib.h>

#define ZSTD_STATIC_LINKING_ONLY   // ZSTD_findDecompressedSize
#include "zstd.h"


@implementation LMZstdCompressor

+ (NSInteger)defaultCompressionLevel
{
    return LMZstdCompressionLevelDefault;
}

+ (NSData*)compressedDataWithData:(NSData*)input
{
    return [self compressedDataWithData:input compressionLevel:self.defaultCompressionLevel];
}

+ (NSData*)compressedDataWithData:(NSData*)input compressionLevel:(NSInteger)compressionLevel
{
    return [self compressedDataWithBytes:input.bytes length:input.length compressionLevel:compressionLevel];
}

+ (NSData*)compressedDataWithBytes:(const void*)bytes length:(NSUInteger)length
{
    return [self compressedDataWithBytes:bytes length:length compressionLevel:self.defaultCompressionLevel];
}

+ (NSData*)compressedDataWithBytes:(const void*)bytes length:(NSUInteger)length compressionLevel:(NSInteger)compressionLevel
{
    return CFBridgingRelease(LMCreateZstdCompressedData(bytes, length, compressionLevel));
}




+ (NSData*)decompressedDataWithData:(NSData*)input
{
    return [self decompressedDataWithBytes:input.bytes length:input.length];
}

+ (NSData*)decompressedDataWithBytes:(const void*)bytes length:(NSUInteger)length
{
    return CFBridgingRelease(LMCreateZstdDecompressedData(bytes, length));
}

+ (NSData*)compressedDataWithData:(NSData*)input dictionary:(NSData*)dictionary
{
    return [self compressedDataWithBytes:input.bytes length:input.length dictionary:dictionary compressionLevel:self.defaultCompressionLevel];
}

+ (NSData*)compressedDataWithBytes:(const void*)bytes length:(NSUInteger)length dictionary:(NSData*)dictionary
{
    return [self compressedDataWithBytes:bytes length:length dictionary:dictionary compressionLevel:self.defaultCompressionLevel];
}

+ (NSData*)compressedDataWithBytes:(const void*)bytes length:(NSUInteger)length dictionary:(NSData*)dictionary compressionLevel:(NSInteger)compressionLevel
{
    if (!dictionary) {
        return nil; // 字典不能为空
    }
    return CFBridgingRelease(LMCreateZstdCompressedDataWithDictionary(bytes, length, dictionary.bytes, dictionary.length, compressionLevel));
}

+ (NSData*)decompressedDataWithData:(NSData*)input dictionary:(NSData*)dictionary
{
    return [self decompressedDataWithBytes:input.bytes length:input.length dictionary:dictionary];
}

+ (NSData*)decompressedDataWithBytes:(const void*)bytes length:(NSUInteger)length dictionary:(NSData*)dictionary
{
    if (!dictionary) {
        return nil; // 字典不能为空
    }
    return CFBridgingRelease(LMCreateZstdDecompressedDataWithDictionary(bytes, length, dictionary.bytes, dictionary.length));
}



@end
