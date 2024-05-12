#include <memory.h>
#include "event.h"
#include "events/client_tick_event.h"
#include "events/client_started_event.h"
#include "player.h"
#include "raylib.h"
#include "events/client_draw_event.h"

#define PLAYER_WALK_VELOCITY (1)
#define PLAYER_JUMP_VELOCITY (2.5)
#define PLAYER_SPAWN_X (0)
#define PLAYER_SPAWN_Y (0)
#define PLAYER_WIDTH (50)
#define PLAYER_HEIGHT (100)

event_subscribe(client_started_event) {
    memset(&Player, 0, sizeof(Player));
    Player.body = CreatePhysicsBodyRectangle((Vector2) {PLAYER_SPAWN_X, PLAYER_SPAWN_Y},
                                             PLAYER_WIDTH, PLAYER_HEIGHT, 1);
    Player.body->freezeOrient = true;
}

event_subscribe(client_tick_event) {
    static Vector2 previous_position;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        if (!IsKeyDown(KEY_D) && !IsKeyDown(KEY_RIGHT)) {
            Player.body->velocity.x = -PLAYER_WALK_VELOCITY;
        }
    } else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        Player.body->velocity.x = PLAYER_WALK_VELOCITY;
    }
    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_W)) &&
        Player.body->velocity.y - 0.008175<1e-6 && Player.body->velocity.y > 0.008175) {
        info("body velocity: %f, delta: %f", Player.body->velocity.y, Player.body->position.y - previous_position.y);
        Player.body->velocity.y = -PLAYER_JUMP_VELOCITY;
    }
    previous_position = Player.body->position;
}

event_subscribe(client_draw_event) {
    DrawRectangle(GetScreenWidth() / 2 - PLAYER_WIDTH / 2,
                  (int) Player.body->position.y - PLAYER_HEIGHT / 2,
                  PLAYER_WIDTH,
                  PLAYER_HEIGHT,
                  BLACK);
}