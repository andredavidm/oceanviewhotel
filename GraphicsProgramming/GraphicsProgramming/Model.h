#ifndef _MODEL_H_
#define _MODEL_H_

#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "SOIL.h"
#include <fstream>

#include <vector>
#include "Vector3.h"
#include "TextureLoader.h"

using namespace std;

class Model
{
public:
	Model();
	~Model();
	
	void renderChair();
	void renderBed();
	void drawModels();
	void modelShadow();


	
private:
	bool loadModel(char* filename, vector<Vector3>* vertex, vector<Vector3>* normals, vector<Vector3>* texCoords);
	void render(static std::vector<Vector3> verts, static std::vector<Vector3> normals, static std::vector<Vector3> texCoords, GLuint texture);

	TextureLoader tx;
	vector<Vector3> Loader_vertex, Loader_normals, Loader_texCoords;
	
	vector<Vector3> chair_vertex, chair_normals, chair_texCoords;
	vector<Vector3> bed_vertex, bed_normals, bed_texCoords;

};

#endif