/************************************************************
参考URL
	■ofVideoGrabber
		https://openframeworks.cc/documentation/video/ofVideoGrabber/
	
	■ofVideoDevice
		https://openframeworks.cc/documentation/video/ofVideoDevice/
			vector formatsは、vector<ofVideoFormat> formats;
		
	■ofVideoFormat
		https://openframeworks.cc/documentation/video/ofVideoFormat/
	
	■ofVideoBaseTypes.h
		https://gitlab.doc.gold.ac.uk/jtasn001/pm_jtasn001_lab1234/blob/8dfcfea04c40c477c5fe1ffa643dd88c3e2a940b/libs/openFrameworks/video/ofVideoBaseTypes.h
		
		contents
			/// \brief Unique identifier for the device if it has one.
			std::string serialID;
		
			/// \brief A list of video device formats provided by the device.
			/// \sa ofVideoFormat
			std::vector<ofVideoFormat> formats;
	
	■Question on ofVideoDevice + identify webcams of same model
		https://forum.openframeworks.cc/t/question-on-ofvideodevice-identify-webcams-of-same-model/15191
		
	■UVC camera control on OF0.10
		https://forum.openframeworks.cc/t/uvc-camera-control-on-of0-10/30971
		
	■openFrameworksでWebカメラを自動的に接続する
		https://miso-engine.hatenablog.com/entry/2017/06/02/132805
		
	■List available webcam resolutions?
		https://forum.openframeworks.cc/t/list-available-webcam-resolutions/28420
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"

/************************************************************
************************************************************/
#define ERROR_MSG(); printf("Error in %s:%d\n", __FILE__, __LINE__);

/************************************************************
************************************************************/
class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	enum{
		WINDOW_WIDTH = 1280,
		WINDOW_HEIGHT = 720,
	};
	enum{
		CAM_WIDTH	= 1920,
		CAM_HEIGHT	= 1080,
	};
	
	
	/****************************************
	****************************************/
	/********************
	********************/
	int FrameRate = 30;
	int now = 0;
	ofTrueTypeFont font;

	/********************
	********************/
	ofVideoGrabber cam;
	int Cam_id;
	
	bool b_CamSearchFailed = false;
	
	int t_LastCamUpdate = 0;
	float Cam_FrameRate = 0;
	float App_FrameRate = 0;
	
	FILE* fp;
	
	ofFbo fbo;
	
	/****************************************
	****************************************/
	void setup_Camera();
	void update_fbo_by_Cam();
	void drawMessage_CamSearchFailed();

public:
	/****************************************
	****************************************/
	ofApp(int _Cam_id);
	~ofApp();
	
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
