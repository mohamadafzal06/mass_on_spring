#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define FPS 120

#define WIDTH 900
#define HEIGHT 600
#define THICK 5
#define MASS_WIDTH 100

#define FLOOR_Y (HEIGHT*0.6)

#define NUM_SPRING_ELEMENTS 16
#define SPRING_ELEMENT_LENGTH 60
#define K 20
#define X_REST (WIDTH/3)
#define FRICTION 0.5

float x_mass = WIDTH*0.7;
float v = 20;
float a = 2;

typedef struct SpringElement {
    Vector2 start, end;
} SpringElement;

SpringElement spring_elements[SPRING_ELEMENT_LENGTH];

void updateSpring() {
}

void drawSpring() {
    float x_spring_delta = x_mass / NUM_SPRING_ELEMENTS;
    float y_end = (float) sqrt(pow(SPRING_ELEMENT_LENGTH, 2) - pow(x_spring_delta, 2));

    for (int i = 0; i < NUM_SPRING_ELEMENTS; i += 2) {
        Vector2 start = {
            x_spring_delta * (float) i, FLOOR_Y - (float) MASS_WIDTH / 2 + (float) SPRING_ELEMENT_LENGTH / 2
        };
        Vector2 end = {start.x + x_spring_delta, start.y - y_end};
        spring_elements[i] = (SpringElement){start, end};
        DrawLineEx(start, end, THICK, WHITE);
    }

    for (int i = 1; i < NUM_SPRING_ELEMENTS; i += 2) {
        Vector2 start = spring_elements[i - 1].end;
        Vector2 end = {start.x + x_spring_delta, start.y + y_end};
        spring_elements[i - 1] = (SpringElement){start, end};
        DrawLineEx(start, end, THICK, WHITE);
    }
}


void drawFloor() {
    const Vector2 start = {0, FLOOR_Y};
    const Vector2 end = {WIDTH, FLOOR_Y};
    DrawLineEx(start, end,THICK,ORANGE);
}

void drawMass() {
    Rectangle rect = {x_mass, FLOOR_Y - MASS_WIDTH - THICK / 2, MASS_WIDTH, MASS_WIDTH};
    DrawRectangleRec(rect, YELLOW);
}

int main(void) {
    printf("Mass on Spring, Here we go!\n");
    InitWindow(WIDTH, HEIGHT, "Spring on Mass Simulation");

    SetTargetFPS(FPS);
    float dt;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(10, 10);
        dt = GetFrameTime();
        drawFloor();
        float friction = a > 0 ? FRICTION : -FRICTION;
        a = -K * (x_mass-X_REST) - v*FRICTION;
        v += a * dt;
        x_mass += v * dt;
        drawMass(x_mass);
        drawSpring();
        DrawText("Mass on Spring Simulation", WIDTH / 10, 100, 30, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
