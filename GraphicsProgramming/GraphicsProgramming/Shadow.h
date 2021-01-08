#pragma once

#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <vector>
#include "Vector3.h"
#include "RoomMaker.h"
#include "Model.h"
#include "ObjectMaker.h"


class Shadow
{
public:

	static void extendVertex(float newVert[3], float lightPosit[4], float x, float y, float z, float ext);
	static std::vector<float> buildShadowVolume(float lightPosit[4], std::vector<float> verts);
	
	static void generateShadowMatrix(float* shadowMatrix, float light_pos[4], GLfloat floor[12]);
	
	void render(static std::vector<float> verts);
	void renderShadow();

	ObjectMaker obj;
	Model model;
	RoomMaker room;


	float lightpos[4];
	
	Vector3 get_light_pos(Vector3 pos);


	float floor[12] = { -1, 0, -1,
					    -1, 0,  1,
					     1, 0,  1,
					     1, 0, -1 };

	float wall0[12] = { 5, -1, -1,
						5, -1,  1,
						5,  1,  1,
						5,  1, -1 };

};