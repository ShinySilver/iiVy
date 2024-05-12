

#include "event.h"
#include "events/client_started_event.h"
#include "physac.h"

#define TERRAIN_WIDTH 2000
#define TERRAIN_HEIGHT 680

event_subscribe(client_started_event){
    PhysicsBody floor = CreatePhysicsBodyRectangle((Vector2){ TERRAIN_WIDTH/2, TERRAIN_HEIGHT }, TERRAIN_WIDTH, 100, 10);
    PhysicsBody platformLeft = CreatePhysicsBodyRectangle((Vector2){ TERRAIN_WIDTH*0.25f, TERRAIN_HEIGHT*0.6f }, TERRAIN_WIDTH*0.25f, 10, 10);
    PhysicsBody platformRight = CreatePhysicsBodyRectangle((Vector2){ TERRAIN_WIDTH*0.75f, TERRAIN_HEIGHT*0.6f }, TERRAIN_WIDTH*0.25f, 10, 10);
    PhysicsBody wallLeft = CreatePhysicsBodyRectangle((Vector2){ -5, TERRAIN_HEIGHT/2 }, 10, TERRAIN_HEIGHT, 10);
    PhysicsBody wallRight = CreatePhysicsBodyRectangle((Vector2){ TERRAIN_WIDTH + 5, TERRAIN_HEIGHT/2 }, 10, TERRAIN_HEIGHT, 10);

    floor->enabled=false;
    platformLeft->enabled=false;
    platformRight->enabled=false;
    wallLeft->enabled=false;
    wallRight->enabled=false;
}