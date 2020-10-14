/************************************************************
************************************************************/
#include "ofApp.h"

/************************************************************
************************************************************/
using namespace std;

/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp(){
	font.load("font/RictyDiminished-Regular.ttf", 15, true, true, true);
}
	
/******************************
******************************/
void ofApp::setup(){	
	/********************
	********************/
	ofSetWindowTitle("test NDI");
	
	ofSetWindowShape( WINDOW_WIDTH, WINDOW_HEIGHT );
	/*
	ofSetVerticalSync(false);
	ofSetFrameRate(0);
	/*/
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	//*/
	
	ofSetEscapeQuitsApp(false);
	
	/********************
	********************/
#ifdef AS_GRABBER	
	grabber_.setUseTexture(true);
	grabber_.setup();
	
#else
	NDIlib_initialize();
	
	auto findSource = [](const string &name_or_url) {
		auto sources = ofxNDI::listSources();
		
		// SJ
		for(int i = 0; i < sources.size(); i++){
			printf("%s, %s\n", sources[i].p_ndi_name.c_str(), sources[i].p_url_address.c_str());
		}
		fflush(stdout);
		
		if(name_or_url == "") {
			// SJ
			printf("name or url is blank\n");
			fflush(stdout);
			
			return make_pair(ofxNDI::Source(), false);
		}
		auto found = find_if(begin(sources), end(sources), [name_or_url](const ofxNDI::Source &s) {
			// SJ
			printf("name or url is : %s\n", name_or_url.c_str());
			fflush(stdout);
			
			return ofIsStringInString(s.p_ndi_name, name_or_url) || ofIsStringInString(s.p_url_address, name_or_url);
		});
		
		if(found == end(sources)) {
			ofLogWarning("ofxNDI") << "no NDI source found by string:" << name_or_url;
			return make_pair(ofxNDI::Source(), false);
		}
		
		return make_pair(*found, true);
	};
	
	/********************
	********************/
	string name_or_url = "";	// Specify name or address of expected NDI source. In case of blank or not found, receiver will grab default(which is found first) source.
	// string name_or_url = "169.254.11.144";	// 実験して取得した結果を入れてみた -> 動作OK.
	
	auto result = findSource(name_or_url);
	if(result.second ? receiver_.setup(result.first) : receiver_.setup()) {
		video_.setup(receiver_);
	}
	
#endif
	
	/********************
	********************/
	printf("Fin : setup\n");
	fflush(stdout);
}

/******************************
******************************/
void ofApp::update(){
	now = ofGetElapsedTimeMillis();
	
	float alpha = 0.03;
	
#ifdef AS_GRABBER
	grabber_.update();
	if(grabber_.isFrameNew()){
		float Current_Cam_FrameRate = 1000.0/(float)(now - t_LastCamUpdate);
		Cam_FrameRate = alpha * Current_Cam_FrameRate + (1 - alpha) * Cam_FrameRate;
		
		t_LastCamUpdate = now;
	}
	
#else	
	if(receiver_.isConnected()) {
		video_.update();
		if(video_.isFrameNew()) {
			/********************
			起動直後、ofxNDIFrame.cpp内の、VideoFrame::decode()にあるWarningが出るが、
			しばらくすると、"FourCC"が定義されて(どこかは不明のまま)、問題なく動作を始める。
			********************/
			// video_.decodeTo(pixels_);
			video_.decodeTo(img.getPixels());
			
			/********************
			********************/
			float Current_Cam_FrameRate = 1000.0/(float)(now - t_LastCamUpdate);
			Cam_FrameRate = alpha * Current_Cam_FrameRate + (1 - alpha) * Cam_FrameRate;
			
			t_LastCamUpdate = now;
		}
	}
#endif

	App_FrameRate = alpha * App_FrameRate + (1 - alpha) * ofGetFrameRate();
}

/******************************
******************************/
void ofApp::draw(){
	ofBackground(0);
	ofSetColor(255);
	
#ifdef AS_GRABBER
	grabber_.draw(0, 0, ofGetWidth(), ofGetHeight());
	
#else
	/*
	if(pixels_.isAllocated()) {
		ofImage(pixels_).draw(0, 0, ofGetWidth(), ofGetHeight());
	}
	*/
	if(img.isAllocated()){
		img.update();
		img.draw(0, 0, ofGetWidth(), ofGetHeight());
	}
#endif
	
	/********************
	********************/
	ofSetColor(0, 100, 255, 255);
	
	char buf[512];
	sprintf(buf, "(App, Cam) = (%5.1f, %5.1f)", App_FrameRate, Cam_FrameRate);
	font.drawString(buf, 10, 30);
}

/******************************
******************************/
void ofApp::keyPressed(int key){
	switch(key){
		case 'a':
#ifdef AS_GRABBER
			printf("(%.1f, %.1f\n)", grabber_.getWidth(), grabber_.getHeight());
#else
			// printf("imageType = %d: (%d, %d)\n", pixels_.getImageType(), pixels_.getWidth(), pixels_.getHeight());
			printf("imageType = %d: (%d, %d)\n", img.getImageType(), img.getWidth(), img.getHeight());
#endif
			fflush(stdout);
			break;
	}
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
