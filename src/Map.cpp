/*
 * Map.cpp
 *
 *  Created on: May 22, 2014
 *      Author: eilel
 */

#include "../include/Map.h"
#include <GL/glut.h>

void fogInit(){
	//GL Fog
	glEnable(GL_FOG);
	float fogColor[] = {0.24f, 0.58f, 0.76f, 1.0f};
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogf(GL_FOG_START, 60.0f);
	glFogf(GL_FOG_END, 100.0f);
}

void lightingInit(){
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float dif[] = {0.5f, 0.5f, 0.5f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
	float amb[] = {0.2f, 0.2f, 0.2f, 0.1f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
}
void displayLight(){
	float pos[] = {2.0f, 10.0f, 0.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
}

void displayMap( EMapType mapType ){
	glBegin(GL_QUADS);
	switch(mapType){
	case ESTANDARD:
		break;
	case ETRUCKS:
		break;
	case EBEACH:
		mapDrawFloor();
		mapDrawStreet();
		mapDrawTunnel();
		mapDrawWater();
		break;
	}
	glEnd();
}

//Texture to be added!
void mapDrawFloor() {
	glColor3f(1.0f, 1.0f, 0.0f);
	glNormal3f(   0,  1.0f,    0);
	glVertex3d(-100, -0.5f, -100);
	glVertex3d( 100, -0.5f, -100);
	glVertex3d( 100, -0.5f,  30 );
	glVertex3d(-100, -0.5f,  30 );
}
void mapDrawTunnel(){
	glColor3f( 0.0, 0.0, 0.0);
	glVertex3d(-95,-0.6,-50);
	glVertex3d(-95,-0.6,-70);
	glVertex3d(-95,8.0,-70);
	glVertex3d(-95,8.0,-50);

	glColor3f( 0.5, 0.5, 0.5);
	glVertex3d(-95 ,-0.6,-70);
	glVertex3d(-125,-0.6,-90);
	glVertex3d(-125,40.0,-90);
	glVertex3d(-95 ,40.0,-70);

	glVertex3d(-95 ,-0.6,-50);
	glVertex3d(-125,-0.6,-30);
	glVertex3d(-125,21.0,-30);
	glVertex3d(-95, 40.0,-50);

	glVertex3d(-95, 8.0,-50);
	glVertex3d(-95, 8.0,-70);
	glVertex3d(-95, 40.0,-70);
	glVertex3d(-95, 40.0,-50);

	glColor3f( 0.0, 0.0, 0.0);
	glVertex3d(95,-0.6,-50);
	glVertex3d(95,-0.6,-70);
	glVertex3d(95,8.0,-70);
	glVertex3d(95,8.0,-50);

	glColor3f( 0.5, 0.5, 0.5);
	glVertex3d(95 ,-0.6,-70);
	glVertex3d(125,-0.6,-90);
	glVertex3d(125,40.0,-90);
	glVertex3d(95 ,40.0,-70);

	glVertex3d(95 ,-0.6,-50);
	glVertex3d(125,-0.6,-30);
	glVertex3d(125,21.0,-30);
	glVertex3d(95, 40.0,-50);

	glVertex3d(95, 8.0,-50);
	glVertex3d(95, 8.0,-70);
	glVertex3d(95, 40.0,-70);
	glVertex3d(95, 40.0,-50);

}

void mapDrawStreet() {
	glColor3f( 0.501f, 0.501f, 0.501f );
	glNormal3f(   0,  1.0f,    -60);
	glVertex3d(-100, -0.45f, -70);
	glVertex3d( 100, -0.45f, -70);
	glVertex3d( 100, -0.45f, -50);
	glVertex3d(-100, -0.45f, -50);

	glColor3f(1.0f,1.0f,1.0f);
	glVertex3d(-95, -0.4, -62);
	glVertex3d(-85, -0.4, -62);
	glVertex3d(-85, -0.4, -58);
	glVertex3d(-95, -0.4, -58);

	glVertex3d(-65, -0.4, -62);
	glVertex3d(-55, -0.4, -62);
	glVertex3d(-55, -0.4, -58);
	glVertex3d(-65, -0.4, -58);

	glVertex3d(-35, -0.4, -62);
	glVertex3d(-25, -0.4, -62);
	glVertex3d(-25, -0.4, -58);
	glVertex3d(-35, -0.4, -58);

	glVertex3d(-5, -0.4, -62);
	glVertex3d( 5, -0.4, -62);
	glVertex3d( 5, -0.4, -58);
	glVertex3d(-5, -0.4, -58);

	glVertex3d(25, -0.4, -62);
	glVertex3d(35, -0.4, -62);
	glVertex3d(35, -0.4, -58);
	glVertex3d(25, -0.4, -58);

	glVertex3d(55, -0.4, -62);
	glVertex3d(65, -0.4, -62);
	glVertex3d(65, -0.4, -58);
	glVertex3d(55, -0.4, -58);

	glVertex3d(85, -0.4, -62);
	glVertex3d(95, -0.4, -62);
	glVertex3d(95, -0.4, -58);
	glVertex3d(85, -0.4, -58);
}
void mapDrawWater(){
	glColor3f( 0.27f, 0.65f, 0.86f);
	glNormal3f(   0, -1.0f,    0);
	glVertex3d(-300, -0.6f, -300);
	glVertex3d( 300, -0.6f, -300);
	glVertex3d( 300, -0.6f,  300);
	glVertex3d(-300, -0.6f,  300);
}

