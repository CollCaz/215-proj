#include "Input.hpp"
#include "Gates.hpp"
#include "Globals.hpp"

#include "raylib.h"

using namespace std;

void AddGatesAndPoints() {
  int keyPressed = GetKeyPressed();
  switch (keyPressed) {
  case KEY_ZERO: {
    Point *p = new Point;
    p->SetOutput(false);
    Objects.back()->SetOutput(false);
  }
  case KEY_ONE: {
    Point *p = new Point;
    p->SetOutput(true);
    Objects.push_back(p);
  } break;
  case KEY_TWO: {
    Gate *g = new AndGate;
    Objects.push_back(g);
    Gates.push_back(g);
  } break;
  }
}
