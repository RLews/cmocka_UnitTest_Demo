

#ifndef UNIT_TEST_TYPE_H
#define UNIT_TEST_TYPE_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef             int32_t        s32;

typedef             int16_t        s16;

typedef             int8_t        s8;

typedef             const int32_t        sc32;

typedef             const int16_t        sc16;

typedef             const int8_t        sc8;

typedef             uint64_t         u64;

typedef             uint32_t         u32;

typedef             uint16_t         u16;

typedef             uint8_t         u8;

typedef             const uint32_t        uc32;

typedef             const uint16_t        uc16;

typedef             const uint8_t        uc8;


#define RXD_BYTE0(x)     (u8)(((x) >>  0) & 0xff)
#define RXD_BYTE1(x)     (u8)(((x) >>  8) & 0xff)
#define RXD_BYTE2(x)     (u8)(((x) >> 16) & 0xff)
#define RXD_BYTE3(x)     (u8)(((x) >> 24) & 0xff)
#define RXD_BYTE4(x)     (u8)(((x) >> 32) & 0xff)
#define RXD_BYTE5(x)     (u8)(((x) >> 40) & 0xff)
#define RXD_BYTE6(x)     (u8)(((x) >> 48) & 0xff)
#define RXD_BYTE7(x)     (u8)(((x) >> 56) & 0xff)

#define RXD_WORDSWAP(x)  (u16)( \
    ((  (u16)RXD_BYTE0((x))) <<  8) | \
    ((  (u16)RXD_BYTE1((x))) <<  0))

#define RXD_DWORDSWAP(x) (u32)( \
    (( (u32)RXD_BYTE0((x))) << 24) | \
    (( (u32)RXD_BYTE1((x))) << 16) | \
    (( (u32)RXD_BYTE2((x))) <<  8) | \
    (( (u32)RXD_BYTE3((x))) <<  0))

#define RXD_QWORDSWAP(x) (u64)( \
    (((u64)RXD_BYTE0((x))) << 56) | \
    (((u64)RXD_BYTE1((x))) << 48) | \
    (((u64)RXD_BYTE2((x))) << 40) | \
    (((u64)RXD_BYTE3((x))) << 32) | \
    (((u64)RXD_BYTE4((x))) << 24) | \
    (((u64)RXD_BYTE5((x))) << 16) | \
    (((u64)RXD_BYTE6((x))) <<  8) | \
    (((u64)RXD_BYTE7((x))) <<  0))

#define RXD_NTOHS(w)                 RXD_WORDSWAP((w))
#define RXD_NTOHL(dw)                RXD_DWORDSWAP((dw))
#define RXD_NTOHLL(qw)               RXD_QWORDSWAP((qw))

#define RXD_HTONS(w)                 RXD_WORDSWAP((w))
#define RXD_HTONL(dw)                RXD_DWORDSWAP((dw))
#define RXD_HTONLL(qw)               RXD_QWORDSWAP((qw))


typedef enum {
    TBOX_FALSE 	= 0,
    TBOX_TRUE 	= !TBOX_FALSE
} tboxTrueOrFalse;



#endif