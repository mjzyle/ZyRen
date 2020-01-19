#pragma once

#include <cmath>


struct Vec2f {
	float x, y;
	Vec2f() {}
	Vec2f(float _x, float _y) { x = _x; y = _y; }
};

struct Vec3f {
	float x, y, z;
	Vec3f() {}
	Vec3f(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }
};

struct Vec4f {
	float x, y, z, h;
	Vec4f() {}
	Vec4f(float _x, float _y, float _z, float _h) { x = _x; y = _y; z = _z; h = _h; }
};

struct Mat4x4 {
	float vals[4][4];
	Mat4x4() {};
	Mat4x4(float _00, float _01, float _02, float _03, float _10, float _11, float _12, float _13,
		   float _20, float _21, float _22, float _23, float _30, float _31, float _32, float _33) {
		float temp[] = { _00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33 };
		for (int i = 0; i < 4; i++) {
			vals[0][i] = temp[i];
			vals[1][i] = temp[i + 4];
			vals[2][i] = temp[i + 8];
			vals[3][i] = temp[i + 12];
		}
	}
};

struct Vertex {
	Vec3f loc, norm;
	Vertex() {}
	Vertex(Vec3f _loc, Vec3f _norm, Vec2f _tex) { loc = _loc; norm = _norm; }
};

// Face structure stores an array of integers corresponding to its associated vertices
struct Face {
	int verts[3], texts[3], norms[3];
	Face() {}
	Face(int _verts[3], int _texts[3], int _norms[3]) {
		for (int i = 0; i < 3; i++) { verts[i] = _verts[i]; }
		for (int i = 0; i < 3; i++) { texts[i] = _texts[i]; }
		for (int i = 0; i < 3; i++) { norms[i] = _norms[i]; }
	}
};
