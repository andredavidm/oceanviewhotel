
#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "SOIL.h"

class TextureLoader
{
public:
	TextureLoader();
	~TextureLoader();

	//For ObjectMaker
	void loadTextures();
	//For Primitives
	void loadTextures2();




	GLuint fanBase0;
	GLuint fanBlade;
	GLuint wallTexture;
	GLuint fanBase1;
	GLuint dirt;
	GLuint palm;
	GLuint trunk;
	GLuint marble;
	GLuint skybox;
	GLuint texture;
	GLuint table0;
	GLuint carpet0;
	GLuint poster0;
	GLuint poster1;

};

