#include "log.h"
#include "event.h"
#include "events/client_started_event.h"
#include "events/client_stopped_event.h"
#include "events/client_tick_event.h"
#include "raylib.h"
#include "events/client_draw_event.h"

#define PHYSAC_IMPLEMENTATION
#include "physac.h"

#define DEFAULT_WIN_WIDTH 1152
#define DEFAULT_WIN_HEIGHT 648

int main(int argc, char** argv) {

    /**
     * Starting client
     */
    SetConfigFlags(FLAG_VSYNC_HINT|FLAG_WINDOW_HIGHDPI|FLAG_MSAA_4X_HINT);
    InitWindow(DEFAULT_WIN_WIDTH, DEFAULT_WIN_HEIGHT, "iiVy");
    InitPhysics();
    info("Client started!");
    event_fire(client_started_event, ((client_started_event) {.current_time_sec=GetTime()}));

    /**
     * Starting the event loop!
     */
    info("Client ticking!");
    while (!WindowShouldClose()) {

        /**
         * Firing the tick event
         */
        event_fire(client_tick_event, ((client_tick_event) {.current_time_sec=GetTime(), .frame_time_sec=GetFrameTime()}));

        /**
         * And now the draw event
         */
        BeginDrawing();
        ClearBackground(BLANK); // we keep it for debug for now
        event_fire(client_early_draw_event, ((client_early_draw_event) {.current_time_sec=GetTime(), .frame_time_sec=GetFrameTime()}));
        event_fire(client_draw_event, ((client_draw_event) {.current_time_sec=GetTime(), .frame_time_sec=GetFrameTime()}));
        event_fire(client_late_draw_event, ((client_late_draw_event) {.current_time_sec=GetTime(), .frame_time_sec=GetFrameTime()}));
        EndDrawing();
    }

    /**
     * Closing all opened buffers and destroying context since all the GL stuff is above
     */
    info("Client exiting.");
    event_fire(client_stopped_event, ((client_stopped_event) {.current_time_sec=GetTime()}));
    ClosePhysics();
    CloseWindow();
    return 0;
}