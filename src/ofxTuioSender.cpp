#include "ofxTuioSender.h"

using namespace ofxTuio;
using namespace TUIO;
using namespace std;

bool InRectCheck(ofRectangle rect, float x, float y) {

	if (rect.x <= x &&
		x <= rect.x + rect.width &&
		rect.y <= y &&
		y <= rect.y + rect.height)
	{
		return 1;
	}
	else {
		return 0;
	}

}

//--------------------------------------------------------------
ofxTuioSender::ofxTuioSender():
	isRun(false),
	isAutoFit(false),
	screen(0, 0, ofGetWidth(), ofGetHeight())
{
	tuioServer = nullptr;
}

//--------------------------------------------------------------
ofxTuioSender::~ofxTuioSender()
{
	activeCursorList.clear();
	if (tuioServer != nullptr) {
		delete tuioServer;
		tuioServer = nullptr;
	}
}

//--------------------------------------------------------------
void ofxTuioSender::setup(ofxTuioSenderProtcol *protocol, string sourceName) {

	ofxTuioSenderProtcol *_protocol = protocol;
	TuioTime::initSession();
	frameTime = TuioTime::getSessionTime();

	tuioServer = new TuioServer(_protocol);
	tuioServer->setSourceName(sourceName.c_str());
	
}

//--------------------------------------------------------------
void ofxTuioSender::addProtocol(ofxTuioSenderProtcol *protocol) {

	if (!tuioServer) return;
	ofxTuioSenderProtcol *_p = protocol;
	tuioServer->addOscSender(_p);

}

//--------------------------------------------------------------
void ofxTuioSender::begin() {

	if (!isRun || !tuioServer) return;
	frameTime = TuioTime::getSessionTime();
	tuioServer->initFrame(frameTime);

}

//--------------------------------------------------------------
void ofxTuioSender::end() {

	if (!isRun || !tuioServer) return;
	tuioServer->stopUntouchedMovingCursors();
	tuioServer->commitFrame();

}

//--------------------------------------------------------------
void ofxTuioSender::run() { 
	reset();
	isRun = true; 
}

//--------------------------------------------------------------
void ofxTuioSender::stop() { isRun = false; }

//--------------------------------------------------------------
void ofxTuioSender::addObject(float obj_x, float obj_y) {

	float _x = obj_x, _y = obj_y;
	if (isAutoFit) {

		bool b = InRectCheck(screen, obj_x, obj_y);
		if (!b) return;

		_x = (obj_x - screen.x) / screen.width;
		_y = (obj_y - screen.y) / screen.height;

	}
	else {
		_x /= ofGetWidth();
		_y /= ofGetHeight();
	}


	TuioCursor *cursor = tuioServer->addTuioCursor(_x, _y);
	activeCursorList.push_back(cursor);

}

//--------------------------------------------------------------
void ofxTuioSender::updateObject(float obj_x, float obj_y) {

	float _x = obj_x, _y = obj_y;
	float width = ofGetWidth();

	if (isAutoFit) {

		bool b = InRectCheck(screen, obj_x, obj_y);
		if (!b) return;

		_x = (obj_x - screen.x) / screen.width;
		_y = (obj_y - screen.y) / screen.height;

		width = screen.width;

	}
	else {
		_x /= ofGetWidth();
		_y /= ofGetHeight();
	}

	TuioCursor *cursor = NULL;
	for (std::list<TuioCursor*>::iterator iter = activeCursorList.begin(); iter != activeCursorList.end(); iter++) {
		TuioCursor *tcur = (*iter);
		float _d = tcur->getDistance(_x, _y);

		if (_d < width) {
			width = _d;
			cursor = tcur;
		}
	}

	if (cursor == NULL) return;
	if (cursor->getTuioTime() == frameTime) return;
	
	tuioServer->updateTuioCursor(cursor, _x, _y);

}

//--------------------------------------------------------------
void ofxTuioSender::removeObject(float obj_x, float obj_y) {

	float _x = obj_x, _y = obj_y;

	if (isAutoFit) {

		bool b = InRectCheck(screen, obj_x, obj_y);
		if (!b) return;

		_x = (obj_x - screen.x) / screen.width;
		_y = (obj_y - screen.y) / screen.height;
		
	}
	else {
		_x /= ofGetWidth();
		_y /= ofGetHeight();
	}


	TuioCursor *cursor = NULL;
	float distance = 0.01f;

	for (std::list<TuioCursor*>::iterator iter = activeCursorList.begin(); iter != activeCursorList.end(); iter++) {
		TuioCursor *tcur = (*iter);
		float _d = tcur->getDistance(_x, _y);
		if (_d < distance) {
			distance = _d;
			cursor = tcur;
		}
	}

	if (cursor != NULL) {
		activeCursorList.remove(cursor);
		tuioServer->removeTuioCursor(cursor);
	}

}

//--------------------------------------------------------------
void ofxTuioSender::setAutoFitScreenArea(const ofRectangle &screen) { this->screen = screen; }

//--------------------------------------------------------------
void ofxTuioSender::setAutoFitRange(bool b) { isAutoFit = b; }

//--------------------------------------------------------------
void ofxTuioSender::setAutoFitRange(bool b, const ofRectangle &screen) {
	
	setAutoFitRange(b);
	setAutoFitScreenArea(screen);

}

//--------------------------------------------------------------
void ofxTuioSender::setAutoFitRange(bool b, int screen_x, int screen_y, int screen_w, int screen_h) {

	setAutoFitRange(b);
	setAutoFitScreenArea(ofRectangle(screen_x, screen_y, screen_w, screen_h));

}

//--------------------------------------------------------------
void ofxTuioSender::setObjectProfile(bool b) { tuioServer->enableObjectProfile(b); }

//--------------------------------------------------------------
void ofxTuioSender::setCursorProfile(bool b) { tuioServer->enableCursorProfile(b); }

//--------------------------------------------------------------
void ofxTuioSender::setBlobProfile(bool b) { tuioServer->enableBlobProfile(b); }

//--------------------------------------------------------------
void ofxTuioSender::setFullUpdate(bool b) {
	if (b) tuioServer->enableFullUpdate();
	else tuioServer->disableFullUpdate();
}

//--------------------------------------------------------------
void ofxTuioSender::setPeriodicMessages(bool b) {
	if (b) tuioServer->enablePeriodicMessages();
	else tuioServer->disablePeriodicMessages();
}

//--------------------------------------------------------------
void ofxTuioSender::setVerbose(bool b) { tuioServer->setVerbose(b); }

//--------------------------------------------------------------
bool ofxTuioSender::hasObjectProfile() { return tuioServer->hasObjectProfile(); }

//--------------------------------------------------------------
bool ofxTuioSender::hasCursorProfile() { return tuioServer->hasCursorProfile(); }

//--------------------------------------------------------------
bool ofxTuioSender::hasBlobProfile() { return tuioServer->hasBlobProfile(); }

//--------------------------------------------------------------
bool ofxTuioSender::hasFullUpdate() { return tuioServer->fullUpdateEnabled(); }

//--------------------------------------------------------------
bool ofxTuioSender::hasPeriodicMessages() { return tuioServer->periodicMessagesEnabled(); }

//--------------------------------------------------------------
bool ofxTuioSender::hasVerbose() { return tuioServer->isVerbose(); }

//--------------------------------------------------------------
bool ofxTuioSender::hasAutoFitRange() { return isAutoFit; }

//--------------------------------------------------------------
ofRectangle ofxTuioSender::getScreen() { return screen; }

//--------------------------------------------------------------
void ofxTuioSender::reset() {

	tuioServer->resetTuioCursors();
	activeCursorList.clear();

}

//--------------------------------------------------------------
int ofxTuioSender::getCursorSize(){ return tuioServer->getTuioCursorCount(); }

//--------------------------------------------------------------
std::vector<ofVec2f> ofxTuioSender::getCursors() {

	std::vector<ofVec2f> curs;

	std::list<TuioCursor*> _c = tuioServer->getTuioCursors();
	for (std::list<TuioCursor*>::iterator iter = _c.begin(); iter != _c.end(); iter++) {
		
		if (*iter != nullptr) {
			TuioCursor *tcur = (*iter);
			float x = tcur->getX();
			float y = tcur->getY();

			curs.push_back(ofVec2f(x, y));

		}
	}
	
	return curs;
}

//--------------------------------------------------------------
std::list<TUIO::TuioCursor*> ofxTuioSender::getCursorsPointer() { return tuioServer->getTuioCursors(); }