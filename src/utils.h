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

int static mod(int a, int b){
    int r = a % b;
    return r < 0 ? r + b : r;
}

