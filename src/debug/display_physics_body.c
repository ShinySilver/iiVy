#include "event.h"
#include "physac.h"
#include "events/client_draw_event.h"
#include "entities/player.h"

/**
 * Displays outlines around physics body
 * Credit goes to https://github.com/victorfisac/Physac/blob/master/examples/physics_movement.c
 */
event_subscribe(client_draw_event){
    int bodiesCount = GetPhysicsBodiesCount();
    for (int i = 0; i < bodiesCount; i++){
        PhysicsBody body = GetPhysicsBody(i);
        int vertexCount = GetPhysicsShapeVerticesCount(i);
        for (int j = 0; j < vertexCount; j++){
            // Get physics bodies shape vertices to draw lines
            // Note: GetPhysicsShapeVertex() already calculates rotation transformations
            Vector2 vertexA = GetPhysicsShapeVertex(body, j);
            vertexA.x-=Player.body->position.x-GetScreenWidth()/2;
            int jj = (((j + 1) < vertexCount) ? (j + 1) : 0);   // Get next vertex or first to close the shape
            Vector2 vertexB = GetPhysicsShapeVertex(body, jj);
            vertexB.x-=Player.body->position.x-GetScreenWidth()/2;
            DrawLineV(vertexA, vertexB, BLACK);     // Draw a line between two vertex positions
        }
    }
}