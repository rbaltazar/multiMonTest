#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{		
	ofSetFrameRate(60);

	ofBackground(0,0,0);

	//int winW=300;
	//for(int i=0; i<3; i++) {
	//	ofxFenster* win=ofxFensterManager::get()->createFenster(400+(i*winW), 0, winW, 300, OF_WINDOW);
	//	win->addListener(new boxWindow());
	//	win->setBackgroundColor(ofRandom(255), ofRandom(255), ofRandom(255));
	//}

	//setup of fensterListener does not get called automatically yet
	imgWin.setup();

	//IF the following code is uncommented, all the following windows should be created on the second display, if there is one available
	ofxDisplayList displays = ofxDisplayManager::get()->getDisplays();
	std::cout<<"NUM DISPLAYS: "<<displays.size()<<'\n';
	ofxDisplay* disp = displays[0];
	std::cout<<"DISPLAY 0 ID: "<<displays[0]->id<<'\n';
	std::cout<<"DISPLAY 1 ID: "<<displays[1]->id<<'\n';
	if(displays.size() > 1)
		disp = displays[1];
	ofxFensterManager::get()->setActiveDisplay(disp);

	//for(int i=0; i<3; i++) {
	//	ofxFenster* win=ofxFensterManager::get()->createFenster(1920+400+(i*winW), 300, winW, 300, OF_WINDOW);
	//	if(i==0) {
	//		ofAddListener(win->events.mouseMoved, this, &testApp::mouseMovedEvent);
	//	}
	//	win->addListener(&imgWin);
	//	win->setWindowTitle("image render "+ofToString(i+1));
	//}
	
	int minX = 0;
	int minY = 0;

	int totalWidth = 0;
	int totalHeight = 0;

	for(int i = 0; i < displays.size(); i++){
		int x = displays[i]->x;
		int y = displays[i]->y;

		minX = min(minX,x);
		minY = min(minY,y);

		totalWidth += displays[i]->width;
		totalHeight = max(displays[i]->height,totalHeight);

		//ofxFenster *win = ofxFensterManager::get()->createFenster(x,y,300,300,OF_WINDOW);
		//win->addListener(new sceneWindow());
		//win->setFullscreen(true);
	}
	ofImage icon;
	icon.loadImage("icon.png");
	ofxFensterManager::get()->setIcon(icon.getPixelsRef());

	std::cout<<"Big Scene Dims: Width=" << totalWidth << " Height="<< totalHeight <<'\n';
	
	scene.allocate(totalWidth,totalHeight,GL_RGBA32F_ARB);
	texture = new ofTexture();

	texture = &scene.getTextureReference();

	for(int i = 0; i < displays.size(); i++){
		int x = displays[i]->x;
		int y = displays[i]->y;

		ofxFenster *win = ofxFensterManager::get()->createFenster(x,y,300,300,OF_WINDOW);
		win->addListener(new sceneWindow(x-minX,y-minY,texture));
		win->setFullscreen(true);
	}

}


//--------------------------------------------------------------
void testApp::update()
{
	scene.begin();

	ofFill();
	ofSetColor(255,0,0);
	ofRect(0,0,1920,1200);

	ofSetColor(0,255,0);
	ofRect(1920,0,1920,1200);

	ofSetColor(0,0,255);
	ofRect(3840,0,1920,1200);

	scene.end();
}

//--------------------------------------------------------------
void testApp::draw()
{
	
	ofNoFill();
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofSetColor(255);
	ofCircle(mouseX, mouseY, 10); //mouseX and mouseY are currently not working reliably

	ofSetRectMode(OF_RECTMODE_CORNER);
	ofFill();
	ofSetColor(255);
	ofVec2f mp=mousePos;
	ofVec2f p;

	float dSquared=100*100;

	for(int x=0; x<ofGetWidth(); x+=40) {
		for(int y=0; y<ofGetHeight(); y+=40) {
			p.set(x, y);
			if(mp.distanceSquared(p)<dSquared) {
				ofRect(x+10, y+10, 20, 20);
			}
		}
	}

	ofSetColor(0);
	ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
	
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
	//cout << (0x0400) << endl;
	//cout << (101 | OF_KEY_MODIFIER) << " " << key << endl;
	if(key=='f')
		ofxFensterManager::get()->getPrimaryWindow()->toggleFullscreen();
	if(key==' ')
		ofxFensterManager::get()->createFenster(0, 0, 400, 300, OF_WINDOW)->addListener(&imgWin);
	if(key == 'c')
		cout << "CLIPBOARD DATA: " << ofxFensterManager::get()->getClipboard() << endl;
}

//this only works if testApp is extending ofxFensterListener and not ofBaseApp
void testApp::mouseMoved(int x, int y, ofxFenster* win)
{
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
	mousePos.set(x, y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
	cout << "PRESSED" << endl;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
	cout << "RELEASED" << endl;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{
	cout << "GOT SOME FILES: "<<endl;
	std::vector<string>::iterator it = dragInfo.files.begin();
	while(it != dragInfo.files.end()){
		cout << *it << endl;
		++it;
	}
}

void testApp::mouseMovedEvent(ofMouseEventArgs &args)
{
	//cout << "MOUSE WAS MOVED" << endl;
}
