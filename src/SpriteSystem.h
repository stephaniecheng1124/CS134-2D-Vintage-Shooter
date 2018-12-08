//
//  SpriteSystem.h
//  spriteEmitter
//
//  Created by Stephanie Cheng on 9/20/18.
//
#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "Sprite.h"
#include "BaseObject.h"

//  Manages all Sprites in a system.  You can create multiple systems
//
class SpriteSystem  {
public:
    void add(Sprite);
    void remove(int);
    void update();
    void draw();
    vector<Sprite> sprites;
    
    
};

