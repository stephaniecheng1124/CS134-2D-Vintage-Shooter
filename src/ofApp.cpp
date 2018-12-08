//  Created by Stephanie Cheng
//  10/30/2018
//  CS134
//  This file sets up all the emitters and the game logic
//  This includes the particle emitters and the sprite emitters

#include "ofApp.h"
#include "ofMain.h"
#include "SpriteSystem.h"
#include "Sprite.h"
#include "Emitter.h"
#include "BaseObject.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "ParticleEmitter.h"
#include "TransformObject.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    //Set up the particle emitter stuff
    // texture loading
    //
    ofDisableArbTex();     // disable rectangular textures
    
    // load textures
    //
    if (!ofLoadImage(particleTex, "images/dot.png")) {
        cout << "Particle Texture File: images/dot.png not found" << endl;
        ofExit();
    }
    
    // load the shader
    //
    #ifdef TARGET_OPENGLES
        shader.load("shaders_gles/shader");
    #else
        shader.load("shaders/shader");
    #endif
    
    //Set particle color to red first
    particleColor = ofColor(255, 98, 20);
    
    //Create Forces
    turbForce = new TurbulenceForce(ofVec3f(-20, -20, -20), ofVec3f(20, 20, 20));
    gravityForce = new GravityForce(ofVec3f(0, -20, 0));
    radialForce = new ImpulseRadialForce(10);
    radialForce2 = new ImpulseRadialForce(5);
    radialForce3 = new ImpulseRadialForce(5);
    
    //Add Forces
    pEmitter.sys->addForce(turbForce);
    pEmitter.sys->addForce(gravityForce);
    pEmitter.sys->addForce(radialForce);
    
    //Emitter settings
    pEmitter.setEmitterType(RadialEmitter);
    pEmitter.setOneShot(true);
    pEmitter.setRandomLife(true);
    pEmitter.setLifespanRange(ofVec2f(0.5, 1));
    pEmitter.setPosition(ofVec2f(ofGetWindowWidth()/2, ofGetWindowHeight()/2));
    pEmitter.setVelocity(ofVec3f(150, 0, 0));
    pEmitter.setGroupSize(20);
    pEmitter.setParticleRadius(5);
    
    //Set up damage effect particle emitter
    damageEffectEmitter.sys->addForce(radialForce2);
    damageEffectEmitter.setEmitterType(RadialEmitter);
    damageEffectEmitter.setParticleRadius(5);
    damageEffectEmitter.setOneShot(true);
    damageEffectEmitter.setGroupSize(1);
    damageEffectEmitter.setLifespan(1);
    damageEffectEmitter.setVelocity(ofVec3f(60, 0, 0));
    damageEffectEmitter.setPosition(ofVec2f(0,0));
    if (damageEffectEmitter.image.load("images/HeartMinus.png")) {
        damageEffectEmitter.haveImage = true;
    }
    
    //Set up get health effect particle emitter
    getHealthEffectEmitter.sys->addForce(radialForce2);
    getHealthEffectEmitter.setEmitterType(RadialEmitter);
    getHealthEffectEmitter.setParticleRadius(5);
    getHealthEffectEmitter.setOneShot(true);
    getHealthEffectEmitter.setGroupSize(1);
    getHealthEffectEmitter.setLifespan(1);
    getHealthEffectEmitter.setVelocity(ofVec3f(60, 0, 0));
    getHealthEffectEmitter.setPosition(ofVec2f(0,0));
    if (getHealthEffectEmitter.image.load("images/HeartPlus.png")) {
        getHealthEffectEmitter.haveImage = true;
    }
    
    //Score and other stats
    score = 0;
    scoreString = ofToString(score);
    scoreDisplay.load("images/digital.ttf", 20);
    level = 0;
    levelString = ofToString(level);
    levelDisplay.load("images/digital.ttf", 20);
    gameActivated = false;
    lastSpawnedBird = 0;
    lastSpawnedSquid = 0;
    win = false;
    lose = false;
    showLoseMessage = false;
    showWinMessage = false;
    showTitle = true;
    titleDisplay.load("images/gunmetl.ttf", 110);
    titleDisplay2.load("images/gunmetl.ttf", 110);
    winDisplay.load("images/digital.ttf", 90);
    loseDisplay.load("images/digital.ttf", 90);
    finalScoreDisplay.load("images/digital.ttf", 30);
    pressSpaceDisplay.load("images/digital.ttf", 40);
    
    life = 5;
    lifeString = ofToString(life);
    lifeImage.load("images/Lives.png");
    lifeDisplay.load("images/digital.ttf", 20);
    
    timeWon= 0;
    bossLife = 25;
    bossAppearTime = 0;
    
    //Create the dragon, heart emitter, and enemy emitters
    emitter = new Emitter(new SpriteSystem());
    octoEmitter = new Emitter(new SpriteSystem());
    heartEmitter = new Emitter(new SpriteSystem());
    
    whaleEmitter1 = new Emitter(new SpriteSystem());
    whaleEmitter2 = new Emitter(new SpriteSystem());
    whaleEmitter3 = new Emitter(new SpriteSystem());
    whaleEmitter4 = new Emitter(new SpriteSystem());
    whaleEmitter5 = new Emitter(new SpriteSystem());
    whaleEmitter6 = new Emitter(new SpriteSystem());
    whaleEmitters.push_back(whaleEmitter1);
    whaleEmitters.push_back(whaleEmitter2);
    whaleEmitters.push_back(whaleEmitter3);
    whaleEmitters.push_back(whaleEmitter4);
    whaleEmitters.push_back(whaleEmitter5);
    whaleEmitters.push_back(whaleEmitter6);
    
    //put these into vectors later
    birdEmitter1 = new Emitter(new SpriteSystem());
    birdEmitter2 = new Emitter(new SpriteSystem());
    birdEmitter3 = new Emitter(new SpriteSystem());
    birdEmitter4 = new Emitter(new SpriteSystem());
    birdEmitter5 = new Emitter(new SpriteSystem());
    birdEmitter6 = new Emitter(new SpriteSystem());
    birdEmitter7 = new Emitter(new SpriteSystem());
    birdEmitter8 = new Emitter(new SpriteSystem());
    birdEmitter9 = new Emitter(new SpriteSystem());
    birdEmitters.push_back(birdEmitter1);
    birdEmitters.push_back(birdEmitter2);
    birdEmitters.push_back(birdEmitter3);
    birdEmitters.push_back(birdEmitter4);
    birdEmitters.push_back(birdEmitter5);
    birdEmitters.push_back(birdEmitter6);
    birdEmitters.push_back(birdEmitter7);
    birdEmitters.push_back(birdEmitter8);
    birdEmitters.push_back(birdEmitter9);
    
    
    squidEmitter1 = new Emitter(new SpriteSystem());
    squidEmitter2 = new Emitter(new SpriteSystem());
    squidEmitter3 = new Emitter(new SpriteSystem());
    squidEmitter4 = new Emitter(new SpriteSystem());
    squidEmitter5 = new Emitter(new SpriteSystem());
    squidEmitters.push_back(squidEmitter1);
    squidEmitters.push_back(squidEmitter2);
    squidEmitters.push_back(squidEmitter3);
    squidEmitters.push_back(squidEmitter4);
    squidEmitters.push_back(squidEmitter5);
   
    
    devilEmitter1 = new Emitter(new SpriteSystem());
    devilEmitter2 = new Emitter(new SpriteSystem());
    devilEmitter3 = new Emitter(new SpriteSystem());
    devilEmitters.push_back(devilEmitter1);
    devilEmitters.push_back(devilEmitter2);
    devilEmitters.push_back(devilEmitter3);
    
    bossEmitter = new Emitter(new SpriteSystem());
    
    /////////////////////////////////////////////////////////////////////////////Setup children////////////////////
    
    //Set an image for the flame children
    if (emitter -> childImage.load("images/flame.png")) {
        emitter -> haveChildImage = true;
        emitter -> childWidth = emitter -> childImage.getWidth();
        emitter -> childHeight = emitter -> childImage.getHeight();
    }
    //Set an image for the heart children
    if (heartEmitter -> childImage.load("images/HeartLife3.png")) {
        heartEmitter -> haveChildImage = true;
        heartEmitter -> childWidth = heartEmitter -> childImage.getWidth();
        heartEmitter -> childHeight = heartEmitter -> childImage.getHeight();
    }
    //Set an image for the octo children
    if (octoEmitter -> childImage.load("images/radarOctopus.png")) {
        octoEmitter -> haveChildImage = true;
        octoEmitter -> childWidth = octoEmitter -> childImage.getWidth();
        octoEmitter -> childHeight = octoEmitter -> childImage.getHeight();
    }
    //Set an image for the whale children
    bool left = true;
    for (std::size_t i = 0; i < whaleEmitters.size(); i++) {
        if(left) {
            if (whaleEmitters[i] -> childImage.load("images/WhaleLeft.png")) {
                whaleEmitters[i] -> haveChildImage = true;
                whaleEmitters[i] -> childWidth = whaleEmitters[i] -> childImage.getWidth();
                whaleEmitters[i] -> childHeight = whaleEmitters[i] -> childImage.getHeight();
            }
            left = false;
        }
        else {
            if (whaleEmitters[i] -> childImage.load("images/WhaleRight.png")) {
                whaleEmitters[i] -> haveChildImage = true;
                whaleEmitters[i] -> childWidth = whaleEmitters[i] -> childImage.getWidth();
                whaleEmitters[i] -> childHeight = whaleEmitters[i] -> childImage.getHeight();
            }
            left = true;
        }
        
    }
    //Set an image for the bird children
    for (std::size_t i = 0; i < birdEmitters.size(); i++) {
        if (birdEmitters[i] -> childImage.load("images/Seagull.png")) {
            birdEmitters[i] -> haveChildImage = true;
            birdEmitters[i] -> childWidth = birdEmitters[i] -> childImage.getWidth();
            birdEmitters[i] -> childHeight = birdEmitters[i] -> childImage.getHeight();
        }
    }
    //Set an image for the squid children
    for (std::size_t i = 0; i < squidEmitters.size(); i++) {
        if (squidEmitters[i] -> childImage.load("images/Squid.png")) {
            squidEmitters[i] -> haveChildImage = true;
            squidEmitters[i] -> childWidth = squidEmitters[i] -> childImage.getWidth();
            squidEmitters[i] -> childHeight = squidEmitters[i] -> childImage.getHeight();
        }
    }
    //Set an image for the devil children
    for (std::size_t i = 0; i < devilEmitters.size(); i++) {
        if (devilEmitters[i] -> childImage.load("images/Devil.png")) {
            devilEmitters[i] -> haveChildImage = true;
            devilEmitters[i] -> childWidth = devilEmitters[i] -> childImage.getWidth();
            devilEmitters[i] -> childHeight = devilEmitters[i] -> childImage.getHeight();
        }
    }
    //Set image for the boss children
    if (bossEmitter -> childImage.load("images/Fire.png")) {
        bossEmitter -> haveChildImage = true;
        bossEmitter -> childWidth = bossEmitter -> childImage.getWidth();
        bossEmitter -> childHeight = bossEmitter -> childImage.getHeight();
    }
    
    ////////////////////////////////////////////////////////////////////////////Setup Emitter START POSITION and Images//////////////////
    
    //Set an image for the dragon emitter
    if (emitter -> image.load("images/dragon.png")) {
        emitter -> haveImage = true;
        emitter -> width = emitter -> image.getWidth();
        emitter -> height = emitter -> image.getHeight();
    }
    //Start: Position the dragon at the bottom middle of the screen
    emitter -> setPosition(ofVec2f(ofGetWindowWidth()/2 - (emitter -> width/2), ofGetWindowHeight() -(emitter -> height)));
    emitter -> moveDir = MoveStop;      //Start off without movement
    
    //Start: Position the octopus spawner at the top left of the screen
    octoEmitter -> setPosition(ofVec2f(ofGetWindowWidth()/2 - (octoEmitter -> width/2), 0));
    
    //Start: Position the heart spawner at the top left of the screen
    heartEmitter -> setPosition(ofVec2f(ofGetWindowWidth()/2 - (heartEmitter -> width/2), 0));
   
    //Start: Position the whale spawners at various locations at the side of the screen
    bool leftSide = true;
    float yCoord = 170;
    float increment = (ofGetWindowHeight() - 100)/6;  //Don't count the top 100 pixels..we want to leave a gap at the top
    for (std::size_t i = 0; i < whaleEmitters.size(); i++) {
        if (leftSide) {
            whaleEmitters[i] -> setPosition(ofVec2f(0 - whaleEmitters[i] -> width, yCoord));
            yCoord += increment;
            leftSide = false;
        }
        else {
            whaleEmitters[i] -> setPosition(ofVec2f(ofGetWindowWidth(), yCoord));
            yCoord += increment;
            leftSide = true;
        }
    }
    
    //Start: Position the bird spawners at various locations at the top of the screen
    float xCoord = 8.5;
    float incrementBird = ofGetWindowWidth()/9;
    for (std::size_t i = 0; i < birdEmitters.size(); i++) {
        birdEmitters[i] -> setPosition(ofVec2f(xCoord, 0 - birdEmitters[i] -> width ));
        xCoord += incrementBird;
    }
    
    //Start: Position the squid spawners at various locations at the top of the screen
    float xCoordSquid = 30;
    float incrementSquid = ofGetWindowWidth()/5;
    for (std::size_t i = 0; i < squidEmitters.size(); i++) {
        squidEmitters[i] -> setPosition(ofVec2f(xCoordSquid, 0- squidEmitters[i] -> width));
        xCoordSquid += incrementSquid;
    }
    
    //Start: Position the devil spawners at various locations at the top of the screen
    float xCoordDevil = 30;
    float incrementDevil = ofGetWindowWidth()/2.5;
    for (std::size_t i = 0; i < devilEmitters.size(); i++) {
        devilEmitters[i] -> setPosition(ofVec2f(xCoordDevil, 0 - devilEmitters[i] -> width));
        xCoordDevil += incrementDevil;
    }
    
    //Set an image for the boss emitter
    if (bossEmitter -> image.load("images/Ship.png")) {
        bossEmitter -> haveImage = true;
        bossEmitter -> width = bossEmitter -> image.getWidth();
        bossEmitter -> height = bossEmitter -> image.getHeight();
    }
    //Start: Position the boss spawner at the top left of the screen
    //bossEmitter -> setPosition(ofVec2f(ofGetWindowWidth()/2 - (bossEmitter -> width/2), 10));
    bossEmitter -> setPosition(ofVec2f(0, -bossEmitter -> height));
    
    ///////////////////////////////////////////////////////////////////////////////////Load sounds for emitters/////////////////
    emitter -> sound.load("sounds/flamestrike.mp3");
    octoEmitter -> sound.load("sounds/explosion.mp3");
    heartEmitter -> sound.load("sounds/bubble.mp3");
    heartEmitter -> sound2.load("sounds/pop.mp3");
    heartEmitter -> sound2Loaded = true;
    for (std::size_t i = 0; i < whaleEmitters.size() - 1; i++) {
        whaleEmitters[i] -> sound.load("sounds/splash.mp3");
    }
    for (std::size_t i = 0; i < birdEmitters.size() - 1; i++) {
        birdEmitters[i] -> sound.load("sounds/explosion.mp3");
    }
    for (std::size_t i = 0; i < squidEmitters.size() - 1; i++) {
        squidEmitters[i] -> sound.load("sounds/Slime.mp3");
    }
    for (std::size_t i = 0; i < devilEmitters.size() - 1; i++) {
        devilEmitters[i] -> sound.load("sounds/explosion.mp3");
    }
    bossEmitter -> sound.load("sounds/bossSplat.mp3");
    
    ///////////////////////////////////////////////////////////////////////////////////////////Set up slider GUI///////////////
    //gui.setup();
    //gui.add(rateSlider.setup("Rate", 0.3, 0.1, 4));
    //gui.add(lifeSlider.setup("Lifespan", 2300, 300, 4000));
    //gui.add(velXSlider.setup("Velocity X", 0, 1000, -1000));
    //gui.add(velYSlider.setup("Velocity Y", -330, 100, -1000));
    
    //-400 velY for the booster powerup
    
    
    //////////////////////////////////////////////////////////////////////////////////////////Set Variables for Emitters///////////
   
    //Assign slider variables to emitter
    //Set up settings of dragon emitter
    emitter ->setLifespan(2300);
    emitter -> setRate(0.3);
    emitter ->setVelocity(ofVec3f(0, -330, 0));
    emitter -> name = "Dragon";
    emitter -> setSpeed(350);
    
    //Set up the settings of octopus emitter
    octoEmitter ->setLifespan(11000);
    octoEmitter -> setRate(1.2);
    octoEmitter ->setVelocity(ofVec3f(0, 110, 0));
    octoEmitter -> name = "OctoMaker";
    octoEmitter -> setSpeed(130);
    octoEmitter -> autoMove();
    octoEmitter -> sinMovement = true;
    
    //Set up the settings of heart emitter
    heartEmitter ->setLifespan(9500);
    heartEmitter -> setRate(13);
    heartEmitter ->setVelocity(ofVec3f(0, 80, 0));
    heartEmitter -> name = "HeartMaker";
    heartEmitter -> autoMove();
    
    //Set up the settings of the whale emitters
    
    float speedDecrease = 20;
    for (std::size_t i = 0; i < whaleEmitters.size() - 1; i++) {
        whaleEmitters[i] -> isEnemyEmitter = true;
        if (i % 2 == 1) {
            whaleEmitters[i] ->setLifespan(14000);
            whaleEmitters[i] -> setRate(1.5);
            whaleEmitters[i] ->setVelocity(ofVec3f(-170 + speedDecrease, 0, 0));
            whaleEmitters[i] -> name = "WhaleMaker";
            speedDecrease += 15;
        }
        else {
            whaleEmitters[i] ->setLifespan(14000);
            whaleEmitters[i] -> setRate(2);
            whaleEmitters[i] ->setVelocity(ofVec3f(185 - speedDecrease, 0, 0));
            whaleEmitters[i] -> name = "WhaleMaker";
            speedDecrease += 15;
        }
     }
    
    //Set the last whale emitter separately
    whaleEmitters[whaleEmitters.size() - 1] -> isEnemyEmitter = true;
    whaleEmitters[whaleEmitters.size() - 1] ->setLifespan(14000);
    whaleEmitters[whaleEmitters.size() - 1] -> setRate(3.5);
    whaleEmitters[whaleEmitters.size() - 1] ->setVelocity(ofVec3f(-185, 0, 0));
    whaleEmitters[whaleEmitters.size() - 1] -> name = "WhaleMaker";
    
    //Set up settings for bird emitter
    for (std::size_t i = 0; i < birdEmitters.size(); i++) {
        birdEmitters[i] -> isEnemyEmitter = true;
        birdEmitters[i] -> sinMovement = true;
        birdEmitters[i] ->setLifespan(14000);
        birdEmitters[i] -> setRate(1);
        birdEmitters[i] ->setVelocity(ofVec3f(0, 200, 0));
        birdEmitters[i] -> name = "BirdMaker";
    }
    
    //Set up settings for squid emitter
    for (std::size_t i = 0; i < squidEmitters.size(); i++) {
        squidEmitters[i] -> isEnemyEmitter = true;
        squidEmitters[i] ->setLifespan(14000);
        squidEmitters[i] -> setRate(2);
        squidEmitters[i] ->setVelocity(ofVec3f(0, 95, 0));
        squidEmitters[i] -> name = "SquidMaker";
    }
    
    //Set up settings for devil emitter
    for (std::size_t i = 0; i < devilEmitters.size(); i++) {
        devilEmitters[i] -> isEnemyEmitter = true;
        devilEmitters[i] -> sinMovement = true;
        devilEmitters[i] ->setLifespan(14000);
        devilEmitters[i] -> setRate(1.6);
        devilEmitters[i] ->setVelocity(ofVec3f(0, 175, 0));
        devilEmitters[i] -> name = "DevilMaker";
        
        //Set different rate for second devil emitter
        if (i % 2 == 1) {
            devilEmitters[i] -> setRate(1.2);
            devilEmitters[i] ->setVelocity(ofVec3f(0, 185, 0));
        }
    }
    
    //Set up settings for boss emitter
    bossEmitter ->setLifespan(16500);
    bossEmitter -> setRate(1);
    bossEmitter ->setVelocity(ofVec3f(0, 290, 0));
    bossEmitter -> name = "Boss";
    bossEmitter -> setSpeed(100);
    bossEmitter -> autoMove();
    
    ///////////////////////////////////////////////////////////////////////////////////////////Set up Background Items & extras////////////////
    //Load background image
    damagedSound.load("sounds/DamageSound.mp3");
    bossDamagedSound.load("sounds/bossDamaged.mp3");
    bossDamagedSound.setVolume(0.6);
    bossLevel = false;
    bgPos1 = ofVec2f(0, 0);
    bgPos2 = ofVec2f(0, -ofGetWindowHeight());
    background.load("images/Night.jpg");
    background2.load("images/Night.jpg");
    background.resize(ofGetWindowWidth(), ofGetWindowHeight());
    background2.resize(ofGetWindowWidth(), ofGetWindowHeight());
    healthBox.load("images/Border.png");
    healthBar.load("images/Health.png");
    bossSound.load("sounds/WithoutFear.mp3");
    bossDefeatedSound.load("sounds/bossExplode.mp3");
    bgSound.load("sounds/SkyFire.mp3");
    winSound.load("sounds/VictoryTune.mp3");
    loseSound.load("sounds/GameOver.mp3");
    bgSound.setVolume(0.4);
    bossSound.setVolume(0.4);
    winSound.setVolume(0.4);
    loseSound.setVolume(0.4);
    bgSound.setLoop(true);
    bossSound.setLoop(true);
    bgSound.play();
    leftPressed = false;
    rightPressed = false;
    upPressed = false;
    downPressed = false;
    
}

//---------------------------------------------------------------------------------------------------------------------------

// load vertex buffer in preparation for rendering
//
void ofApp::loadVbo() {
    if (pEmitter.sys->particles.size() < 1) return;
    
    vector<ofVec3f> sizes;
    vector<ofVec3f> points;
    for (int i = 0; i < pEmitter.sys->particles.size(); i++) {
        points.push_back(pEmitter.sys->particles[i].position);
        sizes.push_back(ofVec3f(20));
    }
    //upload the data to the vbo
    int total = (int)points.size();
    vbo.clear();
    vbo.setVertexData(&points[0], total, GL_STATIC_DRAW);
    vbo.setNormalData(&sizes[0], total, GL_STATIC_DRAW);
}


//---------------------------------------------------------------------------------------------------------------------------
void ofApp::update(){
    
    //Check lives to determine game over
    //cout << "LIFE:" << life << endl;
    if (gameActivated && life <= 0) {
        
        lose = true;
        if (gameActivated && lose) {
            //cout << "CULPRIT2" << endl;
            bgSound.stop();
            bossSound.stop();
            loseSound.play();
            heartEmitter -> stop();
            showLoseMessage = true;
            gameActivated = false;
        }
    }
    
    if(gameActivated) {
        //Update the particle emitters
        pEmitter.update();
        damageEffectEmitter.update();
        getHealthEffectEmitter.update();
        
        //UpdateBG position to get panning effect
        if (bgPos1.y < ofGetWindowHeight() -1) {
            bgPos1 += ofVec2f(0, 1);
        }
        else {
            bgPos1 = ofVec2f(0, -ofGetWindowHeight());
        }
        
        if (bgPos2.y < ofGetWindowHeight() -1) {
            bgPos2 += ofVec2f(0, 1);
        }
        else {
            bgPos2 = ofVec2f(0, -ofGetWindowHeight());
        }
        

        
        emitter -> start();
        emitter -> update();
        heartEmitter -> start();
        heartEmitter -> update();
        checkHeartCollision();   //See if heart touches dragon
    }
    
    //Use this huge ifElse block to know when to switch levels
    
    //LEVEL 1 Octopus
    if(gameActivated && ofGetElapsedTimef() - gameActivateTime < 15) {
        level = 1;
        levelString = ofToString(level);
        
        octoEmitter -> start();
        octoEmitter -> update();
        checkOctoCollision();   //See if octo touches flames or dragon
        
    } //LEVEL 2 Whales
    else if (gameActivated && ofGetElapsedTimef() - gameActivateTime < 35) {
        level = 2;
        levelString = ofToString(level);
        
        //Stop octo emitter and update the remaining octopi
        octoEmitter -> stop();
        if (octoEmitter -> sys -> sprites.size() > 0) {
            octoEmitter -> sys -> update();
            checkOctoCollision();
        }
        
        for (std::size_t i = 0; i < whaleEmitters.size(); i++) {
             whaleEmitters[i] -> start();
             whaleEmitters[i] -> update();
             for (vector<Sprite>::iterator whaleIter = whaleEmitters[i] -> sys -> sprites.begin(); whaleIter != whaleEmitters[i] -> sys -> sprites.end(); whaleIter++) {
                 whaleIter -> trans += ofVec3f(0, sin(ofGetElapsedTimef() * 6 )/1.5, 0);
             }
        }
        checkEmittersCollision(whaleEmitters);
    } //LEVEL 3 Seagulls
    else if (gameActivated && ofGetElapsedTimef() - gameActivateTime < 65) {
        level = 3;
        levelString = ofToString(level);
        
        //Stop all the whale emitters
        stopEmitters(whaleEmitters);
        //Update any remaining whales if there are any
        for (std::size_t i = 0; i < whaleEmitters.size(); i++) {
            if (whaleEmitters[i] -> sys -> sprites.size() > 0) {
                whaleEmitters[i] -> sys -> update();
                
                //Add slight sin wave movement to whales
                for (vector<Sprite>::iterator whaleIter = whaleEmitters[i] -> sys -> sprites.begin(); whaleIter != whaleEmitters[i] -> sys -> sprites.end(); whaleIter++) {
                    whaleIter -> trans += ofVec3f(0, sin(ofGetElapsedTimef() * 4 )/2, 0);
                }
                checkEmittersCollision(whaleEmitters);
            }
        }
        
        //Every 2 seconds turn on two bird emitters
        if (ofGetElapsedTimef() - lastSpawnedBird > 2) {
            for (std::size_t i = 0; i < birdEmitters.size(); i++) {
                birdEmitters[i] -> stop();
            }
            //Activate 4 random emitters
            birdEmitters[floor(ofRandom(0, 8.999999))] -> start();
            birdEmitters[floor(ofRandom(0, 8.999999))] -> start();
            birdEmitters[floor(ofRandom(0, 8.999999))] -> start();
            //birdEmitters[floor(ofRandom(0, 8.999999))] -> start();
            lastSpawnedBird = ofGetElapsedTimef();
        }
        
        //cout << "Random: " << floor(ofRandom(0, 7.999999)) << endl;
        
        //update the emitted seagulls
        for (std::size_t i = 0; i < birdEmitters.size(); i++) {
            birdEmitters[i] -> update();
        }
        checkEmittersCollision(birdEmitters);
        
        
    } //LEVEL 4 Squids
    else if (gameActivated && ofGetElapsedTimef() - gameActivateTime < 90) {
        level = 4;
        levelString = ofToString(level);
        
        //Stop all the bird emitters
        stopEmitters(birdEmitters);
        
        //Update any remaining birds
        for (std::size_t i = 0; i < birdEmitters.size(); i++) {
            if (birdEmitters[i] -> sys -> sprites.size() > 0) {
                birdEmitters[i] -> sys -> update();
                for (vector<Sprite>::iterator birdIter = birdEmitters[i] -> sys -> sprites.begin(); birdIter != birdEmitters[i] -> sys -> sprites.end(); birdIter++) {
                    birdIter -> trans += ofVec3f(0, sin(ofGetElapsedTimef() * 4 )/2, 0);
                }
                checkEmittersCollision(birdEmitters);
            }
        }
        
        //update squid emitters
        
        //Every 6 seconds turn on three squid emitters
        if (ofGetElapsedTimef() - lastSpawnedSquid > 5) {
            for (std::size_t i = 0; i < squidEmitters.size(); i++) {
                squidEmitters[i] -> stop();
            }
            //Activate three random emitters
            squidEmitters[floor(ofRandom(0, 4.999999))] -> start();
            squidEmitters[floor(ofRandom(0, 4.999999))] -> start();
            squidEmitters[floor(ofRandom(0, 4.999999))] -> start();
            lastSpawnedSquid = ofGetElapsedTimef();
        }
        
        //update the emitted squids
        for (std::size_t i = 0; i < squidEmitters.size(); i++) {
            squidEmitters[i] -> update();
            
            //Make the squids follow the player
            for (vector<Sprite>::iterator squidIter = squidEmitters[i] -> sys -> sprites.begin(); squidIter != squidEmitters[i] -> sys -> sprites.end(); squidIter++) {
                
                //Distance from the squid to the player
                float distX = emitter -> trans.x - squidIter -> trans.x;
                float distY = emitter -> trans.y - squidIter -> trans.y;
                
                //Find the normalized vector of the squid to the player
                float hyp = sqrt(distX * distX + distY * distY);
                distX /= hyp;
                distY /= hyp;
                
                //Update the movement
                squidIter -> trans += ofVec3f(distX, distY, 0);
            }
        }
        checkEmittersCollision(squidEmitters);
        
        
    } //LEVEL 5 Boss Level
    else if (gameActivated) {
        
        //One-time calculation to set the time when boss first begins to appear
        if (level == 4) {
            bossAppearTime = ofGetElapsedTimef();
        }
        //Let the boss come downwards for 1.7 seconds
        if (ofGetElapsedTimef() - bossAppearTime < 1.7) {
            bossEmitter -> trans += ofVec3f(0, 2, 0);
        }
        else {
            bossEmitter -> setSpeed(160);
        }
        
        level = 5;
        levelString = ofToString(level);
        
        //Transition the music to the boss level music
        if (bossLevel == false) {
            bgSound.stop();
            bossSound.play();
            bossLevel = true;
        }
        
        //Stop all the squid emitters
        stopEmitters(squidEmitters);
        
        //Update any remaining squids
        for (std::size_t i = 0; i < squidEmitters.size(); i++) {
            if (squidEmitters[i] -> sys -> sprites.size() > 0) {
                squidEmitters[i] -> sys -> update();
                for (vector<Sprite>::iterator squidIter = squidEmitters[i] -> sys -> sprites.begin(); squidIter != squidEmitters[i] -> sys -> sprites.end(); squidIter++) {
                    //Distance from the squid to the player
                    float distX = emitter -> trans.x - squidIter -> trans.x;
                    float distY = emitter -> trans.y - squidIter -> trans.y;
                    
                    //Find the normalized vector of the squid to the player
                    float hyp = sqrt(distX * distX + distY * distY);
                    distX /= hyp;
                    distY /= hyp;
                    
                    //Update the movement
                    squidIter -> trans += ofVec3f(distX, distY, 0);
                }
                 checkEmittersCollision(squidEmitters);
            }
        }
        
        //Start devil emitters & make sin movement for devils
        for (std::size_t i = 0; i < devilEmitters.size(); i++) {
            devilEmitters[i] -> start();
            devilEmitters[i] -> update();
        }
        
        
        bossEmitter -> start();
        bossEmitter -> update();
        
        if (bossLife > 0) {
            checkBossCollision();
            checkEmittersCollision(devilEmitters);
        }
        
        //Explode boss and play explosion sound effect when boss is defeated
        if (bossLife <= 0) {
            adjustColorAndEffect(bossEmitter);
            pEmitter.setPosition(bossEmitter -> trans + ofVec3f(bossEmitter -> width/2, bossEmitter -> height/2, 0));
            pEmitter.sys->reset();
            pEmitter.start();
            
            //One-time play of the explosion sound and recording the time of boss defeat
            if (win == false) {
                bossDefeatedSound.play();
                timeWon = ofGetElapsedTimef();
            }
            win = true;
            
        }
        
        //This happens 1.5 seconds after the boss is defeated
        if (gameActivated && win && (ofGetElapsedTimef() - timeWon > 1.5)) {
            heartEmitter -> stop();
            bossSound.stop();
            winSound.play();
            showWinMessage = true;
            gameActivated = false;
        }
        
    }
    
    
}


//--------------------------------------------------------------

void ofApp::stopEmitters(vector<Emitter*> theEmitters) {
    for (std::size_t i = 0; i < theEmitters.size(); i++) {
        theEmitters[i] -> stop();
    }
}


void ofApp::clearAll(){
    
    for (vector<Sprite>::iterator heartIter = heartEmitter -> sys -> sprites.begin(); heartIter != heartEmitter -> sys -> sprites.end(); heartIter++) {
        heartIter -> lifespan = 0;
    }
    heartEmitter -> sys -> update();
    
    for (vector<Sprite>::iterator octoIter = octoEmitter -> sys -> sprites.begin(); octoIter != octoEmitter -> sys -> sprites.end(); octoIter++) {
        octoIter -> lifespan = 0;
    }
    octoEmitter -> sys -> update();
    
    for (std::size_t i = 0; i < whaleEmitters.size(); i++) {
        for (vector<Sprite>::iterator whaleIter = whaleEmitters[i] -> sys -> sprites.begin(); whaleIter != whaleEmitters[i] -> sys -> sprites.end(); whaleIter++) {
            whaleIter -> lifespan = 0;
        }
        whaleEmitters[i] -> sys -> update();
    }
    
    for (std::size_t i = 0; i < birdEmitters.size(); i++) {
        birdEmitters[i] -> update();
        for (vector<Sprite>::iterator birdIter = birdEmitters[i] -> sys -> sprites.begin(); birdIter != birdEmitters[i] -> sys -> sprites.end(); birdIter++) {
            birdIter -> lifespan = 0;
        }
        birdEmitters[i] -> sys -> update();
    }
    
    for (std::size_t i = 0; i < squidEmitters.size(); i++) {
        squidEmitters[i] -> update();
        for (vector<Sprite>::iterator squidIter = squidEmitters[i] -> sys -> sprites.begin(); squidIter != squidEmitters[i] -> sys -> sprites.end(); squidIter++) {
            squidIter -> lifespan = 0;
        }
        squidEmitters[i] -> sys -> update();
    }
    
    for (std::size_t i = 0; i < devilEmitters.size(); i++) {
        devilEmitters[i] -> update();
        for (vector<Sprite>::iterator devilIter = devilEmitters[i] -> sys -> sprites.begin(); devilIter != devilEmitters[i] -> sys -> sprites.end(); devilIter++) {
            devilIter -> lifespan = 0;
        }
        devilEmitters[i] -> sys -> update();
    }
    
    for (vector<Sprite>::iterator bossIter = bossEmitter -> sys -> sprites.begin(); bossIter != bossEmitter -> sys -> sprites.end(); bossIter++) {
        bossIter -> lifespan = 0;
    }
    bossEmitter -> sys -> update();
    
}

//---------------------------------------------------------------------
void ofApp::checkOctoCollision(){
    
    //Check if the octopus is hit by the flames
    for (vector<Sprite>::iterator flameIter = emitter -> sys -> sprites.begin(); flameIter != emitter -> sys -> sprites.end(); flameIter++) {
        
        for (vector<Sprite>::iterator octoIter = octoEmitter -> sys -> sprites.begin(); octoIter != octoEmitter -> sys -> sprites.end(); octoIter++) {
            
            ofVec3f flameCenter = ofVec3f(flameIter -> trans.x + (flameIter -> width /2), flameIter -> trans.y + (flameIter -> height /2));
            ofVec3f octoCenter = ofVec3f(octoIter -> trans.x + (octoIter -> width /2), octoIter -> trans.y + (octoIter -> height /2));
            
            float dist = flameCenter.distance(octoCenter);
            float contactDist = octoIter -> height/2 + flameIter -> height/2 - 13;
            
            //If they collide, delete the flame and the enemy
            if(dist < contactDist) {
                adjustColorAndEffect(octoEmitter);
                pEmitter.setPosition(octoIter -> trans + ofVec3f(octoIter -> width/2, octoIter -> height/2, 0));
                pEmitter.sys->reset();
                pEmitter.start();
                flameIter -> lifespan = 0;
                octoIter -> lifespan = 0;
                score += 10;
                scoreString = ofToString(score);
                octoEmitter -> sound.play();
            }
        }
    }
    
    //Check if octopus hits the dragon
    for (vector<Sprite>::iterator octoIter = octoEmitter -> sys -> sprites.begin(); octoIter != octoEmitter -> sys -> sprites.end(); octoIter++) {
        
        ofVec3f dragonCenter = ofVec3f(emitter -> trans.x + (emitter -> width /2), emitter -> trans.y + (emitter -> height /2));
        ofVec3f octoCenter = ofVec3f(octoIter -> trans.x + (octoIter -> width /2), octoIter -> trans.y + (octoIter -> height /2));
        
        float dist = dragonCenter.distance(octoCenter);
        float contactDist = octoIter -> height/2 + emitter -> height/2 - 10;
        
        //Reduce if the dragon touches it
        if(dist < contactDist) {
            particleColor = ofColor(255, 98, 20);
            pEmitter.setPosition(octoIter -> trans + ofVec3f(octoIter -> width/2, octoIter -> height/2, 0));
            pEmitter.sys->reset();
            pEmitter.start();
            
            //Start particle emitter (The one that shows the hit effect)
            damageEffectEmitter.setPosition(emitter -> trans);
            damageEffectEmitter.sys->reset();
            damageEffectEmitter.start();
            
            octoIter -> lifespan = 0;
            life -= 1;
            lifeString = ofToString(life);
            damagedSound.play();
        }
        
    }
    
}


//--------------------------------------------------------------

void ofApp::checkHeartCollision(){
    
    //Check if the dragon touches the heart bubbles
    for (vector<Sprite>::iterator heartIter = heartEmitter -> sys -> sprites.begin(); heartIter != heartEmitter -> sys -> sprites.end(); heartIter++) {
        
        ofVec3f dragonCenter = ofVec3f(emitter -> trans.x + (emitter -> width /2), emitter -> trans.y + (emitter -> height /2));
        ofVec3f heartCenter = ofVec3f(heartIter -> trans.x + (heartIter -> width /2), heartIter -> trans.y + (heartIter -> height /2));
        
        float dist = dragonCenter.distance(heartCenter);
        float contactDist = heartIter -> height/2 + emitter -> height/2 - 5;
        
        if(dist < contactDist) {
            //Set plus health effect emitter when draon gains a life
            getHealthEffectEmitter.setPosition(emitter -> trans);
            getHealthEffectEmitter.sys->reset();
            getHealthEffectEmitter.start();
            
            //Delete the heart
            heartIter -> lifespan = 0;
            heartIter -> manualPop = true;
            life += 1;
            lifeString = ofToString(life);
            heartEmitter -> sound.play();
        }
        
    }
    
    
    
}

void ofApp::checkEmittersCollision(vector<Emitter*> enemyEmitters) {
    
    //Check colission with flame and dragon for all enemy emitters
    
    //Check if enemy touches dragon
    for (std::size_t i = 0; i < enemyEmitters.size(); i++) {
        for (vector<Sprite>::iterator enemyIter = enemyEmitters[i] ->sys-> sprites.begin(); enemyIter != enemyEmitters[i] -> sys -> sprites.end(); enemyIter++) {
            
            ofVec3f dragonCenter = ofVec3f(emitter -> trans.x + (emitter -> width /2), emitter -> trans.y + (emitter -> height /2));
            ofVec3f enemyCenter = ofVec3f(enemyIter -> trans.x + (enemyIter -> width /2), enemyIter -> trans.y + (enemyIter -> height /2));
            
            float dist = dragonCenter.distance(enemyCenter);
            float contactDist = enemyIter -> height/2 + emitter -> height/2 - 5;
            
            if(dist < contactDist) {
                adjustColorAndEffect(enemyEmitters[i]);
                pEmitter.setPosition(enemyIter -> trans + ofVec3f(enemyIter -> width/2, enemyIter -> height/2, 0));
                pEmitter.sys->reset();
                pEmitter.start();
                
                //Start particle emitter (The one that shows the hit effect)
                damageEffectEmitter.setPosition(emitter -> trans);
                damageEffectEmitter.sys->reset();
                damageEffectEmitter.start();
                
                enemyIter -> lifespan = 0;
                life -= 1;
                lifeString = ofToString(life);
                damagedSound.play();
            }
            
        }
    }
    
    //check if enemy touches flame
    for (std::size_t i = 0; i < enemyEmitters.size(); i++) {
        for (vector<Sprite>::iterator flameIter = emitter -> sys -> sprites.begin(); flameIter != emitter -> sys -> sprites.end(); flameIter++) {
            
            for (vector<Sprite>::iterator enemyIter = enemyEmitters[i] -> sys -> sprites.begin(); enemyIter != enemyEmitters[i] -> sys -> sprites.end(); enemyIter++) {
                
                ofVec3f flameCenter = ofVec3f(flameIter -> trans.x + (flameIter -> width /2), flameIter -> trans.y + (flameIter -> height /2));
                ofVec3f enemyCenter = ofVec3f(enemyIter -> trans.x + (enemyIter -> width /2), enemyIter -> trans.y + (enemyIter -> height /2));
                
                float dist = flameCenter.distance(enemyCenter);
                float contactDist = enemyIter -> height/2 + flameIter -> height/2 - 20;
                
                //If they collide, delete the flame and the enemy
                if(dist < contactDist) {
                    adjustColorAndEffect(enemyEmitters[i]);
                    pEmitter.setPosition(enemyIter -> trans + ofVec3f(enemyIter -> width/2, enemyIter -> height/2, 0));
                    pEmitter.sys->reset();
                    pEmitter.start();
                    
                    flameIter -> lifespan = 0;
                    enemyIter -> lifespan = 0;
                    score += 10;
                    scoreString = ofToString(score);
                    enemyEmitters[i] -> sound.play();
                }
            }
        }
    }
}


void ofApp::adjustColorAndEffect(Emitter* theEmitter) {
    if (theEmitter -> name == "OctoMaker") {
        particleColor = ofColor(255, 98, 20);
        pEmitter.setVelocity(ofVec3f(150, 0, 0));
        pEmitter.setGroupSize(30);
        radialForce -> set(10);
    }
    else if (theEmitter -> name == "WhaleMaker") {
        particleColor = ofColor(77, 187, 234);
        pEmitter.setVelocity(ofVec3f(120, 0, 0));
        pEmitter.setGroupSize(15);
        radialForce -> set(1);
    }
    else if (theEmitter -> name == "BirdMaker") {
        particleColor = ofColor(255, 251, 150);
        pEmitter.setVelocity(ofVec3f(150, 0, 0));
        pEmitter.setGroupSize(20);
        radialForce -> set(10);
        radialForce -> setHeight(0.05);
    }
    else if (theEmitter -> name == "SquidMaker") {
        particleColor = ofColor(201, 131, 239);
        pEmitter.setVelocity(ofVec3f(80, 0, 0));
        pEmitter.setGroupSize(15);
        radialForce -> set(5);
    }
    else if (theEmitter -> name == "DevilMaker") {
        particleColor = ofColor(145, 239, 130);
        pEmitter.setVelocity(ofVec3f(90, 0, 0));
        pEmitter.setGroupSize(30);
        radialForce -> set(5);
    }
    else {
        particleColor = ofColor(88, 58, 163);
        pEmitter.setVelocity(ofVec3f(200, 0, 0));
        pEmitter.setGroupSize(35);
        radialForce -> set(40);
    }
    
    
}


//----------------------------------------------------------------------------------------

void ofApp::checkBossCollision() {
    //Check if the boss is hit by the dragon flames
    for (vector<Sprite>::iterator flameIter = emitter -> sys -> sprites.begin(); flameIter != emitter -> sys -> sprites.end(); flameIter++) {
        
        ofVec3f flameCenter = ofVec3f(flameIter -> trans.x + (flameIter -> width /2), flameIter -> trans.y + (flameIter -> height /2));
        ofVec3f bossCenter = ofVec3f(bossEmitter -> trans.x + (bossEmitter -> width /2), bossEmitter -> trans.y + (bossEmitter -> height /2));
        
        float dist = flameCenter.distance(bossCenter);
        float contactDist = bossEmitter -> height/2 + flameIter -> height/2 - 13;
        
        //If they collide, delete the flame, increase score, and take hp from the boss
        if(dist < contactDist) {
            flameIter -> lifespan = 0;
            bossLife -= 1;
            score += 40;
            scoreString = ofToString(score);
            bossDamagedSound.play();
        }
    
    }
    
    //Check if dragon is hit by boss flames
    for (vector<Sprite>::iterator bossIter = bossEmitter -> sys -> sprites.begin(); bossIter != bossEmitter -> sys -> sprites.end(); bossIter++) {
        
        ofVec3f flameCenter = ofVec3f(bossIter -> trans.x + (bossIter -> width /2), bossIter -> trans.y + (bossIter -> height /2));
        ofVec3f dragonCenter = ofVec3f(emitter -> trans.x + (emitter -> width /2), emitter -> trans.y + (emitter -> height /2));
        
        float dist = flameCenter.distance(dragonCenter);
        float contactDist = emitter -> height/2 + bossIter -> height/2 - 13;
        
        //If they collide, delete the boss flame and take hp from the dragon
        if(dist < contactDist) {
            //Start particle emitter (The one that shows the hit effect)
            damageEffectEmitter.setPosition(emitter -> trans);
            damageEffectEmitter.sys->reset();
            damageEffectEmitter.start();
            
            bossIter -> lifespan = 0;
            life -= 1;
            damagedSound.play();
        }
        
    }
    
    //Check if boss touches the dragon
    ofVec3f dragonCenter = ofVec3f(emitter -> trans.x + (emitter -> width /2), emitter -> trans.y + (emitter -> height /2));
    ofVec3f bossCenter = ofVec3f(bossEmitter -> trans.x + (bossEmitter -> width /2), bossEmitter -> trans.y + (bossEmitter -> height /2));
    
    float dist = dragonCenter.distance(bossCenter);
    float contactDist = bossEmitter -> height/2 + emitter -> height/2 - 8;
    
    //Reduce if the dragon touches it
    if(dist < contactDist) {
        //Start particle emitter (The one that shows the hit effect)
        damageEffectEmitter.setPosition(emitter -> trans);
        damageEffectEmitter.sys->reset();
        damageEffectEmitter.start();
        
        life -= 1;
        lifeString = ofToString(life);
        damagedSound.play();
    }
        
    
    
}

//----------------------------------------------------------------------------------------
void ofApp::draw(){
    loadVbo();
    
    background.draw(bgPos1);
    background2.draw(bgPos2);
    
    emitter -> draw();
    emitter -> sys -> draw();
    octoEmitter -> sys -> draw();
    heartEmitter -> sys -> draw();
    
    for (std::size_t i = 0; i < whaleEmitters.size(); i++) {
        whaleEmitters[i] -> sys -> draw();
    }
    for (std::size_t i = 0; i < birdEmitters.size(); i++) {
        birdEmitters[i] -> sys -> draw();
    }
    for (std::size_t i = 0; i < squidEmitters.size(); i++) {
        squidEmitters[i] -> sys -> draw();
    }
    for (std::size_t i = 0; i < devilEmitters.size(); i++) {
        devilEmitters[i] -> sys -> draw();
    }
    
    
    bossEmitter -> sys -> draw();
    
    if (level == 5 && bossLife > 0) {
        healthBox.draw(bossEmitter -> trans.x + bossEmitter -> width/2 - healthBox.getWidth()/2, bossEmitter -> trans.y + bossEmitter -> height + 5);
        if (bossLife > 0) {
            healthBar.resize(bossLife * 4, 6);
            healthBar.draw(bossEmitter -> trans.x + 3 + bossEmitter -> width/2 - healthBox.getWidth()/2, bossEmitter -> trans.y + bossEmitter -> height + 8);
        }

        bossEmitter -> draw();
        
    }
    
    damageEffectEmitter.sys -> draw();
    getHealthEffectEmitter.sys -> draw();
    
    //gui.draw();
    
    //pEmitter.sys -> draw();
    
    
    //Draw explosion
    //Fireworks red Octopus explosion
    ofSetColor(particleColor);
    
    //Blue grey Whale explosion
    //ofSetColor(174, 211, 226);
    
    //Yellowy Seagull explosion
    //ofSetColor(255, 251, 150);
    
    //Purple Squid explosion
    ///ofSetColor(201, 131, 239);
    
    //Green Devil explosion
    //ofSetColor(145, 239, 130);
    
    //Deep Purple boss explosion
    //ofSetColor(88, 58, 163);
    
    //Glowy Blue
    //ofSetColor(77, 187, 234);
    
    // this makes everything look glowy :)
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnablePointSprites();
    
    // begin drawing the particles
    shader.begin();
    
    // draw particle emitter here..
    //    emitter.draw();
    particleTex.bind();
    vbo.draw(GL_POINTS, 0, (int)pEmitter.sys->particles.size());
    particleTex.unbind();
    
    //  end drawing in the camera
    shader.end();
    ofDisablePointSprites();
    ofDisableBlendMode();
    ofEnableAlphaBlending();

    //Change color back to normal
    ofSetColor(255,255,255);
    
    //Draw UI overlay
    scoreDisplay.drawString("LEVEL " + levelString, 40, 30);
    scoreDisplay.drawString("SCORE " + scoreString, ofGetWindowWidth()/2 - 40, 30);
    lifeImage.draw(ofGetWindowWidth()/2 + 180, 8);
    lifeDisplay.drawString("x " + lifeString, ofGetWindowWidth()/2 + 218, 30);
    if (showTitle) {
        titleDisplay.drawString("GALAXY", ofGetWindowWidth()/2 - 200, ofGetWindowHeight()/2 - 70);
        titleDisplay.drawString("WAR", ofGetWindowWidth()/2 - 120, ofGetWindowHeight()/2 + 60);
    }
    
    if (showLoseMessage) {
        cout << "LOSE MESSAGE DRAWING" << endl;
        loseDisplay.drawString("YOU LOSE", ofGetWindowWidth()/2 - 180, ofGetWindowHeight()/2);
        finalScoreDisplay.drawString("Your Score " + scoreString, ofGetWindowWidth()/2 - 110, ofGetWindowHeight()/2 + 50);
    }
    else if (showWinMessage) {
        loseDisplay.drawString("YOU WIN", ofGetWindowWidth()/2 - 180, ofGetWindowHeight()/2);
        finalScoreDisplay.drawString("Your Score " + scoreString, ofGetWindowWidth()/2 - 110, ofGetWindowHeight()/2 + 50);
    }
    
    if (!gameActivated) {
        pressSpaceDisplay.drawString("Press 'p' to start playing", ofGetWindowWidth()/2 - 250, ofGetWindowHeight()/2 + 105);
        
    }
    
}

//--------------------------------------------------------------

void ofApp::moveSprite(MoveDir dir) {
    emitter -> moveDir = dir;
}

//--------------------------------------------------------------
    
void ofApp::stopSprite() {
    emitter -> moveDir = MoveStop;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'F':
        case 'f':
            ofToggleFullscreen();
            break;
        case ' ':
            emitter -> emit();
            break;
        case 'd':
        case OF_KEY_RIGHT:
            rightPressed = true;
            moveSprite(MoveRight);
            break;
        case 'a':
        case OF_KEY_LEFT:
            leftPressed = true;
            moveSprite(MoveLeft);
            break;
        case 'w':
        case OF_KEY_UP:
            upPressed = true;
            moveSprite(MoveUp);
            break;
        case 's':
        case OF_KEY_DOWN:
            downPressed = true;
            moveSprite(MoveDown);
            break;
        case 'p':
        case 'P':
            if(!gameActivated && !lose && !win) {
                gameActivateTime = ofGetElapsedTimef();
                gameActivated = true;
                showTitle = false;
            }
            else if (lose || win) {
                emitter -> setPosition(ofVec2f(ofGetWindowWidth()/2 - (emitter -> width/2), ofGetWindowHeight() -(emitter -> height)));
                emitter -> moveDir = MoveStop;      //Start off without movement
                gameActivateTime = ofGetElapsedTimef();
                gameActivated = true;
                clearAll();
                life = 5;
                level = 0;
                bossLife = 25;
                bossLevel = false;
                bossEmitter -> setPosition(ofVec2f(0, -bossEmitter -> height));
                lifeString = ofToString(life);
                cout << "RESETTT------->life=5" << endl;
                score = 0;
                scoreString = ofToString(score);
                lose = false;
                win = false;
                showLoseMessage = false;
                showWinMessage = false;
                bgSound.play();
            }
            break;
        
        
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key) {
        case 'w':
        case 'a':
        case 's':
        case 'd':
        case OF_KEY_LEFT:
            leftPressed = false;
            if (!rightPressed && !upPressed &&!downPressed) {
                stopSprite();
            }
            break;
        case OF_KEY_RIGHT:
            rightPressed = false;
            if (!leftPressed && !upPressed &&!downPressed) {
                stopSprite();
            }
            break;
        case OF_KEY_UP:
            upPressed = false;
            if (!rightPressed && !leftPressed &&!downPressed) {
                stopSprite();
            }
            break;
        case OF_KEY_DOWN:
            downPressed = false;
            if (!rightPressed && !leftPressed &&!upPressed) {
                stopSprite();
            }
            break;
        case ' ':
            emitter -> stop();
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
