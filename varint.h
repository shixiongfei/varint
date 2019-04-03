/*
 *  varint.h
 *
 *  copyright (c) 2019 Xiongfei Shi
 *
 *  author: Xiongfei Shi <jenson.shixf(a)gmail.com>
 *  license: Apache2.0
 *
 *  https://github.com/shixiongfei/varint
 *
 *      1 byte:                    0 -                  127
 *      2 bytes:                 128 -                16383
 *      3 bytes:               16384 -              2097151
 *      4 bytes:             2097152 -            268435455
 *      5 bytes:           268435456 -          34359738367
 *      6 bytes:         34359738368 -        4398046511103
 *      7 bytes:       4398046511104 -      562949953421311
 *      8 bytes:     562949953421312 -    72057594037927935
 *      9 bytes:   72057594037927936 -  9223372036854775807
 *     10 bytes: 9223372036854775808 - 18446744073709551615
 *
 */
 
#ifndef ___VARINT_H__
#define ___VARINT_H__

#include <stdint.h>

#define VARINT16_MAXSIZE 3
#define VARINT32_MAXSIZE 5
#define VARINT64_MAXSIZE 10

#ifdef __cplusplus
extern "C" {
#endif

int varint_fromint64(int64_t num, void *buffer, int len);
int varint_fromuint64(uint64_t num, void *buffer, int len);

int varint_toint64(int64_t *num, const void *buffer, int len);
int varint_touint64(uint64_t *num, const void *buffer, int len);

#ifdef __cplusplus
};
#endif

#endif /* ___VARINT_H__ */
