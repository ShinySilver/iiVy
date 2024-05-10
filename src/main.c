#include "log.h"
#include "event.h"
#include "events/client_started_event.h"
#include "events/client_stopped_event.h"
#include "events/client_tick_event.h"
#include "raylib.h"
#include "events/client_draw_event.h"

#define DEFAULT_WIN_WIDTH 1280
#define DEFAULT_WIN_HEIGHT 648

int main(int argc, char** argv) {

    /**
     * Starting client
     */
    InitWindow(DEFAULT_WIN_WIDTH, DEFAULT_WIN_HEIGHT, "iiVy");
    info("Client started!");
    event_fire(client_started_event, ((client_started_event) {.current_time_ns=time_ns()}));

    /**
     * Starting the event loop!
     */
    info("Client ticking!");
    u32 previous_tick, current_tick = time_ns(), previous_draw, current_draw = time_ns();
    while (!WindowShouldClose()) {

        /**
         * Firing the tick event
         */
        previous_tick=current_tick;
        current_tick=time_ns();
        event_fire(client_tick_event, ((client_tick_event) {.current_time_ns=current_tick, .previous_time_ns=previous_tick}));

        /**
         * And now the draw event
         */
        BeginDrawing();
        previous_draw=current_draw;
        current_draw=time_ns();
        ClearBackground(BLANK);
        event_fire(client_draw_event, ((client_draw_event) {.current_time_ns=current_draw, .previous_time_ns=previous_draw}));
        EndDrawing();
    }

    /**
     * Closing all opened buffers and destroying context since all the GL stuff is above
     */
    info("Client exiting.");
    event_fire(client_stopped_event, ((client_stopped_event) {.current_time_ns=time_ns()}));
    CloseWindow();
    return 0;
}