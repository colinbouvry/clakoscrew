#pragma once

#include "ofMain.h"
#include "ofxOpenLase.h"
#include "ofxCinderTimeline.h"

class ofApp : public ofBaseApp{

	public:
	    //enum Type { suitelazer1  suitelazer2 dessins tete explosion grenade couteau pan};
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        ofxCinderTimeline::Timeline& timeline() { return *mTimeline; }
    private:
        void playAnim();
        void FinishGroup();
        ofxOpenLaseRenderer mOl;
        std::shared_ptr<ofxCinderTimeline::Timeline> mTimeline;

        struct Animation
        {
            ofxCinderTimeline::Anim<ofVec3f> mScaleAnim;
            ofxCinderTimeline::Anim<ofVec3f> mRotateAnim;
            ofxCinderTimeline::Anim<ofVec3f> mTranslateAnim;
            ofxCinderTimeline::Anim<int> mNumIldaAnim;
        };

        std::vector<Animation> mAnimation;
        std::vector<ofDirectory *>  mListFileIlda;

        int mNumIlda;

        int mNumGroup;
};
