#include "event.h"
#include "utils.h"
#include "events/client_tick_event.h"
#include "events/client_started_event.h"
#include "raylib.h"
#include "external/glad.h"

static u64 current_time;
static u32 count, accum;
static char win_title[256];
static const GLubyte *gl_renderer_name;
static const GLubyte *gl_vendor_name;

event_subscribe(client_started_event){
    current_time = time_ns();
    accum = INT32_MAX; // triggers the renaming on the first frame.
    gl_renderer_name = glGetString(GL_RENDERER);
    gl_vendor_name = glGetString(GL_VENDOR);
}

event_subscribe(client_tick_event){
    u64 new_time = time_ns();
    accum += new_time - current_time;
    current_time = new_time;
    count++;
    if (accum / 1e9 >= 1) {
        double frame_time = (accum / (double) count / 1e9);
        snprintf(win_title, 256, "iiVy - %0.2fms - %0.2fFPS - %s %s - %dx%d", frame_time*1e3,
                 1./frame_time, gl_vendor_name, gl_renderer_name, GetRenderWidth(), GetRenderHeight());
        SetWindowTitle(win_title);
        accum = 0;
        count = 0;
    }
}