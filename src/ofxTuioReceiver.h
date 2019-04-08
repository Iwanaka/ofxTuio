#pragma once
#include "TuioClient.h"
#include "TuioListener.h"
#include "UdpReceiver.h"
#include "TcpReceiver.h"
#include "ofEvents.h"

namespace ofxTuio {

	typedef TUIO::TcpReceiver ofxTuioTcpReceiver;
	typedef TUIO::UdpReceiver ofxTuioUdpReceiver;
	typedef TUIO::OscReceiver ofxTuioReceiverProtcol;
	typedef TUIO::TuioObject ofxTuioObject;
	typedef TUIO::TuioCursor ofxTuioCursor;
	typedef TUIO::TuioBlob ofxTuioBlob;

	class ofxTuioReceiver : public TUIO::TuioListener
	{
	public:
		ofxTuioReceiver();
		~ofxTuioReceiver();

		void setup(ofxTuioReceiverProtcol *protocol);
		void connect(bool lock = false);
		void disconnect();
		bool isConnected();

		ofEvent<ofxTuioObject> AddTuioObject;
		ofEvent<ofxTuioObject> UpdateTuioObject;
		ofEvent<ofxTuioObject> RemoveTuioObject;

		ofEvent<ofxTuioCursor> AddTuioCursor;
		ofEvent<ofxTuioCursor> UpdateTuioCursor;
		ofEvent<ofxTuioCursor> RemoveTuioCursor;

		ofEvent<ofxTuioBlob> AddTuioBlob;
		ofEvent<ofxTuioBlob> UpdateTuioBlob;
		ofEvent<ofxTuioBlob> RemoveTuioBlob;

	private:

		void addTuioObject(TUIO::TuioObject *tobj) override;
		void updateTuioObject(TUIO::TuioObject *tobj) override;
		void removeTuioObject(TUIO::TuioObject *tobj) override;

		void addTuioCursor(TUIO::TuioCursor *tcur) override;
		void updateTuioCursor(TUIO::TuioCursor *tcur) override;
		void removeTuioCursor(TUIO::TuioCursor *tcur) override;

		void addTuioBlob(TUIO::TuioBlob *tblb) override;
		void updateTuioBlob(TUIO::TuioBlob *tblb) override;
		void removeTuioBlob(TUIO::TuioBlob *tblb) override;

		void refresh(TUIO::TuioTime frameTime) override;

		ofxTuioReceiverProtcol *protocol;
		TUIO::TuioClient *client;

	};

}