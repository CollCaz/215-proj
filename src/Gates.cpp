#include "Gates.hpp"
#include "Globals.hpp"
#include <iostream>
#include <raylib-cpp.hpp>
#include <string>

using namespace std;

Point::Point(bool output, float xpos, float ypos, float(size))
    : output(output), xpos(xpos), ypos(ypos), label(to_string(output)),
      size(size), height(size), width(size), Draged(false), Held(false),
      MouseOn(false), ConectedTo(nullptr) {}

Point::Point() : output(false), ConectedTo(nullptr) {}

bool Point::Solve() { return output; }

void Point::Draw() {
  lineFrom = raylib::Vector2(this->xpos, this->ypos);
  lineFrom.DrawLine(lineTo, 4, color);
  color.DrawText(this->label, xpos, ypos, 20);
}

void Point::SetLineTo(raylib::Vector2 to) { this->lineTo = to; }
void Point::SetDragged(bool d) { this->Draged = d; }

void Point::DragToConnect() {
  if (this->Draged && this->ConectedTo) {
    this->ConectedTo->RemoveConnection(this);
    this->ConectedTo = nullptr;
  }
  if (this->Draged && DraggingConnection) {
    this->lineTo = raylib::Mouse::GetPosition();
    BeingDragged = this;
  } else if (BeingDragged == this) {
    BeingDragged = nullptr;
  }
}

void Point::SetConnectedTo(Gate *g) { this->ConectedTo = g; }

void Point::SetPosition(float x, float y) {
  this->xpos = x - 20;
  this->ypos = y - 20;
}

void Point::OffsetPosition(raylib::Vector2 off) {
  this->xpos += off.x;
  this->ypos += off.y;
}

void Point::OffsetLineTo(raylib::Vector2 off) {
  this->lineTo.x += off.x;
  this->lineTo.y += off.y;
}

void Point::Move() {
  if (Held) {
    Vector2 mousePos = raylib::Mouse::GetPosition();
    OffsetPosition(raylib::Mouse::GetDelta());
  }
}

void Point::CheckMouse() {
  Vector2 mousePos = raylib::Mouse::GetPosition();
  if (mousePos.x >= this->xpos && mousePos.x <= this->xpos + this->width &&
      mousePos.y >= this->ypos && mousePos.y <= this->ypos + this->height) {
    this->MouseOn = true;
  } else {
    this->MouseOn = false;
  }
}

void Point::HoldAndDrag() {
  if (raylib::Mouse::IsButtonUp(0)) {
    this->Held = false;
  }

  if (raylib::Mouse::IsButtonUp(1)) {
    this->Draged = false;
    if (!this->ConectedTo) {
      SetLineTo(raylib::Vector2(this->xpos, this->ypos));
    }
    DraggingConnection = false;
    BeingDragged = nullptr;
  }

  // Releaseing
  if (!this->MouseOn) {
    return;
  }

  if (raylib::Mouse::IsButtonPressed(0)) {
    this->Held = true;
  }
  if (raylib::Mouse::IsButtonPressed(1)) {
    this->Draged = true;
    BeingDragged = this;
    DraggingConnection = true;
  }
};

Gate::Gate(Point *a, Point *b) {
  Vector2 mousePos = GetMousePosition();
  this->xpos = mousePos.x;
  this->ypos = mousePos.y;
  this->width = 50;
  this->height = 50;
  this->MouseOn = false;
  this->Draged = false;
  this->Held = false;
  this->inputs[0] = a->output;
  this->inputs[1] = b->output;
  this->connection1 = nullptr;
  this->connection2 = nullptr;
}

void Gate::Connect() {
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
    Vector2 mouseDelta = raylib::Mouse::GetDelta();
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
  lineFrom = raylib::Vector2(this->xpos + this->width,
                             this->ypos + (this->height / 2.0));
  lineFrom.DrawLine(lineTo, 4, color);
  rec.SetSize(this->height, this->width);
  rec.SetPosition(this->xpos, this->ypos);
  rec.Draw(color);
}

void Gate::Cycle() {
  this->connectPos1 = raylib::Vector2(this->xpos, this->ypos + 10);
  this->connectPos2 = raylib::Vector2(this->xpos, this->ypos + 40);
  CheckMouse();
  HoldAndDrag();
  DragToConnect();
  Connect();
  Move();

  Draw();
};
