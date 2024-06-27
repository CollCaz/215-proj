#pragma once

#include "Vector2.hpp"
#include <raylib-cpp.hpp>
#include <string>

using namespace std;

class Gate;
class Point {
private:
  string label;
  float size;

protected:
  bool Draged;
  raylib::Vector2 lineFrom;
  raylib::Vector2 lineTo;
  Gate *ConectedTo;
  bool MouseOn;
  bool Held;
  float xpos;
  float ypos;
  float height;
  float width;

public:
  bool output;

  explicit Point(bool output, float xpos, float ypos, float(size));

  explicit Point();

  bool Solve();

  void Draw();

  void SetLineTo(raylib::Vector2 to);
  void SetDragged(bool d);

  void DragToConnect();

  void SetPosition(float x, float y);
  void SetConnectedTo(Gate *g);

  void OffsetPosition(raylib::Vector2 off);

  void OffsetLineTo(raylib::Vector2 off);

  void Move();

  void CheckMouse();

  void HoldAndDrag();

  void Cycle() {
    CheckMouse();
    Move();
    HoldAndDrag();
    DragToConnect();
    Draw();
  }
};

class Gate : public Point {
  bool inputs[2];
  bool output;

protected:
  raylib::Rectangle rec;
  raylib::Vector2 connectPos1;
  raylib::Vector2 connectPos2;
  Point *connection1;
  Point *connection2;

public:
  Gate(Point *a, Point *b);

  void Connect();

  void RemoveConnection(Point *p);

  void Move();

  void Draw();

  void Cycle();
};
