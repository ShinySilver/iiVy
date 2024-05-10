#pragma once


#include <time.h>
#include <bits/stdint-uintn.h>
#include <bits/stdint-intn.h>

/*
 * Useful attributes
 */

#define common __attribute__((common))
#define constructor __attribute__((constructor))

/*
 * Shorter type names
 */

typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

/*
 * Misc functions
 */

u64 static time_ns(void) {
    struct timespec spec;
    clock_gettime(CLOCK_MONOTONIC, &spec);
    return spec.tv_sec*(u64)1e9+spec.tv_nsec;
}

u32 static mod(u32 a, u32 b){
    u32 r = a % b;
    return r < 0 ? r + b : r;
}

