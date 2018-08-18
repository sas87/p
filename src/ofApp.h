#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseClicked(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

private:
	int time;
	bool isRunning;
	int box[4];

	int gene;

	vector<vector<float>> world;
	vector<vector<bool>> col_w;
	vector<vector<float>> pre_w;
	void geneChange();

	template<typename T_0>
	void addVecter(vector<vector<T_0>> &vv0, vector<vector<T_0>> vv1, int px, int py);
	template<typename T_1>
	void addVecter(vector<vector<T_1>> &vv0, vector<vector<T_1>> vv1);

	ofVec3f FlotoCol(float p);

	ofVec2f toRelativeC(ofVec2f v);
	void toRelativeC(int* vx, int* vy);
	ofVec2f toAbsoluteC(ofVec2f &v);
	void toAbsoluteC(int* vx, int* vy);

	int toRelativeCx(int vx);
	int toRelativeCy(int vy);
	int toAbsoluteCx(int vx);
	int toAbsoluteCy(int vy);

	/*
	ofImage  img;
	bool videc;
	int pic;*/


};


