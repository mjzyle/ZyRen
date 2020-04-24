#include "Render.h"
#include "Geometry.h"
#include "tgaimage.h"
#include "Mesh.h"
#include "Algebra.h"
#include "Transform.h"
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;


// Determine barycentric coordinates of a 3D triangle
Vec3f barycentric(Vec3f* points, Vec3f p) {
	Vec3f u = cross(Vec3f(points[2].x - points[0].x, points[1].x - points[0].x, points[0].x - p.x),
		Vec3f(points[2].y - points[0].y, points[1].y - points[0].y, points[0].y - p.y));

	if (std::abs(u.z) > 1e-2) {
		return Vec3f(1.0f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
	}

	return Vec3f(-1.0f, 1.0f, 1.0f);
}


// Render a texture-mapped triangle
void triangle(Vec3f* points, float* zbuffer, TGAImage& image, Vec2f* tex, float intensity, Mesh m, int height, int width, TGAImage& texture) {
	Vec2f bboxmin(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	Vec2f bboxmax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
	Vec2f clamp(image.get_width() - 1, image.get_height() - 1);

	for (int i = 0; i < 3; i++) {
		bboxmin.x = max(0.0f, min(bboxmin.x, points[i].x));
		bboxmax.x = min(clamp.x, max(bboxmax.x, points[i].x));
		bboxmin.y = max(0.0f, min(bboxmin.y, points[i].y));
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