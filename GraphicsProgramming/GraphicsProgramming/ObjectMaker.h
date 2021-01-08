#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Vector3.h"
#include "SOIL.h"
#include <math.h>
#include "ProceduralGenerator.h"

class ObjectMaker : public ProceduralGenerator
{
public:
	ObjectMaker();
	~ObjectMaker();


	void drawVase();
	void drawPlant();
	void drawFan();
	void drawWindow();
	void drawBlinds();
	void drawTable();

	float fanrot;
	float fanspeed;

private:
	ProceduralGenerator pg;
};

