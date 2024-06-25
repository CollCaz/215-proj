#include "Mouse.hpp"
#include "Rectangle.hpp"
#include "Vector2.hpp"
#include "raylib.h"
#include <cstddef>
#include <iostream>
#include <ostream>
#include <raylib-cpp.hpp>
#include <string>
using namespace ::std;

raylib::Color textColor(LIGHTGRAY);

class Point;

Point *BeingDragged;

class Point {
  string label;
  float size;

public:
  bool output;

  bool MouseOn;
  bool Held;
  bool Draged;
  raylib::Vector2 lineFrom;
  raylib::Vector2 lineTo;
  float xpos;
  float ypos;
  float height;
  float width;

  explicit Point(bool output, float xpos, float ypos, float(size))
      : output(output), xpos(xpos), ypos(ypos), label(to_string(output)),
        size(size), height(size), width(size), Draged(false), Held(false) {}

  explicit Point() : output(false) {}

  bool Solve() { return output; }

  void Draw() {
    lineFrom = raylib::Vector2(this->xpos, this->ypos);
    lineFrom.DrawLine(lineTo, 4, textColor);
    textColor.DrawText(this->label, xpos, ypos, 20);
  }

  void DragToConnect() {
    if (this->Draged) {
      this->lineTo = raylib::Mouse::GetPosition();
      BeingDragged = this;
    }
  }

  void SetPosition(float x, float y) {
    this->xpos = x - 20;
    this->ypos = y - 20;
    cout << this->ypos << endl;
    cout << ypos << endl;
  }

  void Move() {
    if (Held) {
      Vector2 mousePos = raylib::Mouse::GetPosition();
      SetPosition(mousePos.x, mousePos.y);
    }
  }

  void CheckMouse() {
    Vector2 mousePos = raylib::Mouse::GetPosition();
    if (mousePos.x >= this->xpos && mousePos.x <= this->xpos + this->width &&
        mousePos.y >= this->ypos && mousePos.y <= this->ypos + this->height) {
      this->MouseOn = true;
    } else {
      this->MouseOn = false;
    }
  }

  void HoldAndDrag() {
    if (!MouseOn) {
      return;
    }

    if (raylib::Mouse::IsButtonPressed(0)) {
      this->Held = true;
    } else if (raylib::Mouse::IsButtonPressed(1)) {
      this->Draged = true;
    }

    if (raylib::Mouse::IsButtonUp(0)) {
      this->Held = false;
    }

    if (raylib::Mouse::IsButtonUp(1)) {
      this->Draged = false;
      BeingDragged = nullptr;
    }
  }

  void Cycle() {
    CheckMouse();
    HoldAndDrag();
    DragToConnect();
    Draw();
    Move();
  }
};

class Gate : public Point {
  bool inputs[2];

  raylib::Rectangle rec;

public:
  raylib::Vector2 connectPos1;
  raylib::Vector2 connectPos2;
  bool connected1;

  Gate(Point *a, Point *b) {
    Vector2 mousePos = GetMousePosition();
    this->xpos = mousePos.x;
    this->ypos = mousePos.y;
    this->width = 50;
    this->height = 50;
    this->inputs[0] = a->output;
    this->inputs[1] = b->output;
  }

  void Connect() {
    if (BeingDragged != nullptr && this->MouseOn) {
      cout << "AA" << endl;
      BeingDragged->lineTo =
          this->connected1 ? this->connectPos1 : this->connectPos2;
      this->connected1 = true;
      BeingDragged->Draged = false;
    }
  }

  void Draw() {
    rec.SetSize(this->height, this->width);
    rec.SetPosition(this->xpos, this->ypos);
    rec.Draw(textColor);
  }

  void Cycle() {
    CheckMouse();
    HoldAndDrag();
    DragToConnect();
    Connect();
    Move();

    this->connectPos1 = raylib::Vector2(this->xpos, this->ypos + 10);
    this->connectPos2 = raylib::Vector2(this->xpos, this->ypos + 40);

    Draw();
  }
};

int main() {

  // Initialization
  int screenWidth = 800;
  int screenHeight = 450;
  int b = 3;
  Point pa = Point(true, 100, 200, 20);
  Point pb = Point(false, 100, 225, 20);
  Gate g = Gate(&pa, &pb);

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
    if (BeingDragged != nullptr) {
      cout << BeingDragged->MouseOn;
    }

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);
    // textColor.DrawText("Congrats! You created your first window!", 190, 200,
    //                    20);
    EndDrawing();
  }

  return 0;
}
