#pragma once

#include "Geometry.h"


// Vector * Vector
float dot(Vec4f a, Vec4f b);
float dot(Vec3f a, Vec3f b);
Vec4f cross(Vec4f a, Vec4f b);
Vec3f cross(Vec3f a, Vec3f b);

// Vector + Vector
Vec4f add(Vec4f a, Vec4f b);

// Vector - Vector
Vec4f sub(Vec4f a, Vec4f b);
Vec3f sub(Vec3f a, Vec3f b);

// Matrix x Vector
Vec4f mult(Mat4x4 m, Vec4f v);

// Matrix x Matrix
Mat4x4 mult(Mat4x4 m1, Mat4x4 m2);

// Normalize Vector
Vec3f normalize(Vec3f v);