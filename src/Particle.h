//  Modified by Stephanie Cheng
//  11/1/2018
//  CS134
//  This file is the header file for the particle

#pragma once
#include "ofMain.h"

class ParticleForceField;

class Particle {
public:
	Particle();

	ofVec3f position;
	ofVec3f velocity;
	ofVec3f acceleration;
	ofVec3f forces;
	float	damping;
	float   mass;
	float   lifespan;
	float   radius;
	float   birthtime;
	void    integrate();
	void    draw();
	float   age();        // sec
	ofColor color;
    ofImage image;
    bool    hasImage;
};


