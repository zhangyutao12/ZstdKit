//
//  LMZstdCompression.h
//  ZstdKit
//
//  Created by Micha Mazaheri on 4/12/18.
//  Copyright © 2018 Paw. All rights reserved.
//

#ifndef LMZstdCompression_h
#define LMZstdCompression_h

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFData.h>

CF_EXPORT int16_t LMZstdCompressionLevelDefault;

/**
 Creates a newly created CFData.
 The input is compressed via the Zstd algorithm.
 
 @param bytes Input bytes.
 @param length Input length (number of bytes).
 @param compressionLevel Compression level (you can pass LMZstdCompressionLevelDefault).
 @return Return the newly created compressed data.
 */
CF_EXPORT CFDataRef LMCreateZstdCompressedData(const void* bytes, CFIndex length, int16_t compressionLevel);

/**
 Creates a newly created CFData.
 The input is decompressed via the Zstd algorithm.
 
 @param bytes Input bytes.
 @param length Input length (number of bytes).
 @return Return the newly created decompressed data.
 */
CF_EXPORT CFDataRef LMCreateZstdDecompressedData(const void* bytes, CFIndex length);

/**
 Compresses the input bytes using the Zstd algorithm and a specified dictionary.
 Creates and returns a newly created CFDataRef containing the compressed data.
 Will return NULL if the compression fails.

 @param bytes The input bytes to compress.
 @param length The length of the input data (in bytes).
 @param dict The dictionary to use for compression.
 @param dictSize The size of the dictionary (in bytes).
 @param compressionLevel The level of compression to apply (higher values typically yield better compression but slower speeds).
 @return A CFDataRef object containing the compressed data, or NULL if compression fails.
 */
CF_EXPORT CFDataRef LMCreateZstdCompressedDataWithDictionary(const void* bytes, CFIndex length, const void* dict, CFIndex dictSize, int16_t compressionLevel);

/**
 Decompresses the input compressed bytes using the Zstd algorithm and a specified dictionary.
 Creates and returns a newly created CFDataRef containing the decompressed data.
 Will return NULL if the decompression fails.

 @param compressedBytes The input bytes to decompress.
 @param compressedLength The length of the compressed data (in bytes).
 @param dict The dictionary to use for decompression.
 @param dictSize The size of the dictionary (in bytes).
 @return A CFDataRef object containing the decompressed data, or NULL if decompression fails.
 */
CF_EXPORT CFDataRef LMCreateZstdDecompressedDataWithDictionary(const void* compressedBytes, CFIndex compressedLength, const void* dict, CFIndex dictSize);

#endif /* LMZstdCompression_h */
