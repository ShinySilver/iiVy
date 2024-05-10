#include <memory.h>
#include <stdint.h>
#include "event.h"
#include "events/client_tick_event.h"
#include "events/client_started_event.h"
#include "player.h"
#include "raylib.h"

#define PLAYER_WALK_SPEED (1000)

event_subscribe(client_started_event){
    memset(&Player, 0, sizeof(Player));
    Player.x = INT16_MAX; // Can't be bothered to handle parallax around 0.
}

event_subscribe(client_tick_event){
    u32 delta_ns = event->current_time_ns-event->previous_time_ns;
    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)){
        if(!IsKeyDown(KEY_D) && !IsKeyDown(KEY_RIGHT)){
            Player.x+=delta_ns*1e-9*PLAYER_WALK_SPEED;
        }
    }else if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)){
        Player.x-=delta_ns*1e-9*PLAYER_WALK_SPEED;
    }
}