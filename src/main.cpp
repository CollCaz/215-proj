#include "Gates.hpp"
#include "Globals.hpp"
#include <raylib-cpp.hpp>
#include <string>

using namespace ::std;

int main() {

  // Initialization
  int screenWidth = 800;
  int screenHeight = 450;
  int b = 3;
  Point pa = Point(true, 100, 200, 20);
  Point pb = Point(false, 100, 225, 20);
  Gate g = Gate(&pa, &pb);
  Gate g2 = Gate(&pa, &pb);
  g2.SetPosition(40, 20);

  raylib::Window w(screenWidth, screenHeight, "Raylib C++ Starter Kit Example");

  SetTargetFPS(60);

  // Main game loop
  while (!w.ShouldClose()) // Detect window close button or ESC key
  {
    // Update

    // TODO: Update your variables here
    pa.Cycle();
    pb.Cycle();
    g.Cycle();
    g2.Cycle();

    if (DraggingConnection && raylib::Mouse::IsButtonReleased(1)) {
      DraggingConnection = false;
    }

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);
    // color.DrawText("Congrats! You created your first window!", 190, 200,
    //                    20);
    EndDrawing();
  }

  return 0;
}
