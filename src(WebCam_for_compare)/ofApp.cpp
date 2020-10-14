/************************************************************
************************************************************/
#include "ofApp.h"

/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp(int _Cam_id)
: Cam_id(_Cam_id)
{
	font.load("font/RictyDiminished-Regular.ttf", 15, true, true, true);
	
	fp = fopen("../../../data/Log.csv", "w");
}

/******************************
******************************/
ofApp::~ofApp(){
	fclose(fp);
	
	printf("Good-bye\n");
	fflush(stdout);
}

/******************************
******************************/
void ofApp::setup(){
	/********************
	********************/
	ofSetWindowTitle("WebCam");
	
	ofSetWindowShape( WINDOW_WIDTH, WINDOW_HEIGHT );
	ofSetVerticalSync(true);
	ofSetFrameRate(FrameRate);
	
	ofSetEscapeQuitsApp(false);
	
	/********************
	********************/
	setup_Camera();
}

/******************************
******************************/
void ofApp::setup_Camera()
{
	/********************
	********************/
	printf("> setup camera\n");
	fflush(stdout);
	
	/********************
	細かく情報出してもらう
	********************/
	ofSetLogLevel(OF_LOG_VERBOSE);
    cam.setVerbose(true);
	
	vector< ofVideoDevice > Devices = cam.listDevices();// 上 2行がないと、List表示されない.
	
	/********************
	********************/
	if(Cam_id == -1){
		ofExit();
		return;
	}else{
		if(Devices.size() <= Cam_id) { ERROR_MSG(); ofExit(); return; }
		
		cam.setDeviceID(Cam_id);
		printf("\n> cam set device id = %d\n", Cam_id);
		printf("> DeviceID     = %d\n", Devices[Cam_id].id);
		printf("> CamName      = %s\n", Devices[Cam_id].deviceName.c_str());
		printf("> HardwareName = %s\n", Devices[Cam_id].hardwareName.c_str());
		printf("> serialID     = %s\n", Devices[Cam_id].serialID.c_str());
		
		printf( "\n> Cam size asked  = (%d, %d)\n", int(CAM_WIDTH), int(CAM_HEIGHT) );
		/*
			https://openframeworks.cc/documentation/video/ofVideoGrabber/#show_setDesiredFrameRate
				Set's the desired frame rate of the grabber. This should be called before initGrabber(), which will try to initialize at the desired frame rate. 
				Not all frame rates will be supported, but this at least gives you some abilitity to try grab at different rates.
		*/
		cam.setDesiredFrameRate(30);
		cam.initGrabber(CAM_WIDTH, CAM_HEIGHT);
		printf( "> Cam size actual = (%d, %d)\n\n", int(cam.getWidth()), int(cam.getHeight()) );
		fflush(stdout);
		
		/* */
		// fbo.allocate(int(cam.getWidth()), int(cam.getHeight()), GL_RGBA);
		fbo.allocate(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA);
	}
}

/******************************
******************************/
void ofApp::update(){
	/********************
	********************/
	now = ofGetElapsedTimeMillis();
	
	/********************
	********************/
	float alpha = 0.03;
	
    cam.update();
    if(cam.isFrameNew()){
		update_fbo_by_Cam();
		
		float Current_Cam_FrameRate = 1000.0/(float)(now - t_LastCamUpdate);
		Cam_FrameRate = alpha * Current_Cam_FrameRate + (1 - alpha) * Cam_FrameRate;
		
		t_LastCamUpdate = now;
	}
	
	App_FrameRate = alpha * App_FrameRate + (1 - alpha) * ofGetFrameRate();
}

/******************************
******************************/
void ofApp::update_fbo_by_Cam(){
	fbo.begin();
		ofClear(0, 0, 0, 0);
		ofSetColor(255, 255, 255, 255);
		cam.draw(0, 0, fbo.getWidth(), fbo.getHeight());
	fbo.end();
}

/******************************
******************************/
void ofApp::draw(){
	/********************
	********************/
	ofBackground(0);
	ofSetColor(255, 255, 255, 255);
	
	fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
	
	/********************
	********************/
	ofSetColor(0, 100, 255, 255);
	
	char buf[512];
	sprintf(buf, "(App, Cam) = (%5.1f, %5.1f)", App_FrameRate, Cam_FrameRate);
	font.drawString(buf, 10, 30);
}

/******************************
******************************/
void ofApp::drawMessage_CamSearchFailed(){
	ofBackground(0);
	ofSetColor(255, 0, 0, 255);
	
	char buf[512];
	sprintf(buf, "USB Camera not Exsist");
	font.drawString(buf, ofGetWidth()/2 - font.stringWidth(buf)/2, ofGetHeight()/2);
}

/******************************
******************************/
void ofApp::keyPressed(int key){

}

/******************************
******************************/
void ofApp::keyReleased(int key){

}

/******************************
******************************/
void ofApp::mouseMoved(int x, int y ){

}

/******************************
******************************/
void ofApp::mouseDragged(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mousePressed(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseReleased(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseEntered(int x, int y){

}

/******************************
******************************/
void ofApp::mouseExited(int x, int y){

}

/******************************
******************************/
void ofApp::windowResized(int w, int h){

}

/******************************
******************************/
void ofApp::gotMessage(ofMessage msg){

}

/******************************
******************************/
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
