#pragma once

#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "SOIL.h"
#include "Vector"
#include "TextureLoader.h"

#include <vector>
#include "Vector3.h"
#include "SOIL.h"

class Model
{
public:
	
	Model();
	~Model();
	
	bool load(char* modelFilename, char* textureFilename);
	bool loadModel(char* filename);
	void render2(static std::vector<float> verts);
	GLuint myTexture;
	TextureLoader tx;

	std::vector<Vector3> vertex, normals, texCoords;

};
