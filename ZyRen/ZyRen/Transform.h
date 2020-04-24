#pragma once

#include "Geometry.h"


Vec3f world2screen(Vec3f v, int height, int width);
Vec3f perspective(Vec3f v, Vec3f camera);
