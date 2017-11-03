#include "Particle.h"



void Particle::update() {

 
    // Update the velocity based on the acceleration.
    velocity += acceleration;
    
    
    // Update the position based on the velocity.
    position += velocity;
    
    age++;
    
}


void Particle::draw() {
//    int randomColor = ofRandom(255);
//    
//    ofSetColor(randomColor, randomColor, randomColor);
    ofDrawCircle(position, radius);
}
