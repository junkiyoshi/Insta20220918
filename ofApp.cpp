#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(1.5);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	ofTranslate(0, ofGetWindowHeight() * 0.5);

	int span = 5;
	ofColor color;

	ofMesh line;
	line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
	
	for (int base_y = -150; base_y <= 150; base_y += 300) {

		for (int hue = 0; hue <= 256; hue += 16) {

			color.setHsb(hue, 255, 255);
			auto scale = 0.02;

			for (int start_x = 30; start_x < ofGetWindowWidth(); start_x += 120) {

				for (int x = start_x; x < start_x + 90; x += span) {

					auto y = start_x % 120 == 30 ?
						base_y + ofMap(sin((hue + x) * scale + ofGetFrameNum() * 0.05), -1, 1, -80, 80) :
						base_y + ofMap(cos((hue + x) * scale + ofGetFrameNum() * 0.05), -1, 1, -80, 80);
					line.addVertex(glm::vec3(x, y, 0));
					line.addColor(color);

					if (x > start_x) {

						line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 2);
					}
					else {

						ofSetColor(color);
						ofDrawCircle(line.getVertex(line.getNumVertices() - 1), 2);
					}
				}

				ofSetColor(color);
				ofDrawCircle(line.getVertex(line.getNumVertices() - 1), 2);
			}
		}
	}

	line.drawVertices();
	line.drawWireframe();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}