#include <raylib.h>

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "Moving Texture");
  SetTargetFPS(60);

  Texture2D rocketship = LoadTexture("res/rocket.png");

  Rectangle source = {0, 0, (float)rocketship.width, (float)rocketship.height};

  Rectangle dest = {100, 100, 128, 128};
  if (rocketship.id == 0) {
    CloseWindow();
  }
  while (!WindowShouldClose()) {
    // Movement
    if (IsKeyDown(KEY_A))
      dest.x -= 5;

    if (IsKeyDown(KEY_D))
      dest.x += 5;

    if (IsKeyDown(KEY_W))
      dest.y -= 5;

    if (IsKeyDown(KEY_S))
      dest.y += 5;

    // Screen wrapping
    if (dest.x + dest.width < 0)
      dest.x = screenWidth;

    if (dest.x > screenWidth)
      dest.x = -dest.width;

    if (dest.y + dest.height < 0)
      dest.y = screenHeight;

    if (dest.y > screenHeight)
      dest.y = -dest.height;

    BeginDrawing();
    ClearBackground(SKYBLUE);

    DrawTexturePro(rocketship, source, dest, (Vector2){0, 0}, 0.0f, WHITE);

    EndDrawing();
  }

  UnloadTexture(rocketship);
  CloseWindow();

  return 0;
}

// void quit() {
//   UnloadTexture(rocketship);
//   CloseWindow();
// }
