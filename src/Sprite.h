//
//  Sprite.h
//  spriteEmitter
//
//  Created by Stephanie Cheng on 9/20/18.
//
#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "ofApp.h"
#include "BaseObject.h"






//  General Sprite class  (similar to a Particle)
//
class Sprite : public BaseObject {
public:
    Sprite();
    void draw();
    float age();
    void setImage(ofImage);
    float speed;    //   in pixels/sec
    ofVec3f velocity; // in pixels/sec
    ofImage image;
    float birthtime; // elapsed time in ms
    float lifespan;  //  time in ms
    string name;
    bool haveImage;
    float width, height;
    bool sound2Loaded;
    bool sinMovement;
    ofSoundPlayer sound2;
    bool manualPop;

};
