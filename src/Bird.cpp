//
//  Bird.cpp
//  myBoid01
//
//  Created by kuha on 2016/03/07.
//
//

#include "Bird.hpp"
//#include "Bird.h"

Bird::Bird( vector<Bird>* const _pSelfGroup, const int _id, const ofColor _circleColor, vector<Bird>* const _pEnemyGroup, vector<Bird>* const _pFriendGroup, vector<Bird>* const _pFriendGroup2 ) :
pSelfGroup(_pSelfGroup),
pEnemyGroup(_pEnemyGroup),
pFriendGroup(_pFriendGroup),
pFriendGroup2(_pFriendGroup2),
id(_id),
circleColor(_circleColor),
pos( ofRandom( 0, ofGetWidth() ), ofRandom( 0, ofGetHeight() ) ),
vel( ofRandom(-2,2), ofRandom(-2,2) ),
separationVel(0,0), alignmentVel(0,0), cohesionVel(0,0), groupCenterPos(0,0)
{
//    head = ofRandom(0.5,3.0);
    head = 2;
//    tail = head * 3.0;
    tail = head * 4.0;
    acc.set(0, 0);
//    cout << "CTOR, ID:" << id << endl;
}

Bird::~Bird()
{
//    cout << "DTOR, ID:" << id << endl;
}

void Bird::update()
{
    int separationCount = 0;
    int alignmentCount = 0;
    int cohesionCount = 0;
    separationVel.set(0,0); alignmentVel.set(0,0); cohesionVel.set(0,0);
    groupCenterPos.set(0,0);
    
    for(int i = 0; i < pSelfGroup->size(); i++)
    {
        Bird& rAnother = pSelfGroup->at(i);
        
        if(rAnother.id != id)
        {
            float dist = pos.distance( rAnother.pos );
            
            if(dist < 10)
            {
                separationVel += pos - rAnother.pos;
                separationCount++;
            }
            else if(dist < 35)
            {
                alignmentVel += rAnother.vel.getNormalized();
                alignmentCount++;
            }
            else if(dist < 60)
            {
                groupCenterPos += rAnother.pos;
                cohesionCount++;
            }
        }
    }
    
    for(int i = 0; i < pFriendGroup->size(); i++)
    {
        Bird& rAnother = pFriendGroup->at(i);
        
        //if(rAnother.id != id)
        //{
        float dist = pos.distance( rAnother.pos );
        
        if(dist < 10)
        {
            separationVel += pos - rAnother.pos;
            separationCount++;
        }
        else if(dist < 35)
        {
            alignmentVel += rAnother.vel.getNormalized();
            alignmentCount++;
        }
        else if(dist < 60)
        {
            groupCenterPos += rAnother.pos;
            cohesionCount++;
        }
        //}
    }
    
    for(int i = 0; i < pFriendGroup2->size(); i++)
    {
        Bird& rAnother = pFriendGroup2->at(i);
        
        //if(rAnother.id != id)
        //{
        float dist = pos.distance( rAnother.pos );
        
        if(dist < 10)
        {
            separationVel += pos - rAnother.pos;
            separationCount++;
        }
        else if(dist < 35)
        {
            alignmentVel += rAnother.vel.getNormalized();
            alignmentCount++;
        }
        else if(dist < 60)
        {
            groupCenterPos += rAnother.pos;
            cohesionCount++;
        }
        //}
    }
    
    for(int i = 0; i < pEnemyGroup->size(); i++)
    {
        Bird& rAnother = pEnemyGroup->at(i);
        float dist = pos.distance( rAnother.pos );
        
        if(dist < 60)
        {
            separationVel += pos - rAnother.pos;
            separationCount++;
        }
    }
    
    separationVel /= separationCount;
    separationVel.normalize();
    
    alignmentVel /= alignmentCount;
    alignmentVel.normalize();
    
    groupCenterPos /= cohesionCount;
    cohesionVel = groupCenterPos - pos;
    cohesionVel.normalize();
    
    vel += (separationVel*0.15) + (alignmentVel*0.035) + (cohesionVel*0.02);
    
    //if(vel.length() > 2)
    //{
    //  vel.scale(2);
    //}
    vel.scale(1.5);
    pos += vel;
    
    if( pos.x < 0 )
    {
        vel.x *= -1;
        pos.x = (0) + (0-pos.x);
    }
    else if( pos.x > ofGetWidth()-1 )
    {
        vel.x *= -1;
        pos.x = (ofGetWidth()-1) - ( pos.x - (ofGetWidth()-1) );
    }
    if( pos.y < 0 )
    {
        vel.y *= -1;
        pos.y = (0) + (0-pos.y);
    }
    else if( pos.y > ofGetHeight()-1 )
    {
        vel.y *= -1;
        pos.y = (ofGetHeight()-1) - ( pos.y - (ofGetHeight()-1) );
    }
}

void Bird::draw()
{
    ofSetColor(circleColor);
//    ofNoFill();
    ofCircle(pos, head);
 //   ofRect(pos,head, head);
//    ofCircle(pos, 2);
    ofLine(pos.x + vel.x * tail * 0.5, pos.y + vel.y * tail * 0.5, pos.x - vel.x * tail, pos.y - vel.y * tail);
//    ofFill();
}

void Bird::addAttractiveForce(float x, float y, float radius, float scale)
{
    // óÕÇÃíÜêSì_Çê›íË
    ofVec2f posOfForce;
    posOfForce.set(x,y);
    // ÉpÅ[ÉeÉBÉNÉãÇ∆óÕÇÃíÜêSì_Ç∆ÇÃãóó£ÇåvéZ
    ofVec2f diff = pos - posOfForce;
    float length = diff.length();
    // óÕÇ™ì≠Ç≠îÕàÕÇ©Ç«Ç§Ç©îªíËÇ∑ÇÈïœêî
    bool bAmCloseEnough = true;
    // Ç‡Çµê›íËÇµÇΩîºåaÇÊÇËäOë§ÇæÇ¡ÇΩÇÁÅAåvéZÇµÇ»Ç¢
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
    // ê›íËÇµÇΩîºåaÇÃì‡ë§ÇæÇ¡ÇΩÇÁ
    if (bAmCloseEnough == true){
        // ãóó£Ç©ÇÁì_Ç…Ç©Ç©ÇÈóÕÉxÉNÉgÉãÇåvéZ
        float pct = 1 - (length / radius);
        diff.normalize();
        acc.x = acc.x - diff.x * scale * pct;
        acc.y = acc.y - diff.y * scale * pct;
    }
}

void Bird::birdAttract(ofVec2f posA, float scale)
{
//    scale = 0.06;
    ofVec2f diff = pos - posA;
    float length = diff.length();
//    double length2 = pow(length, 2.0);
    double length2 = pow(length, 1.5);
    if(length < ofGetWidth() / 6) vel += ( posA - pos ) / ( length ) * scale;
//    if(length2 > 2.0) vel += ( posA - pos ) / ( length2 ) * 1.5;
}
