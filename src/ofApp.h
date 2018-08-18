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
	int counter;
	bool start;
	bool isRunning;
	int base[4];
	int gene;

	vector<vector<bool>> world;
	vector<vector<bool>> pre_w;
	void geneChange();
	void addVecter(vector<vector<bool>> vv1, int px, int py);
	void addVecter(vector<vector<bool>> vv1);

	ofImage     img;
	bool videc;
	int pic;

};



