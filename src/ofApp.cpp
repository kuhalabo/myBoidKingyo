#include "ofApp.h"

//#define RBOID 100
#define BOID1 200
//#define GBOID 50
#define BOID2 200
//#define BBOID 25
#define BOID3 200
#define BOID4 200

#define BGCOLORn ofColor(0,0,0,32) // black
#define BGCOLORd ofColor(32,178,170,32); // Emerald Green

#define COLOR1n ofColor(255,0,0,255) // red
#define COLOR2n ofColor(0,255,0,255)  // green
#define COLOR3n ofColor(0,255,255,255) //cyan
#define COLOR4n ofColor(255,255,0,255) // yellow
#define COLOR5n ofColor(255,165,0,255) //orange

#define COLOR1d ofColor(255,0,0,255) // red
//#define COLOR2d ofColor(76,103,51,255)  // Ivy Green
#define COLOR2d ofColor(255,0,255,255)  // mazenta
#define COLOR3d ofColor(0,0,255) // blue
#define COLOR4d ofColor(255,255,0,255) // Yellow
#define COLOR5d ofColor(255,165,0,255) //orange

#define FRATE 20

int mm; // present minute
int hh; // present hour
int ss; // present second
bool nightmode;

#define SOUDLIMIT 0.1
#define BALLMAX 300
#define NIGHT_START 18
#define DAY_START 8

//--------------------------------------------------------------
void ofApp::setup()
{
//    cout << "aaa" << endl;
    
    
    ofToggleFullscreen();
    ofSetFrameRate(FRATE);
    ofEnableAlphaBlending();
    ofSetBackgroundColor(0,0,0);
//    ofSetBackgroundColor(255,255,255);
    ofSetBackgroundAuto(false);
    ofSetCircleResolution(64);
    ofHideCursor();
    ofSetRectMode(OF_RECTMODE_CENTER);

//    bgcolor = ofColor(32,178,170,32); // Emerald Green
    bgcolor = BGCOLORn;
    ofSetBackgroundColor(bgcolor);

    ballsNum = 7;
    counterBall = 0;
    // self, enemy, friend1, friend2
    birds1.reserve(BOID1);
    for(int i = 0; i < BOID1; i++)
    {
        birds1.push_back(*new Bird( &birds1, i, COLOR1n, &birds2, &birds3, &nullBirds));
    }
    
    birds2.reserve(BOID2);
    for(int i = 0; i < BOID2; i++)
    {
        birds2.push_back(*new Bird( &birds2, i, COLOR2n, &nullBirds, &birds3, &nullBirds));
    }
    
    birds3.reserve(BOID3);
    for(int i = 0; i < BOID3; i++)
    {
        birds3.push_back(*new Bird( &nullBirds, i, COLOR3n, &nullBirds, &birds2, &nullBirds));
    }
    
    birds4.reserve(BOID4);
    for(int i = 0; i < BOID4; i++)
    {
        birds4.push_back(*new Bird( &birds4, i, COLOR4n, &birds1, &birds3, &nullBirds));
    }
    
   	soundStream.printDeviceList();
 //   soundStream.setup(this, 0, 1, 44100, 256, 4);
    soundStream.setup(this, 0, 1, 44100, 128, 4);
    
    hh = ofGetHours();
    setNightMode(hh);
    setColorDayNight();

}

//--------------------------------------------------------------
void ofApp::update()
{
//    cout << ofGetFrameNum() << endl;
    for(int i = 0; i < balls.size(); i++)
    {
        if(balls[i].visible) balls[i].update();
    }

    for(int i = 0; i < birds1.size(); i++)
    {
        birds1[i].update();
    }
    
    for(int i = 0; i < birds2.size(); i++)
    {
        birds2[i].update();
    }
    
    for(int i = 0; i < birds3.size(); i++)
    {
        birds3[i].update();
    }
    
    for(int i = 0; i < birds4.size(); i++)
    {
        birds4[i].update();
//        birds4[i].update();
    }

    for(int i = 0; i < balls.size(); i++)
    {
        if(balls[i].visible){
            for(int j = 0; j < birds1.size(); j++)
            {
                switch ( balls[i].fish )
                {
                    case 1 :
                        birds1[j].birdAttract(balls[i].pos, 0.06 * balls[i].radius * 0.06);
                        break;
                    case 2 :
                        birds2[j].birdAttract(balls[i].pos, 0.06 * balls[i].radius * 0.06);
                        break;
                    case 3 :
                        birds3[j].birdAttract(balls[i].pos, 0.06 * balls[i].radius * 0.06);
                        break;
                    case 4 :
                        birds4[j].birdAttract(balls[i].pos, 0.06 * balls[i].radius * 0.06);
                        break;
                    case 5 :
                        birds1[j].birdAttract(balls[i].pos, 0.06 * balls[i].radius * 0.06);
                        birds4[j].birdAttract(balls[i].pos, 0.06 * balls[i].radius * 0.06);
                        break;
                }
            }
        }
    }
    
    if( ofGetFrameNum() % ( FRATE * 60 ) == 0){
        counterBall++;
        //        cout << ofGetFrameNum() << endl;
        //        cout << counterBall << endl;
        if(counterBall % 3 == 0) ballGenerate( ofPoint( ofRandom(0, ofGetWidth()), ofRandom( 0, ofGetHeight())),0);
    }

}

//--------------------------------------------------------------
void ofApp::draw()
{
//    ofSetColor(0,0,0,32);
//    ofSetColor(255,255,255,32);
    ofSetColor(bgcolor);
    ofRect( ofGetWidth()/2, ofGetHeight()/2, ofGetWidth(),ofGetHeight() );

    for(int i = 0; i < balls.size(); i++)
    {
        if(balls[i].visible) balls[i].draw();
    }
    
    for(int i = 0; i < birds1.size(); i++)
    {
        birds1[i].draw();
    }
    for(int i = 0; i < birds2.size(); i++)
    {
        birds2[i].draw();
    }
    for(int i = 0; i < birds3.size(); i++)
    {
        birds3[i].draw();
    }
    for(int i = 0; i < birds4.size(); i++)
    {
        birds4[i].draw();
    }

//    cout << curVol << endl;
    if( curVol > SOUDLIMIT) {
        //        cout << curVol << endl;
        ballGenerate( ofPoint( ofRandom(0, ofGetWidth()), ofRandom( 0, ofGetHeight())), curVol * BALLMAX);
        counterBall = 0;
    }
    
    mm = ofGetMinutes();
    if( mm % 10 < 1 ) {
        hh = ofGetHours();
        setNightMode(hh);
        setColorDayNight();
    }
}


//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    curVol = 0.0;
    
    // samples are "interleaved"
    for (int i = 0; i < bufferSize; i++){
        curVol += input[i] * input[i];
    }
    
    //this is how we get the mean of rms :)
    curVol /= bufferSize;
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f')
    {
        ofToggleFullscreen();
    }
    if (key == 'b')
    {
        for(int i = 0; i < balls.size(); i++)
        {
            balls[i].visible = false;
        }
    }
    if (key == 'B')
    {
        for(int i = 0; i < balls.size(); i++)
        {
            balls[i].visible = true;
        }
    }
    
    if (key == 'c')
    {
        balls.clear();
    }
    if (key == 's')
    {
        ofShowCursor();
    }
    if (key == 'h')
    {
        ofHideCursor();
    }
    if( key == 'S' ){
        soundStream.start();
    }
    
    if( key == 'E' ){
        soundStream.stop();
    }
    
    if( key == 'n' ){
        nightmode = true;
        setColorDayNight();
    }
    if( key == 'd' ){
        nightmode = false;
        setColorDayNight();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mouse_pressed = true;
//    myball.visible = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    mouse_pressed = false;
    ballGenerate(ofPoint(x,y),0);
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

//--------------------------------------------------------------
void ofApp::ballGenerate(ofPoint _pos, float _radius){
    if( ballsNum <= balls.size() )
    {
        balls.erase(balls.begin());
    }
    Ball b;
    b.pos = _pos;
    if(_radius > 0.9 ) b.radius = _radius;
    int f = ofRandom(1,6);
    if(nightmode){
        switch ( f )
        {
            case 1: b.bcolor = COLOR1n; b.fish = 1; break;
            case 2: b.bcolor = COLOR2n; b.fish = 2; break;
            case 3: b.bcolor = COLOR3n; b.fish = 3; break;
            case 4: b.bcolor = COLOR4n; b.fish = 4; break;
            case 5: b.bcolor = COLOR5n; b.fish = 5; break;
        }
    }
    else{
        switch ( f )
        {
            case 1: b.bcolor = COLOR1d; b.fish = 1; break;
            case 2: b.bcolor = COLOR2d; b.fish = 2; break;
            case 3: b.bcolor = COLOR3d; b.fish = 3; break;
            case 4: b.bcolor = COLOR4d; b.fish = 4; break;
            case 5: b.bcolor = COLOR5d; b.fish = 5; break;
        }
        
    }
    balls.push_back(b);
    counterBall = 0;
}

//--------------------------------------------------------------
void ofApp::setColorDayNight(){
    if( nightmode ){
        bgcolor = BGCOLORn; // Black
        for(int i = 0; i < BOID1; i++)
        {
            birds1[i].circleColor = COLOR1n;
        }
        for(int i = 0; i < BOID2; i++)
        {
            birds2[i].circleColor = COLOR2n;
        }
        for(int i = 0; i < BOID3; i++)
        {
            birds3[i].circleColor = COLOR3n;
        }
        for(int i = 0; i < BOID4; i++)
        {
            birds4[i].circleColor = COLOR4n;
        }

        for(int i = 0; i < balls.size(); i++)
        {
            switch ( balls[i].fish )
            {
                case 1: balls[i].bcolor = COLOR1n; break;
                case 2: balls[i].bcolor = COLOR2n; break;
                case 3: balls[i].bcolor = COLOR3n; break;
                case 4: balls[i].bcolor = COLOR4n; break;
                case 5: balls[i].bcolor = COLOR5n; break;
            }
        }
        
    }
    else{
        bgcolor = BGCOLORd;
        for(int i = 0; i < BOID1; i++)
        {
            birds1[i].circleColor = COLOR1d;
        }
        for(int i = 0; i < BOID2; i++)
        {
            birds2[i].circleColor = COLOR2d;
        }
        for(int i = 0; i < BOID3; i++)
        {
            birds3[i].circleColor = COLOR3d;
        }
        for(int i = 0; i < BOID4; i++)
        {
            birds4[i].circleColor = COLOR4d;
        }
        for(int i = 0; i < balls.size(); i++)
        {
            switch ( balls[i].fish )
            {
                case 1: balls[i].bcolor = COLOR1d; break;
                case 2: balls[i].bcolor = COLOR2d; break;
                case 3: balls[i].bcolor = COLOR3d; break;
                case 4: balls[i].bcolor = COLOR4d; break;
                case 5: balls[i].bcolor = COLOR5d; break;
            }
        }

    }
}

//--------------------------------------------------------------
void ofApp::setNightMode(int h){
    if( h < DAY_START || h >= NIGHT_START ){
        nightmode = true;
    }
    else {
        nightmode = false;
    }
}

