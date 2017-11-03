#pragma once


#include "ofMain.h"
#include "Particle.h"
#include "ofxCvHaarFinder.h"
#include <sstream>

class ofApp : public ofBaseApp
{
public:
    void setup() override;
    void update() override;
    void draw() override;

    ofVideoGrabber grabber;
    ofxCvHaarFinder finder;

    ofPixels capturePixels;
    ofTexture captureTexture;


    // Particle System
    void mousePressed(int x, int y, int button) override;

    void addParticleAtPosition(float x, float y);


    std::vector<Particle> particles;

    // For Capturing Images:
    ofImage img;
    void keyPressed(int key) override;
    int noOfImages = 0;
};



};
