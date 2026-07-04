#include <raylib.h>

#include <stdbool.h>

#define screenWidth 800
#define screenHeight 650
#define MAX_BULLETS 10
#define MAX_ENEMIES 10

typedef struct {
  Vector2 position;
  Vector2 speed;
  bool active;
} Bullet;

typedef struct {
  Vector2 position;
  Vector2 speed;
  bool alive;
} Enemy;

int main() {

  InitWindow(screenWidth, screenHeight, "woobly waablly");
  SetTargetFPS(60);

  Texture2D rocketship = LoadTexture("res/rocket.png");
  if (rocketship.id == 0) {
    CloseWindow();
    return 1;
  }

  Rectangle source = {0, 0, (float)rocketship.width, (float)rocketship.height};
  Rectangle dest = {100, 100, 128, 128};

  // Bullet variables
  Bullet bullets[MAX_BULLETS] = {0};
  float bulletSpeedY = -8.0f;
  int bulletWidth = 5;
  int bulletHeight = 15;

  // Enemy variables
  Enemy enemies[MAX_ENEMIES] = {0};
  float enemyWidth = 20;
  float enemHeight = 20;
  float spawnTimer = 0.0f;
  float spawnTime = 1.5f;

  while (!WindowShouldClose()) {
    spawnTimer += GetFrameTime();
    if (IsKeyDown(KEY_A))
      dest.x -= 5;
    if (IsKeyDown(KEY_D))
      dest.x += 5;
    if (IsKeyDown(KEY_W))
      dest.y -= 5;
    if (IsKeyDown(KEY_S))
      dest.y += 5;

    if (dest.x + dest.width < 0)
      dest.x = screenWidth;
    if (dest.x > screenWidth)
      dest.x = -dest.width;
    if (dest.y + dest.height < 0)
      dest.y = screenHeight;
    if (dest.y > screenHeight)
      dest.y = -dest.height;

    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) {
      for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) {
          bullets[i].position.x =
              dest.x + (dest.width / 2) - (bulletWidth / 2.0f);
          bullets[i].position.y = dest.y;
          bullets[i].speed.y = bulletSpeedY;
          bullets[i].active = true;
          break;
        }
      }
    }

    if (spawnTimer > spawnTime) {
      for (int e = 0; e < MAX_ENEMIES; e++) {
        if (!enemies[e].alive) {
          enemies[e].position.x =
              GetRandomValue(0, screenWidth - (int)enemyWidth);
          enemies[e].position.y = -40;
          enemies[e].alive = true;
          spawnTimer = 0.0f;
          break;
        }
      }
    }

    for (int i = 0; i < MAX_BULLETS; i++) {
      if (bullets[i].active) {
        bullets[i].position.y += bullets[i].speed.y;

        if (bullets[i].position.y < 0) {
          bullets[i].active = false;
        }
      }
    }

    for (int i = 0; i < MAX_ENEMIES; i++) {
      if (enemies[i].alive) {
        enemies[i].position.y += 4;
        if (enemies[i].position.y > screenHeight) {
          enemies[i].alive = false;
        }
      }
    }

    BeginDrawing();
    ClearBackground(DARKBLUE);

    for (int i = 0; i < MAX_BULLETS; i++) {
      if (bullets[i].active) {
        DrawRectangle(bullets[i].position.x, bullets[i].position.y, bulletWidth,
                      bulletHeight, YELLOW);
      }
    }

    for (int i = 0; i < MAX_ENEMIES; i++) {
      if (enemies[i].alive) {
        DrawCircle(enemies[i].position.x, enemies[i].position.y, enemyWidth / 2,
                   RED);
      }
    }

    DrawTexturePro(rocketship, source, dest, (Vector2){0, 0}, 0.0f, WHITE);

    EndDrawing();
  }
  UnloadTexture(rocketship);
  CloseWindow();

  return 0;
}
