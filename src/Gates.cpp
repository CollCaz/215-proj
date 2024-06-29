#include "Gates.hpp"
#include "Globals.hpp"
#include <raylib.h>
#include <string>

#include <iostream>

using namespace std;

Point::Point() {
  Vector2 mousePos = GetMousePosition();
  this->xpos = mousePos.x;
  this->ypos = mousePos.y;
  this->label = to_string(output);
  this->size = 20;
  this->height = 20;
  this->width = 20;
  this->Draged = false;
  this->Held = false;
  this->MouseOn = false;
  this->ConectedTo = nullptr;
}

void Point::SetOutput(bool o) {
  this->output = o;
  this->label = to_string(this->output);
}

bool Point::Solve() { return output; }

void Point::Draw() {
  lineFrom = Vector2{this->xpos, this->ypos};
  DrawLineEx(lineFrom, lineTo, 2, color);
  DrawText(this->label.c_str(), xpos, ypos, 20, color);
}

void Point::SetLineTo(Vector2 to) { this->lineTo = to; }
void Point::SetDragged(bool d) { this->Draged = d; }

void Point::DragToConnect() {
  if (this->Draged && this->ConectedTo) {
    this->ConectedTo->RemoveConnection(this);
    this->ConectedTo = nullptr;
  }
  if (this->Draged && DraggingConnection) {
    this->lineTo = GetMousePosition();
    BeingDragged = this;
  } else if (BeingDragged == this) {
    BeingDragged = nullptr;
  }
}

void Point::SetConnectedTo(Gate *g) { this->ConectedTo = g; }

void Point::SetPosition(Vector2 v) {
  this->xpos = v.x - 20;
  this->ypos = v.y - 20;
}

void Point::OffsetPosition(Vector2 off) {
  this->xpos += off.x;
  this->ypos += off.y;
}

void Point::OffsetLineTo(Vector2 off) {
  this->lineTo.x += off.x;
  this->lineTo.y += off.y;
}

void Point::Move() {
  if (Held) {
    OffsetPosition(GetMouseDelta());
  }
}

void Point::CheckMouse() {
  Vector2 mousePos = GetMousePosition();
  if (mousePos.x >= this->xpos && mousePos.x <= this->xpos + this->width &&
      mousePos.y >= this->ypos && mousePos.y <= this->ypos + this->height) {
    this->MouseOn = true;
  } else {
    this->MouseOn = false;
  }
}

void Point::HoldAndDrag() {
  if (IsMouseButtonUp(0)) {
    this->Held = false;
  }

  if (IsMouseButtonUp(1)) {
    this->Draged = false;
    if (!this->ConectedTo) {
      SetLineTo(Vector2{this->xpos, this->ypos});
    }
    DraggingConnection = false;
    BeingDragged = nullptr;
  }

  // Releaseing
  if (!this->MouseOn) {
    return;
  }

  if (IsMouseButtonPressed(0)) {
    this->Held = true;
  }
  if (IsMouseButtonPressed(1)) {
    this->Draged = true;
    BeingDragged = this;
    DraggingConnection = true;
  }
};

Gate::Gate() {
  Vector2 mousePos = GetMousePosition();
  this->xpos = mousePos.x;
  this->ypos = mousePos.y;
  this->width = 50;
  this->height = 50;
  this->MouseOn = false;
  this->Draged = false;
  this->Held = false;
  this->connection1 = nullptr;
  this->connection2 = nullptr;
}

void Gate::ConnectToThis() {
  if (BeingDragged == this) {
    return;
  }

  if (BeingDragged != nullptr && this->MouseOn) {
    BeingDragged->SetLineTo((this->connection1) ? this->connectPos2
                                                : this->connectPos1);
    BeingDragged->SetConnectedTo(this);
    BeingDragged->SetDragged(false);
    if (!this->connection1) {
      this->connection1 = BeingDragged;
    } else {
      this->connection2 = BeingDragged;
    }
  }
}

void Gate::RemoveConnection(Point *p) {
  if (this->connection1 == p) {
    this->connection1 = nullptr;
  } else if (this->connection2 == p) {
    this->connection2 = nullptr;
  }
}

void Gate::Move() {
  if (Held) {
    Vector2 mouseDelta = GetMouseDelta();
    OffsetPosition(mouseDelta);
    if (this->connection1) {
      this->connection1->OffsetLineTo(mouseDelta);
    }
    if (this->connection2) {
      this->connection2->OffsetLineTo(mouseDelta);
    }
  }
}

void Gate::Draw() {
  lineFrom = Vector2{this->xpos + this->width, this->ypos + (this->height / 2)};
  DrawLineEx(this->lineFrom, this->lineTo, 4, color);
  rec.height = this->height;
  rec.width = this->width;
  rec.x = this->xpos;
  rec.y = this->ypos;
  DrawRectangleRec(rec, color);
}

string Gate::Print() { return "Gate"; }

void Gate::Update() {
  this->connectPos1 = Vector2{this->xpos, this->ypos + 10};
  this->connectPos2 = Vector2{this->xpos, this->ypos + 40};
  CheckMouse();
  HoldAndDrag();
  DragToConnect();
  ConnectToThis();
  Move();
};

// And Gate

bool AndGate::Solve() {
  bool solution = this->connection1->output && this->connection2->output;
  cout << solution << endl;
  return solution;
}
