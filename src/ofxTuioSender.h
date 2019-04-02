#pragma once
#include "TuioServer.h"
#include "TuioCursor.h"
#include "ofRectangle.h"
#include "ofVec2f.h"
#include "ofAppRunner.h"

namespace ofxTuio {

	typedef TUIO::UdpSender ofxTuioOSC;
	typedef TUIO::WebSockSender ofxTuioWebSocket;
	typedef TUIO::TcpSender ofxTuioTCP;
	typedef TUIO::FlashSender ofxTuioFlash;

	typedef TUIO::OscSender ofxTuioProtocol;

	class ofxTuioSender
	{
	public:
		ofxTuioSender();
		~ofxTuioSender();

		void setup(ofxTuioProtocol *protocol, std::string sourceName);
		void addProtocol(ofxTuioProtocol *protocol);
		void run();
		void stop();
		void begin();
		void end();


		void addObject(float obj_x, float obj_y);
		void updateObject(float obj_x, float obj_y);
		void removeObject(float obj_x, float obj_y);


		void setAutoFitScreenArea(const ofRectangle &screen);
		void setAutoFitRange(bool b);
		void setAutoFitRange(bool b, const ofRectangle &screen);
		void setAutoFitRange(bool b, int screen_x, int screen_y, int screen_w, int screen_h);
		
		void setObjectProfile(bool b);
		void setCursorProfile(bool b);
		void setBlobProfile(bool b);
		void setFullUpdate(bool b);
		void setPeriodicMessages(bool b);
		void setVerbose(bool b);

		bool hasObjectProfile();
		bool hasCursorProfile();
		bool hasBlobProfile();
		bool hasFullUpdate();
		bool hasPeriodicMessages();
		bool hasVerbose();

		bool hasAutoFitRange();
		ofRectangle getScreen();

		void reset();

		int getCursorSize();
		std::vector<ofVec2f> getCursors();
		std::list<TUIO::TuioCursor*> getCursorsPointer();

	private:

		TUIO::TuioTime frameTime;
		TUIO::TuioServer *tuioServer;
		std::list<TUIO::TuioCursor*> activeCursorList;

		bool isRun, isAutoFit;
		ofRectangle screen;

	};

}