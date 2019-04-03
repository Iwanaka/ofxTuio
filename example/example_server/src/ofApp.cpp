#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0);

	//setup address, port and server name. basically it is UDP protocol.
	tuio.setup(new ofxTuioOscSender("127.0.0.1", 3333), "example");
	
	//add protocol if you want
	//tuio.addProtocol(new ofxTuioWebSocketSender(8080));
	//tuio.addProtocol(new ofxTuioFlashSender());
	//tuio.addProtocol(new ofxTuio::ofxTuioTcpSender(3333));

	//setting etc
	tuio.setObjectProfile(false);
	tuio.setBlobProfile(false);

	//set detect area info
	area.rect.set(0, 0, ofGetWidth(), ofGetHeight());
	area.isPress = false;

	//auto calculate, fit to range 0.0 - 1.0
	tuio.setAutoFitRange(true, area.rect);

	//starting position send
	tuio.run();

}

//--------------------------------------------------------------
void ofApp::update(){

	int size = 3;
	float x = (float)ofGetMouseX(), y = (float)ofGetMouseY();
	bool mouse = ofGetMousePressed(0);

	//Please enter the content if you want to send.
	tuio.begin();
	{
		//add new object
		if (mouse && !isPress) {
			isPress = true;
			for (int i = 0; i < size; i++)
				tuio.addObject(x + i * 50, y + i * 50);
		}


		//update object only already exits and mutched session id
		if (isPress) {
			for (int i = 0; i < size; i++)
				tuio.updateObject(x + i * 50, y + i * 50);
		}


		//remove object
		if (!mouse && isPress) {
			isPress = false;
			for (int i = 0; i < size; i++)
				tuio.removeObject(x + i * 50, y + i * 50);
		}
	}
	tuio.end();

}

//--------------------------------------------------------------
void ofApp::draw(){

	//area
	ofSetColor(255);
	ofNoFill();
	ofSetLineWidth(2);
	ofDrawRectangle(area.rect);
	ofFill();


	// draw the sending cursor position and etc
	ofSetColor(ofColor::red);

	//get current cursors
	vector<ofVec2f> cursors = tuio.getCursors();
	vector<ofVec2f>::iterator it;
	for (it = cursors.begin(); it != cursors.end(); it++) {

		ofDrawCircle(
			glm::vec2(
				tuio.getScreen().x + it->x * tuio.getScreen().width,
				tuio.getScreen().y + it->y * tuio.getScreen().height),
			20);

	}


	ofSetColor(255);
	ofDrawBitmapString("left click and drag : send mouse position as tuio protocol", 20, 20);
	ofDrawBitmapString("right click and drag : change detecting area", 20, 40);
	ofDrawBitmapString("r key : clear current arguments and infomations", 20, 60);


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	//reset arguments
	if (key == 'r') tuio.reset();

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

	if (area.isPress && button == 2)
		area.rect = ofRectangle(area.rect.position, x - area.rect.x, y - area.rect.y);

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	if (button == 2) {
		area.isPress = true;
		area.rect = ofRectangle(x, y, 0, 0);
	}

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

	if (area.isPress || button == 2) {
		area.isPress = false;
		//update area
		tuio.setAutoFitScreenArea(area.rect);
	}
}

