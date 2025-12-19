#include <math.h>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "../build/external/raylib-master/src/raylib.h"
#include "dataset.h"

void drawGraph(int screenWidth, int screenHeight, int gridSize, int scale, float zoom, float minX, float maxX, float minY, float maxY) {
    float thickness = fmax(1.0f, 1.0f / zoom);
    int centerX = screenWidth / 2;
    int centerY = screenHeight / 2;

    // // Draw grid lines
    // for (float i = minX; i < maxX; i += 1.0f) {
    //     DrawLineEx((Vector2){centerX + i * scale, 0}, (Vector2){centerX + i * scale, (float)screenHeight}, thickness, Fade(WHITE, 0.5f));
    // }
    // for (float i = minY; i < maxY; i += 1.0f) {
    //     DrawLineEx((Vector2){0, centerY - i * scale}, (Vector2){(float)screenWidth, centerY - i * scale}, thickness, Fade(WHITE, 0.5f));
    // }

    // Draw axes
    DrawLineEx((Vector2){centerX + minX * scale, (float)centerY}, (Vector2){centerX + maxX * scale, (float)centerY}, thickness, WHITE);
    DrawLineEx((Vector2){(float)centerX, centerY - minY * scale}, (Vector2){(float)centerX, centerY - maxY * scale}, thickness, WHITE);

    // Draw numbers on axes
    for (int i = -20; i <= 20; i++) {
        if (i == 0) continue;
        DrawText(TextFormat("%d", i), centerX + i * scale, centerY + 5, 10, WHITE);
    }
    for (int i = -20; i <= 20; i++) {
        if (i == 0) continue;
        DrawText(TextFormat("%d", i), centerX + 5, centerY - i * scale, 10, WHITE);
    }
}

void drawData(int centerX, int centerY, int scale) {
    for (auto P : Points) {
        Color c;
        switch (P.Catag) {
            case 1:
                c = GREEN;
                break;
            case -1:
                c = RED;
                break;
        }
        DrawCircle(centerX + P.x * scale, centerY - P.y * scale, 5.0f, c);
    }
}

void draw_a_line(float w1, float w2, float b, int screenWidth, int screenHeight, int centerX, int centerY, int scale, Color color, float minX, float maxX) {
    // w1*x + w2*y + b = 0
    // y = (-w1*x - b) / w2
    if (fabs(w2) > 1e-6) {
        float y1 = (-w1 * (-20.0f) - b) / w2;
        float y2 = (-w1 * (20.0f) - b) / w2;
        DrawLineEx((Vector2){centerX + (-20.0f) * scale, centerY - y1 * scale}, (Vector2){centerX + (20.0f) * scale, centerY - y2 * scale}, 2.0f, color);
    } else { // Vertical line
        float x = -b / w1;
        DrawLineEx((Vector2){centerX + x * scale, 0}, (Vector2){centerX + x * scale, (float)screenHeight}, 2.0f, color);
    }
}

void drawPlanesHandler(size_t &i) {
    if (IsKeyDown(KEY_N) && i < Planes.size() - 1) {
        i++;
    }
}

int main() {
    int screenWidth = 1920;
    int screenHeight = 1080;
    const int gridSize = 30;
    const int scale = 50;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "support vector machine");

    Camera2D camera = { 0 };
    camera.offset = (Vector2){ (float)screenWidth / 2, (float)screenHeight / 2 };
    camera.target = (Vector2){ (float)screenWidth / 2, (float)screenHeight / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 0.8f;

    SetTargetFPS(60);
    srand(time(NULL));

    size_t i = 0;

    float minX = -20.0f;
    float maxX = 20.0f;
    float minY = -20.0f;
    float maxY = 20.0f;

    while (!WindowShouldClose()) {
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();


        if (IsKeyDown(KEY_D)) {
            camera.target.x += 10;
        }
        if (IsKeyDown(KEY_A)) {
            camera.target.x -= 10;
        }
        if (IsKeyDown(KEY_S)) {
            camera.target.y += 10;
        }
        if (IsKeyDown(KEY_W)){ 
            camera.target.y -= 10;
        }
        if (IsKeyDown(KEY_UP)) {
            camera.zoom += 0.025;
        }
        if (IsKeyDown(KEY_DOWN)) {
            camera.zoom -= 0.025;
        }
        camera.zoom += ((float)GetMouseWheelMove()*0.05f);
        if (camera.zoom > 3.0f) {
            camera.zoom = 3.0f;
        }
        else if (camera.zoom < 0.1f) {
            camera.zoom = 0.1f;
        }

        drawPlanesHandler(i);

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);
        
        drawGraph(screenWidth, screenHeight, gridSize, scale, camera.zoom, minX, maxX, minY, maxY);
        drawData(screenWidth / 2, screenHeight / 2, scale);
        draw_a_line(Planes[i].w1, Planes[i].w2, Planes[i].b, screenWidth, screenHeight, screenWidth / 2, screenHeight / 2, scale, BLUE, minX, maxX);

        EndMode2D();

        DrawText(TextFormat("Epoch: %03i", i), 40, 60, 30, WHITE);
        DrawText(TextFormat("Plane: %03fx + %03fy + %03f = 0", Planes[i].w1, Planes[i].w2, Planes[i].b), 600, 60, 30, WHITE);
        DrawFPS(1600, 60);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
