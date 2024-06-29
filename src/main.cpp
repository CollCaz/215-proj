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
  int b = 3;
  Point pa = Point(true, 100, 200, 20);
  Objects.push_back(&pa);

  Point pb = Point(false, 100, 225, 20);
  Objects.push_back(&pb);

  Gate g = Gate(&pa, &pb);
  Objects.push_back(&g);
  Gates.push_back(&g);

  Gate g2 = Gate(&pa, &pb);
  g2.SetPosition(40, 20);
  Objects.push_back(&g2);
  Gates.push_back(&g2);

  InitWindow(screenWidth, screenHeight, "Raylib C++ Starter Kit Example");

  SetTargetFPS(120);

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update

    // TODO: Update your variables here
    for (int i = 0; i < Objects.size(); i++) {
      Objects.at(i)->Update();
    }

    if (DraggingConnection && IsMouseButtonReleased(1)) {
      DraggingConnection = false;
    }

    AddGatesAndPoints();

    // Draw
    for (int i = 0; i < Objects.size(); i++) {
      Objects.at(i)->Draw();
    }

    DrawFPS(20, 20);
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Congrats! You created your first window!", 190, 200, 20,
             LIGHTGRAY);
    EndDrawing();
  }

  return 0;
}
