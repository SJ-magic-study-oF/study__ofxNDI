/************************************************************
■nariakiiwatani/ofxNDI
	https://github.com/nariakiiwatani/ofxNDI
	
	■Project setting
		Build Phases > Copy Files
		select "Destination" to Executables
		click +
		add libndi.4.dylib ... @ /Users/nobuhiro/Documents/source/openframeworks/of_v0.11.0_osx_release/addons/ofxNDI/libs/NDI/lib/osx/x64
			Destination: check	: Copy item if needed
			Added folders		: Create groups
			
			
		sj_note
			*.appでなく、exe本体のdirにdylibがcopyされるのがpoint.
			
	
	■α6000 setting
		HDMI解像度		= 1080p
		HDMI機器制御	= 切
		リモコン		= 切

■compare with C920
	[Device]
		NDI Device =	magewell : Pro Convert HDMI Plus
						https://magewell.dpsj.co.jp/pro-convert-family/pro-convert-hdmi-plus
		Cam = 			α 6000
		
	[Result]
		FrameRate		: 	NDIの方が安定。C920は結構揺れる
		DynamicRange	:	ミラーレス一眼の方が広い
		反応速度		: 	NDI(ミラーレス一眼)は、かなり速い
							webCamは、目に見えて遅れる
							
		ノイズ			:	NDIの方がノイズが大きく見える。
		CPU占有率		:	Camera側が1920x1080でしか送れないためNDIの方が不利。
							同じ解像度 同士の比較では、差異なし。
							
	[CPU占有率]
		web cam (1920x1080)		:	55%
		AS_GRABBER(1920x1080)	:	55%
		NDI Receiver(1920x1080)	:	55%
************************************************************/
#pragma once

/************************************************************
************************************************************/
// #define AS_GRABBER

/************************************************************
************************************************************/
#include "ofMain.h"

#ifdef AS_GRABBER
	#include "ofxNDIVideoGrabber.h"
#else
	#include "ofxNDIReceiver.h"
	#include "ofxNDIRecvStream.h"
#endif

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
#ifdef AS_GRABBER
	ofxNDIVideoGrabber grabber_;
#else
	ofxNDIReceiver receiver_;
	ofxNDIRecvVideoFrameSync video_;
#endif
	
	/********************
	ofImageを定義し、allocateしてgetPixels()を使い、decodeTo()に渡すと、何故かsegmentation faultでstopした。
	詳しいことは、わからなかったが、「使い方」と割り切ろう。
	
	ofImageで、allocせずに、
		video_.decodeTo(img.getPixels());
	と使うと、okだった。
	ofImage版の方が、処理も軽かった。
	draw前にimg.update()するのを忘れずに!
	********************/
	ofPixels pixels_;
	ofImage img;
	
	/********************
	********************/
	ofTrueTypeFont font;
	int now = 0;
	int t_LastCamUpdate = 0;
	float Cam_FrameRate = 0;
	float App_FrameRate = 0;
	
public:
	/****************************************
	****************************************/
	ofApp();
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
