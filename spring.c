#include <stdio.h>
#include <raylib.h>

#define FPS 120

#define WIDTH 900
#define HEIGHT 600
#define THICK 5
#define MASS_WIDTH 100

#define FLOOR_Y HEIGHT*0.6



void drawFloor() {
    const Vector2 start = {0, FLOOR_Y};
    const Vector2 end = {WIDTH, FLOOR_Y};
    DrawLineEx(start, end,THICK,ORANGE);
}

void drawMass(float x) {
    Rectangle rect = {x, FLOOR_Y - MASS_WIDTH - THICK / 2, MASS_WIDTH, MASS_WIDTH};
    DrawRectangleRec(rect, YELLOW);
}

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Spring on Mass Simulation");

    float x = 0;
    SetTargetFPS(FPS);
    float dt;
    float v = 20;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(10, 10);
        dt = GetFrameTime();
        drawFloor();
        x += v * dt;
        drawMass(x);
        DrawText("Spring on Mass Simulating", WIDTH / 10, 100, 30, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
