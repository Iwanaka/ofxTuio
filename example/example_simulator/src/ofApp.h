#pragma once

#include "ofMain.h"
#include "ofxTuio.h"

class tuioReceiver : public ofBaseApp {

public: 

	void setup() {

		ofBackground(0);
		receiver.setup(new ofxTuioUdpReceiver(3333));
		ofAddListener(receiver.AddTuioCursor, this, &tuioReceiver::tuioAdded);
		ofAddListener(receiver.UpdateTuioCursor, this, &tuioReceiver::tuioUpdated);
		ofAddListener(receiver.RemoveTuioCursor, this, &tuioReceiver::tuioRemoved);

		receiver.connect();

	}
	void draw() {

		ofSetColor(ofColor::yellow);
		ofDrawCircle(cur.x * ofGetWidth(), cur.y * ofGetHeight(), 30);

	}

	void tuioAdded(ofxTuioCursor & tuioCursor) {
		ofVec2f pos = ofVec2f(tuioCursor.getX(), tuioCursor.getY());
		long id = tuioCursor.getSessionID();
		cout << "add " << id << " at " << pos << endl;

		cur = pos;

	}
	void tuioUpdated(ofxTuioCursor & tuioCursor) {
		ofVec2f pos = ofVec2f(tuioCursor.getX(), tuioCursor.getY());
		long id = tuioCursor.getSessionID();
		cout << "update " << id << " at " << pos << endl;

		cur = pos;

	}
	void tuioRemoved(ofxTuioCursor & tuioCursor) {
		ofVec2f pos = ofVec2f(tuioCursor.getX(), tuioCursor.getY());
		long id = tuioCursor.getSessionID();
		cout << "remove " << id << " at " << pos << endl;

		cur = pos;

	}

private:

	ofxTuioReceiver receiver;
	ofVec2f cur;

};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyReleased(int key);

		ofxTuioSender sender;
		bool isPress;

};
