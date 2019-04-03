/*
 *  varint.c
 *
 *  copyright (c) 2019 Xiongfei Shi
 *
 *  author: Xiongfei Shi <jenson.shixf(a)gmail.com>
 *  license: Apache2.0
 *
 *  https://github.com/shixiongfei/varint
 */

#include "varint.h"

int varint_fromint64(int64_t num, void *buffer, int len) {
  /* ZIGZAG ENCODE */
  num = ((num << 1) ^ (num >> ((sizeof(int64_t) << 3) - 1)));
  return varint_fromuint64((uint64_t)num, buffer, len);
}

int varint_fromuint64(uint64_t num, void *buffer, int len) {
  unsigned int p0 = (unsigned int)num;
  unsigned int p1 = (unsigned int)(num >> 28);
  unsigned int p2 = (unsigned int)(num >> 56);
  unsigned char *buf = (unsigned char *)buffer;
  int size = -1;

  if (0 == p2)
    if (0 == p1)
      if (p0 < (1 << 14))
        size = (p0 < (1 << 7)) ? 1 : 2;
      else
        size = (p0 < (1 << 21)) ? 3 : 4;
    else if (p1 < (1 << 14))
      size = (p1 < (1 << 7)) ? 5 : 6;
    else
      size = (p1 < (1 << 21)) ? 7 : 8;
  else
    size = (p2 < (1 << 7)) ? 9 : 10;

  if (size <= 0)
    return 0;

  if (buf) {
    if (len < size)
      return 0;

    switch (size) {
    case 10:
      buf[9] = (unsigned char)((p2 >> 7) | 0x80);
    case 9:
      buf[8] = (unsigned char)(p2 | 0x80);
    case 8:
      buf[7] = (unsigned char)((p1 >> 21) | 0x80);
    case 7:
      buf[6] = (unsigned char)((p1 >> 14) | 0x80);
    case 6:
      buf[5] = (unsigned char)((p1 >> 7) | 0x80);
    case 5:
      buf[4] = (unsigned char)(p1 | 0x80);
    case 4:
      buf[3] = (unsigned char)((p0 >> 21) | 0x80);
    case 3:
      buf[2] = (unsigned char)((p0 >> 14) | 0x80);
    case 2:
      buf[1] = (unsigned char)((p0 >> 7) | 0x80);
    case 1:
      buf[0] = (unsigned char)(p0 | 0x80);
    }

    buf[size - 1] &= 0x7F;
  }

  return size;
}

int varint_toint64(int64_t *num, const void *buffer, int len) {
  int s;

  s = varint_touint64((uint64_t *)num, buffer, len);

  if (num)
    *num = (((*num) >> 1) ^ -((int64_t)((*num) & 1))); /* ZIGZAG DECODE */

  return s;
}

int varint_touint64(uint64_t *num, const void *buffer, int len) {
  unsigned int p0 = 0, p1 = 0, p2 = 0;
  const unsigned char *buf = (const unsigned char *)buffer;
  int s = 0, i;

  if (len <= 0)
    return 0;

  if (len > VARINT64_MAXSIZE)
    len = VARINT64_MAXSIZE;

  for (i = 0; i < len; ++i) {
    switch (i) {
    case 0:
      p0 = (buf[i] & 0x7F);
      break;
    case 1:
      p0 |= (buf[i] & 0x7F) << 7;
      break;
    case 2:
      p0 |= (buf[i] & 0x7F) << 14;
      break;
    case 3:
      p0 |= (buf[i] & 0x7F) << 21;
      break;
    case 4:
      p1 = (buf[i] & 0x7F);
      break;
    case 5:
      p1 |= (buf[i] & 0x7F) << 7;
      break;
    case 6:
      p1 |= (buf[i] & 0x7F) << 14;
      break;
    case 7:
      p1 |= (buf[i] & 0x7F) << 21;
      break;
    case 8:
      p2 = (buf[i] & 0x7F);
      break;
    case 9:
      p2 |= (buf[i] & 0x7F) << 7;
      break;
    }

    if (!(buf[i] & 0x80)) {
      s = i + 1;
      break;
    }
  }

  if (num)
    *num = ((uint64_t)p0 | (((uint64_t)(p1)) << 28) | (((uint64_t)(p2)) << 56));

  return s;
}
