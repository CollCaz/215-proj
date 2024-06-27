#include "Globals.hpp"
#include "raylib.h"

raylib::Color color = raylib::Color(LIGHTGRAY);
Point* BeingDragged = nullptr;
bool DraggingConnection = false;
