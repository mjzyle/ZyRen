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
#include "Algebra.h"
#include "Transform.h"
#include "Render.h"

using namespace std;


// Mesh variables
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);

// Screen variables
const int height = 800;
const int width = 800;
const bool drawPerspective = true;

// Texture variables
TGAImage texture;

// Lighting/camera variables
Vec3f light_dir(0, 0, -1);
Vec3f camera(0, 0, 3);


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
				coords_screen[j] = world2screen(perspective(v, camera), height, width);
			}
			else {
				coords_screen[j] = world2screen(v, height, width);
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
			triangle(coords_screen, zbuffer, scene, tex, intensity, m, height, width, texture);
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