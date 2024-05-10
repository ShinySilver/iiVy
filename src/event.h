#pragma once

#include <stdlib.h>
#include "log.h"
#include "utils.h"

#define event_register(event_type) \
    struct event_type ## _struct; \
    typedef struct event_type ## _struct event_type; \
    void common (** event_type ## _register)(event_type *); \
    unsigned int common event_type ## _register_length; \
    struct event_type ## _struct

#define event_subscribe(event_type) \
    static void on_ ## event_type(event_type *); \
    static void  constructor on_ ## event_type ## _subscriber(void) \
    { \
        void *_event_register = realloc(event_type ## _register, (++event_type ## _register_length)*sizeof(void *)); \
        if(_event_register == NULL) fatal("Out of memory"); \
        event_type ## _register = _event_register; \
        event_type ## _register[event_type ## _register_length - 1] = on_ ## event_type; \
    } \
    static void on_ ## event_type(event_type *event)

#define event_fire(event_type, event) \
    { \
        event_type _event = event; \
        for(int i = 0; i<event_type ## _register_length; i++) \
            event_type ## _register[i](&_event);\
    }

