/************************************************************
■nariakiiwatani/ofxNDI
	https://github.com/nariakiiwatani/ofxNDI
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "ofxNDIReceiver.h"
#include "ofxNDIRecvStream.h"

/************************************************************
************************************************************/

/**************************************************
**************************************************/
class ofApp : public ofBaseApp{	
private:
	/****************************************
	****************************************/
	enum{
		WINDOW_WIDTH	= 1280,
		WINDOW_HEIGHT	= 720,
	};
	
	/****************************************
	****************************************/
	ofxNDIReceiver receiver_;
	ofxNDIRecvVideoFrameSync video_;
	
	/********************
	ofImageを定義し、allocateしてgetPixels()を使い、decodeTo()に渡すと、何故かsegmentation faultでstopした。
	詳しいことは、わからなかったが、「使い方」と割り切ろう。
	********************/
	ofPixels pixels_;
	
public:
	/****************************************
	****************************************/
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
};
