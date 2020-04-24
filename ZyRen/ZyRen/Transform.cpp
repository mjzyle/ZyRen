#include "Transform.h"
#include "Geometry.h"
#include "Algebra.h"

using namespace std;


// Convert world coordinates to screen coordinates
Vec3f world2screen(Vec3f v, int height, int width) {
	return Vec3f(int((v.x + 1.0) * width / 2.0 + 0.5), int((v.y + 1.0) * height / 2.0 + 0.5), v.z);
}


// Apply a perspective transformation to a point
Vec3f perspective(Vec3f v, Vec3f camera) {
	Vec4f vh = Vec4f(v.x, v.y, v.z, 1.0f);
	Mat4x4 m = Mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, -1 / camera.z, 1);
	Vec4f temp = mult(m, vh);
	return Vec3f(temp.x / temp.h, temp.y / temp.h, temp.z / temp.h);
}
