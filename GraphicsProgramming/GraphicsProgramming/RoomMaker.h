#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ProceduralGenerator.h"
#include "TextureLoader.h"
#include <array>
#include "ObjectMaker.h"
class RoomMaker
{
public:
	RoomMaker();
	~RoomMaker();

	void renderRoom();
	void drawRoom();
	void drawFloor(int map[], float height, GLuint texture);
	void drawScene();

	void update(float dt);
	void renderFloor();
	void renderRoof();
	void drawShadows();

	

private:
	int map[10] = { 7,7,7,5,5,5,5,4,4,4 };
	ProceduralGenerator pg;
	TextureLoader tx;
	ObjectMaker obj;
};

