#include "ofApp.h"
#include "ofMain.h"
#include "SpriteSystem.h"
#include "Sprite.h"
#include "Emitter.h"
#include "BaseObject.h"




//  Add a Sprite to the Sprite System
//
void SpriteSystem::add(Sprite s) {
    sprites.push_back(s);
}

// Remove a sprite from the sprite system. Note that this function is not currently
// used. The typical case is that sprites automatically get removed when the reach
// their lifespan.
//
void SpriteSystem::remove(int i) {
    sprites.erase(sprites.begin() + i);
}


//  Update the SpriteSystem by checking which sprites have exceeded their
//  lifespan (and deleting).  Also the sprite is moved to its next
//  location based on velocity and direction.
//
void SpriteSystem::update() {

    if (sprites.size() == 0) return;
    vector<Sprite>::iterator s = sprites.begin();
    vector<Sprite>::iterator tmp;

    // check which sprites have exceed their lifespan and delete
    // from list.  When deleting multiple objects from a vector while
    // traversing at the same time, use an iterator.
    //
    while (s != sprites.end()) {
        if (s->lifespan != -1 && s->age() > s->lifespan) {
            if(s -> sound2Loaded && !(s -> manualPop)) {s -> sound2.play();}
            tmp = sprites.erase(s);
            s = tmp;
            
        }
        else s++;
    }

    //  Move sprite
    //
    for (int i = 0; i < sprites.size(); i++) {
        sprites[i].trans += sprites[i].velocity / ofGetFrameRate();
        if (sprites[i].sinMovement) {
            sprites[i].trans += ofVec3f(sin(sprites[i].birthtime + ofGetElapsedTimef() * 2 )/1.2, 0, 0);
        }
    }
}


//  Render all the sprites
//
void SpriteSystem::draw() {
    for (int i = 0; i < sprites.size(); i++) {
        //cout << "drawing sprite: " << endl;
        sprites[i].draw();
    }
}


