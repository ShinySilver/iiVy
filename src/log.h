#pragma once

#include <stdio.h>
#include <stdlib.h>

#define info(_message, ...) {printf("INFO: %s:%d: ", __FILE__, __LINE__); printf(_message, ##__VA_ARGS__); printf("\n");}
#define warn(_message, ...) {printf("WARN: %s:%d: ", __FILE__, __LINE__); printf(_message, ##__VA_ARGS__); printf("\n");}
#define error(_message, ...) {fprintf(stderr, "ERROR: %s:%d: ", __FILE__, __LINE__); fprintf(stderr, _message, ##__VA_ARGS__); fprintf(stderr, "\n");}
#define fatal(_message, ...) {fprintf(stderr, "FATAL: %s:%d: ", __FILE__, __LINE__); fprintf(stderr, _message, ##__VA_ARGS__); fprintf(stderr, "\n"); exit(0);}