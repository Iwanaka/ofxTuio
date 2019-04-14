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

	list<cursor*>::iterator it;
	for (it = cursors.begin(); it != cursors.end(); it++) {

		auto c = (*it);

		ofVec2f pos = ofVec2f(c->pos.x * ofGetWidth(), c->pos.y * ofGetHeight());
		string id = ofToString(c->sessionID);

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

	cursor *c = new cursor();
	c->pos = pos;
	c->sessionID = id;
	cursors.push_back(c);

}

//--------------------------------------------------------------
void ofApp::tuioUpdated(ofxTuioCursor &tuioCursor) {

	ofVec2f pos = ofVec2f(tuioCursor.getX(), tuioCursor.getY());
	long id = tuioCursor.getSessionID();
	cout << "update " << id << " at " << pos << endl;

	list<cursor*>::iterator it;
	for (it = cursors.begin(); it != cursors.end(); it++) {
		auto _c = (*it);
		if (_c->sessionID != id) continue;
		
		_c->pos = ofVec2f(tuioCursor.getPosition().getX(), tuioCursor.getPosition().getY());

	}
}

//--------------------------------------------------------------
void ofApp::tuioRemoved(ofxTuioCursor &tuioCursor) {

	ofVec2f pos = ofVec2f(tuioCursor.getX(), tuioCursor.getY());
	long id = tuioCursor.getSessionID();
	cout << "remove " << id << " at " << pos << endl;

	cursor *c = nullptr;
	list<cursor*>::iterator it;
	for (it = cursors.begin(); it != cursors.end(); it++) {
		auto _c = (*it);
		if (_c->sessionID != id) continue;
		c = _c;
	}

	cursors.remove(c);

}