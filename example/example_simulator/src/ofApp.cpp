#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0);	
	sender.setup(new ofxTuioOscSender("127.0.0.1", 3333), "example");
	sender.setAutoFitRange(true, ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
	sender.run();

}

//--------------------------------------------------------------
void ofApp::update(){

	float x = (float)ofGetMouseX(), y = (float)ofGetMouseY();
	bool mouse = ofGetMousePressed(0);
	sender.begin();
	{
		if (mouse && !isPress) {
			isPress = true;
			sender.addObject(x, y);
		}

		if (isPress) sender.updateObject(x, y);
		
		if (!mouse && isPress) {
			isPress = false;
			sender.removeObject(x, y);
		}
	}
	sender.end();

}

//--------------------------------------------------------------
void ofApp::draw(){

	vector<ofVec2f> cursors = sender.getCursors();
	vector<ofVec2f>::iterator it;
	for (it = cursors.begin(); it != cursors.end(); it++) {

        ofDrawCircle(
            glm::vec2(
                sender.getScreen().x + it->x * sender.getScreen().width,
                sender.getScreen().y + it->y * sender.getScreen().height),
            20);

	}

	ofSetColor(255);
	ofDrawBitmapString("left click and drag : send mouse position as tuio protocol", 20, 20);

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	if (key == 'r') sender.reset();

}
