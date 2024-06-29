#include "Globals.hpp"
#include "Gates.hpp"
#include "raylib.h"
#include <vector>

Color color = LIGHTGRAY;
Point *BeingDragged = nullptr;
bool DraggingConnection = false;

vector<Point *> Objects = vector<Point *>();
vector<Gate *> Gates = vector<Gate *>();
