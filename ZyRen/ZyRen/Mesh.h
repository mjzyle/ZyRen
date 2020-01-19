#pragma once

#include "Geometry.h"


class Mesh
{
private:
	char *filename;
	Vertex *verts;
	Face *faces;
	Vec2f *texts;
	int vertCount = 0, texCount = 0, normCount = 0, faceCount = 0;
public:
	Mesh(char *_filename);
	~Mesh();
	Vertex getVert(int i);
	Face getFace(int i);
	Vec2f getTex(int i);
	int getVertCount();
	int getTexCount();
	int getNormCount();
	int getFaceCount();
};

