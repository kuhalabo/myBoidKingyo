#pragma once

#include "ofMain.h"
#include "ofGraphics.h"
#include "Bird.hpp"
#include "Ball.hpp"

class ofApp : public ofBaseApp
{
public:
    bool mouse_pressed;
    ofVec2f mousePos;

    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    vector<Bird> birds1;
    vector<Bird> birds2;
    vector<Bird> birds3;
    vector<Bird> birds4;
    vector<Bird> nullBirds;
    
    ofColor bgcolor;

    int ballsNum;
    int counterBall;

    void ballGenerate(ofPoint _pos, float _radius);
    void setColorDayNight();
    void setNightMode(int h);
    
//    Ball myball;
    vector<Ball> balls;

// sound
    void audioIn(float * input, int bufferSize, int nChannels);
    ofSoundStream soundStream;
    float curVol;
    
};
