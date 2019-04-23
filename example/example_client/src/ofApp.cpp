#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0);

	//setup port
	tuio.setup(new ofxTuioUdpReceiver(3333));
	//or tcp...
	//tuio.setup(new ofxTuioTcpReceiver(3333));
	

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

	vector<cursor> c = cursors;
	for (int i = 0; i < c.size(); i++) {

		ofVec2f pos = ofVec2f(c[i].pos.x * ofGetWidth(), c[i].pos.y * ofGetHeight());
		string id = ofToString(c[i].sessionID);

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

	vector<cursor> c = cursors;
	for (int i = 0; i < c.size(); i++) {
		if (c[i].sessionID != id) continue;
		c[i].pos = ofVec2f(tuioCursor.getPosition().getX(), tuioCursor.getPosition().getY());
	}
	cursors = c;
}

//--------------------------------------------------------------
void ofApp::tuioRemoved(ofxTuioCursor &tuioCursor) {

	ofVec2f pos = ofVec2f(tuioCursor.getX(), tuioCursor.getY());
	long id = tuioCursor.getSessionID();
	cout << "remove " << id << " at " << pos << endl;

	vector<cursor> c = cursors;
	for (int i = 0; i < c.size(); i++) {
		if (c[i].sessionID != id) continue;
		c.erase(c.begin() + i);
		break;
	}

	cursors = c;

}