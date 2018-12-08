//  Created by Stephanie Cheng
//  10/25/18
//  CS134
//  The header file for ofApp.cpp which declares all variables, objects, and methods

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Sprite.h"
#include "Emitter.h"
#include "SpriteSystem.h"
#include "BaseObject.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "ParticleEmitter.h"
#include "TransformObject.h"

//typedef enum { MoveStop, MoveLeft, MoveRight, MoveUp, MoveDown } MoveDir;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        void moveSprite(MoveDir);
        void stopSprite();
        void checkOctoCollision();
        void checkHeartCollision();
        void checkBossCollision();
        void checkEmittersCollision(vector<Emitter*>);
        void stopEmitters(vector<Emitter*>);
        void clearAll();
        void adjustColorAndEffect(Emitter *);
		void loadVbo();
    
        //Particle emitter for the damage effect
        ParticleEmitter damageEffectEmitter;
        ImpulseRadialForce* radialForce2;
    
        //Particle emitter for the get life effect
        ParticleEmitter getHealthEffectEmitter;
        ImpulseRadialForce* radialForce3;
    
        //For the explosions
        ParticleEmitter pEmitter;
        TurbulenceForce* turbForce;
        GravityForce* gravityForce;
        ImpulseRadialForce* radialForce;
        CyclicForce* cyclicForce;
    
        // textures
        ofTexture  particleTex;
        // shaders
        ofVbo vbo;
        ofShader shader;
    
        ofColor particleColor;
    
        // Game emitters
        Emitter* emitter;
        Emitter* heartEmitter;
    
        Emitter* octoEmitter;
    
        Emitter* whaleEmitter1;
        Emitter* whaleEmitter2;
        Emitter* whaleEmitter3;
        Emitter* whaleEmitter4;
        Emitter* whaleEmitter5;
        Emitter* whaleEmitter6;
        vector<Emitter*> whaleEmitters;
    
        Emitter* birdEmitter1;
        Emitter* birdEmitter2;
        Emitter* birdEmitter3;
        Emitter* birdEmitter4;
        Emitter* birdEmitter5;
        Emitter* birdEmitter6;
        Emitter* birdEmitter7;
        Emitter* birdEmitter8;
        Emitter* birdEmitter9;
        vector<Emitter*> birdEmitters;
        float lastSpawnedBird;
    
    
        Emitter* squidEmitter1;
        Emitter* squidEmitter2;
        Emitter* squidEmitter3;
        Emitter* squidEmitter4;
        Emitter* squidEmitter5;
        vector<Emitter*> squidEmitters;
        float lastSpawnedSquid;
    
        Emitter* devilEmitter1;
        Emitter* devilEmitter2;
        Emitter* devilEmitter3;
        vector<Emitter*> devilEmitters;
    
        Emitter* bossEmitter;
        float bossAppearTime;
    
        ofxFloatSlider rateSlider;
        ofxFloatSlider lifeSlider;
        ofxFloatSlider velXSlider;
        ofxFloatSlider velYSlider;
        ofxLabel screenSize;
    
        ofxPanel gui;
        ofImage background;
        ofImage background2;
        ofSoundPlayer bgSound;
        ofSoundPlayer winSound;
        ofSoundPlayer loseSound;
        ofSoundPlayer bossSound;
    
        ofVec2f bgPos1;
        ofVec2f bgPos2;
    
        float timeWon;
        int score;
        int level;
        int life;
        int bossLife;
        float gameActivateTime;
        string lifeString;
        string scoreString;
        string levelString;
        bool gameActivated;
        bool win;
        bool lose;
        bool showLoseMessage;
        bool showWinMessage;
        bool bossLevel;
        bool leftPressed;
        bool rightPressed;
        bool upPressed;
        bool downPressed;
        bool showTitle;
    
        ofImage lifeImage;
        ofImage healthBox;
        ofImage healthBar;
        ofTrueTypeFont titleDisplay;
        ofTrueTypeFont titleDisplay2;
        ofTrueTypeFont scoreDisplay;
        ofTrueTypeFont levelDisplay;
        ofTrueTypeFont lifeDisplay;
        ofTrueTypeFont winDisplay;
        ofTrueTypeFont loseDisplay;
        ofTrueTypeFont finalScoreDisplay;
        ofTrueTypeFont pressSpaceDisplay;
    
        ofSoundPlayer damagedSound;
        ofSoundPlayer bossDamagedSound;
        ofSoundPlayer bossDefeatedSound;
		

};
