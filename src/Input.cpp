#include "Input.hpp"
#include "raylib.h"
#include <iostream>

using namespace std;

void AddGatesAndPoints() {
  int keyPressed = GetKeyPressed();
  switch (keyPressed) {
  case KEY_ONE:
    cout << "One" << endl;
    break;
  case KEY_TWO:
    cout << "Two" << endl;
    break;
  }
}
