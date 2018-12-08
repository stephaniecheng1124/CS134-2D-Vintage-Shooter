//  Created by Stephanie Cheng
//  9/20/18
//  CS134
//  The emitter class

//  Emitter.cpp
//  spriteEmitter

#include <stdio.h>
#include "ofApp.h"
#include "ofMain.h"
#include "SpriteSystem.h"
#include "Sprite.h"
#include "Emitter.h"
#include "BaseObject.h"


Emitter::Emitter(SpriteSystem* s) {
    
    //Initialize Emitter stuff

    sys = s;                                    //Assign a spritesystem to this emitter
    rate = 1;                                   //Inteval between each emission of fireball (in seconds)
    velocity = ofVec3f(0, 0, 0);                // Velocity of fireballs in pixels/sec
    speed = 120;                                // Speed of dragon in screenspace coordinates per second  (pixels)
    //float lifespan;                           //Set this later when we figure out lives for turret
    started = false;                            //Change to true when spacebar is pressed
    lastSpawned = 0;                            //Milliseconds after program load since the last fireball spawn
    drawable = true;                            //Umm I dunno what's this!
    haveChildImage = false;                     //If no image, draw the rectangle
    haveImage = false;                          //If no image, draw the rectangle
    width = 55;                                //Default emitter width & height
    height = 55;
    childWidth = 10;                            //Default projectile width & height
    childHeight = 10;
    autoMovement = false;
    autoRight = true;
    sound2Loaded = false;
    isEnemyEmitter = false;
    sinMovement = false;
    
    //Initialize base object stuff
    scale.x = 1.0;
    scale.y = 1.0;
    rot = 0;
    
}

void Emitter::draw() {
    if(!haveImage) {
        ofSetColor(255, 255, 255);
        ofDrawRectangle(trans,width,height);
    }
    else {
        image.draw(trans.x, trans.y);
    }
}

void Emitter::emit() {
    
    //Start firing according to the spawn rate
    if (started && ofGetElapsedTimef() - lastSpawned > rate) {
        Sprite child;
        child.name = "Projectile";
        child.image = childImage;
        child.velocity = velocity;
        child.width = childWidth;
        child.height = childHeight;
        child.lifespan = lifespan;
        child.haveImage = haveChildImage;
        child.sound2Loaded = sound2Loaded;
        child.sound2 = sound2;
        child.sinMovement = sinMovement;
        //cout << "Making new child: " << name << endl;
        //Set spawn location depending on which emitter it is
        if (name != "Boss") {
            child.setPosition(ofVec2f(this->trans.x + (width/2) - (child.width/2), this->trans.y - child.height));
        }
        else {
            child.setPosition(ofVec2f(this->trans.x + (width/2) - (child.width/2) + 38, this->trans.y + 28));
        }
        lastSpawned = ofGetElapsedTimef();
        sys -> add(child);
        
        //Play sound only if it is the dragon emitter or boss emitter
        if (name == "Boss" || (!autoMovement && !isEnemyEmitter)) {
           sound.play();
        }
        lastSpawned = ofGetElapsedTimef();
    }
    
    
}

void Emitter::start() {
    started = true;
}

void Emitter::stop() {
    started = false;
}

void Emitter::autoMove() {
    autoMovement = true;
}

void Emitter::autoMoveStop() {
    autoMovement = false;
}

void Emitter::setLifespan(float life) {
    lifespan = life;
}

void Emitter::setVelocity(ofVec3f vel) {
    velocity = vel;
}

void Emitter::setChildImage(ofImage i) {
    childImage = i;
    haveChildImage = true;
}

void Emitter::setImage(ofImage i) {
    image = i;
    haveImage = true;
}

void Emitter::setChildSize(float w, float h) {
    childWidth = w;
    childHeight = h;
}

void Emitter::setRate(float r) {
    rate = r;
}

void Emitter::setSpeed(float s) {
    speed = s;
}

float Emitter::maxDistPerFrame() {
    return 0;
}

void Emitter::update() {
    
    float dist = speed * 1 / ofGetFrameRate();
    ofVec3f dir;
    
    if (autoMovement && started) {
        emit();

        //Set move direction
        if (autoRight) {
            moveDir = MoveRight;
        }
        else {
            moveDir = MoveLeft;
        }
    }
    else if (isEnemyEmitter) {
         emit();
    }

    //Check which direction the emitter is moving
    switch (moveDir)
    {
        case MoveStop:
            dir = ofVec3f(0, 0, 0);
            break;
        case MoveUp:
            
            dir = ofVec3f(0, -dist, 0);
            break;
        case MoveDown:
            dir = ofVec3f(0, dist, 0);
            break;
        case MoveLeft:
            dir = ofVec3f(-dist, 0, 0);
            break;
        case MoveRight:
            dir = ofVec3f(dist, 0, 0);
            break;
    }
    
    
    
    
    //Check if the emitter will move off the screen
    if(trans.x + dir.x <= (ofGetWindowWidth() - width) && trans.x + dir.x >= 0 && trans.y + dir.y <= (ofGetWindowHeight() - height) && trans.y + dir.y >= 0)
    {
        //Move emitter in specified direction by adding the direction vector
        trans += dir;
    }
    else
    {
        //Position doesn't change
        trans += ofVec3f(0, 0, 0);
        
        //If the automoving emitter reaches the end of one side, switch directions
        if(autoMovement) {
            if (autoRight) {
                autoRight = false;
            }
            else {
                autoRight = true;
            }
        }
    }
    

    sys -> update();
    
}












