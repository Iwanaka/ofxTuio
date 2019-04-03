# ofxTuio

### Overview
This addon is Tuio1.1 wrapper for openframeworks. <br>
https://www.tuio.org/?specification <br>
It included samples are "server", "client" and "simulator".<br>

### Dependency
ofxOsc

### Examples
#### client and server
<img src="images/crousel.gif" width="612px">

#### tuio simulator
<img src="images/crousel.gif" width="450px">

### Getting Started

#### client
1. include "ofxTuio.h" and instance the class
```cpp
#include "ofxTuio.h"

class ofApp : public ofBaseApp{

	void setup();
	void update();
	void draw();


	//event notify classes
	void tuioAdded(ofxTuioCursor & tuioCursor);
	void tuioRemoved(ofxTuioCursor & tuioCursor);
	void tuioUpdated(ofxTuioCursor & tuioCursor);

	ofxTuioReceiver tuio;

```

2. setup connect port and notify events
```cpp

//set up port and chose protocol
tuio.setup(new ofxTuioUdpReceiver(3333));
//or tcp...
//tuio.setup(new ofxTuioTcpReceiver(3333));

//add event listener
ofAddListener(tuio.AddTuioCursor, this, &ofApp::tuioAdded);
ofAddListener(tuio.UpdateTuioCursor, this, &ofApp::tuioUpdated);
ofAddListener(tuio.RemoveTuioCursor, this, &ofApp::tuioRemoved);

//connect
tuio.connect();

```

#### server
1. include "ofxTuio.h" and instance the class
```cpp
#include "ofxTuio.h"

class ofApp : public ofBaseApp{

	void setup();
	void update();
	void draw();

	ofxTuioSender tuio;

	//mouse click flag for just this example
	bool isPress = false;

```

2. setup protocol. address and port.
```cpp

//setup address, port and server name. basically it is UDP protocol.
tuio.setup(new ofxTuioOscSender("127.0.0.1", 3333), "example");
//add protocol if you want
//tuio.addProtocol(new ofxTuioWebSocketSender(8080));
//tuio.addProtocol(new ofxTuioFlashSender());
//tuio.addProtocol(new ofxTuio::ofxTuioTcpSender(3333));

//auto calculate, fit to range 0.0 - 1.0. ofRectangle is screen size
tuio.setAutoFitRange(true, ofRectangle( 0, 0, 500, 500));

//starting position send
tuio.run();

```

3. adding object. Object is you want send position between begin() - end(). 
```cpp

tuio.begin();
{

	float x = (float)ofGetMouseX(), y = (float)ofGetMouseY();
	bool mouse = ofGetMousePressed(0);

	//add object
	if(mouse && !isPress){
		isPress = true;
		tuio.addObject(x, y);
	}
	
	//update object
	if (isPress) tuio.updateObject(x, y);
	
	//remove object
	if (!mouse && isPress) {
		isPress = false;
		tuio.removeObject(x, y);
	}
}
tuio.end();

```