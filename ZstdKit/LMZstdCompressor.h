//
//  LMZstdCompressor.h
//  ZstdKit
//
//  Created by Micha Mazaheri on 4/12/18.
//  Copyright © 2018 Paw. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface LMZstdCompressor : NSObject

@property (class, nonatomic, assign, readonly) NSInteger defaultCompressionLevel;

/**
 Creates a newly created NSData, with the default compression level.
 The input is compressed via the Zstd algorithm.
 
 @param input Input data.
 @return Return the newly created compressed data.
 */
+ (nullable NSData*)compressedDataWithData:(NSData* _Nonnull)input;

/**
 Creates a newly created NSData.
 The input is compressed via the Zstd algorithm.
 
 @param input Input data.
 @param compressionLevel Compression level.
 @return Return the newly created compressed data.
 */
+ (nullable NSData*)compressedDataWithData:(NSData* _Nonnull)input compressionLevel:(NSInteger)compressionLevel;

/**
 Creates a newly created NSData, with the default compression level.
 The input is compressed via the Zstd algorithm.
 
 @param bytes Input bytes.
 @param length Input length (number of bytes).
 @return Return the newly created compressed data.
 */
+ (nullable NSData*)compressedDataWithBytes:(const void* _Nonnull)bytes length:(NSUInteger)length;

/**
 Creates a newly created NSData.
 The input is compressed via the Zstd algorithm.
 
 @param bytes Input bytes.
 @param length Input length (number of bytes).
 @param compressionLevel Compression level.
 @return Return the newly created compressed data.
 */
+ (nullable NSData*)compressedDataWithBytes:(const void* _Nonnull)bytes length:(NSUInteger)length compressionLevel:(NSInteger)compressionLevel;

/**
 Creates a newly created NSData.
 The input is decompressed via the Zstd algorithm.
 Will return nil (error) if the input was only partial.
 
 @param input Input data.
 @return Return the newly created decompressed data.
 */
+ (nullable NSData*)decompressedDataWithData:(NSData* _Nonnull)input;

/**
 Creates a newly created NSData.
 The input is decompressed via the Zstd algorithm.
 Will return nil (error) if the input was only partial.
 
 @param bytes Input bytes.
 @param length Input length (number of bytes).
 @return Return the newly created decompressed data.
 */
+ (nullable NSData*)decompressedDataWithBytes:(const void* _Nonnull)bytes length:(NSUInteger)length;


+ (nullable NSData*)compressedDataWithData:(NSData* _Nonnull)input dictionary:(NSData* _Nonnull)dictionary;


/**
 Compresses the input bytes using the Zstd algorithm and a given dictionary.
 Creates and returns a newly compressed NSData object.
 Will return nil if the compression fails.

 @param bytes Input bytes to be compressed.
 @param length Input length (number of bytes).
 @param dictionary The dictionary to use for compression.
 @return A newly created NSData object containing the compressed data, or nil if compression fails.
 */
+ (nullable NSData*)compressedDataWithBytes:(const void* _Nonnull)bytes
                                     length:(NSUInteger)length
                                 dictionary:(NSData* _Nonnull)dictionary;

/**
 Compresses the input bytes using the Zstd algorithm, a given dictionary, and the specified compression level.
 Creates and returns a newly compressed NSData object.
 Will return nil if the compression fails.

 @param bytes Input bytes to be compressed.
 @param length Input length (number of bytes).
 @param dictionary The dictionary to use for compression.
 @param compressionLevel The level of compression to apply (higher values typically yield better compression but slower speeds).
 @return A newly created NSData object containing the compressed data, or nil if compression fails.
 */
+ (nullable NSData*)compressedDataWithBytes:(const void* _Nonnull)bytes
                                     length:(NSUInteger)length
                                 dictionary:(NSData* _Nonnull)dictionary
                          compressionLevel:(NSInteger)compressionLevel;

/**
 Decompresses the input data using the Zstd algorithm and a given dictionary.
 Creates and returns a newly decompressed NSData object.
 Will return nil if the decompression fails.

 @param input The compressed NSData to decompress.
 @param dictionary The dictionary to use for decompression.
 @return A newly created NSData object containing the decompressed data, or nil if decompression fails.
 */
+ (nullable NSData*)decompressedDataWithData:(NSData* _Nonnull)input
                                  dictionary:(NSData* _Nonnull)dictionary;

/**
 Decompresses the input bytes using the Zstd algorithm and a given dictionary.
 Creates and returns a newly decompressed NSData object.
 Will return nil if the decompression fails.

 @param bytes Input bytes to decompress.
 @param length Input length (number of bytes).
 @param dictionary The dictionary to use for decompression.
 @return A newly created NSData object containing the decompressed data, or nil if decompression fails.
 */
+ (nullable NSData*)decompressedDataWithBytes:(const void* _Nonnull)bytes
                                       length:(NSUInteger)length
                                   dictionary:(NSData* _Nonnull)dictionary;
@end
