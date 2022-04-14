#pragma once

#include "ofMain.h"

struct ShapeColors {
    ofColor outer;
    ofColor middle;
    ofColor inner;
    
    ShapeColors(ofColor, ofColor, ofColor);
};

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);

        float distance = 0;
        float previousMouseX = 0;
        float previousMouseY = 0;
};
