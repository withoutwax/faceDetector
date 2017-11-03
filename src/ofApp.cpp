#include "ofApp.h"


void ofApp::setup()
{
    grabber.setup(640, 480);
    finder.setup("haarcascade_frontalface_default.xml");

    captureTexture.allocate(200, 200, GL_RGBA);

}


void ofApp::update()
{
    // Camera Update
    grabber.update();

    if (grabber.isFrameNew())
    {
        finder.findHaarObjects(grabber.getPixels());
    }






    // Particle System
    auto iter  = particles.begin();

    while (iter != particles.end()) {

        iter->update();

        if (iter->age > 120 || iter->position.y > ofGetHeight() || iter->position.x > ofGetWidth() || iter->position.x < 0) {
            // Delete the particle from the collection.
            iter = particles.erase(iter);
        } else {
            iter++;
        }
    }
}


void ofApp::draw()
{

    ofFill();
    ofSetColor(255);
    grabber.draw(0, 0);


    // Face tracking App
     ofNoFill();
     for(unsigned int i = 0; i < finder.blobs.size(); i++)
     {
     // Ignore small "faces".
     if (finder.blobs[i].boundingRect.getArea() > 150 * 150)
     {
     ofRectangle rect = finder.blobs[i].boundingRect;

     float xNose = rect.getCenter().x;
     float yNose = rect.getCenter().y;
     float yEye = rect.getCenter().y - 0.11 * rect.getHeight();
     float yMouth = rect.getCenter().y + 0.24 * rect.getHeight();
     float xEyeOffset = 0.18 * rect.getWidth();

     float xEyeRight = xNose + xEyeOffset;
     float xEyeLeft  = xNose - xEyeOffset;

     ofDrawCircle(xEyeRight, yEye, 10);
     ofDrawCircle(xEyeLeft, yEye, 10);

     ofDrawCircle(xNose, yNose, 10);

     ofDrawRectangle(xNose - 20, yMouth - 5, 40, 10);

     ofDrawRectangle(rect);

     }
     }



    // Particle System
    // A "range-for" loop.
    for (Particle& p: particles) {
        int gray = ofMap(p.age, 0, 120, 0, 255);
        //int decRadius = ofMap(p.age, 0, 120, p.radius, 0);
        ofSetColor(gray);
        //p.radius = decRadius;
        p.draw();
    }


    // Continuous spit of balls
    //addParticleAtPosition(ofGetMouseX(), ofGetMouseY());




    captureTexture.draw(ofGetMouseX(), ofGetMouseY(), 200, 200);
}




void ofApp::mousePressed(int x, int y, int button) {

    int randomNoParticles = ofRandom(10);

    for (int i = 0; i < randomNoParticles; i++) {
        addParticleAtPosition(x, y);
    }

    // Save the (Section of the) image
    capturePixels = grabber.getPixels();

    // Upload the captured pixels to the texture.
    captureTexture.loadData(capturePixels);



}


void ofApp::addParticleAtPosition(float x, float y) {

    Particle p;
    p.position.x = x;
    p.position.y = y;

    p.velocity.x = ofRandom(-10, 10);
    p.velocity.y = ofRandom(-10, 10);

    p.acceleration.y = 0.5;

    // Add the particle instance to our collection of particles.
    particles.push_back(p);



}


// Take a screen shot!
void ofApp::keyPressed(int key) {
    if (key == ' ') {

        char c = (char)noOfImages;

        img.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
        img.save("screenshot.png");
        noOfImages++;
    }
}
