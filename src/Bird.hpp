//
//  Bird.hpp
//  myBoid01
//
//  Created by kuha on 2016/03/07.
//
//

#ifndef Bird_hpp
#define Bird_hpp

#include <stdio.h>

#endif /* Bird_hpp */

#pragma once

#include "ofMain.h"

class Bird
{
public:
    Bird(vector<Bird>* const, const int, ofColor, vector<Bird>* const, vector<Bird>* const, vector<Bird>* const);
    virtual ~Bird();
    
    virtual void update();
    virtual void draw();
    
    void resetForce();  // óÕÇÉäÉZÉbÉg
    void updateForce(); // óÕÇçXêV
    void updatePos();   // à íuÇÃçXêV
    void addAttractiveForce(float, float, float, float);
    void birdAttract(ofVec2f, float);
    void bird(ofVec2f);
    
    int id;
    float head;
    float tail;
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f acc;
    ofColor circleColor;
    
protected:
    vector<Bird>* pSelfGroup;
    vector<Bird>* pEnemyGroup;
    vector<Bird>* pFriendGroup;
    vector<Bird>* pFriendGroup2;
    
    ofVec2f separationVel;
    ofVec2f alignmentVel;
    ofVec2f cohesionVel;
    ofVec2f groupCenterPos;
//    ofColor circleColor;
    
private:
    
};