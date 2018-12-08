//
//  Sprite.cpp
//  spriteEmitter
//
//  Created by Stephanie Cheng on 9/20/18.
//

#include <stdio.h>
#include "ofApp.h"
#include "ofMain.h"
#include "SpriteSystem.h"
#include "Sprite.h"
#include "Emitter.h"
#include "BaseObject.h"


Sprite::Sprite() {
    
    //Initialize base obj stuff
    
    //Change the trans location later when the emitter creates the sprite object
    trans.x = 0;
    trans.y = 0;
    scale.x = 1.0;
    scale.y = 1.0;
    rot = 0;
    
    //Initialize Sprite variables
    speed = 0;                              //  default speed in pixels/sec
    velocity = ofVec3f(0, 0);              // default velocity in pixels/sec
    birthtime = ofGetElapsedTimeMillis(); // elapsed time since spawning in ms
    lifespan = 2000;                     // time for sprite to live in ms
    //string name;                      // already set this in the emitter
   
    
    haveImage = false;               // see if child has an image loaded
    sound2Loaded = false;                       //Default sound 2 not loaded..only heart emitter has it
    manualPop = false;               //No burst noise if dragon pops bubble.. a different pop will be played

    sinMovement = false;            //Use this for the devil emitter
}


//Draw the sprite
void Sprite::draw() {
    if(!haveImage) {
        ofSetColor(255, 255, 255);
        ofDrawRectangle(trans,width,height);
    }
    else {
        image.draw(trans.x, trans.y);
    }
    
}

//Return the sprite's age in ms
float Sprite::age() {
    return ofGetElapsedTimeMillis() - birthtime;
}

//Set the image of the sprite
void Sprite::setImage(ofImage i) {
    image = i;
    haveImage = true;
}


