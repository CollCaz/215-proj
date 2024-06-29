#pragma once

#include <string>

#include <raylib.h>

using namespace std;

class Gate;
class Point {
private:
  float size;

protected:
  string label;
  bool Draged;
  Vector2 lineFrom;
  Vector2 lineTo;
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

  bool virtual Solve();

  void virtual Draw();

  void SetLineTo(Vector2 to);
  void SetDragged(bool d);

  void DragToConnect();

  void SetPosition(float x, float y);
  void SetConnectedTo(Gate *g);

  void OffsetPosition(Vector2 off);

  void OffsetLineTo(Vector2 off);

  void Move();

  void CheckMouse();

  void HoldAndDrag();

  void virtual Update() {
    CheckMouse();
    Move();
    HoldAndDrag();
    DragToConnect();
  }
};

class Gate : public Point {
  bool inputs[2];
  bool output;

protected:
  Rectangle rec;
  Vector2 connectPos1;
  Vector2 connectPos2;
  Point *connection1;
  Point *connection2;

public:
  Gate(Point *a, Point *b);

  void ConnectToThis();

  void RemoveConnection(Point *p);

  void Move();

  void Draw() override;

  string Print();

  void Update() override;
};
