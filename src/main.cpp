#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
    auto settings = ofGLFWWindowSettings();
    settings.doubleBuffering = false;
    settings.setSize(1024, 768);

    ofCreateWindow(settings);
	ofRunApp(new ofApp());
}
