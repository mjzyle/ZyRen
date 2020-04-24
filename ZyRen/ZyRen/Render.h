#pragma once

#include "Render.h"
#include "Geometry.h"
#include "tgaimage.h"
#include "Mesh.h"
#include "Algebra.h"
#include "Transform.h"

using namespace std;


Vec3f barycentric(Vec3f* points, Vec3f p);
void triangle(Vec3f* points, float* zbuffer, TGAImage& image, Vec2f* tex, float intensity, Mesh m, int height, int width, TGAImage& texture);