#include "ObjectMaker.h"

ObjectMaker::ObjectMaker() {


	fanspeed = 100;
	tx.loadTextures();


}

ObjectMaker::~ObjectMaker() {

}



void ObjectMaker::drawFan() {

	//Start
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
		//Draw the Blades
		glPushMatrix();
			
			glRotatef(fanrot, 0, 1, 0);
				
				glPushMatrix();
					pg.drawFan(tx.fanBlade);
					glRotatef(90, 0, 1, 0);
					pg.drawFan(tx.fanBlade);
					glRotatef(90, 0, 1, 0);	
					pg.drawFan(tx.fanBlade);
					glRotatef(90, 0, 1, 0);
					pg.drawFan(tx.fanBlade);
					glPopMatrix();
		glPopMatrix();


		//Draw Base
		//DrawBottom
		glPushMatrix();
			glScalef(0.5, 0.5, 0.5);
			glTranslatef(0, -0.4, 0);
			pg.drawSphere(50, tx.fanBase1, 3);
		glPopMatrix();
		//DrawTop
		glPushMatrix();
			glTranslatef(0, 1, 0);
			glScalef(1.0, -0.75, 1.0);
			pg.drawSphere(50, tx.fanBase0, 3);
		glPopMatrix();




	//Finish
	glPopMatrix();

}

void ObjectMaker::drawVase() {

	glPushMatrix();
	glRotatef(90, 1, 0, 0);

	glPushMatrix();
		//draw vase
		drawCylinder(1, 2, tx.fanBlade);
		//draw dirt
		glRotatef(90, 1, 0, 0);
		drawCircle(1.44, tx.dirt);
		glPushMatrix();
			//draw bottom
			glTranslatef(0, 2, 0);
			drawCircle(1.44, tx.dirt);
			glPopMatrix();
		glPopMatrix();
		glPopMatrix();


}

void ObjectMaker::drawPlant() {

	glPushMatrix();
	glScalef(0.2, 0.2, 0.2);

	drawVase();

	glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		drawCylinder(0.15, 7, tx.trunk);
	glPopMatrix();

	//Enable our lord and saviour png alpha channel filter
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1f);

	glPushMatrix();
		//draw first quad
		glScalef(8, 8, 8);
		glTranslatef(-0.5, 0.4, 0);
	
	
		drawPlane(tx.palm);
	

		glPushMatrix();
			//draw second
			glRotatef(90, 0, 1, 0);
			glTranslatef(-0.5,0, 0.5);
			drawPlane(tx.palm);
		glPopMatrix(); 
		//Draw first again
			drawPlane(tx.palm);
			glPopMatrix();
	glPopMatrix();
	glDisable(GL_ALPHA_TEST);

}

void ObjectMaker::drawWindow() {

	glEnable(GL_TEXTURE_2D);

	glColor4f(0.8, 0.85, 0.9 , 1);
	//draw horizontal bars
	glPushMatrix();
		pg.drawCube(8, 1, 0.5, NULL);
		glTranslatef(0, 3, 0);
		pg.drawCube(8, 0.5, 0.5, NULL);
		glTranslatef(0, 2.5, 0);
		pg.drawCube(8, 0.5, 0.5, NULL);
	glPopMatrix();

	//draw vertical bars
	glPushMatrix();
		pg.drawCube(0.5, 6, 0.5, NULL);
		glTranslatef(2, 0, 0);
		pg.drawCube(0.5, 6, 0.5, NULL);
		glTranslatef(3.5, 0, 0);
		pg.drawCube(0.5, 6, 0.5, NULL);
		glTranslatef(2, 0, 0);
		pg.drawCube(0.5, 6, 0.5, NULL);
	glPopMatrix();

	//drawGlass
	glPushMatrix();
		glEnable(GL_BLEND);
		glColor4f(0.7, 0.8, 0.99, 0.4);
		glTranslatef(0, 0, 0.25);
		glScalef(8, 6, 8);
		pg.drawPlane(NULL);
		glDisable(GL_BLEND);
	glPopMatrix();

	
	glDisable(GL_TEXTURE_2D);
	glColor4f(1, 1, 1, 1);
}

void ObjectMaker::drawBlinds() {
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
		glScalef(0.2, 0.2, 0.2);

		int i;
		for(i = 0; i <4*4; i+=3){
				
				glPushMatrix();
				glTranslatef(0, -i, 0);
					glRotatef(-30, 1, 0, 0);
					pg.drawCube(20, 2, 0.5, NULL);
				glPopMatrix();
		
		}
		glPushMatrix();
			glTranslatef(0, -i, 0);
			glRotatef(3, 0, 0, 1);
			pg.drawCube(20, 2, 0.5, NULL);
		glPopMatrix();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void ObjectMaker::drawTable() {


	

	glEnable(GL_BLEND);


	glEnable(GL_TEXTURE_2D);
	glColor3f(0.4,0.4, 0.5);
	//Draw Feet
	glPushMatrix();
		pg.drawCube(2, 4, 2, tx.table0);
		glTranslatef(10, 0, 0);
		pg.drawCube(2, 4, 2, tx.table0);
		glTranslatef(0, 0, 10);
		pg.drawCube(2, 4, 2, tx.table0);
		glTranslatef(-10,0, 0);
		pg.drawCube(2, 4, 2, tx.table0);
	glPopMatrix();


	//Stand
	glPushMatrix();
		glTranslatef(1, 4, 0.5);
		glPushMatrix();
			pg.drawCube(10, 0.5, 0.5,NULL);
			glRotatef(-90, 0, 1, 0);
			pg.drawCube(10.5, 0.5, 0.5, NULL);
			glPopMatrix();
		glTranslatef(0, 0, 10);
		pg.drawCube(10, 0.5, 0.5, NULL);
		glRotatef(-90, 0, 1, 0);
		glTranslatef(-10, 0, -10);
		pg.drawCube(10, 0.5, 0.5, NULL);

	glPopMatrix();


	//draw top
	glColor4f(0.3, 0.4, 0.45, 0.3);
	glPushMatrix();
		glTranslatef(0, 4.6, 0);
		glRotatef(90, 1, 0, 0);
		glScalef(12, 12, 12);
		pg.drawPlane(NULL);
	glPopMatrix();


	glDisable(GL_BLEND);




	glDisable(GL_TEXTURE_2D);
}