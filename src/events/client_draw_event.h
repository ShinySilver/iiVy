#pragma once

#include "event.h"

/**
 * Called by the client each frame. It is called before the main "client draw event". Can be used to draw backgrounds.
 */
event_register(client_early_draw_event) {
    float current_time_sec;
    float frame_time_sec;
};

/**
 * Called by the client each frame. Most of the raylib's Draw function calls should be done here.
 */
event_register(client_draw_event) {
    float current_time_sec;
    float frame_time_sec;
};

/**
 * Called by the client each frame. It is called before the main "client draw event". Can be used to draw overlays.
 */
event_register(client_late_draw_event) {
    float current_time_sec;
    float frame_time_sec;
};