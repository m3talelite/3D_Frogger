/*
 * Map.h
 *
 *  Created on: May 22, 2014
 *      Author: eilel
 */

#ifndef MAP_H_
#define MAP_H_

enum EMapType{
	ESTANDARD,
	ETRUCKS,
	EBEACH
};

void fogInit();
void lightingInit();
void displayLight();

void displayMap( EMapType );
void mapDrawFloor();
void mapDrawTunnel();
void mapDrawStreet();
void mapDrawWater();

#endif /* MAP_H_ */
