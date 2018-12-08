//
//  Emitter.h
//  spriteEmitter
//
//  Created by Stephanie Cheng on 9/20/18.
//
#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "ofApp.h"
#include "SpriteSystem.h"
#include "Sprite.h"

typedef enum { MoveStop, MoveLeft, MoveRight, MoveUp, MoveDown } MoveDir;

//  General purpose Emitter class for emitting sprites
//  This works similar to a Particle emitter
//
class Emitter: public BaseObject {
public:
    Emitter(SpriteSystem *);
    void draw();
    void start();
    void emit();
    void stop();
    void setLifespan(float);
    void setVelocity(ofVec3f);
    void setChildImage(ofImage);
    void setChildSize(float w, float h);
    void setImage(ofImage);
    void setRate(float);
    void setSpeed(float);
    float maxDistPerFrame();
    void update();
    void autoMove();
    void autoMoveStop();
    
    SpriteSystem *sys;
    
    string name;
    float rate;
    float speed;
    ofVec3f velocity;
    MoveDir moveDir;
    float lifespan;
    bool started;
    bool autoMovement;
    bool sinMovement;
    bool autoRight;
    float lastSpawned;
    ofImage childImage;
    ofImage image;
    ofSoundPlayer sound;
    ofSoundPlayer sound2;
    bool sound2Loaded;
    bool drawable;
    bool haveChildImage;
    bool haveImage;
    float width, height;
    float childWidth, childHeight;
    bool isEnemyEmitter;
    
};
