//
//  Ball.cpp
//  myBoid01
//
//  Created by kuha on 2016/03/08.
//
//

#include "Ball.hpp"

Ball::Ball(){
    pos = ofPoint(ofGetWidth()/2, ofGetHeight()/2);
    vel = ofPoint(ofRandom(-0.8,0.8),ofRandom(-0.8,0.8));
    acc = ofPoint(0,0);
    radius = ofRandom(35,50);
//    bcolor = ofColor(ofRandom(200,255), ofRandom(0,255), ofRandom(0,255), 80);
    fish = 1;
    visible = true;
    
}
Ball::~Ball(){}

void Ball::update(){
    acc = ofPoint(ofRandom(-0.1,0.1),ofRandom(-0.1,0.1));
    vel += acc;
    if( vel.length() > 1 ) {
        vel.x *= 0.75;
        vel.y *= 0.75;
    }
    pos += vel;
    
    if( pos.x > ofGetWidth() || pos.x < 0 ){
        vel.x *= -1;
    }
    if( pos.y > ofGetHeight() || pos.y < 0 ){
        vel.y *= -1;
    }
    if( ( ofGetFrameNum() ) % ( 30 * 3 ) == 0) radius *= 0.99;
    if(radius < 2.0) visible = false;
  
}

void Ball::draw(){
//    ofSetColor(bcolor);
//    ofNoFill();

    int radius2 = radius * ofRandom(1.0,1.5);
//    ofSetColor(231, 227, 255, 10);
    ofSetColor(bcolor.r, bcolor.g, bcolor.b, 10);
    ofCircle(pos, radius2);
//    ofSetColor(231, 227, 255, 30);
    ofSetColor(bcolor.r, bcolor.g, bcolor.b, 20);
    ofCircle(pos, radius2 * 0.75);
//    ofFill();
//    ofRotateX(5);
//    ofRect(pos, radius2 * 0.75, radius2 * 0.75);
//    ofSetColor(231, 227, 255, 80);
    ofSetColor(bcolor.r, bcolor.g, bcolor.b, 30);
    ofCircle(pos, radius * 0.3);
}
