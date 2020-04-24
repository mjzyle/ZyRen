#include "Algebra.h"
#include "Geometry.h"

using namespace std;


// Vector * Vector
float dot(Vec4f a, Vec4f b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
float dot(Vec3f a, Vec3f b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Vector x Vector
Vec4f cross(Vec4f a, Vec4f b) {
	return Vec4f(a.y * b.z - a.z * b.y, -(a.x * b.z - a.z * b.x), a.x * b.y - a.y * b.x, 1);
}
Vec3f cross(Vec3f a, Vec3f b) {
	return Vec3f(a.y * b.z - a.z * b.y, -(a.x * b.z - a.z * b.x), a.x * b.y - a.y * b.x);
}

// Vector + Vector
Vec4f add(Vec4f a, Vec4f b) {
	return Vec4f(a.x + b.x, a.y + b.y, a.z + b.z, 1.f);
}
Vec3f add(Vec3f a, Vec3f b) {
	return Vec3f(a.x + b.x, a.y + b.y, a.z + b.z);
}

// Vector - Vector
Vec4f sub(Vec4f a, Vec4f b) {
	return Vec4f(a.x - b.x, a.y - b.y, a.z - b.z, 1.f);
}
Vec3f sub(Vec3f a, Vec3f b) {
	return Vec3f(a.x - b.x, a.y - b.y, a.z - b.z);
}

// Matrix x Vector
Vec4f mult(Mat4x4 m, Vec4f v) {
	return Vec4f(m.vals[0][0] * v.x + m.vals[0][1] * v.y + m.vals[0][2] * v.z + m.vals[0][3] * v.h,
		m.vals[1][0] * v.x + m.vals[1][1] * v.y + m.vals[1][2] * v.z + m.vals[1][3] * v.h,
		m.vals[2][0] * v.x + m.vals[2][1] * v.y + m.vals[2][2] * v.z + m.vals[2][3] * v.h,
		m.vals[3][0] * v.x + m.vals[3][1] * v.y + m.vals[3][2] * v.z + m.vals[3][3] * v.h);
}

// Matrix x Matrix
Mat4x4 mult(Mat4x4 m1, Mat4x4 m2) {
	return Mat4x4(
		m1.vals[0][0] * m2.vals[0][0] + m1.vals[0][1] * m2.vals[1][0] + m1.vals[0][2] * m2.vals[2][0] + m1.vals[0][3] * m2.vals[3][0],
		m1.vals[0][0] * m2.vals[0][1] + m1.vals[0][1] * m2.vals[1][1] + m1.vals[0][2] * m2.vals[2][1] + m1.vals[0][3] * m2.vals[3][1],
		m1.vals[0][0] * m2.vals[0][2] + m1.vals[0][1] * m2.vals[1][2] + m1.vals[0][2] * m2.vals[2][2] + m1.vals[0][3] * m2.vals[3][2],
		m1.vals[0][0] * m2.vals[0][3] + m1.vals[0][1] * m2.vals[1][3] + m1.vals[0][2] * m2.vals[2][3] + m1.vals[0][3] * m2.vals[3][3],

		m1.vals[1][0] * m2.vals[0][0] + m1.vals[1][1] * m2.vals[1][0] + m1.vals[1][2] * m2.vals[2][0] + m1.vals[1][3] * m2.vals[3][0],
		m1.vals[1][0] * m2.vals[0][1] + m1.vals[1][1] * m2.vals[1][1] + m1.vals[1][2] * m2.vals[2][1] + m1.vals[1][3] * m2.vals[3][1],
		m1.vals[1][0] * m2.vals[0][2] + m1.vals[1][1] * m2.vals[1][2] + m1.vals[1][2] * m2.vals[2][2] + m1.vals[1][3] * m2.vals[3][2],
		m1.vals[1][0] * m2.vals[0][3] + m1.vals[1][1] * m2.vals[1][3] + m1.vals[1][2] * m2.vals[2][3] + m1.vals[1][3] * m2.vals[3][3],

		m1.vals[2][0] * m2.vals[0][0] + m1.vals[2][1] * m2.vals[1][0] + m1.vals[2][2] * m2.vals[2][0] + m1.vals[2][3] * m2.vals[3][0],
		m1.vals[2][0] * m2.vals[0][1] + m1.vals[2][1] * m2.vals[1][1] + m1.vals[2][2] * m2.vals[2][1] + m1.vals[2][3] * m2.vals[3][1],
		m1.vals[2][0] * m2.vals[0][2] + m1.vals[2][1] * m2.vals[1][2] + m1.vals[2][2] * m2.vals[2][2] + m1.vals[2][3] * m2.vals[3][2],
		m1.vals[2][0] * m2.vals[0][3] + m1.vals[2][1] * m2.vals[1][3] + m1.vals[2][2] * m2.vals[2][3] + m1.vals[2][3] * m2.vals[3][3],

		m1.vals[3][0] * m2.vals[0][0] + m1.vals[3][1] * m2.vals[1][0] + m1.vals[3][2] * m2.vals[2][0] + m1.vals[3][3] * m2.vals[3][0],
		m1.vals[3][0] * m2.vals[0][1] + m1.vals[3][1] * m2.vals[1][1] + m1.vals[3][2] * m2.vals[2][1] + m1.vals[3][3] * m2.vals[3][1],
		m1.vals[3][0] * m2.vals[0][2] + m1.vals[3][1] * m2.vals[1][2] + m1.vals[3][2] * m2.vals[2][2] + m1.vals[3][3] * m2.vals[3][2],
		m1.vals[3][0] * m2.vals[0][3] + m1.vals[3][1] * m2.vals[1][3] + m1.vals[3][2] * m2.vals[2][3] + m1.vals[3][3] * m2.vals[3][3]
	);
}

// Normalize Vector
Vec3f normalize(Vec3f v) {
	float mag = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	return Vec3f(v.x / mag, v.y / mag, v.z / mag);
}