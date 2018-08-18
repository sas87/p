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
	box[3] = 512;    //y幅
					 //512x512の箱を定義

	world = vector<vector<float>>(128, vector<float>(128, 0.0f));  //箱 
	col_w = vector<vector<bool>>(world.size(), vector<bool>(world[0].size(), false));

	vector<vector<float>> st = { {1,0,1,1 } };

	vector<vector<float>> rum = vector<vector<float>>(100, vector<float>(100, 0.0f));
	for (size_t i = 0; i < rum.size(); i++)
	{
		for (size_t j = 0; j < rum[0].size(); j++)
		{
			if (ofRandom(1.0f) > 0.99f)rum[i][j] = ofRandom(1.0f);
			
		}
	}

	vector<vector<bool>> rum_c = vector<vector<bool>>(64, vector<bool>(64, 0.0f));
	for (size_t i = 0; i < rum_c.size(); i++)
	{
		for (size_t j = 0; j < rum_c[0].size(); j++)
		{
			rum_c[i][j] = (ofRandom(1.0f) > 0.9f);
		}
	}
	
	addVecter<float>(world,rum);
	//addVecter<bool>(col_w, rum_c);
	ofSetFrameRate(60);

}

//--------------------------------------------------------------
void ofApp::update() {
	time++;
	//if (time % 10 == 0)
	{
		
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
		ofDrawRectangle(box[0] + box[2] + 12, box[1] + i * height, 2 * width, height);
	}

	for (size_t i = 0; i < (int)world.size(); i++)
	{
		int py = box[1] + i * box[3] / (int)world.size();                       //行

		for (size_t j = 0; j < (int)world[0].size(); j++)
		{
			int px = box[0] + j * box[2] / (int)world[i].size();               //列

			
			if (!col_w[i][j])
			{
				float p = 1 - world[i][j];
				ofSetColor(FlotoCol(world[i][j]).x, FlotoCol(world[i][j]).y, FlotoCol(world[i][j]).z);
				//ofSetColor(255 * p*8, 255 * p * 8, 255 * p * 8);
			}else ofSetColor(200, 200, 200);
			
			ofDrawRectangle(px, py, width, height);

			ofSetColor(255,255,255);
			//ofDrawBitmapString(ofToString((float)(world[i][j])*100)+" %", px, py +10);
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
	for (size_t i = 0 + 1; i < (int)pre_w.size() - 1; i++)
	{
		for (size_t j = 0 + 1; j < (int)pre_w[i].size() - 1; j++)
		{
			float p = 1.0f / 8.0f;
			

			int c=0;

			if (!col_w[i - 1][j - 1]) 
			{
				world[i - 1][j - 1] += 1.0f*pre_w[i][j] * p;
				c++; 
			}
			if (!col_w[i - 1][j])
			{
				world[i - 1][j]     += 1.0f*pre_w[i][j] * p;
				c++;
			}			
			if (!col_w[i - 1][j + 1])
			{world[i - 1][j + 1] += 1.0f*pre_w[i][j] * p;
				c++;
			}	
			if (!col_w[i][j - 1])
			{
				world[i][j - 1]     += 1.0f*pre_w[i][j] * p;
				c++;
			}			
			if (!col_w[i][j + 1])
			{
				world[i][j + 1]     += 1.0f*pre_w[i][j] * p;
				c++;
			}	
			if (!col_w[i + 1][j - 1])
			{
				world[i + 1][j - 1] += 1.0f*pre_w[i][j] * p;
				c++;
			}		
			if (!col_w[i + 1][j])
			{
				world[i + 1][j]     += 1.0f*pre_w[i][j] * p;
				c++;
			}			
			if (!col_w[i + 1][j + 1])
			{
				world[i + 1][j + 1] += 1.0f*pre_w[i][j] * p;
				c++;
			}

			world[i][j] -= pre_w[i][j] * p * c;
		}
	}/**/
}

template<typename T_0>
void ofApp::addVecter(vector<vector<T_0>> &vv0, vector<vector<T_0>> vv1, int px, int py)
{
	if (px < 0 || py < 0 || py + (int)vv1.size() > vv0.size() || px + (int)vv1.size() > vv0[0].size())return;

	for (size_t i = py; i < py + (int)vv1.size(); i++)
	{
		for (size_t j = px; j < px + (int)vv1[0].size(); j++)
		{
			vv0[i][j] = vv1[i - py][j - px];
		}
	}
}

template<typename T_1>
void ofApp::addVecter(vector<vector<T_1>> &vv0, vector<vector<T_1>> vv1)
{
	int py = ((int)vv0.size() - vv1.size()) / 2;
	int px = ((int)vv0.at(0).size() - vv1[0].size()) / 2;

	ofApp::addVecter(vv0, vv1, px, py);
}

ofVec3f ofApp::FlotoCol(float p)
{
	
	p *= 80.0f;
	p = 1.0f - p;
	if (p <= 1 && p >= 0)
	{/*
		int r = 128 + 127 * sin(2.0f*p*PI / 2.0f - PI / 2.0f);
		int g = 128 + 64 * sin(2.0f*p*PI - PI / 2.0f);
		int b = 128 + 64 * sin(2.0f*p*PI - PI / 4.0f);
		return ofVec3f(r, g, b);*/
		int r = p * 255;
		int g = p * 255;
		int b = p*255;
		return ofVec3f(r, g, b);
	}
	else return ofVec3f(0, 0, 0);
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

