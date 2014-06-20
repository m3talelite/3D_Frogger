/*
 * GameObject.h
 *
 *  Created on: May 20, 2014
 *      Author: eilel
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "ObjectLoader.h"

enum EObjectType{
	ETRUCK,
	EPLAYER,
	EFLAG
};

class GameObject{
public:
	GameObject( float x, float y, float z, float siz, bool dir, EObjectType );
	~GameObject();

	float getPosX()  { return x; }
	float getPosY()  { return y; }
	float getPosZ()  { return z; }
	float getSize()  { return size; }
	bool getDirection() { return direction; }
	EObjectType getObjectType() { return objectType; }

	void setPosX ( float );
	void setPosY ( float );
	void setPosZ ( float );
	void setSize ( float );
	void setDirection( bool );

	void display();

	ObjModel *model;
private:
	float x, y, z;
	float size;
	bool direction;
	EObjectType objectType;
};

void moveObjectOverMap( GameObject* );
bool collision( GameObject*, GameObject* );
bool playerOutOfBounds( GameObject* player );
void setObjectStartLocation( float[], GameObject* );

#endif /* GAMEOBJECT_H_ */
