//
//  Ball.hpp
//  myBoid01
//
//  Created by kuha on 2016/03/08.
//
//

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>

#endif /* Ball_hpp */

#pragma once
#include "ofMain.h"

class Ball {
public:
    ofVec2f pos;
    ofPoint vel;
    ofPoint acc;
    float radius;
    ofColor bcolor;
    int fish;
    bool visible;
    
public:
    Ball();
    ~Ball();
    void draw();
    void update();
    
};