#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "Geometry.h"
#include "Mesh.h"
#include "TGAImage.h"

using namespace std;


// Mesh variables
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);
const int width = 800;
const int height = 800;
const bool drawPerspective = true;

// Texture variables
TGAImage texture;

// Lighting variables
Vec3f light_dir(0, 0, -1);
Vec3f camera(0, 0, -10);


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


// Convert world coordinates to screen coordinates
Vec3f world2screen(Vec3f v) {
	return Vec3f(int((v.x + 1.0) * width / 2.0 + 0.5), int((v.y + 1.0) * height / 2.0 + 0.5), v.z);
}


// Apply a perspective transformation to a point
Vec3f perspective(Vec3f v) {
	Vec4f vh = Vec4f(v.x, v.y, v.z, 1.0f);
	Mat4x4 m = Mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, -1 / camera.z, 1);
	Vec4f temp = mult(m, vh);
	return Vec3f(temp.x / temp.h, temp.y / temp.h, temp.z / temp.h);
}


// Determine barycentric coordinates of a 3D triangle
Vec3f barycentric(Vec3f *points, Vec3f p) {
	Vec3f u = cross(Vec3f(points[2].x - points[0].x, points[1].x - points[0].x, points[0].x - p.x), 
				    Vec3f(points[2].y - points[0].y, points[1].y - points[0].y, points[0].y - p.y));

	if (std::abs(u.z) > 1e-2) {
		return Vec3f(1.0f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
	}

	return Vec3f(-1.0f, 1.0f, 1.0f);
}


// Texture-mapped triangle
void triangle(Vec3f *points, float *zbuffer, TGAImage &image, Vec2f *tex, float intensity, Mesh m) {
	Vec2f bboxmin(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	Vec2f bboxmax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
	Vec2f clamp(image.get_width() - 1, image.get_height() - 1);

	for (int i = 0; i < 3; i++) {
		bboxmin.x = max(   0.0f, min(bboxmin.x, points[i].x));
		bboxmax.x = min(clamp.x, max(bboxmax.x, points[i].x));
		bboxmin.y = max(   0.0f, min(bboxmin.y, points[i].y));
		bboxmax.y = min(clamp.y, max(bboxmax.y, points[i].y));
	}


	Vec3f p;
	for (p.x = bboxmin.x; p.x <= bboxmax.x; p.x++) {
		for (p.y = bboxmin.y; p.y <= bboxmax.y; p.y++) {
			Vec3f bc_screen = barycentric(points, p);
			if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0) continue;

			p.z = 0;
			p.z += points[0].z * bc_screen.x;
			p.z += points[1].z * bc_screen.y;
			p.z += points[2].z * bc_screen.z;
			if (zbuffer[int(p.x + p.y * width)] < p.z) {
				zbuffer[int(p.x + p.y * width)] = p.z;

				// Interpolate UV values using barycentric coordinates of the face
				Vec3f uvI;
				uvI.x = bc_screen.x * tex[0].x + bc_screen.y * tex[1].x + bc_screen.z * tex[2].x;
				uvI.y = bc_screen.x * tex[0].y + bc_screen.y * tex[1].y + bc_screen.z * tex[2].y;

				// Use inteprolated UV to determine color from the diffuse map
				TGAColor temp = texture.get(uvI.x * texture.get_width(), uvI.y * texture.get_height());
				TGAColor color = TGAColor(temp.r * intensity, temp.g * intensity, temp.b * intensity, 255);
				image.set(p.x, p.y, color);
			}

		}
	}
}


int main(int argc, char** argv) {
	Mesh m = Mesh("Meshes/head.obj");
	
	ofstream mainReport;
	string line;
	mainReport.open("Reports/Main_Report.txt");

	TGAImage scene(width, height, TGAImage::RGB);
	
	float *zbuffer = new float[width * height];

	texture.read_tga_file("Textures/head_diffuse.tga");
	texture.flip_vertically();

	int facesProcessed = 0, facesDrawn = 0;

	// Process each triangular face
	for (int i = 0; i < m.getFaceCount(); i++) {
		Face f = m.getFace(i);
		Vec2f tex[3] = { m.getTex(f.texts[0] - 1), m.getTex(f.texts[1] - 1) , m.getTex(f.texts[2] - 1) };

		Vec3f coords_screen[3], coords_world[3];
		mainReport << "Processing face " << i + 1 << endl;

		// Process each vertex, converting world coordinates to screen coordinates
		for (int j = 0; j < 3; j++) {
			int k = f.verts[j] - 1;
			Vec3f v = Vec3f(m.getVert(k).loc.x, m.getVert(k).loc.y, m.getVert(k).loc.z);

			mainReport << "    Processing vertex " << k + 1 << endl;
			mainReport << "        (x,y,z) = " 
				<< m.getVert(k).loc.x << " " << m.getVert(k).loc.y << " " << m.getVert(k).loc.z << endl;

			if (drawPerspective) {
				coords_screen[j] = world2screen(perspective(v));
			}
			else {
				coords_screen[j] = world2screen(v);
			}
			
			coords_world[j] = v;

			mainReport << "        Converted to screen coordinates "
				<< coords_screen[j].x << " " << coords_screen[j].y << " " << coords_screen[j].z << endl;


		}

		Vec3f norm = cross(sub(coords_world[2], coords_world[0]), sub(coords_world[1], coords_world[0]));
		norm = normalize(norm);
		float intensity = dot(norm, light_dir);
		mainReport << "    Intensity = " << intensity << endl;

		if (intensity > 0) {
			triangle(coords_screen, zbuffer, scene, tex, intensity, m);
			facesDrawn++;
			mainReport << "    Face drawn" << endl;
		}

		mainReport << "\n" << endl;
	}

	mainReport << facesDrawn << " faces drawn out of " <<  m.getFaceCount() << " total" << endl;

	scene.flip_vertically();
	scene.write_tga_file("Images/scene.tga");

	mainReport.close();
	return 0;
}