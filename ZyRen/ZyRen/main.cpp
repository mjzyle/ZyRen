#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Geometry.h"
#include "Mesh.h"

using namespace std;


// Vector * Vector
float dot(Vec4f a, Vec4f b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}


// Vector x Vector
Vec4f cross(Vec4f a, Vec4f b) {
	return Vec4f(a.y * b.z - a.z * b.y, a.x * b.z - a.z * b.x, a.x * b.y - a.y * b.x, 1);
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

/*
void printVector(Vec4f v, ofstream report) {
	report << v.x << " " << v.y << " " << v.z << " " << v.h << endl;
}


void printMatrix(Mat4x4 mat, ofstream report) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			report << mat.vals[i][j] << " ";
		}
		report << endl;
	}
}
*/

int main(int argc, char** argv) {
	Mesh m = Mesh("Meshes/head.obj");
	
	ofstream mainReport;
	string line;
	mainReport.open("Reports/Main_Report.txt");

	/*
	mainReport << "Vertex data:" << endl;
	for (int i = 0; i < m.getVertCount(); i++) {
		mainReport << "Location " << i << ": " << m.getVert(i).loc.x << ", " << m.getVert(i).loc.y << ", " << m.getVert(i).loc.z << endl;
		mainReport << "Normal " << i << ": " << m.getVert(i).norm.x << ", " << m.getVert(i).norm.y << ", " << m.getVert(i).norm.z << endl;
	}

	mainReport << "Face data:" << endl;
	for (int i = 0; i < m.getFaceCount(); i++) {
		mainReport << "Vertices " << i << ": " << m.getFace(i).verts[0] << ", " << m.getFace(i).verts[1] << ", " << m.getFace(i).verts[2] << endl;
		mainReport << "Textures " << i << ": " << m.getFace(i).texts[0] << ", " << m.getFace(i).texts[1] << ", " << m.getFace(i).texts[2] << endl;
	}
	

	Vec4f v(1.0, 2.0, 3.0, 1.0);
	Mat4x4 mat1(2.0f, 1.0f, 0.0f, 0.0f, 
				0.0f, 1.0f, 0.0f, 0.0f, 
				0.0f, 0.0f, 1.0f, 0.0f, 
				0.0f, 0.0f, 0.0f, 1.0f);
	Mat4x4 t = mult(mat1, mat1);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mainReport << mat1.vals[i][j] << " ";
		}
		mainReport << endl;
	}

	mainReport << "   *" << endl;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mainReport << mat1.vals[i][j] << " ";
		}
		mainReport << endl;
	}

	mainReport << "   =" << endl;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mainReport << t.vals[i][j] << " ";
		}
		mainReport << endl;
	}
	*/

	mainReport.close();
	return 0;
}