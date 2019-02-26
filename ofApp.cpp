#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	int span = 144;
	bool flag = true;
	for (int y = span * 0.5; y < ofGetHeight(); y += span) {

		for (int x = span * 0.5; x < ofGetWidth(); x += span) {

			vector<glm::vec2> vertices;
			int len_base = 100;
			for (int param = 0; param < 100; param++) {

				auto location = glm::vec2(x, y) + this->make_point(len_base, param);
				auto noise_value = ofNoise(location.x * 0.003, location.y * 0.003, ofGetFrameNum() * 0.01);
				int noise_len = len_base;
				if (noise_value > 0.7) { noise_len = ofMap(noise_value, 0.7, 1, len_base, len_base + 44); }
				if (noise_value < 0.3) { noise_len = ofMap(noise_value, 0, 0.3, len_base - 44, len_base); }
				noise_len = (noise_len / 20) * 20;

				vertices.push_back(glm::vec2(x, y) + this->make_point(noise_len, param));
			}

			flag ? ofFill() : ofNoFill();
			flag = !flag;

			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);
		}
	}
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}