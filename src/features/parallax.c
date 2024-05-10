#include "event.h"
#include "events/client_draw_event.h"
#include "events/client_started_event.h"
#include "raylib.h"
#include "player.h"

#define PARALLAX_NAME "nature_1"
#define CLOUD_SPEED (10)
#define LAYER_2_SPEED (0.05)
#define LAYER_3_SPEED (0.25)
#define LAYER_4_SPEED (0.5)
#define SCALE (2)

Texture2D t1, t2, t3, t4;
float wind;

event_subscribe(client_started_event){
    t1 = LoadTexture("resources/textures/parallax/" PARALLAX_NAME "/1.png");
    t2 = LoadTexture("resources/textures/parallax/" PARALLAX_NAME "/2.png");
    t3 = LoadTexture("resources/textures/parallax/" PARALLAX_NAME "/3.png");
    t4 = LoadTexture("resources/textures/parallax/" PARALLAX_NAME "/4.png");
}

event_subscribe(client_draw_event){
    /**
     * Have the clouds move with the wind
     */
    u32 delta_ns = event->current_time_ns-event->previous_time_ns;
    wind += delta_ns * 1e-9 * CLOUD_SPEED;

    /**
     * Draw the textures depending on the player pos
     * player moves right, the texture move slightly left. If the image is a bit too left, teleport it to the right (2*width)
     */
    // texture 1 - unmoving
    DrawTextureEx(t1, (Vector2){0, 0 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(t1, (Vector2){t1.width*SCALE, 0 }, 0.0f, 2.0f, WHITE);

    // texture 2 - affected by the wind!
    int tmp = (int)mod(Player.x*LAYER_2_SPEED+wind, t2.width*SCALE);
    DrawTextureEx(t2, (Vector2){tmp, 0 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(t2, (Vector2){ tmp-t2.width*SCALE, 0 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(t2, (Vector2){ tmp+t2.width*SCALE, 0 }, 0.0f, 2.0f, WHITE);

    // texture 3
    tmp = (int)mod(Player.x*LAYER_3_SPEED, t3.width*SCALE);
    DrawTextureEx(t3, (Vector2){tmp, 0 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(t3, (Vector2){ tmp-t3.width*SCALE, 0 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(t3, (Vector2){ tmp+t3.width*SCALE, 0 }, 0.0f, 2.0f, WHITE);

    // texture 4
    tmp = (int)mod(Player.x*LAYER_4_SPEED, t4.width*SCALE);
    DrawTextureEx(t4, (Vector2){tmp, 0 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(t4, (Vector2){ tmp-t4.width*SCALE, 0 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(t4, (Vector2){ tmp+t4.width*SCALE, 0 }, 0.0f, 2.0f, WHITE);
}