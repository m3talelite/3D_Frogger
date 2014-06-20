/*
 * Cube.cpp
 *
 *  Created on: May 20, 2014
 *      Author: eilel
 */

#include "../include/GameObject.h"
#include "../include/ObjectLoader.h"
#include <GL/glut.h>
#include <iostream>
#include <time.h>

GameObject::GameObject(float x, float y, float z, float size, bool dir, EObjectType objTyp) :
		x(x), y(y), z(z), size(size), direction(dir), objectType(objTyp) {
	switch(this->objectType){
	case EPLAYER:
		this->model = new ObjModel("./Frog1.obj");
		break;
	case ETRUCK:
		this->model = new ObjModel("./trk2.obj");
		break;
	case EFLAG:
		this->model = new ObjModel("./flag.obj");
		break;
	}
}
GameObject::~GameObject() {
	std::cout << "Removed cube" << std::endl;
}

void GameObject::setPosX(float x) 		{ this->x = x; }
void GameObject::setPosY(float y)		{ this->y = y; }
void GameObject::setPosZ(float z) 		{ this->z = z; }
void GameObject::setSize(float siz) 	{ this->size = siz; }
void GameObject::setDirection(bool dir)	{ this->direction = dir; }

void GameObject::display() {
	glBegin(GL_QUADS);
	switch(this->objectType){
	case EPLAYER:
		glColor3f(0.0,1.0,0.0);
		model->draw();
		break;
	case ETRUCK:
		glColor3f(0.7f,0.7f,0.7f);
		model->draw();
		break;
	case EFLAG:
		glColor3f(0.8f, 0.0f, 0.0f);
		model->draw();
		break;
	default:
		glBegin(GL_QUADS);
		glColor3f(1.0, 1.0, 1.0);
		glNormal3f( x,  y, z + 1);
		glVertex3d(size / 2 + x, -size / 2, size / 2 + z);
		glVertex3d(size / 2 + x, size / 2, size / 2 + z);
		glVertex3d(-size / 2 + x, size / 2, size / 2 + z);
		glVertex3d(-size / 2 + x, -size / 2, size / 2 + z);
		// face 2
	//	glColor3f(0.0, 0.0, 0.0);
		glNormal3f( x,  y, z - 1);
		glVertex3d(size / 2 + x, -size / 2, -size / 2 + z);
		glVertex3d(size / 2 + x, size / 2, -size / 2 + z);
		glVertex3d(-size / 2 + x, size / 2, -size / 2 + z);
		glVertex3d(-size / 2 + x, -size / 2, -size / 2 + z);
		// face 3
	//	glColor3f(1.0, 1.0, 0.0);
		glNormal3f( x + 1,  y, z);
		glVertex3d(size / 2 + x, size / 2, size / 2 + z);
		glVertex3d(size / 2 + x, -size / 2, size / 2 + z);
		glVertex3d(size / 2 + x, -size / 2, -size / 2 + z);
		glVertex3d(size / 2 + x, size / 2, -size / 2 + z);
		// face 4
	//	glColor3f(0.0, 1.0, 1.0);
		glNormal3f( x - 1,  y, z);
		glVertex3d(-size / 2 + x, -size / 2, size / 2 + z);
		glVertex3d(-size / 2 + x, size / 2, size / 2 + z);
		glVertex3d(-size / 2 + x, size / 2, -size / 2 + z);
		glVertex3d(-size / 2 + x, -size / 2, -size / 2 + z);
		// face 5
	//	glColor3f(0.0, 0.0, 1.0);
		glNormal3f( x,  y + 1, z);
		glVertex3d(size / 2 + x, size / 2, size / 2 + z);
		glVertex3d(size / 2 + x, size / 2, -size / 2 + z);
		glVertex3d(-size / 2 + x, size / 2, -size / 2 + z);
		glVertex3d(-size / 2 + x, size / 2, size / 2 + z);
		// face 6
	//	glColor3f(1.0, 0.0, 1.0);
		glNormal3f( x,  y - 1, z);
		glVertex3d(size / 2 + x, -size / 2, size / 2 + z);
		glVertex3d(size / 2 + x, -size / 2, -size / 2 + z);
		glVertex3d(-size / 2 + x, -size / 2, -size / 2 + z);
		glVertex3d(-size / 2 + x, -size / 2, size / 2 + z);
		glEnd();

		break;
	}


}

void moveObjectOverMap(GameObject* object) {
	if(object->getObjectType() != ETRUCK){
		return;
	}
	if (object->getDirection()) {
		if (object->getPosX() > 120) {
			object->setDirection(!object->getDirection());
			object->setPosZ(object->getPosZ() - 12.0f);
		}
		object->setPosX(object->getPosX() + 0.6f);
	} else {
		if (object->getPosX() < -120) {
			object->setDirection(!object->getDirection());
			object->setPosZ(object->getPosZ() + 12.0f);
		}
		object->setPosX(object->getPosX() - 0.6f);
	}
}

bool collision(GameObject *object_1, GameObject *object_2){
		if (		(object_2->getPosX() - (object_2->getSize() ) ) > (object_1->getPosX() - (object_1->getSize() ) )
				&&  (object_2->getPosX() + (object_2->getSize() ) ) < (object_1->getPosX() + (object_1->getSize()  ))
				&&  (object_2->getPosZ() - (object_2->getSize() ) ) > (object_1->getPosZ() - (object_1->getSize()  ))
				&&  (object_2->getPosZ() + (object_2->getSize() ) ) < (object_1->getPosZ() + (object_1->getSize()  ))
				)	{
			return true;
		}
		return false;
}

bool playerOutOfBounds(GameObject *player){
	if(player->getPosX() > 100.0f
			||player->getPosX() < -100.0f
			||player->getPosZ() > 30.0f
			||player->getPosZ() < -100.0f)
		return true;
	return false;
}


