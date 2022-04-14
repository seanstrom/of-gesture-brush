#include "ofApp.h"

bool drawIsOn = false;
bool darkTheme = true;
bool bgShapesTheme = true;
bool palleteTheme = true;
ofColor bgColor = ofColor(darkTheme ? 0: 250);

ShapeColors::ShapeColors(ofColor outerColor, ofColor middleColor, ofColor innerColor) {
    outer = outerColor;
    middle = middleColor;
    inner = innerColor;
}

ShapeColors pickRandomColors(float alphaOffset = 0) {
    float darkerRedValue = ofRandom(5, 175);
    float darkerGreenValue = ofRandom(80, 200);
    float darkerBlueValue = ofRandom(10, 200);
    
    float lighterRedValue = ofRandom(155, 255);
    float lighterGreenValue = ofRandom(155, 255);
    float lighterBlueValue = ofRandom(155, 255);
    
    float bgAlpha = 92 + alphaOffset;
    float fgAlpha = 120 + alphaOffset;
    
    if (palleteTheme) {
        ofColor outerColor(140, 85);
        ofColor darkerColor(darkerRedValue, darkerGreenValue, darkerBlueValue, bgAlpha);
        ofColor lighterColor(lighterRedValue, lighterGreenValue, lighterBlueValue, fgAlpha);
        return ShapeColors(outerColor, darkerColor, lighterColor);
    } else {
        ofColor outerColor(200, 85);
        ofColor darkerColor(darkerRedValue, darkerGreenValue, darkerBlueValue, fgAlpha);
        ofColor lighterColor(lighterRedValue, lighterGreenValue, lighterBlueValue, bgAlpha);
        return ShapeColors(outerColor, lighterColor, darkerColor);
    }
}

ofColor getThemeBg() {
    return ofColor(darkTheme ? 0: 250);
}


//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(60);
    ofSetCircleResolution(200);
    ofSetBackgroundAuto(false);
    ofSetBackgroundColor(bgColor);
}

//--------------------------------------------------------------
void ofApp::update() {
    distance = ofDist(previousMouseX, previousMouseY, mouseX, mouseY);
    previousMouseX = mouseX;
    previousMouseY = mouseY;
}

//--------------------------------------------------------------
void ofApp::draw() {
    if (drawIsOn) {
        float posX = mouseX;
        float posY = mouseY;
        float roundedRectRadius = 5;
        float randomTag = ofRandom(1, 3);
        float clampedDistance = ofClamp(distance, 10, 100);
        float alphaOffset = ofMap(clampedDistance, 10, 100, 0, 70);
        ShapeColors colors = pickRandomColors(alphaOffset);
        
        float innerOffset =
              randomTag >= 3 ? 0.90f
            : randomTag >= 2 ? 0.85f
            : randomTag >= 1 ? 0.80f
            : 0.8f;

        
        // Calculate Sizes
        
        float radius = clampedDistance;
        float outerRadius = radius + 4;
        float innerRadius = radius * innerOffset;
        
        float innerShapeSide = innerRadius / 2;
        float outerShapeSide = outerRadius / 2;
        float middleShapeSide = radius / 2;


        // Draw Shapes
        
        ofSetColor(colors.outer);
        ofRectangle outerRect = ofRectangle();
        outerRect.setFromCenter(posX, posY, outerShapeSide, outerShapeSide);
        ofDrawRectRounded(outerRect, roundedRectRadius);
        
        ofSetColor(colors.middle);
        ofRectangle rect = ofRectangle();
        rect.setFromCenter(posX, posY, middleShapeSide, middleShapeSide);
        ofDrawRectRounded(rect, roundedRectRadius);
        
        ofSetColor(colors.inner);
        ofRectangle innerRect(posX, posY, innerShapeSide, innerShapeSide);
        ofDrawRectRounded(innerRect, roundedRectRadius);

        
        // Draw background shapes
        
        ofNoFill();
        ofSetLineWidth(3);
        ofSetColor(bgShapesTheme ? 90 : 220, 10);
    
        float backgroundRadius = radius * 2.5f;
        while(backgroundRadius > 0) {
            backgroundRadius -= 5;
            ofSetCircleResolution(3);
            ofDrawCircle(posX, posY, backgroundRadius);
        }
        
        ofSetCircleResolution(200);
        ofFill();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == ' ') {
        palleteTheme = !palleteTheme;
    }
    
    if (key == OF_KEY_TAB) {
        bgShapesTheme = !bgShapesTheme;
    }
    
    if (key == OF_KEY_BACKSPACE) {
        ofClear(getThemeBg());
    }
    
    if (key == OF_KEY_RETURN) {
        darkTheme = !darkTheme;
        ofClear(getThemeBg());
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    drawIsOn = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    drawIsOn = false;
}