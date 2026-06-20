#include <raylib.h>

int screenWidth = 800;
int screenHeight = 600;
float radius = 35.5;
float circleX = 300;
float circleY = 300;
Vector2 enemy;
int main() {

  InitWindow(screenWidth, screenHeight, "woobly wabbbaly");
  SetTargetFPS(60);
  Texture2D rocketship = LoadTexture("res/cool.png");

  Rectangle source = {0, 0, rocketship.width, rocketship.height};
  Rectangle dest = {100, 100, 128, 128}; // draw at 128x1
  while (!WindowShouldClose()) {
    // Screen wrapping
    if (IsKeyDown(KEY_A))
      circleX -= 5;
    if (IsKeyDown(KEY_D))
      circleX += 5;
    if (IsKeyDown(KEY_W))
      circleY -= 5;
    if (IsKeyDown(KEY_S))
      circleY += 5;

    // Screen wrapping
    if (circleX + radius < 0)
      circleX = screenWidth + radius;

    if (circleX - radius > screenWidth)
      circleX = -radius;

    if (circleY + radius < 0)
      circleY = screenHeight + radius;

    if (circleY - radius > screenHeight)
      circleY = -radius;
    BeginDrawing();
    ClearBackground(SKYBLUE);
    DrawTexturePro(rocketship, source, dest, (Vector2){0, 0}, 0.0f, WHITE);
    // DrawCircle(circleX, circleY, radius, RED);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
