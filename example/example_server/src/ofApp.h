#pragma once

#include "ofMain.h"
#include "ofxTuio.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyReleased(int key);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		
		struct detectArea {
			ofRectangle rect;
			bool isPress;
		};

		detectArea area;
		ofxTuioSender tuio;
		bool isPress = false;

};
