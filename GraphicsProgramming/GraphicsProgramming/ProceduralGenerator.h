#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Vector3.h"
#include "SOIL.h"
#include <math.h>
#include "TextureLoader.h"

class ProceduralGenerator
{
public:
	ProceduralGenerator();
	~ProceduralGenerator();

	void drawWall(float ax, float az, float bx, float bz, float height, Vector3 direction, GLuint texture);
	void drawCircle(float radius, GLuint texture);
	void drawSphere(int segments, GLuint texture, float hemisphere);
	void drawEllipse();
	void drawFan(GLuint texture);
	void drawCone(float radius, float height, GLuint texture);
	void drawPlane(GLuint texture);
	void drawFloorTile(float v, float i, float height, GLuint texture);
	void drawCube(float width, float height, float depth, GLuint texture);
	void drawCylinder(float radius, float height, GLuint texture);

	TextureLoader tx;

private:
	
	float theta, delta;
};

