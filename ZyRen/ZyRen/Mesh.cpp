#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Mesh.h"
#include "Geometry.h"

using namespace std;

// CONSTRUCTORS
Mesh::Mesh(char *_filename) {
	// Determine counts for mesh attributes to allocate space appropriately
	string line;
	ifstream objectFile;
	ofstream objectReport;
	objectFile.open(_filename);
	objectReport.open("Reports/Mesh_Report.txt");
	if (objectFile.is_open()) {
		while (getline(objectFile, line)) {
			istringstream stream(line.c_str());
			char trash;
			if (!line.compare(0, 2, "# ")) {
				int count;
				string type;
				stream >> trash;	
				stream >> count;
				stream >> type;
				if (!type.compare("vertices")) { vertCount = count; }
				else if (!type.compare("faces")) { faceCount = count; }
				else if (!type.compare("texture")) { texCount = count; }
				else if (!type.compare("vertex")) { normCount = count; }
			}
 		}
		objectReport << "Vertices: " << vertCount << endl;
		objectReport << "Textures: " << texCount << endl;
		objectReport << "Normals: " << normCount << endl;
		objectReport << "Faces: " << faceCount << endl;
		objectFile.close();
	}
	else {
		cout << "ERROR: Unable to open file " << _filename << endl;
	}

	// Process mesh data
	verts = new Vertex[vertCount];
	faces = new Face[faceCount];
	texts = new Vec2f[texCount];
	objectFile.open(_filename);
	if (objectFile.is_open()) {
		int vertsProcessed = 0, normsProcessed = 0, textsProcessed = 0, facesProcessed = 0;
		while (getline(objectFile, line)) {
			istringstream stream(line.c_str());
			char trash;
			// Save vertex location data
			if (!line.compare(0, 2, "v ")) {
				stream >> trash;
				stream >> verts[vertsProcessed].loc.x;
				stream >> verts[vertsProcessed].loc.y;
				stream >> verts[vertsProcessed].loc.z;
				vertsProcessed++;
			}
			// Save vertex texture data
			else if (!line.compare(0, 3, "vt ")) {
				stream >> trash;
				stream >> trash;
				stream >> texts[textsProcessed].x;
				stream >> texts[textsProcessed].y;
				textsProcessed++;
			}
			// Save vertex normal data
			else if (!line.compare(0, 3, "vn ")) {
				stream >> trash;
				stream >> trash;
				stream >> verts[normsProcessed].norm.x;
				stream >> verts[normsProcessed].norm.y;
				stream >> verts[normsProcessed].norm.z;
				normsProcessed++;
			}
			// Save face data
			else if (!line.compare(0, 2, "f ")) {
				stream >> trash;
				stream >> faces[facesProcessed].verts[0];
				stream >> trash;
				stream >> faces[facesProcessed].texts[0];
				stream >> trash;
				stream >> faces[facesProcessed].norms[0];

				stream >> faces[facesProcessed].verts[1];
				stream >> trash;
				stream >> faces[facesProcessed].texts[1];
				stream >> trash;
				stream >> faces[facesProcessed].norms[1];

				stream >> faces[facesProcessed].verts[2];
				stream >> trash;
				stream >> faces[facesProcessed].texts[2];
				stream >> trash;
				stream >> faces[facesProcessed].norms[2];

				facesProcessed++;
			}
		}
		objectReport << "Vertices processed: " << vertsProcessed << endl;
		objectReport << "Textures processed: " << textsProcessed << endl;
		objectReport << "Normals processed: " << normsProcessed << endl;
		objectReport << "Faces processed: " << facesProcessed << endl;
		objectFile.close();
	}
	else {
		cout << "ERROR: Unable to open file " << _filename << endl;
	}

	// Print ALL mesh details
	for (int i = 0; i < faceCount; i++) {
		objectReport << "Face " << i + 1 << ":" << endl;
		for (int j = 0; j < 3; j++) {
			objectReport << "    Vert " << faces[i].verts[j] <<
				": x = " << verts[faces[i].verts[j] - 1].loc.x <<
				", y = " << verts[faces[i].verts[j] - 1].loc.y <<
				", z = " << verts[faces[i].verts[j] - 1].loc.z << endl;
		}
	}

	objectReport.close();
}

Mesh::~Mesh() {
}

// METHODS
Vertex Mesh::getVert(int i) {
	return verts[i];
}

Face Mesh::getFace(int i) {
	return faces[i];
}

Vec2f Mesh::getTex(int i) {
	return texts[i];
}

int Mesh::getVertCount() {
	return vertCount;
}

int Mesh::getTexCount() {
	return texCount;
}

int Mesh::getNormCount() {
	return normCount;
}

int Mesh::getFaceCount() {
	return faceCount;
}
