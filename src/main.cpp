#include "Gates.hpp"
#include "Globals.hpp"
#include "Input.hpp"
#include "raylib.h"

using namespace std;

static void DrawStyleEditControls(void);

int main() {

  // Initialization
  int screenWidth = 800;
  int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Raylib C++ Starter Kit Example");

  SetTargetFPS(120);

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update

    // TODO: Update your variables here

    AddGatesAndPoints();

    for (int i = 0; i < Objects.size(); i++) {
      Objects.at(i)->Update();
    }

    if (DraggingConnection && IsMouseButtonReleased(1)) {
      DraggingConnection = false;
    }

    // Draw
    for (int i = 0; i < Objects.size(); i++) {
      Objects.at(i)->Draw();
    }

    DrawFPS(20, 20);
    BeginDrawing();
    ClearBackground(RAYWHITE);
    // DrawText("Congrats! You created your first window!", 190, 200, 20,
    // LIGHTGRAY);
    EndDrawing();
  }

  return 0;
}
