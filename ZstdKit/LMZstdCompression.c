//
//  LMZstdCompression.c
//  ZstdKit
//
//  Created by Micha Mazaheri on 4/12/18.
//  Copyright © 2018 Paw. All rights reserved.
//

#include "LMZstdCompression.h"

#include <stdio.h>
#include <stdlib.h>

#define ZSTD_STATIC_LINKING_ONLY   // ZSTD_findDecompressedSize
#include "zstd.h"

int16_t LMZstdCompressionLevelDefault = 3 /* ZSTD_CLEVEL_DEFAULT */;

CFDataRef LMCreateZstdCompressedData(const void* bytes, CFIndex length, int16_t compressionLevel)
{
    if (bytes == NULL || length == 0) {
        return NULL;
    }
    
    // malloc the buffer
    const size_t maxOutputSize = ZSTD_compressBound(length);
    UInt8* outputBuffer = malloc(maxOutputSize);
    
    // compress
    const size_t outputSize = ZSTD_compress(outputBuffer, maxOutputSize, bytes, (size_t)length, (int)compressionLevel);
    
    // if failure, free buffer and return nil
    if (ZSTD_isError(outputSize)) {
        if (outputBuffer != NULL) {
            free(outputBuffer);
            outputBuffer = NULL;
        }
        return NULL;
    }
    
    // copy output data to a new NSData
    CFDataRef outputData = CFDataCreate(kCFAllocatorDefault, outputBuffer, outputSize);
    
    // free output buffer
    free(outputBuffer);
    outputBuffer = NULL;
    
    return outputData;
}


// 使用 ZSTD 字典进行压缩的函数
CFDataRef LMCreateZstdCompressedDataWithDictionary(const void* bytes, CFIndex length, const void* dict, CFIndex dictSize, int16_t compressionLevel)
{
    if (bytes == NULL || length == 0 || dict == NULL || dictSize == 0) {
        return NULL;
    }
    // 创建 ZSTD 压缩上下文
    ZSTD_CCtx* cctx = ZSTD_createCCtx();
    if (cctx == NULL) {
        return NULL;
    }
    // 计算压缩缓冲区的最大可能大小
    const size_t maxOutputSize = ZSTD_compressBound(length);
    UInt8* outputBuffer = malloc(maxOutputSize);
    if (outputBuffer == NULL) {
        return NULL;
    }
    
    // 使用字典进行压缩
    const size_t compressedSize = ZSTD_compress_usingDict(
                                                          cctx,
                                                          outputBuffer,          // 压缩结果存放的缓冲区
                                                          maxOutputSize,         // 压缩结果缓冲区的大小
                                                          bytes,                 // 输入数据
                                                          (size_t)length,        // 输入数据的大小
                                                          dict,                  // 压缩字典
                                                          (size_t)dictSize,      // 压缩字典的大小
                                                          (int)compressionLevel  // 压缩级别
                                                          );
    
    // 检查压缩是否成功
    if (ZSTD_isError(compressedSize)) {
        free(outputBuffer);
        return NULL;
    }
    
    // 将压缩数据拷贝到 CFData 对象
    CFDataRef outputData = CFDataCreate(kCFAllocatorDefault, outputBuffer, compressedSize);
    
    // 释放缓冲区
    free(outputBuffer);
    
    return outputData;
}


CFDataRef LMCreateZstdDecompressedData(const void* bytes, CFIndex length)
{
    if (bytes == NULL || length == 0) {
        return NULL;
    }
    
    // find the output size
    unsigned long long outputBufferSize = ZSTD_findDecompressedSize(bytes, length);
    if (ZSTD_CONTENTSIZE_ERROR == outputBufferSize ||
        ZSTD_CONTENTSIZE_UNKNOWN == outputBufferSize) {
        return NULL;
    }
    
    // malloc the buffer
    UInt8* outputBuffer = malloc((size_t)outputBufferSize);
    
    // decompress
    size_t outputSize = ZSTD_decompress(outputBuffer, (size_t)outputBufferSize, bytes, length);
    
    // if invalid output size, return NULL
    if (outputSize != outputBufferSize) {
        if (outputBuffer != NULL) {
            free(outputBuffer);
            outputBuffer = NULL;
        }
        return NULL;
    }
    
    // copy output data to a new NSData
    CFDataRef outputData = CFDataCreate(kCFAllocatorDefault, outputBuffer, (CFIndex)outputBufferSize);
    
    // free output buffer
    free(outputBuffer);
    outputBuffer = NULL;
    
    return outputData;
}

// 使用 ZSTD 字典进行解压缩的函数
CFDataRef LMCreateZstdDecompressedDataWithDictionary(const void* compressedBytes, CFIndex compressedLength, const void* dict, CFIndex dictSize)
{
    if (compressedBytes == NULL || compressedLength == 0 || dict == NULL || dictSize == 0) {
        return NULL;
    }
    
    // 创建 ZSTD 解压上下文
    ZSTD_DCtx* dctx = ZSTD_createDCtx();
    if (dctx == NULL) {
        return NULL;
    }
    
    // 计算解压缩所需的最大缓冲区大小
    // find the output size
    unsigned long long outputBufferSize = ZSTD_findDecompressedSize(compressedBytes, compressedLength);
    if (ZSTD_CONTENTSIZE_ERROR == outputBufferSize ||
        ZSTD_CONTENTSIZE_UNKNOWN == outputBufferSize) {
        return NULL;
    }
    
    
    UInt8* outputBuffer = malloc(outputBufferSize);
    if (outputBuffer == NULL) {
        ZSTD_freeDCtx(dctx);
        return NULL;
    }
    
    // 使用字典进行解压缩
    size_t actualDecompressedSize = ZSTD_decompress_usingDict(
                                                              dctx,                     // 解压上下文
                                                              outputBuffer,             // 解压结果存放的缓冲区
                                                              outputBufferSize,         // 解压缓冲区的大小
                                                              compressedBytes,          // 输入压缩数据
                                                              (size_t)compressedLength, // 输入压缩数据的大小
                                                              dict,                     // 解压字典
                                                              (size_t)dictSize          // 解压字典的大小
                                                              );
    
    // 检查解压缩是否成功
    if (ZSTD_isError(actualDecompressedSize)) {
        free(outputBuffer);
        ZSTD_freeDCtx(dctx);
        return NULL;
    }
    
    // 将解压后的数据拷贝到 CFData 对象
    CFDataRef outputData = CFDataCreate(kCFAllocatorDefault, outputBuffer, actualDecompressedSize);
    
    // 释放资源
    free(outputBuffer);
    ZSTD_freeDCtx(dctx);
    
    return outputData;
}
