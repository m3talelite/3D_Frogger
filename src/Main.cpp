/*
 * Main.cpp
 *
 *  Created on: May 20, 2014
 *      Author: eilel
 */

#include <iostream>
#include <vector>
#include <cstring>
#include <time.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include <math.h>
#include "../include/Map.h"
#include "../include/GameObject.h"
#include "../include/ObjectLoader.h"

#define Window_Width 	960
#define Window_Height 	640

//Create an array of 256 boolean values.
//The default of the boolean states is false.
bool keyStates[256];
float cameraX, cameraZ;
float eyeAngle = 0;
GLfloat xTrans = 0, zTrans = 0, rotation = 0;
float startLocation[3] = { 1.0, 1.0, 1.0 };
GameObject player(startLocation[0], startLocation[1], startLocation[2], 1.0f, false, EPLAYER);
std::vector<GameObject*> gameObjects;
int streak = 0;

void exitGame();

void init() {
	for (unsigned int i = 0; i < 20; ++i) {
		gameObjects.push_back(
				new GameObject(-137.0f + (i * 40), 4.0f, -54.0f, 6, true, ETRUCK));
	}
	gameObjects.push_back(new GameObject(3.0f, 0.0f, -80.0f, 4, false, EFLAG));
//	fogInit();
}

void setObjectStartLocation(float pos[], GameObject *obj) {
	obj->setPosX(pos[0]);
	obj->setPosY(pos[1]);
	obj->setPosZ(pos[2]);
	xTrans = 0;
	zTrans = 0;
	rotation = 0;
}

void renderText(float x, float y, float z, float rotation, std::string str){
	glTranslatef(-55, 10, -55);
	glRotatef(90, 0, 0, 1);
	glColor4f( 1,1,1,1);
	glRasterPos2i(x, y);
	for (unsigned int i = 0; i < str.length(); ++i){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)str[i]);
	}
}

void display() {
	glEnable(GL_DEPTH_TEST | GL_FOG);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//set a white background
	glClearColor(0.27f, 0.65f, 0.86f, 1.0f);

	gluLookAt(cameraX + player.getPosX(), player.getPosY() + 4.0f,
			cameraZ + player.getPosZ(),	//Camera - Eye, your point of view
			player.getPosX(), player.getPosY(), player.getPosZ(), //Center - Object or postion you're looking at
			0, 1, 0);	//Up vector, (-1,0,0) is een kwartslag naar rechts, enz

	displayMap(EBEACH);

	glPushMatrix();
	glTranslatef(player.getPosX() + 0.6, 0.0f, player.getPosZ() - 0.6f);
	glRotatef(rotation, 0.0f, -1.0f, 0.0f);
	player.display();
	glPopMatrix();

	for (unsigned int i = 0; i < gameObjects.size(); ++i) {
		glPushMatrix();
		switch (gameObjects[i]->getObjectType()) {
		case ETRUCK:
			glTranslatef(gameObjects[i]->getPosX(), 0.0f,
					gameObjects[i]->getPosZ());
			if (!gameObjects[i]->getDirection())
				glRotatef(180, 0.0, 1.0, 0.0);
				break;
		case EFLAG:
			glTranslatef(gameObjects[i]->getPosX(), 0.0f, gameObjects[i]->getPosZ());
			break;
		default:
			break;
		}
		gameObjects[i]->display();
		glPopMatrix();
	}
//	glPushMatrix();
//	renderText(player.getPosX(), player.getPosY(), player.getPosZ(), rotation, "message in a bottle");
//	glPopMatrix();
	displayLight();
	glutSwapBuffers();
}
void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (float) width / (float) height, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
}
//Keyboard methods
void keyBoardPressed(unsigned char input, int x, int y) {
	keyStates[input] = true;
}
void keyBoardUp(unsigned char input, int x, int y) {
	keyStates[input] = false;
}
void keyHandler() {
	if (keyStates['w']) {
		player.setPosX(player.getPosX() - sin(-eyeAngle));
		player.setPosZ(player.getPosZ() - cos(-eyeAngle));
		xTrans -= sin(-eyeAngle);
		zTrans -= cos(-eyeAngle);
	}
	if (keyStates['a']) {
		eyeAngle -= 0.06f;
		rotation -= 3.45f;
	}
	if (keyStates['s']) {
		player.setPosX(player.getPosX() + sin(-eyeAngle));
		player.setPosZ(player.getPosZ() + cos(-eyeAngle));
		xTrans += sin(-eyeAngle);
		zTrans += cos(-eyeAngle);

	}
	if (keyStates['d']) {
		eyeAngle += 0.06f;
		rotation += 3.45f;
	}
	if (keyStates[27]) {
		exitGame();
	}
}
//Mouse methods
void mouseButton(int button, int state, int x, int y) {
}
void mouseMotion(int x, int y) {
}

void IdleFunc() {
	keyHandler();
	cameraX = 10 * sin(-eyeAngle);
	cameraZ = 10 * cos(-eyeAngle);
	glutPostRedisplay();
	if (playerOutOfBounds(&player)) {
		streak = 0;
		setObjectStartLocation(startLocation, &player);
		eyeAngle = 0;
	}
	for (unsigned int i = 0; i < gameObjects.size(); ++i) {
		moveObjectOverMap(gameObjects[i]);
		if (collision(gameObjects[i], &player)) {
			switch (gameObjects[i]->getObjectType()) {
			case ETRUCK:
				std::cout << "You Died!" << std::endl;
				streak = 0;
				break;
			case EFLAG:
				std::cout << "You win!" << std::endl;
				++streak;
				break;
			case EPLAYER:
				break;
			}
			setObjectStartLocation(startLocation, &player);
			eyeAngle = 0;
		}
	}
}

void exitGame() {
	gameObjects.clear();
	exit(0);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(Window_Width, Window_Height);
	glutCreateWindow("3D_Computer_Graphics");
//	alutInit(&argc, argv);
	init();
	// Register callbacks:
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//Keyboard functions.
	glutKeyboardFunc(keyBoardPressed);
	glutKeyboardUpFunc(keyBoardUp);
	//Mouse functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);
	glutIdleFunc(IdleFunc);
	// Turn the flow of control over to GLUT
	glutMainLoop();
	return 0;
}
