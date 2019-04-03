/*
 *  test.c
 *
 *  copyright (c) 2019 Xiongfei Shi
 *
 *  author: Xiongfei Shi <jenson.shixf(a)gmail.com>
 *  license: Apache2.0
 *
 *  https://github.com/shixiongfei/varint
 */

#include <inttypes.h> 
#include <stdio.h>

#include "varint.h"

int main(int argc, char *argv[]) {
    int64_t ni64, i64 = 12345678987654321;
    uint64_t nu64, u64 = 1234567890987654321;
    char i64buf[VARINT64_MAXSIZE] = { 0 };
    char u64buf[VARINT64_MAXSIZE] = { 0 };

    printf("%i bytes, varint fromint64\n", varint_fromint64(i64, i64buf, sizeof(i64buf)));
    printf("%i bytes, varint fromuint64\n", varint_fromuint64(u64, u64buf, sizeof(u64buf)));
    printf("%i bytes, varint toint64\n", varint_toint64(&ni64, i64buf, sizeof(i64buf)));
    printf("%i bytes, varint touint64\n", varint_touint64(&nu64, u64buf, sizeof(u64buf)));
    printf("i64 = %"PRIi64"\n", ni64);
    printf("u64 = %"PRIu64"\n", nu64);

    return 0;
}
