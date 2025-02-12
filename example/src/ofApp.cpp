#include "ofApp.h"


//#define USE_LOAD_DIALOG

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    //----- Loading sound player begin -------.
#ifdef USE_LOAD_DIALOG
    ofFileDialogResult result = ofSystemLoadDialog();
    if (result.bSuccess) {
        player.load(result.getPath());
    }
#else
    
    
    player.load( ofToDataPath("../../../../../examples/sound/soundPlayerExample/bin/data/sounds/beat.wav",true),
                //set the following to true if you want to stream the audio data from the disk on demand instead of
                //reading the whole file into memory. Default is false
                false);
#endif
    
    ofxSoundUtils::printOutputSoundDevices();
    
    auto outDevices = ofxSoundUtils::getOutputSoundDevices();
    
    int outDeviceIndex = 0;
    
    cout << ofxSoundUtils::getSoundDeviceString(outDevices[outDeviceIndex], false, true) << endl;
    
    
    ofSoundStreamSettings soundSettings;
    soundSettings.numInputChannels = 0;
    soundSettings.numOutputChannels = 2;
    soundSettings.sampleRate = player.getSoundFile().getSampleRate();
    soundSettings.bufferSize = 256;
    soundSettings.numBuffers = 1;
    
    stream.setup(soundSettings);
    
    stream.setOutput(output);
    
    
    // ------- GUI setup begin -------
    gui.setup();
    gui.add(player.volume);
    gui.add(filter.parameters);
    

    wave.setup(0, 0, ofGetWidth(), ofGetHeight());
    
    
    player.connectTo(filter).connectTo(wave).connectTo(output);
//    player.connectTo(wave).connectTo(output);
    player.play();
    player.setLoop(true);
    
}
//--------------------------------------------------------------
void ofApp::exit(){
	stream.close();
}
//--------------------------------------------------------------
void ofApp::update(){
}
//--------------------------------------------------------------
void ofApp::draw(){
	

	ofSetColor(ofColor::white);
	wave.draw();

	
	ofSetColor(ofColor::yellow);
	player.drawDebug(20, gui.getShape().getMaxY() + 20);
	
	gui.draw();
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){}
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){}
