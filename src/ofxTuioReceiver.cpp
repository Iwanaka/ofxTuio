#include "ofxTuioReceiver.h"

using namespace ofxTuio;
using namespace TUIO;
//--------------------------------------------------------------
ofxTuioReceiver::ofxTuioReceiver()
{
	client = nullptr;
	protocol = nullptr;
}

//--------------------------------------------------------------
ofxTuioReceiver::~ofxTuioReceiver()
{

	if (client != nullptr) {

		client->removeAllTuioListeners();
		if (client->isConnected()) client->disconnect();

		delete client;
		client = nullptr;
	}

	if (protocol != nullptr) {

		if (protocol->isConnected()) protocol->disconnect();

		delete protocol;
		protocol = nullptr;
	}
}

//--------------------------------------------------------------
void ofxTuioReceiver::setup(ofxTuioReceiverProtcol *protocol) {

	if (client != nullptr) {
		client->removeAllTuioListeners();
		delete client;
		client = nullptr;
	}
	
	ofxTuioReceiverProtcol *_protocol = protocol;
	this->protocol = protocol;
	this->client = new TuioClient(_protocol);

	this->client->addTuioListener(this);

}

//--------------------------------------------------------------
void ofxTuioReceiver::connect(bool lock) {

	if (!client) return;
	this->client->connect(lock);
}

//--------------------------------------------------------------
void ofxTuioReceiver::disconnect() {

	if (!client) return;
	this->client->disconnect();

}

//--------------------------------------------------------------
bool ofxTuioReceiver::isConnected() { return client->isConnected(); }

//--------------------------------------------------------------
void ofxTuioReceiver::addTuioObject(TuioObject *tobj) {
	
	//std::cout << "add obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << "/" << tobj->getTuioSourceID() << ") " << tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle() << std::endl;
	ofNotifyEvent(AddTuioObject, (*tobj), this);

}

//--------------------------------------------------------------
void ofxTuioReceiver::updateTuioObject(TuioObject *tobj) {
	
	//std::cout << "set obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << "/" << tobj->getTuioSourceID() << ") " << tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle()
		//<< " " << tobj->getMotionSpeed() << " " << tobj->getRotationSpeed() << " " << tobj->getMotionAccel() << " " << tobj->getRotationAccel() << std::endl;
	ofNotifyEvent(UpdateTuioObject, (*tobj), this);
}

//--------------------------------------------------------------
void ofxTuioReceiver::removeTuioObject(TuioObject *tobj) {
	
	//std::cout << "del obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << "/" << tobj->getTuioSourceID() << ")" << std::endl;
	ofNotifyEvent(RemoveTuioObject, (*tobj), this);

}

//--------------------------------------------------------------
void ofxTuioReceiver::addTuioCursor(TuioCursor *tcur) {
	
	//std::cout << "add cur " << tcur->getCursorID() << " (" << tcur->getSessionID() << "/" << tcur->getTuioSourceID() << ") " << tcur->getX() << " " << tcur->getY() << std::endl;
	ofNotifyEvent(AddTuioCursor, (*tcur), this);

}

//--------------------------------------------------------------
void ofxTuioReceiver::updateTuioCursor(TuioCursor *tcur) {
	
	//std::cout << "set cur " << tcur->getCursorID() << " (" << tcur->getSessionID() << "/" << tcur->getTuioSourceID() << ") " << tcur->getX() << " " << tcur->getY()
		//<< " " << tcur->getMotionSpeed() << " " << tcur->getMotionAccel() << " " << std::endl;
	ofNotifyEvent(UpdateTuioCursor, (*tcur), this);

}

//--------------------------------------------------------------
void ofxTuioReceiver::removeTuioCursor(TuioCursor *tcur) {
	
	//std::cout << "del cur " << tcur->getCursorID() << " (" << tcur->getSessionID() << "/" << tcur->getTuioSourceID() << ")" << std::endl;
	ofNotifyEvent(RemoveTuioCursor, (*tcur), this);

}

//--------------------------------------------------------------
void ofxTuioReceiver::addTuioBlob(TuioBlob *tblb) {
	
	//std::cout << "add blb " << tblb->getBlobID() << " (" << tblb->getSessionID() << "/" << tblb->getTuioSourceID() << ") " << tblb->getX() << " " << tblb->getY() << " " << tblb->getAngle() << " " << tblb->getWidth() << " " << tblb->getHeight() << " " << tblb->getArea() << std::endl;
	ofNotifyEvent(AddTuioBlob, (*tblb), this);

}

//--------------------------------------------------------------
void ofxTuioReceiver::updateTuioBlob(TuioBlob *tblb) {
	
	//std::cout << "set blb " << tblb->getBlobID() << " (" << tblb->getSessionID() << "/" << tblb->getTuioSourceID() << ") " << tblb->getX() << " " << tblb->getY() << " " << tblb->getAngle() << " " << tblb->getWidth() << " " << tblb->getHeight() << " " << tblb->getArea()
		//<< " " << tblb->getMotionSpeed() << " " << tblb->getRotationSpeed() << " " << tblb->getMotionAccel() << " " << tblb->getRotationAccel() << std::endl;
	ofNotifyEvent(UpdateTuioBlob, (*tblb), this);

}

//--------------------------------------------------------------
void ofxTuioReceiver::removeTuioBlob(TuioBlob *tblb) {
	
	//std::cout << "del blb " << tblb->getBlobID() << " (" << tblb->getSessionID() << "/" << tblb->getTuioSourceID() << ")" << std::endl;
	ofNotifyEvent(RemoveTuioBlob, (*tblb), this);

}

//--------------------------------------------------------------
void  ofxTuioReceiver::refresh(TuioTime frameTime) {
	//std::cout << "refresh " << frameTime.getTotalMilliseconds() << std::endl;
}