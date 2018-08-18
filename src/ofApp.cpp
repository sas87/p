#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
	//ofDisableAntiAliasing();

	isRunning = false;
	time = 0;
	gene = 0;
	ofBackground(200, 200, 200);
	//videc = false;
	//pic = 0;                          //画像保存

	box[0] = 50;     //x座標
	box[1] = 80;     //y座標
	box[2] = 512;    //x幅
	box[3] = 256;    //y幅
					 //512x512の箱を定義

	world = vector<vector<bool>>(128, vector<bool>(128, false));  //箱 

	
	ofSetFrameRate(60);

}

//--------------------------------------------------------------
void ofApp::update() {
	time++;
	if (time > 1000)time = 0;
	if (isRunning && (world != pre_w))
	{
	    geneChange();
		gene++;
		/*                                //画像保存
		if (videc && pic < 140) 
		{
			img.grabScreen(0, 0, 2*box[0]+box[2], 2*box[1] + box[3]);
			img.save("002/"+ofToString(pic)+".png");
			pic++;
		}
		*/
	}

}

//--------------------------------------------------------------

void ofApp::draw() {

	int width = box[2] / (int)world[0].size();
	int height = box[3] / (int)world.size();

	ofSetColor(200, 200, 200);
	ofNoFill();
	ofDrawRectangle(box[0], box[1], box[2], box[3]);
	ofSetColor(0, 0, 0);
	ofFill();

	for (size_t i = 0; i < (int)world.size(); i++)
	{
		float ic = 1.0f - i * 1.0f / (float)world.size();
		ofSetColor(FlotoCol(ic).x, FlotoCol(ic).y, FlotoCol(ic).z);
		ofDrawRectangle(box[0] + box[2] + 12, box[1] + i * height, 2*width, height);
	}

	for (size_t i = 0; i < (int)world.size(); i++)
	{
		int py = box[1] + i * box[3] / (int)world.size();                       //行

		for (size_t j = 0; j < (int)world[0].size(); j++)
		{
			int px = box[0] + j * box[2] / (int)world[i].size();               //列

			if (world[i][j])
			{
				ofSetColor(0, 0, 0);
			}
			else
			{
				ofSetColor(255, 255, 255);
			}
			ofSetColor(255* i / (int)world.size(), 255 * j / (int)world[i].size(), 128,128);                           //Debug
			ofDrawRectangle(px, py, width, height);
		}
	}

	ofSetColor(0, 0, 0);
	ofDrawBitmapString(
		(string)""
		+ ofToString(ofGetFrameRate()) + "fps\r\n"
		+ "box: " + ofToString(box[2]) + " x " + ofToString(box[3]) + "\r\n"
		+ "     " + ofToString(world[0].size()) + " x " + ofToString(world.size()) + "\r\n"
		+ "isRunning: " + ofToString(isRunning) + "\r\n"
		+ "g: " + ofToString(gene) + "\r\n"
		, box[0] + box[2] + 50, box[1] + 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'a')ofApp::setup();
	if (key == 'z')isRunning = !isRunning;

	if (key == 'x') {
		//videc = true;
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

ofVec3f ofApp::FlotoCol(float p)
{
	/*
	if (p<=(1.0f/6.0f))
	{

	}*/
	int r = 128 + 127 * sin(2.0f*p*PI / 2.0f - PI / 2.0f);
	int g = 128 + 64 * sin(2.0f*p*PI - PI / 2.0f);
	int b = 128 + 64 * sin(2.0f*p*PI - PI / 4.0f);
	return ofVec3f(r,g,b);
}

ofVec2f ofApp::toRelativeC(ofVec2f v)
{
	return ofVec2f(v.x - box[0] - (box[2] / 2), v.y - box[1] - (box[3] / 2));
}
void ofApp::toRelativeC(int* vx, int* vy)
{
	*vx = *vx - box[0] - (box[2] / 2);
	*vy = *vy - box[1] - (box[3] / 2);
}
ofVec2f ofApp::toAbsoluteC(ofVec2f &v)
{
	return ofVec2f(v.x + box[0] + (box[2] / 2), v.y + box[1] + (box[3] / 2));;
}
void ofApp::toAbsoluteC(int* vx, int* vy)
{
	*vx = *vx + box[0] + (box[2] / 2);
	*vy = *vy + box[1] + (box[3] / 2);
}
int ofApp::toRelativeCx(int vx)
{
	return vx - box[0] - (box[2] / 2);
}
int ofApp::toRelativeCy(int vy)
{
	return vy - box[1] - (box[3] / 2);;
}
int ofApp::toAbsoluteCx(int vx)
{
	return vx + box[0] + (box[2] / 2);
}
int ofApp::toAbsoluteCy(int vy)
{
	return vy + box[0] + (box[2] / 2);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

