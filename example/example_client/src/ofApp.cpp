#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0);

	//setup port
	tuio.setup(new ofxTuioUdpReceiver(3333));

	//add event
	ofAddListener(tuio.AddTuioCursor, this, &ofApp::tuioAdded);
	ofAddListener(tuio.UpdateTuioCursor, this, &ofApp::tuioUpdated);
	ofAddListener(tuio.RemoveTuioCursor, this, &ofApp::tuioRemoved);

	//you can use lock.
	//When you want to only receive, use it.
	tuio.connect(false);
	cout << "connect : " << tuio.isConnected() << endl;

}

//--------------------------------------------------------------
void ofApp::draw(){

	vector<cursor>::iterator it;
	for (it = cursors.begin(); it != cursors.end(); it++) {

		ofVec2f pos = ofVec2f(it->pos.x * ofGetWidth(), it->pos.y * ofGetHeight());
		string id = ofToString(it->sessionID);

		ofSetColor(255);
		ofDrawCircle(pos, 20);

		ofSetColor(0);
		ofDrawBitmapString(id, pos);
	}

}

//--------------------------------------------------------------
void ofApp::tuioAdded(ofxTuioCursor &tuioCursor) {

	ofVec2f pos = ofVec2f(tuioCursor.getX(), tuioCursor.getY());
	long id = tuioCursor.getSessionID();
	cout << "add " << id << " at " << pos << endl;

	cursor c;
	c.pos = pos;
	c.sessionID = id;
	cursors.push_back(c);

}

//--------------------------------------------------------------
void ofApp::tuioUpdated(ofxTuioCursor &tuioCursor) {

	ofVec2f pos = ofVec2f(tuioCursor.getX(), tuioCursor.getY());
	long id = tuioCursor.getSessionID();
	cout << "update " << id << " at " << pos << endl;

	vector<cursor>::iterator it;
	for (it = cursors.begin(); it != cursors.end(); it++) {
		if (it->sessionID == id) {
			it->pos = pos;
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::tuioRemoved(ofxTuioCursor &tuioCursor) {

	ofVec2f pos = ofVec2f(tuioCursor.getX(), tuioCursor.getY());
	long id = tuioCursor.getSessionID();
	cout << "remove " << id << " at " << pos << endl;

	vector<cursor>::iterator it;
	for (it = cursors.begin(); it != cursors.end(); it++) {
		if (it->sessionID == id) {
			cursors.erase(it);
			break;
		}
	}
}