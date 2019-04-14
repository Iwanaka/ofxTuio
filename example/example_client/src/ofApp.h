#pragma once

#include "ofMain.h"
#include "ofxTuio.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void draw();
		
		void tuioAdded(ofxTuioCursor & tuioCursor);
		void tuioRemoved(ofxTuioCursor & tuioCursor);
		void tuioUpdated(ofxTuioCursor & tuioCursor);

		struct cursor {
			ofVec2f pos;
			long sessionID;
		};
		list<cursor*> cursors;

		ofxTuioReceiver tuio;

};
