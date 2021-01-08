#include "RoomMaker.h"

RoomMaker::RoomMaker(){

	tx.loadTextures2();
}

RoomMaker::~RoomMaker(){

}

void RoomMaker::drawRoom() {

	//Right side
	pg.drawWall(0, 0, 0, 4, 3, { 1,0,0 }, tx.wallTexture);
	//window here

	pg.drawWall(0, 8, 0, 10, 3, { 1,0,0 }, tx.wallTexture);


	pg.drawWall(0, 10, 4, 10, 3, { 0,0,1 }, tx.wallTexture);


	//Left side
	pg.drawWall(4, 7, 4, 10, 3, { -1,0,0 }, tx.wallTexture);
	pg.drawWall(4, 7, 5, 7, 3, { 0,0,-1 }, tx.wallTexture);
	pg.drawWall(5, 3, 5, 7, 3, { -1,0,0 }, tx.wallTexture);
	pg.drawWall(5, 3, 7, 3, 3, { 0,0,-1 }, tx.wallTexture);
	pg.drawWall(5, 3, 7, 3, 3, { 0,0,-1 }, tx.wallTexture);
	pg.drawWall(7, 0, 7, 3, 3, { -1,0,0 }, tx.wallTexture);
	pg.drawWall(4, 0, 7, 0, 3, { 0,0,-1 }, tx.wallTexture);
	pg.drawWall(0, 0, 2, 0, 3, { 0,0,-1 }, tx.wallTexture);





	


}

void RoomMaker::renderFloor() {

	drawFloor(map, 0,tx.marble);

}
void RoomMaker::renderRoof() {

	drawFloor(map, 3,NULL);
}

void RoomMaker::drawFloor(int map[], float height, GLuint texture) {

	int i;

	for ( i = 0; i < 10 ; i++)
	{
		for (int v = 0; v < map[i]; v++)
		{
			pg.drawFloorTile(v,i,height,texture);
		}
	}
}

void RoomMaker::update(float dt) {

	//Update fan speed
	obj.fanrot += obj.fanspeed * dt;

}

void RoomMaker::drawScene() {

	//draw objects in the scene
	glEnable(GL_TEXTURE_2D);

	glColor4f(1, 1, 1, 1);

	//Draw Celling Fans
	glPushMatrix();
		glTranslatef(2, 2.7, 5);
		obj.drawFan();
		glTranslatef(0, 0, 3);
		obj.drawFan();
	glPopMatrix();



	//draw plants
	glPushMatrix();
		glScalef(0.8, 0.8, 0.8);
		glTranslatef(1, 0.35, 6);
		obj.drawPlant();
		glTranslatef(0, 0, 2.5);
		obj.drawPlant();
	glPopMatrix();


	//draw table
	glPushMatrix();
		glTranslatef(1.3, 0, 6);
		glScalef(0.1, 0.1, 0.1);
		obj.drawTable();
	glPopMatrix();


	//render window
	glPushMatrix();
		glTranslatef(-0.125, 0, 8);
		glRotatef(90, 0, 1, 0);
		glScalef(0.5, 0.5, 0.5);

			glPushMatrix();


				glTranslatef(0, 5.5, 0.75);
				obj.drawBlinds();
				glTranslatef(4.2, 0, 0);
				obj.drawBlinds();
			glPopMatrix();
		obj.drawWindow();
	glPopMatrix();



	//draw plants2
	glPushMatrix();
		glScalef(0.7, 0.7, 0.7);
		glTranslatef(7, 0.35, 1);
		obj.drawPlant();
		glTranslatef(0, 0, 2.5);
		obj.drawPlant();
	glPopMatrix();

	//draw carpet0
	glPushMatrix();
		
		glTranslatef(0.5, 0.01, 2.2);
		glRotatef(-90, 1, 0, 0);
		glScalef(4, 2, 1);
		pg.drawPlane(tx.carpet0);
	glPopMatrix();

	//drawPosters
	glPushMatrix();

		glTranslatef(3.99, 0.5, 9);
		glRotatef(90, 0, 1, 0);
		glScalef(1.5, 2.4, 1);
		pg.drawPlane(tx.poster0);

	glPopMatrix();
	glPushMatrix();
		glTranslatef(6.99, 0.5, 2);
		glRotatef(90, 0, 1, 0);
		glScalef(1.5, 2.4, 1);
		pg.drawPlane(tx.poster1);
	glPopMatrix();





	glDisable(GL_TEXTURE_2D);
}

void RoomMaker::drawShadows() {

	

	//render window
	glPushMatrix();
	glTranslatef(-0.125, 0, 8);
	glRotatef(90, 0, 1, 0);
	glScalef(0.5, 0.5, 0.5);

	//draw blinds
		glPushMatrix();
			glTranslatef(0, 5.5, 0.75);
			obj.drawBlinds();
			glTranslatef(4.2, 0, 0);
			obj.drawBlinds();
		glPopMatrix();
	glPopMatrix();


	//draw plants
	glPushMatrix();
		glScalef(0.8, 0.8, 0.8);
		glTranslatef(1, 0.35, 6);
		obj.drawPlant();
		glTranslatef(0, 0, 2.5);
		obj.drawPlant();
	glPopMatrix();

	


}