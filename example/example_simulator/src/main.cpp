#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){

	ofGLFWWindowSettings settings;

	//sender window
	settings.setSize(600, 600);
	settings.setPosition(ofVec2f(0, 0));
	shared_ptr<ofAppBaseWindow> senderWindow = ofCreateWindow(settings);

	//receiver window
	settings.setSize(300, 300);
	settings.setPosition(ofVec2f(600, 0));
	shared_ptr<ofAppBaseWindow> receiverWindow = ofCreateWindow(settings);


	shared_ptr<ofApp> senderApp(new ofApp);
	shared_ptr<tuioReceiver> receiverApp(new tuioReceiver);


	ofRunApp(receiverWindow, receiverApp);
	ofRunApp(senderWindow, senderApp);

	ofRunMainLoop();

}
