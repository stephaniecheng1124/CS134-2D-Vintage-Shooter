#pragma once

//
//  BaseObject.h
//  spriteEmitter
//
//  Created by Stephanie Cheng on 9/22/18.
//


// This is a base object that all drawable object inherit from
// It is possible this will be replaced by ofNode when we move to 3D
//
class BaseObject {
public:
    BaseObject();
    ofVec2f trans, scale;
    float    rot;
    bool    bSelected;
    void setPosition(ofVec2f p) { trans = p;  }
};
