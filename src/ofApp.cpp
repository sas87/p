#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
	//ofDisableAntiAliasing();

	start = false;
	counter = 0;
	gene = 0;
	videc = false;
	pic = 0;

	base[0] = 80;  //x座標
	base[1] = 80;  //y座標
	base[2] = 256;  //x幅
	base[3] = 256;  //y幅

	ofBackground(255, 255, 255);

	world = vector<vector<bool>>(128, vector<bool>(128, false));

	ofSetFrameRate(60);

}

//--------------------------------------------------------------
void ofApp::update() {
	counter++;
	if (counter > 1000)counter = 0;
	if (start && (world != pre_w))
	{
		//if (counter % 2 == 0) 
	    geneChange();
		gene++;
		/**/
		if ( pic < 140) 
		{
			img.grabScreen(0, 0, 2*base[0]+base[2], 2*base[1] + base[3]);
			img.save("002/"+ofToString(pic)+".png");
			pic++;
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofSetColor(200, 200, 200);
	ofDrawRectangle(base[0] - 5, base[1] - 5, base[2] + 10, base[3] + 10);
	ofSetColor(0, 0, 0);

	for (size_t i = 0; i < ; i++)
	{

	}

	for (size_t i = 0; i < (int)world.size(); i++)
	{
		int py = base[1] + i * base[3] / (int)world.size();                       //行

		for (size_t j = 0; j < (int)world[0].size(); j++)
		{
			int px = base[0] + j * base[2] / (int)world[i].size();               //列

			if (world[i][j])
			{
				ofSetColor(0, 0, 0);
			}
			else
			{
				ofSetColor(255, 255, 255);
			}
			ofSetColor(255* i / (int)world.size(), 255 * j / (int)world[i].size(), 128);                           //Debug
			ofDrawRectangle(px, py, base[2] / (int)world[i].size(), base[3] / (int)world[i].size());

			//ofSetColor(128, 128, 128);                                                                             //Debug
			//ofDrawBitmapString(ofToString(i) + "," + ofToString(j), px, py+10);                                    //Debug
		}
	}/**/

	ofSetColor(0, 0, 0);
	ofDrawBitmapString("g:"+ofToString(gene),10,15);

	//ofDrawBitmapString(ofToString(ofGetFrameRate()) + "fps", 10, 15);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'a')ofApp::setup();
	if (key == 'z')start = true;

	if (key == 'x') {
		videc = true;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

void ofApp::mouseClicked(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

void ofApp::geneChange()
{
	pre_w = world;
	for (size_t i = 0+1; i < (int)pre_w.size()-1; i++)
	{
		for (size_t j = 0+1; j < (int)pre_w[i].size()-1; j++)
		{
			int env = 0;
						
			if (pre_w[i - 1][j - 1]) env++;
			if (pre_w[i - 1][j]) env++;
			if (pre_w[i - 1][j + 1]) env++;
			if (pre_w[i][j - 1]) env++;
			if (pre_w[i][j + 1]) env++;
			if (pre_w[i + 1][j - 1]) env++;
			if (pre_w[i + 1][j]) env++;
			if (pre_w[i + 1][j + 1]) env++;
		
			if (pre_w[i][j])
			{
				world[i][j] = (env == 2 || env == 3) ? true : false;
			}
			else 
			{
				world[i][j] = (env == 3) ? true : false;
			}
			/*

			world[i][j] = (env >= 1) ? true : false;*/
		}
	}/**/
}

void ofApp::addVecter(vector<vector<bool>> vv1, int px, int py)
{
	if (px < 0 || py < 0 || py + (int)vv1.size() > world.size() || px + (int)vv1.size() > world[0].size())return;

	vector<vector<bool>> line;
	for (size_t i = py; i < py+(int)vv1.size(); i++)
	{
		for (size_t j = px; j < px + (int)vv1[0].size(); j++)
		{
			world[i][j] = vv1[i - py][j - px];
		}
	}
}

void ofApp::addVecter(vector<vector<bool>> vv1)
{
	int py = ((int)world.size() - vv1.size()) / 2;
	int px = ((int)world[0].size() - vv1[0].size()) / 2;

	ofApp::addVecter(vv1, px, py);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

